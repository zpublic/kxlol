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

bool ClientConnection::sendBuf(const char *buf, int len) {
    char head[4];
    head[0] = (len >> 24) & 0xFF;
    head[1] = (len >> 16) & 0xFF;
    head[2] = (len >> 8) & 0xFF;
    head[3] = len & 0xFF;
    if (_sendBuf.freeSize() >= 4 + len) {
        if (_sendBuf.write(head, 4) == 4 && _sendBuf.write(buf, len) == len) {
            return true;
        }
    }
    return false;
}

bool ClientConnection::peekBuf(std::vector<char> *buf) {
    assert(buf != nullptr);
    char head[4];
    if (!_recvBuf.peek(head, 4, false)) {
        return false;
    }

    size_t len = (unsigned char)head[0];
    len <<= 8;
    len |= (unsigned char)head[1];
    len <<= 8;
    len |= (unsigned char)head[2];
    len <<= 8;
    len |= (unsigned char)head[3];
    assert(len <= INT_MAX);

    if (_recvBuf.size() >= (int)len + 4) {
        _recvBuf.skip(4);
        buf->resize(len);
        _recvBuf.peek(&(*buf)[0], (int)len, true);
        return true;
    }

    return false;
}

void ClientConnection::_connectToServer(const char *ip, unsigned short port) {
    struct sockaddr_in serverAddr = { 0 };
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = ::inet_addr(ip);
    serverAddr.sin_port = htons(port);

    int ret = ::connect(_socket, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr));
    if (ret == SOCKET_ERROR) {
        LOG_DEBUG("Cannot connect to %s:%hu\n", ip, port);
        _isWaiting = false;
        _isConnectSuccess = false;
        return;
    }
    LOG_DEBUG("connect to %s:%hu\n", ip, port);

    _isWaiting = false;
    _isConnectSuccess = true;

    _sendThread = new std::thread([this]() {
        while (!_sendNeedQuit) {
            int ret = _sendBuf.doSend(std::bind(&::send, _socket, std::placeholders::_1, std::placeholders::_2, 0));
            if (ret == SOCKET_ERROR) {
                break;
            }
        }
    });

    _recvThread = new std::thread([this]() {
        while (!_recvNeedQuit) {
            int ret = _recvBuf.doRecv(std::bind(&::recv, _socket, std::placeholders::_1, std::placeholders::_2, 0));
            if (ret == SOCKET_ERROR) {
                break;
            }
        }
    });
}
