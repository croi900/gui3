#pragma once 
#include "surface.h"
#include <string>
#include <functional> 

class Button : public Surface{
private:
    std::string label;
    std::function<void()> callback;
public:

    void draw();

    void set_label(const std::string & new_label);
    std::string & get_label();

    Button(){};
    Button(u32 x, u32 y, u32 w, u32 h, std::string text, std::function<void()> callback);
    ~Button(){};
};


Button::Button(u32 x, u32 y, u32 w, u32 h, std::string text, std::function<void()> callback) : Surface(x,y,w,h){
    //s = new Surface(x, y, w, h);
    this->label = text;
    this->callback = callback; 

    this->paint = [this](Surface* sf){
        float clk = sf->get_dcomp()->clk;
        int mx = GetMouseX();
        int my = GetMouseY();

        sf->get_dcomp()->octogon(0,0,sf->get_w(),sf->get_h(),0.22,RGB(32,32,32));

        if( mx <= sf->get_x() + sf->get_w() * sf->get_pixel_width() && 
            my <= sf->get_y() + sf->get_h() * sf->get_pixel_width() && 
            mx >= sf->get_x() && my >= sf->get_y() )
        {
            sf->get_dcomp()->octogon(0,2,sf->get_w(),sf->get_h()-2,0.22,ORANGE);
        }else
        {
            sf->get_dcomp()->octogon(0,2,sf->get_w(),sf->get_h()-2,0.22,RGB(100,113,136));
        }
            
        sf->get_dcomp()->octogon(0,1,sf->get_w(),sf->get_h()-1,0.22,RGB(186,161,196));
        for(int i = 3; i <= (sf->get_h())/2; ++i){
            sf->get_dcomp()->octogon(1,i,sf->get_w()-1,sf->get_h()-i,0.22,RGB(64,64,96));
        }
        // printf("%d\n",sf->get_h());
        for(int y = 0; y < sf->get_h(); ++y)
        {
            for(int x = 0; x < sf->get_w(); ++x)
            {
            
                DrawRectangle(
                    sf->get_x() + sf->get_pixel_width() * x,
                    sf->get_y() + sf->get_pixel_width() * y,
                    sf->get_pixel_width(),sf->get_pixel_width(),
                    sf->at(x,y));
            
            }
        }
        auto tv = MeasureTextEx(GetFontDefault(),label.c_str(), sf->get_h() * sf->get_pixel_width() * 0.4, 2);
        auto tw = tv.x;
        auto th = tv.y;

        float vx = (sf->get_x() + (sf->get_w()*1. * sf->get_pixel_width()*1. - tw)/2);
        float vy = (sf->get_y() + (sf->get_h()*1. * sf->get_pixel_width()*1. - th)/2);
        Vector2 v = {vx, vy};
        DrawTextEx(GetFontDefault(),label.c_str(),v,sf->get_h() * sf->get_pixel_width() * 0.4,2,BLACK);
    };

    this->on_mouse_left = [this](Surface*, u32, u32){
        this->callback();
    };
}

void Button::draw(){
    this->draw();
}

void Button::set_label(const std::string& new_label){
    this->label = new_label;
}

std::string& Button::get_label(){
    return this->label;
}