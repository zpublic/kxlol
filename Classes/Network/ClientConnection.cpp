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
    _connectThread = new std::thread(std::bind(&ClientConnection::_connectToServer, this, ip, port));
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

bool ClientConnection::peekBuf(std::vector<char> *buf) {
    assert(buf != nullptr);
    _recvMutex.lock();
    if (_recvQueue.empty()) {
        _recvMutex.unlock();
        return false;
    }
    *buf = std::move(_recvQueue.front());
    _recvQueue.pop_front();
    _recvMutex.unlock();
    return true;
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
        size_t len = buf[0];
        len <<= 8;
        len |= buf[1];
        len <<= 8;
        len |= buf[2];
        len <<= 8;
        len |= buf[3];
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
    char buf[4];
    while (!_sendNeedQuit) {
        _sendMutex.lock();
        if (_sendQueue.empty()) {
            _sendMutex.unlock();
        }
        else {
            std::vector<char> packet(std::move(_sendQueue.front()));
            _sendQueue.pop_front();
            _sendMutex.unlock();

            size_t len = packet.size();
            assert(len <= INT_MAX);

            buf[0] = (len >> 24) & 0xFF;
            buf[1] = (len >> 16) & 0xFF;
            buf[2] = (len >> 8) & 0xFF;
            buf[3] = len & 0xFF;
            if (::send(_socket, buf, 4, 0) != 4) {
                LOG_DEBUG("Send error\n");
                break;
            }
            if (::send(_socket, &packet[0], len, 0) != len) {
                LOG_DEBUG("Send error\n");
                break;
            }
        }
    }
}
