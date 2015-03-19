#include "ClientConnection.h"
#include <utility>
#include <assert.h>
#include <stdio.h>
#if PLATFORM_IS_WINDOWS
#pragma comment(lib, "ws2_32.lib")
#endif

#define LOG_DEBUG printf

#if PLATFORM_IS_WINDOWS
struct WinSockLibLoader {
    WinSockLibLoader() {
        WSADATA data;
        WORD ver = MAKEWORD(2, 2);
        int ret = ::WSAStartup(ver, &data);
        if (ret != 0) {
            LOG_DEBUG("WSAStartup failed: last error %d", ::WSAGetLastError());
        }
    }
    ~WinSockLibLoader() {
        ::WSACleanup();
    }
};
#endif

ClientConnection::ClientConnection() {
#if PLATFORM_IS_WINDOWS
    static WinSockLibLoader loader;
#endif

    _socket             = INVALID_SOCKET;
    _connectThread      = nullptr;
    _isWaiting          = true;
    _isConnectSuccess   = false;
    _sendThread         = nullptr;
    _sendNeedQuit       = false;
    _recvThread         = nullptr;
    _recvNeedQuit       = false;
}

ClientConnection::~ClientConnection() {

}

void ClientConnection::connentToServer(const char *ip, unsigned short port) {
    if (_isConnectSuccess || _connectThread != nullptr) {
        return;
    }

    _socket = ::socket(AF_INET, SOCK_STREAM, 0);
    if (_socket == INVALID_SOCKET) {
        return;
    }

    _isWaiting = true;
    _connectThread = new std::thread(std::bind(&ClientConnection::_connectToServer, this, std::placeholders::_1, std::placeholders::_2), ip, port);
}

void ClientConnection::quit() {
    if (_socket != INVALID_SOCKET) {
#if PLATFORM_IS_WINDOWS
        ::closesocket(_socket);
#else
        ::shutdown(_socket, SHUT_RDWR);
#endif
        _socket = INVALID_SOCKET;
    }

    if (_connectThread != nullptr) {
        _connectThread->join();
        delete _connectThread;
        _connectThread = nullptr;
    }

    if (_sendThread != nullptr) {
        _sendNeedQuit = true;
        _sendThread->join();
        delete _sendThread;
        _sendThread = nullptr;
    }

    if (_recvThread != nullptr) {
        _recvNeedQuit = true;
        _recvThread->join();
        delete _recvThread;
        _recvThread = nullptr;
    }
    _isConnectSuccess = false;
}

void ClientConnection::sendBuf(const char *buf, int len) {
    _sendMutex.lock();
    _sendQueue.push_back(std::move(std::vector<char>(buf, buf + len)));
    _sendMutex.unlock();
}

void ClientConnection::sendBuf(std::vector<char> &&buf) {
    _sendMutex.lock();
    _sendQueue.push_back(buf);
    _sendMutex.unlock();
}

bool ClientConnection::peekBuf(std::vector<char> *buf) {
    assert(buf != nullptr);
    if (!_recvMutex.try_lock()) {
        return false;
    }
    if (_recvQueue.empty()) {
        _recvMutex.unlock();
        return false;
    }
    *buf = std::move(_recvQueue.front());
    _recvQueue.pop_front();
    _recvMutex.unlock();
    return true;
}

bool ClientConnection::peekBuf(std::vector<char> *buf, const std::function<bool (const std::vector<char> &)> &checkFunc) {
    assert(buf != nullptr);
    if (!_recvMutex.try_lock()) {
        return false;
    }
    if (_recvQueue.empty()) {
        _recvMutex.unlock();
        return false;
    }
    for (std::deque<std::vector<char> >::iterator it = _recvQueue.begin(); it != _recvQueue.end(); ++it) {
        if (checkFunc(*it)) {
            *buf = std::move(*it);
            _recvQueue.erase(it);
            _recvMutex.unlock();
            return true;
        }
    }
    _recvMutex.unlock();
    return false;
}

