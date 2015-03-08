#include "SystemConfig.h"

const char* const kxlol::SystemConfig::GetSystemFont()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
    return "Microsoft YaHei";
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    return "Droid Sans Fallback";
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    return "Heiti SC";
#endif

    //若您的目标系统不是以上的几种系统，请按照以上格式在下面添加您的目标系统和对应的默认字体名称

    //------------------------------------------------------------------------------------------
}
