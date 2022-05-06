#pragma once

#include "surface.h"
#include "raylib.h"
#include "button.h"
#include "pixeldraw.h"
#include "manager.h"
#include "perlin.h"

#include <string.h>
#include <iostream>
#include <cstring>
#include <sstream>

template <class T>
class InputBox : public Surface{
private:
    bool selected = false;
    char text[1024];
    int pos = 0;
    float bsclk;
    
    void internal_think();
public:

    void draw();

    void set_label(const std::string & new_label);
    std::string & get_label();

    T get();

    InputBox(){};
    InputBox(u32 x, u32 y, u32 w, u32 h);
    ~InputBox(){};
};

template <class T>
InputBox<T>::InputBox(u32 x, u32 y, u32 w, u32 h) : Surface(x, y, w, h){
    this->paint = [this](Surface * sf){
        float clk = sf->get_dcomp()->clk;
        int mx = GetMouseX();
        int my = GetMouseY();
        char chr = (char)GetCharPressed();

        sf->get_dcomp()->octogon(0,0,sf->get_w(),sf->get_h(),0.11,RGB(32,32,32));

        if( this->selected )
        {
            sf->get_dcomp()->octogon(0,2,sf->get_w(),sf->get_h()-2,0.11,ORANGE);
        }else
        {
            sf->get_dcomp()->octogon(0,2,sf->get_w(),sf->get_h()-2,0.11,RGB(100,113,136));
        }
            
        sf->get_dcomp()->octogon(0,1,sf->get_w(),sf->get_h()-1,0.11,RGB(186,161,196));
        for(int i = 3; i <= (sf->get_h())/2; ++i){
            sf->get_dcomp()->octogon(1,i,sf->get_w()-1,sf->get_h()-i,0.11,RGB(54,54,128));
        }

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

        auto tv = MeasureTextEx(GetFontDefault(),this->text, sf->get_h() * sf->get_pixel_width() * 0.4, 2);
        auto tw = tv.x;
        auto th = tv.y;

        float vx = (sf->get_x() + (sf->get_w()*1. * sf->get_pixel_width()*1. - tw)/2);
        float vy = (sf->get_y() + (sf->get_h()*1. * sf->get_pixel_width()*1. - th)/2);
        Vector2 v = {vx, vy};
        DrawTextEx(GetFontDefault(),this->text,v,sf->get_h() * sf->get_pixel_width() * 0.4,2,BLACK);
        
    
        this->internal_think();
    };

    this->on_mouse_left = [this](Surface*, u32, u32){
        this->selected = true;
    };

    
}
template <class T>
void InputBox<T>::internal_think(){
    if(this->selected == true && IsKeyPressed(KEY_ENTER)){
        this->selected = false;
    }
    
    if(this->selected == true){
        if(chr >= 32)
        {
            this->text[pos++] = chr;
            this->text[pos] = 0;
        } 
        if(IsKeyDown(KEY_BACKSPACE) && clk > bsclk && pos > 0)
        {
            this->text[--pos] = 0;
            bsclk = clk + 0.06;
        }
    }

    try{
        std::cout<<this->get()<<std::endl;
    }catch(...){

    }
}
template <class T>
T InputBox<T>::get(){
    if(std::is_same<T,std::string>())
    {
        std::string val;
        std::istringstream ss(this->text);
        std::getline(ss,val);
        return val;
    }

    T val;
    std::istringstream ss(this->text);
    ss>>val;
    return val;
}
