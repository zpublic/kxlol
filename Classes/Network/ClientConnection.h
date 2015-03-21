#ifndef _CLIENT_CONNECTION_H_
#define _CLIENT_CONNECTION_H_
#if (defined _WIN32) || (defined WIN32)
#   define PLATFORM_IS_WINDOWS 1
#   include <winsock2.h>
#   include <mswsock.h>
#   include <windows.h>
#else
#   define PLATFORM_IS_WINDOWS 0
#   include <sys/socket.h>
#   include <netinet/in.h>
#   include <arpa/inet.h>
#   define INVALID_SOCKET (-1)
#   define SOCKET_ERROR (-1)
typedef int SOCKET;
#endif

#include <thread>
#include <vector>
#include "CircularIOBuffer.h"

class ClientConnection final {

public:
    ClientConnection();
    ~ClientConnection();

    void connentToServer(const char *ip, unsigned short port);
    void quit();

    bool isWaiting() const { return _isWaiting; }
    bool isConnectSuccess() const { return _isConnectSuccess; }
    bool sendBuf(const char *buf, int len);
    bool peekBuf(std::vector<char> *buf);

private:
    ClientConnection(const ClientConnection &);
    ClientConnection(ClientConnection &&);
    ClientConnection &operator=(const ClientConnection &);
    ClientConnection &operator=(ClientConnection &&);

    SOCKET                          _socket;
    std::thread                     *_connectThread;
    volatile bool                   _isWaiting;
    volatile bool                   _isConnectSuccess;

    std::thread                     *_sendThread;
    volatile bool                   _sendNeedQuit;
    SocketSendBuffer<1024>          _sendBuf;

    std::thread                     *_recvThread;
    volatile bool                   _recvNeedQuit;
    SocketRecvBuffer<1024>          _recvBuf;

    void _connectToServer(const char *ip, unsigned short port);
};

#endif
