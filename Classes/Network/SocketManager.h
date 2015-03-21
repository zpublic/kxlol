#ifndef _SOCKET_MANAGER_H_
#define _SOCKET_MANAGER_H_

#include "ClientConnection.h"
#include "msgpack/msgpack.hpp"

#include "cocos2d.h"

#define KEY_SOCKET_CONNECTION_TEST "KEY_SOCKET_CONNECTION_TEST"
#define KEY_SOCKET_PEEK "KEY_SOCKET_PEEK"

//#define SOCKET_MANAGER_DEBUG

class SocketManager {
public:
    void connectToServer(const char *ip, unsigned short port, const std::function<void (SocketManager *thiz, bool result)> &callback) {
        _cc.connentToServer(ip, port);

        cocos2d::Scheduler *scheduler = cocos2d::Director::getInstance()->getScheduler();
        scheduler->schedule([this, scheduler, callback](float) {
            if (_cc.isWaiting()) {
                return;
            }
            scheduler->unschedule(KEY_SOCKET_CONNECTION_TEST, this);
            if (!_cc.isConnectSuccess()) {
                callback(this, false);
            }
            callback(this, true);
            scheduler->schedule([this](float) {
                std::vector<char> buf;
                if (!_cc.peekBuf(&buf) || buf.size() < 4) {
                    return;
                }
                int protocal = SocketManager::readProtocal(&buf[0]);
                _packets.insert(std::make_pair(protocal, std::move(buf)));
            }, this, 0.0F, CC_REPEAT_FOREVER, 0.0F, false, KEY_SOCKET_PEEK);
        }, this, 0.0F, CC_REPEAT_FOREVER, 0.0F, false, KEY_SOCKET_CONNECTION_TEST);
    }

    template <class _T> void send(int protocal, const _T &data) {
        msgpack::sbuffer sbuf;
        msgpack::pack(sbuf, data);

        std::vector<char> buf(4 + sbuf.size());
        writeProtocal(&buf[0], protocal);
        _cc.sendBuf(std::move(buf));
    }

    template <class _RECV, class _SEND, class _FUNC>
    void sendAndRegisterRecvCallback(int protocal, const _SEND &data, _FUNC &&callback) {
        msgpack::sbuffer sbuf;
        msgpack::pack(sbuf, data);

        std::vector<char> buf(4 + sbuf.size());
        writeProtocal(&buf[0], protocal);
        memcpy(&buf[4], sbuf.data(), sbuf.size());
        _cc.sendBuf(&buf[0], buf.size());

        _Helper *helper = _Helper::create([this, protocal, callback](_Helper *thiz) {
            std::unordered_map<int, std::vector<char> >::iterator it = _packets.find(protocal);
            if (it != _packets.end()) {
                std::vector<char> buf(std::move(it->second));
                _packets.erase(it);

                thiz->shutdown();
                thiz->autorelease();
#ifdef SOCKET_MANAGER_DEBUG
                --_helperCnt;
                CCLOG("%d _helperCnt = %u", __LINE__, _helperCnt);
#endif
                msgpack::unpacked msg;
                msgpack::unpack(&msg, &buf[4], buf.size() - 4);
                msgpack::object obj = msg.get();

                _RECV data;
                obj.convert(&data);
                callback(std::move(data));
            }
        });
        helper->startup();
#ifdef SOCKET_MANAGER_DEBUG
        ++_helperCnt;
        CCLOG("%d _helperCnt = %u", __LINE__, _helperCnt);
#endif
    }

    template <class _RECV, class _SEND>
    void sendAndRegisterRecvCallback(int protocal, const _SEND &data, const std::function<void (_RECV &&)> &callback) {
        sendAndRegisterRecvCallback<_RECV, _SEND, const std::function<void (_RECV &&)> &>(protocal, data, callback);
    }

private:
    ClientConnection _cc;
    std::unordered_map<int, std::vector<char> > _packets;

    static void writeProtocal(char *buf, int protocal) {
        buf[0] = (protocal >> 24) & 0xFF;
        buf[1] = (protocal >> 16) & 0xFF;
        buf[2] = (protocal >>  8) & 0xFF;
        buf[3] = (protocal      ) & 0xFF;
    }

    static int readProtocal(const char *buf) {
        int protocal = (unsigned char)buf[0];
        protocal <<= 8;
        protocal |= (unsigned char)buf[1];
        protocal <<= 8;
        protocal |= (unsigned char)buf[2];
        protocal <<= 8;
        protocal |= (unsigned char)buf[3];
        return protocal;
    }

#ifdef SOCKET_MANAGER_DEBUG
    unsigned _helperCnt = 0;
#endif

    class _Helper : public cocos2d::Ref {
    public:
        static _Helper *create(const std::function<void (_Helper *thiz)> &callback) {
            _Helper *ret = new (std::nothrow) _Helper();
            ret->_callback = callback;
            return ret;
        }

        void startup() {
            cocos2d::Director::getInstance()->getScheduler()->schedule(
                (cocos2d::SEL_SCHEDULE)&_Helper::update, this, 0.0F, CC_REPEAT_FOREVER, 0.0F, false);
        }

        void shutdown() {
            cocos2d::Director::getInstance()->getScheduler()->unschedule((cocos2d::SEL_SCHEDULE)&_Helper::update, this);
        }

        void update(float) {
            _callback(this);
        }

    private:
        std::function<void (_Helper *)> _callback;
    };
};

#endif
