#include "AequitasKeyMap.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

void AequitasKeyMap::LoadKeyMap()
{
    rapidjson::Document doc;
    auto file_path = FileUtils::getInstance()->fullPathForFilename("piano/piano.json");
    auto contentStr = FileUtils::getInstance()->getStringFromFile(file_path);
    doc.Parse<0>(contentStr.c_str());

    const rapidjson::Value& vol_control     = doc["vol_control"];
    const rapidjson::Value& group_vol       = doc["group_vol"];
    const rapidjson::Value& key_map         = doc["key_map"];

    auto it = vol_control.MemberonBegin();
    for(; it != vol_control.MemberonEnd(); ++it)
    {
        const char* name = it->name.GetString();
        const char* value = it->value.GetString();
        m_map_vol_control.insert(std::make_pair(atoi(name), std::string(value)));
    }

    it = group_vol.MemberonBegin();
    for(; it != group_vol.MemberonEnd(); ++it)
    {
        m_vec_group_vol.push_back(it->value.GetInt() / 100.0f);
    }

    it = key_map.MemberonBegin();
    for(; it != key_map.MemberonEnd(); ++it)
    {
        const char* name = it->name.GetString();
        const rapidjson::Value &val = it->value;
        m_map_key_map.insert(std::make_pair(
            atoi(name),
            make_tuple(
            std::string(val["wav"].GetString()),
            val["group"].GetInt())
            ));
    }
}

bool AequitasKeyMap::OnVolControl( int key )
{
    auto i = m_map_vol_control.find(key);
    if (i != m_map_vol_control.end())
    {
        ///> 调节分组的音量
        return true;
    }
    return false;
}

bool AequitasKeyMap::OnKey( int key )
{
    auto i = m_map_key_map.find(key);
    if (i != m_map_key_map.end())
    {
        auto s = std::get<0>(i->second);
        auto g = std::get<1>(i->second);

        char sPath[30] = {0};
        sprintf_s(sPath, "piano/%s.wav", s.c_str());
        SimpleAudioEngine::getInstance()->playEffect(sPath, false, 1.0f, 0.0f, GetVol(g));
        return true;
    }
    return false;
}

float AequitasKeyMap::GetVol( int group )
{
    if (group < 1 || group > (int)m_vec_group_vol.size())
    {
        return 1.0f;
    }
    return m_vec_group_vol[group - 1];
}
