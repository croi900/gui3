#pragma once

#include "surface.h"
#include "raylib.h"
#include "button.h"
#include "pixeldraw.h"
#include "manager.h"
#include "perlin.h"

#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <queue>
#include <random>
#define DRAW_LATTICE 1
#define LATTICE_LIMIT 4

#define NODE_RANGE 8
#define EDGE_RANGE 8

static float r;

struct gpoint {
    u32 x, y;
    //RELATION OF EQUALITY BY DISTANCE
    bool operator==(gpoint other){
        return ((x - other.x)*(x - other.x) + (y - other.y)*(y - other.y)) < (2*(r/2-NODE_RANGE))*(2*(r/2-NODE_RANGE));
    }
};

class DiGraph : public Surface{
private:
    u32 GRAPH_DIVISION = 12;
    u32 n,m,a[200][200];

    std::vector<gpoint> lattice;

    std::vector<std::pair<gpoint,gpoint>> edges;
    std::vector<gpoint> graph;

    void gen_point_ring(gpoint & p, std::queue<gpoint>& q);
    void gen_lattice();

    float zoom;

    bool condition();

public:

    void draw();
    void regenerate();

    u32 get_n(){return n;};
    void set_n(u32 n){this->n = n;};

    u32 get_m(){return m;};
    void set_m(u32 m){this->m = m;};

    u32 get_divison(){return GRAPH_DIVISION;};
    void set_division(u32 div){this->GRAPH_DIVISION = div;};

    DiGraph(){};
    DiGraph(u32 x, u32 y, u32 w, u32 h);
    DiGraph(u32 x, u32 y, u32 w, u32 h, u32 n);
    ~DiGraph(){};
};
int cnt = 0;

bool DiGraph::condition()
{
    return rand()%100 > 66;
}
DiGraph::DiGraph(u32 x, u32 y, u32 w, u32 h) : Surface(x, y, w, h){
    this->n = 50;
    this->set_pixel_width(1);
    gpoint g = {(x + w/2),(y + h/2)};
    this->lattice.push_back(g);
    gen_lattice();
    this->paint = [this](Surface * sf){
        DrawRectangleLines(sf->get_x(),sf->get_y(),sf->get_w(),sf->get_h(),BLUE);
        float clk = sf->get_dcomp()->clk;
        int mx = GetMouseX();
        int my = GetMouseY();
        

        for(auto const& pt : this->graph)
        {

            //std::cout<<pt.x<<' '<<pt.y<<'\n';
            cnt++;
            DrawCircle(pt.x,pt.y,5,RGB(255,10 * (cnt/(this->n-1)),255));
        }
        for(auto const& i : this->edges){
            DrawLine(i.first.x,i.first.y,i.second.x,i.second.y,RGB(0,0,0));
        }
        cnt = 0;
    };

    this->on_mouse_wheel = [this](Surface*, float dt){
        this->zoom += dt;
    };

    
}

DiGraph::DiGraph(u32 x, u32 y, u32 w, u32 h,u32 n) : Surface(x, y, w, h){
    srand(time(NULL));
    this->n = n;
    this->set_pixel_width(1);
    gpoint g = {(x + w/2),(y + h/2)};
    this->lattice.push_back(g);
    gen_lattice();
    this->paint = [this](Surface * sf){
        DrawRectangleLines(sf->get_x(),sf->get_y(),sf->get_w(),sf->get_h(),BLUE);
        float clk = sf->get_dcomp()->clk;
        int mx = GetMouseX();
        int my = GetMouseY();
        

        for(auto const& pt : this->graph)
        {
            DrawCircle(pt.x,pt.y,NODE_RANGE,RGB(255,10 * (cnt/(this->n-1)),255));
        }
        for(auto const& i : this->edges){
            DrawLine(i.first.x,i.first.y,i.second.x,i.second.y,RGB(0,0,0));
        }
    };

    this->on_mouse_wheel = [this](Surface*, float dt){
        this->zoom += dt;
        std::cout<<this->zoom<<std::endl;
        
    };

    
}

void DiGraph::gen_point_ring(gpoint & p, std::queue<gpoint>& q) 
{
    float t = 0;
    

    for(float t = 0; t <= 2 * M_PI; t += 2*M_PI/GRAPH_DIVISION)
    {
        r = this->get_w() / (sqrt(this->n) * (2));
        float i = t;//+ (100.0 - rand()%200)/100.0;
        u32 off_x = cos(i) * r;
        u32 off_y = sin(i) * r;
        u32 mx = p.x + off_x;
        u32 my = p.y + off_y;

        if( mx <= this->get_x() + this->get_w()  && 
            my <= this->get_y() + this->get_h()  && 
            mx >= this->get_x() && my >= this->get_y()
            && condition() && graph.size() < n )
        {   
            gpoint np = {p.x + off_x, p.y + off_y};

            // if(((np.x - p.x)*(np.x - p.x)+(np.y - p.y)*(np.y - p.y)) < r*r)
            //     continue;
            // this->lattice.push_back({p.x + off_x, p.y + off_y});
            if(std::find(graph.begin(), graph.end(), np) == graph.end()){
                this->graph.push_back(np);
                this->edges.push_back({p,np});
                q.push(np);
            }
            
        }
    }
}

static constexpr u32 S(u32 d, u32 n){
    u32 r = 1;
    for(int i = 1; i <= d; ++i){
        r += (n-1)*i;
    }
    return r;
}

void DiGraph::gen_lattice() 
{
    std::queue<gpoint> queue;
    u32 lattice_limit = S(LATTICE_LIMIT, this->n);
    for(auto const& pt : this->lattice)
    {
        queue.push(pt);
        graph.push_back(pt);
    }
    gpoint cp;
    while(queue.size() > 0 ){
        cp = queue.front();
        queue.pop();
        this->gen_point_ring(cp,queue);
    }

}

void DiGraph::regenerate()
{
    this->graph.clear();
    this->edges.clear();
    this->gen_lattice();

    std::cout<<edges.size()<<std::endl;
}


