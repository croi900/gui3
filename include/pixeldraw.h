#pragma once

#include <math.h>
#include <raylib.h>
#include <stdint.h>
#include <utility>
#include <cstdio>
#include "raylib.h"
#include "surface.h"


typedef uint32_t u32;
typedef double f64;

template<typename T> constexpr
T min(T const& a, T const& b) {
  return a < b ? a : b;
}

template<typename T> constexpr
T max(T const& a, T const& b) {
  return a > b ? a : b;
}

template<typename T> constexpr
T clamp(T const& a, T const& b, T const& x) {
  return max(min(x,b),a);
}

namespace pdraw{
    f64 distance(f64 x1, f64 y1, f64 x2, f64 y2){
        return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
    }

    std::pair<f64,f64> cubic_bezier_offset(  
        u32 x1, u32 y1, u32 x2, u32 y2,
        u32 x3, u32 y3, u32 x4, u32 y4,
        f64 t)
    {
            f64 a = pow((1.0 - t), 3.0);
            f64 b = 3.0 * t * pow((1.0 - t), 2.0);
            f64 c = 3.0 * pow(t, 2.0) * (1.0 - t);
            f64 d = pow(t, 3.0);
    
            f64 x = a * x1 + b * x2 + c * x3 + d * x4;
            f64 y = a * y1 + b * y2 + c * y3 + d * y4;
            
            return {x,y};
    }

    Surface* init_background(){
        Surface* sf = new Surface(0,0,GetScreenWidth()/4,GetScreenHeight()/4);

        sf->paint = [](Surface* sf){
            
            sf->get_dcomp()->rect_filled(0,0,sf->get_w(),sf->get_h(),RGB(65, 65, 69));
            sf->get_dcomp()->octogon(0,1,sf->get_w(),sf->get_h()-1,0.03,RGB(186,161,196));
            sf->get_dcomp()->octogon(0,0,sf->get_w(),sf->get_h(),0.03,RGB(32,32,32));
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
        };

        return sf;
    }

    void draw_title(const char* title){
        auto tv = MeasureTextEx(GetFontDefault(),title, 120, 12);
        auto tw = tv.x;
        auto th = tv.y;
        DrawText(title,GetScreenWidth()/2 - tw/2,
                    GetScreenHeight()/16,
                    120,BLACK);
    }

}