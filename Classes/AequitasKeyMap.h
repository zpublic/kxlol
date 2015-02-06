#ifndef __AEQUITAS_KEY_MAP_H__
#define __AEQUITAS_KEY_MAP_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include <vector>
#include <tuple>
#include <map>

typedef std::tuple<std::string, int>            tAequitasWav;

class AequitasKeyMap
{
public:
    void LoadKeyMap();
    bool OnVolControl(int key);
    bool OnKey(int key);
    float GetVol( int group );

private:
    std::vector<float>                    m_vec_group_vol;
    std::map<int, std::string>          m_map_vol_control;
    std::map<int, tAequitasWav>         m_map_key_map;
};

#endif // __AEQUITAS_KEY_MAP_H__
