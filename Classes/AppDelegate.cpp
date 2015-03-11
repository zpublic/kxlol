#include "AppDelegate.h"
#include "WelcomeScene.h"
#include "Network/ClientConnection.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("kxlol");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    director->setDepthTest(true);

    // create a scene. it's an autorelease object
    auto scene = WelcomeScene::createScene();

    // run
    director->runWithScene(scene);

    static ClientConnection cs;
    cs.connentToServer("192.168.199.140", 8899);
    Scheduler *scheduler = director->getScheduler();
    scheduler->schedule([scheduler](float) {
        if (cs.isWaiting()) {
            return;
        }
        if (cs.isConnectSuccess()) {
            CCLOG("Connect Success");
            scheduler->schedule([](float) {
                const char *str = "Hello World!";
                cs.sendBuf(str, strlen(str));
                CCLOG("send: %s", str);
            }, &cs, 1.0F, CC_REPEAT_FOREVER, 0.0F, false, "NETWORK_SEND");

            scheduler->schedule([](float) {
                std::vector<char> buf;
                if (cs.peekBuf(&buf)) {
                    CCLOG("recv: %.*s", (int)buf.size(), &buf[0]);
                }
            }, &cs, 0.0F, CC_REPEAT_FOREVER, 0.0F, false, "NETWORK_RECV");
        }
        scheduler->unschedule("CONNECTION_TEST", &cs);
    }, &cs, 0.0F, CC_REPEAT_FOREVER, 0.0F, false, "CONNECTION_TEST");

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
