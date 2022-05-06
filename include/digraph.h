#pragma once

#include "surface.h"
#include "raylib.h"
#include "button.h"
#include "pixeldraw.h"
#include "manager.h"
#include "perlin.h"

#include <vector>

#define DRAW_LATTICE 1

struct gpoint {
    u32 x, y;
}

class DiGraph : public Surface{
private:
    u32 n,m,a[200][200];

    std::vector<gpoint> lattice;

    void gen_point_ring(gpoint & p);
    void gen_lattice();

public:

    void draw();

    void set_label(const std::string & new_label);
    std::string & get_label();

    T get();

    DiGraph(){};
    DiGraph(u32 x, u32 y, u32 w, u32 h);
    ~DiGraph(){};
};

DiGraph::DiGraph(u32 x, u32 y, u32 w, u32 h) : Surface(x, y, w, h){
    this->paint = [this](Surface * sf){
        float clk = sf->get_dcomp()->clk;
        int mx = GetMouseX();
        int my = GetMouseY();
        
    };

    this->on_mouse_left = [this](Surface*, u32, u32){
    };

    
}

void DiGraph::gen_point_ring(gpoint & p) 
{
    
}