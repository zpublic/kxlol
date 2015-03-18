#ifndef _NETWORK_TEST_SCENE_H_
#define _NETWORK_TEST_SCENE_H_

#include "../Network/SocketManager.h"

USING_NS_CC;

class NetworkTestScene : public Scene {
public:
    virtual bool init() override;

    CREATE_FUNC(NetworkTestScene)
};

#endif
