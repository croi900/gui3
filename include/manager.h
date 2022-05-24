#pragma once

#include <unordered_map>
#include <algorithm>
#include <functional>
#include <string>
#include "surface.h"
#include "raylib.h"

class Manager
{
private:
    std::unordered_map<std::string,Surface*> surfaces;
public:
    Manager(/* args */);
    ~Manager();

    void add_surface(const std::string & name, u32 x, u32 y, u32 w, u32 h);
    void add_surface(const std::string & name, Surface * sf);
    void rem_surface(std::string const& idx);
    void rem_surface(Surface * sf);

    std::function<void()> page_draw = [](){};

    void manage_mouse();
    void manage_drawing();

    u32 get_size();

    Surface* operator[](const std::string & name) { return surfaces[name]; }
};

Manager::Manager(/* args */)
{

}

Manager::~Manager()
{

}

void Manager::add_surface(const std::string & name, u32 x, u32 y, u32 w, u32 h)
{
    Surface* ptr = new Surface(x,y,w,h);
    this->surfaces.insert({name,ptr});
}

void Manager::add_surface(const std::string & name, Surface * sf)
{
    this->surfaces.insert({name,sf});
}

void Manager::rem_surface(const std::string & name)
{
    this->surfaces.erase(name);
}

void Manager::rem_surface(Surface * sf)
{
    for(const auto & pair : this->surfaces)
    {
        auto needle = pair.second;
        if( needle == sf){
            surfaces.erase(pair.first);
            return;
        }
    }
}

void Manager::manage_mouse()
{
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        
        u32 mx = GetMouseX();
        u32 my = GetMouseY();
        DrawRectangle(mx-5,my-5,10,10,GREEN);
        for(const auto & pair : this->surfaces)
        {
            auto sf = pair.second;
            if( mx <= sf->get_x() + sf->get_w() * sf->get_pixel_width() && 
                my <= sf->get_y() + sf->get_h() * sf->get_pixel_width() && 
                mx >= sf->get_x() && my >= sf->get_y() )
            {
                sf->on_mouse_left(sf,mx,my);
            }
        }
    }

    if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
        u32 mx = GetMouseX();
        u32 my = GetMouseY();
        for(const auto & pair : this->surfaces)
        {
            auto sf = pair.second;
            if( mx <= sf->get_x() + sf->get_w() && 
                my <= sf->get_y() + sf->get_h() && 
                mx >= sf->get_x() && my >= sf->get_y() )
            {
                sf->on_mouse_right(sf,mx,my);
            }
        }
    }

    if(IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)){
        u32 mx = GetMouseX();
        u32 my = GetMouseY();
        for(const auto & pair : this->surfaces)
        {
            auto sf = pair.second;
            if( mx <= sf->get_x() + sf->get_w() && 
                my <= sf->get_y() + sf->get_h() && 
                mx >= sf->get_x() && my >= sf->get_y() )
            {
                sf->on_mouse_wheel_pressed(sf,mx,my);
            }
        }
    }

    if(GetMouseWheelMove() != 0){
        u32 mx = GetMouseX();
        u32 my = GetMouseY();
        for(const auto & pair : this->surfaces)
        {
            auto sf = pair.second;
            if( mx <= sf->get_x() + sf->get_w() && 
                my <= sf->get_y() + sf->get_h() && 
                mx >= sf->get_x() && my >= sf->get_y() )
            {
                sf->on_mouse_wheel(sf,GetMouseWheelMove());
            }
        }
    }
    
}

void Manager::manage_drawing()
{
    for(const auto & pair : this->surfaces)
    {
        auto sf = pair.second;
        sf->draw();
    }

    this->page_draw();
}

u32 Manager::get_size()
{
    return this->surfaces.size();
}


std::string c_pg = "menu";// current page
std::unordered_map<std::string,Manager*> page;
