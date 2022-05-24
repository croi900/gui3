#pragma once

#include <math.h>
#include <raylib.h>
#include <stdint.h>
#include <utility>
#include <cstdio>
#include "raylib.h"
#include "surface.h"
#include "drawcomponent.h"

typedef uint32_t u32;
typedef double f64;



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

    bool intersecting(float p0_x, float p0_y, float p1_x, float p1_y, 
    float p2_x, float p2_y, float p3_x, float p3_y, float *i_x, float *i_y)
    {
        float s1_x, s1_y, s2_x, s2_y;
        s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
        s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;

        float s, t;
        s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
        t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

        if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
        {
            // Collision detected
            if (i_x != NULL)
                *i_x = p0_x + (t * s1_x);
            if (i_y != NULL)
                *i_y = p0_y + (t * s1_y);
            return 1;
        }

        return 0; // No collision
    }

}