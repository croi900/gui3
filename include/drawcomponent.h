#pragma once
#include <math.h>
#include <raylib.h>
#include <stdint.h>
#include <utility>
#include <vector>
#include <cstdio>

typedef uint32_t u32;
typedef double f64;

template<typename T> constexpr
T const& min(T const& a, T const& b) {
  return a < b ? a : b;
}
template<typename T> constexpr
T const& max(T const& a, T const& b) {
  return a > b ? a : b;
}
template<typename T> constexpr
T const& clamp(T const& a, T const& b,T const& x) {
  return max(a,min(b,x));
}

class DrawComponent{
public:

    std::vector<Color> &pixel_data;

    u32 psz;
    u32 px;
    u32 py;
    u32 sw;
    u32 sh;

    f64 clk = 0;

    DrawComponent(u32  p, u32  x, u32  y, u32  w, u32  h, std::vector<Color> & data) 
    : psz(p) , px(x) , py(y) , sw(w) , sh(h) , pixel_data(data){};

    DrawComponent(std::vector<Color> & data):pixel_data(data){};

    void init(u32  p, u32  x, u32  y, u32  w, u32  h, std::vector<Color> & data){
        psz = p;
        px = x;
        py = y;
        sw = w;
        sh = h;
        pixel_data = data;
    }

    void pixel(u32 x, u32 y, Color c){
        if(x < 0 || y < 0 || x >= sw || y >= sh) return;
        pixel_data[y * sw + x] = c;
    }

    void rect_filled(u32 left, u32 top, u32 right, u32 bottom, Color col){
      for(int x = left; x <= right; ++x){
        for(int y = top; y <= bottom; ++y){
          pixel(x,y,col);
        }
      }
    }

    void rect(u32 left, u32 top, u32 right, u32 bottom, Color col){
      for(int x = left; x <= right; ++x){
        pixel(x,top,col);
        pixel(x,bottom,col);
      }

      for(int y = top; y <= bottom; ++y){
        pixel(left,y,col);
        pixel(right,y,col);
      }
    }

    void line(int x0, int y0, int x1, int y1, Color col) {
 
      int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
      int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
      int err = (dx>dy ? dx : -dy)/2, e2;
    
      for(;;){
        pixel(x0,y0,col);
        if (x0==x1 && y0==y1) break;
        e2 = err;
        if (e2 >-dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
      }
    }

    void octogon(u32 x, u32 y, u32 w, u32 h, double p, Color color) {
      // line(p1 * h, y , p2 * h, y,color);
      // line(p1 * h, h - 1, p2 * h, h - 1,color);

      // line(x, p1 * h, x , p2 * h, color);
      // line(w - 1, p1 * h, w - 1 , p2 * h,color);
      
      // line(p1 * h,y,x,p1 * h,color);
      // line(p2 * h,y, w - 1, p1 * h ,color);
      // line(p1 * h, h - 1,x, h*p2,color);
      // line(w - 1 , p2 * h,p2 * h, h - 1,color);
      w -= 1;
      h -= 1;
      u32 off = p * h;
      u32 x1 = x + off;
      u32 y1 = y + off;
      u32 x2 = w - off;
      u32 y2 = h - off;
      
      

      line(x1,y,x2,y,color);
      line(x2,y,w,y1,color);
      line(w,y1,w,y2,color);
      line(w,y2,x2,h,color);
      line(x2,h,x1,h,color);
      line(x1,h,x,y2,color);
      line(x,y2,x,y1,color);
      line(x,y1,x1,y,color);
    }


};

