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

#include <functional>
#include <thread>
#include <mutex>
#include <deque>
#include <vector>

class ClientConnection final {

public:
    ClientConnection();
    ~ClientConnection();

    void connentToServer(const char *ip, unsigned short port);
    void quit();

    bool isWaiting() const { return _isWaiting; }
    bool isConnectSuccess() const { return _isConnectSuccess; }
    void sendBuf(const char *buf, int len);
    bool peekBuf(std::vector<char> *buf);

private:
    ClientConnection(const ClientConnection &) = delete;
    ClientConnection(ClientConnection &&) = delete;
    ClientConnection &operator=(const ClientConnection &) = delete;
    ClientConnection &operator=(ClientConnection &&) = delete;

    SOCKET                          _socket             = INVALID_SOCKET;
    std::thread                     *_connectThread     = nullptr;
    volatile bool                   _isWaiting          = true;
    volatile bool                   _isConnectSuccess   = false;

    std::thread                     *_sendThread        = nullptr;
    std::mutex                      _sendMutex;
    std::deque<std::vector<char> >  _sendQueue;
    volatile bool                   _sendNeedQuit       = false;

    std::thread                     *_recvThread        = nullptr;
    std::mutex                      _recvMutex;
    std::deque<std::vector<char> >  _recvQueue;
    volatile bool                   _recvNeedQuit       = false;

    void _connectToServer(const char *ip, unsigned short port);
    void _recvThreadFunc();
    void _sendThreadFunc();
};

#endif