void ClientConnection::_connectToServer(const char *ip, unsigned short port) {
    struct sockaddr_in serverAddr = { 0 };
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = ::inet_addr(ip);
    serverAddr.sin_port = htons(port);

    int ret = ::connect(_socket, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr));
    if (ret == SOCKET_ERROR) {
        LOG_DEBUG("Connot connect to %s:%hu\n", ip, port);
        _isWaiting = false;
        _isConnectSuccess = false;
        return;
    }
    LOG_DEBUG("connect to %s:%hu\n", ip, port);

    _isWaiting = false;
    _isConnectSuccess = true;
    _sendThread = new std::thread(std::bind(&ClientConnection::_sendThreadFunc, this));
    _recvThread = new std::thread(std::bind(&ClientConnection::_recvThreadFunc, this));
}

void ClientConnection::_recvThreadFunc() {
    char buf[4];
    while (!_recvNeedQuit) {
        if (::recv(_socket, buf, 4, 0) == SOCKET_ERROR) {
            LOG_DEBUG("Recv error\n");
            break;
        }
        size_t len = (unsigned char)buf[0];
        len <<= 8;
        len |= (unsigned char)buf[1];
        len <<= 8;
        len |= (unsigned char)buf[2];
        len <<= 8;
        len |= (unsigned char)buf[3];
        assert(len <= INT_MAX);

        std::vector<char> cache;
        cache.resize(len);
        if (::recv(_socket, &cache[0], len, 0) == SOCKET_ERROR) {
            LOG_DEBUG("Recv error\n");
            break;
        }

        LOG_DEBUG("recv: %.*s\n", (int)len, &cache[0]);

        _recvMutex.lock();
        _recvQueue.push_back(std::move(cache));
        _recvMutex.unlock();
    }
}

void ClientConnection::_sendThreadFunc() {
    while (!_sendNeedQuit) {
        _sendMutex.lock();
        if (_sendQueue.empty()) {
            _sendMutex.unlock();
        }
        else {
            if (_sendQueue.size() == 1) {
                std::vector<char> packet(std::move(_sendQueue.front()));
                _sendQueue.pop_front();
                _sendMutex.unlock();
                
                size_t len = packet.size();
                assert(len <= INT_MAX);
                packet.resize(len + 4);
                memmove(&packet[4], &packet[0], len);
                packet[0] = (len >> 24) & 0xFF;
                packet[1] = (len >> 16) & 0xFF;
                packet[2] = (len >> 8) & 0xFF;
                packet[3] = len & 0xFF;
                len += 4;
                if (::send(_socket, &packet[0], len, 0) != len) {
                    LOG_DEBUG("Send error\n");
                    break;
                }
            } else {
                std::vector<char> packet(std::move(_sendQueue.front()));
                _sendQueue.pop_front();

                size_t len = packet.size();
                assert(len <= INT_MAX);
                packet.resize(len + 4);
                memmove(&packet[4], &packet[0], len);
                packet[0] = (len >> 24) & 0xFF;
                packet[1] = (len >> 16) & 0xFF;
                packet[2] = (len >>  8) & 0xFF;
                packet[3] = (len      ) & 0xFF;
                len += 4;

                while (!_sendQueue.empty()) {
                    std::vector<char> append(std::move(_sendQueue.front()));
                    _sendQueue.pop_front();

                    size_t len1 = append.size();
                    assert(len1 <= INT_MAX);
                    if (len + 4 + len1 > 1024) {
                        break;
                    }
                    packet.resize(len + len1 + 4);
                    packet[len + 0] = (len1 >> 24) & 0xFF;
                    packet[len + 1] = (len1 >> 16) & 0xFF;
                    packet[len + 2] = (len1 >>  8) & 0xFF;
                    packet[len + 3] = (len1      ) & 0xFF;
                    memcpy(&packet[len + 4], &append[0], len1);
                    len += (4 + len1);
                }

                _sendMutex.unlock();

                if (::send(_socket, &packet[0], len, 0) != len) {
                    LOG_DEBUG("Send error\n");
                    break;
                }
            }
        }
    }
}
