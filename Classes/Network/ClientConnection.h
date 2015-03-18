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
    void sendBuf(std::vector<char> &&buf);
    bool peekBuf(std::vector<char> *buf);
    bool peekBuf(std::vector<char> *buf, const std::function<bool (const std::vector<char> &)> &checkFunc);

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
    std::mutex                      _sendMutex;
    std::deque<std::vector<char> >  _sendQueue;
    volatile bool                   _sendNeedQuit;

    std::thread                     *_recvThread;
    std::mutex                      _recvMutex;
    std::deque<std::vector<char> >  _recvQueue;
    volatile bool                   _recvNeedQuit;

    void _connectToServer(const char *ip, unsigned short port);
    void _recvThreadFunc();
    void _sendThreadFunc();
};

#endif
