#include "NetworkTestScene.h"
#include "cocos-ext.h"

bool NetworkTestScene::init() {
    if (!Scene::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Label *label = Label::createWithTTF("Waiting for connecting", "fonts/Marker Felt.ttf", 30);
    this->addChild(label);
    label->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height - 100));

    static SocketManager sm;
    sm.connectToServer("192.168.1.102", 8899, [=](SocketManager *thiz, bool result) {
        label->setString(result ? "connect succeeded" : "connect failed");
        if (!result) {
            return;
        }

        ui::Button *button = ui::Button::create();
        button->loadTextureNormal("CloseNormal.png", ui::Widget::TextureResType::LOCAL);
        button->setScale9Enabled(true);
        this->addChild(button);
        button->setPosition(Vec2(100, 100));
        button->addTouchEventListener([this](Ref *sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED) {
                std::vector<std::string> vec;
                vec.push_back("Hello");
                vec.push_back("MessagePack111");

                sm.sendAndRegisterRecvCallback<std::vector<std::string> >(100, vec, [](std::vector<std::string> &&rvec) {
                    std::for_each(rvec.begin(), rvec.end(), [](const std::string &s){ CCLOG("111---%s", s.c_str()); });
                });
            }
        });

        button = ui::Button::create();
        button->loadTextureNormal("CloseNormal.png", ui::Widget::TextureResType::LOCAL);
        button->setScale9Enabled(true);
        this->addChild(button);
        button->setPosition(Vec2(200, 100));
        button->addTouchEventListener([this](Ref *sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED) {
                std::vector<std::string> vec;
                vec.push_back("Hello");
                vec.push_back("MessagePack222");

                sm.sendAndRegisterRecvCallback(200, vec,
                    std::function<void(std::vector<std::string> &&)>([](std::vector<std::string> &&rvec) {
                    std::for_each(rvec.begin(), rvec.end(), [](const std::string &s){ CCLOG("222---%s", s.c_str()); });
                }));

            }
        });

        button = ui::Button::create();
        button->loadTextureNormal("CloseNormal.png", ui::Widget::TextureResType::LOCAL);
        button->setScale9Enabled(true);
        this->addChild(button);
        button->setPosition(Vec2(300, 100));
        button->addTouchEventListener([this](Ref *sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED) {
                std::vector<std::string> vec;
                vec.push_back("Hello");
                vec.push_back("MessagePack333");

                auto func3 = [](std::vector<std::string> &&rvec) {
                    std::for_each(rvec.begin(), rvec.end(), [](const std::string &s){ CCLOG("333---%s", s.c_str()); });
                };
                sm.sendAndRegisterRecvCallback<std::vector<std::string> >(300, vec, func3);
            }
        });

        button = ui::Button::create();
        button->loadTextureNormal("CloseNormal.png", ui::Widget::TextureResType::LOCAL);
        button->setScale9Enabled(true);
        this->addChild(button);
        button->setPosition(Vec2(400, 100));
        button->addTouchEventListener([this](Ref *sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED) {
                std::vector<std::string> vec;
                vec.push_back("Hello");
                vec.push_back("MessagePack444");

                std::function<void(std::vector<std::string> &&)> func4 = [](std::vector<std::string> &&rvec) {
                    std::for_each(rvec.begin(), rvec.end(), [](const std::string &s){ CCLOG("444---%s", s.c_str()); });
                };
                sm.sendAndRegisterRecvCallback(400, vec, func4);
            }
        });


    });


    return true;
}