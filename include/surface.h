#pragma once
#include <raylib.h>
#include <functional>
#include <stdint.h>
#include "drawcomponent.h"
#include <algorithm>
#include <vector>
#include <cstdio>

typedef uint32_t u32;
struct anim_dp{
	Vector2 pos;
	Color col;
};


Color RGB(u32 r, u32 g, u32 b){
	r %= 255; g %= 255; b %= 255;
	return Color{(unsigned char)(r),(unsigned char)(g),(unsigned char)(b),255};
}

Color RGBA(u32 r, u32 g, u32 b, u32 a){
	r %= 255; g %= 255; b %= 255;
	return Color{(unsigned char)(r),(unsigned char)(g),(unsigned char)(b),(unsigned char)(a)};
}

typedef std::vector<anim_dp> AnimData;
class AnimState {
public:
    u32 w,h,x,y,sz;
    float clk = 0;
    AnimState(u32 w, u32 h,u32 x, u32 y, u32 sz){
        this->w = w;
        this->h = h;
        this->x = x;
        this->y = y;
        this->sz = sz;
    };
};

class Surface
{
private:
    std::vector<Color> pixel_data;

    u32 width,heigth;
    u32 pos_x,pos_y;
    u32 pixel_width = 8;

    
    
    bool is_animatig = false;
    bool begin_animation = false;
    bool should_draw = true;
    DrawComponent* dcomp;

    

public:
    
    Surface();
    Surface(u32,u32,u32,u32);
    ~Surface();
    std::function<void(Surface*)> paint; // x,y,w,h,sz

    std::function<void(Surface* sf, AnimState & tg)> anim_begin;
    std::function<void(Surface* sf)> anim_end;
    std::function<void(AnimState & tg, u32, u32, u32, u32, u32)> anim_paint;// x,y,w,h,sz


    std::function<void(Surface*, u32, u32)> on_mouse_left = [](Surface*, u32, u32){};
    std::function<void(Surface*, u32, u32)> on_mouse_right = [](Surface*, u32, u32){};
    std::function<void(Surface*, u32, u32)> on_mouse_wheel_pressed = [](Surface*, u32, u32){};
    std::function<void(Surface*, float)> on_mouse_wheel = [](Surface*, float){};

    void draw();
    void animate(AnimState&);

    void set_pos(u32,u32);
    void set_x(u32 x){this->pos_x = x;};
    void set_y(u32 y){this->pos_y = y;};
    
    void set_width(u32 w){this->width = w;};
    void set_heigth(u32 h){this->heigth = h;};
    void set_size(u32 w,u32 h){this->width = w; this->heigth = h;};

    void set_pixel_width(u32 pw){this->pixel_width=pw;};

    u32 get_x() {return this->pos_x;};
    u32 get_y() {return this->pos_y;};

    u32 get_w() {return this->width;};
    u32 get_h() {return this->heigth;};
    
    u32 get_pixel_width() {return this->pixel_width;};

    DrawComponent* get_dcomp(){return this->dcomp;};

    void reset_internal_clock();
    f64 get_internal_clock(){return dcomp->clk;};

    Color at(u32 x, u32 y){
        
        if(x < 0 || y < 0 || x >= width || y >= heigth) return PINK;
        return pixel_data[y * width + x];
            
    }
    
};

Surface::Surface(/* args */)
{
}

Surface::Surface(u32 x, u32 y, u32 w, u32 h)
{
    dcomp = new DrawComponent(pixel_data);

    this->width = w;
    this->heigth = h;
    this->pos_x = x;
    this->pos_y = y;
    this->pixel_width = 4;

    if(w*h > 1024){
        this->pixel_data.resize(w*h + 2);
    }else{
        this->pixel_data.resize(1024);
    }
    
    this->dcomp->init(this->pixel_width,this->get_x(), this->get_y(),this->width,this->heigth,this->pixel_data);
    this->paint = [](Surface* sf){
        float clk = sf->dcomp->clk;

        for(int y = 0; y < sf->get_h(); y++)
        {
            for(int x = 0; x < sf->get_w(); x++)
            {
                sf->dcomp->pixel(x,y,(x%2==y%2 ? BLUE : ORANGE)); 
            }
        }

        for(int y = 0; y < sf->heigth; ++y)
        {
            for(int x = 0; x < sf->width; ++x)
            {
        
                DrawRectangle(
                            sf->pos_x + sf->pixel_width * x ,
                            sf->pos_y + sf->pixel_width * y ,
                            sf->pixel_width,sf->pixel_width,
                            sf->pixel_data[y * sf->width + x]);
            }
        }
    };
}

Surface::~Surface()
{
}

void Surface::draw(){
    this->dcomp->clk += GetFrameTime();

    if(should_draw)
        this->paint(this);

    std::fill(pixel_data.begin(), pixel_data.end(), RGBA(0,0,0,0));
}


void Surface::animate(AnimState & tg){
    if(this->begin_animation){
        this->anim_begin(this, tg);

        std::swap(this->pos_x , tg.x);
        std::swap(this->pos_y , tg.y);
        std::swap(this->width , tg.w);
        std::swap(this->heigth , tg.h);
        std::swap(this->pixel_width , tg.sz);

        this->begin_animation = false;
        this->is_animatig = true;
        this->should_draw = false;
    }
    
    if(this->is_animatig){
        this->anim_paint(tg,this->pos_x,this->pos_y,this->width,this->heigth,this->pixel_width);

        if(tg.x == this->pos_x && tg.y == this->pos_y && tg.w == this->width && tg.h == this->heigth && tg.sz == this->pixel_width){
            this->is_animatig = false;
            this->should_draw = true;
            this->anim_end(this);
        }
    }
}

void Surface::reset_internal_clock(){
    this->dcomp->clk = 0;
}

void Surface::set_pos(u32 x, u32 y){
    this->pos_x = x;
    this->pos_y = y;
}

static char pressed_char;

char next_char()
{
    return pressed_char;
}

void update_char()
{
    pressed_char = (char)GetCharPressed();
}