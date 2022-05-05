#pragma once

#include <vector>
#include <algorithm>
#include "surface.h"

class SurfaceGroup{
private:
    std::vector<std::pair<u32,Surface*>> surfaces;
public:

    u32 add_surface(Surface* sf);
    u32 add_surface(u32 x,u32 y,u32 w,u32 h);
    void remove_surface(u32 idx);
    u32 get_surface(u32 x, u32 y);
    u32 get_surface(u32 idx);

    SurfaceGroup();
    ~SurfaceGroup();
};

SurfaceGroup::SurfaceGroup(){

}

SurfaceGroup::SurfaceGroup(){

}

u32 SurfaceGroup::add_surface(Surface* sf){
    u32 x = sf->get_x();

    auto lb = std::lower_bound(surfaces.begin(), surfaces.end(), x,
    [](const std::pair<u32,Surface*> & a, const u32 b){
        return a.first < b;
    });

    surfaces.insert(lb, {x,sf});

    return lb - surfaces.begin();

}