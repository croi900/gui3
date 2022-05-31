#pragma once

#include "surface.h"
#include "raylib.h"
#include "button.h"
#include "pixeldraw.h"
#include "manager.h"
#include "perlin.h"
#include "input_box.h"
#include "digraph.h"
#include <string>

void init_graph_gen(){
    page["graph_gen"] = new Manager();

    auto digraph = new DiGraph(GetScreenWidth() * 0.05,GetScreenHeight() * 0.05,
                                GetScreenWidth() * 0.45,GetScreenHeight() * 0.9, 23);
    page["graph_gen"]->add_surface("digraph", digraph);

    auto input = new InputBox<u32>(GetScreenWidth() - 120*4 - GetScreenWidth()/16,
                                    GetScreenHeight() * 0.15,120,20);
    page["graph_gen"]->add_surface("tbx_nr_nodes", input);

    auto input_div = new InputBox<u32>(GetScreenWidth() - 120*4 - GetScreenWidth()/16,
                                    GetScreenHeight() * 0.15 + 120,120,20);
    page["graph_gen"]->add_surface("tbx_graph_divison", input_div);

    auto input_muchii = new InputBox<u32>(GetScreenWidth() - 120*4 - GetScreenWidth()/16,
                                    GetScreenHeight() * 0.15 + 240,120,20);
    page["graph_gen"]->add_surface("tbx_graph_edges", input_muchii);

    auto button = new Button(GetScreenWidth() - 120*4 - GetScreenWidth()/16,
                        GetScreenHeight() * 0.85,120,20,"GENERAZA",[digraph,input,input_div](){
        digraph->set_n(input->get());
        digraph->set_division(input_div->get());
        digraph->set_m(input_muchii->get());
		digraph->regenerate();
	});
	page["graph_gen"]->add_surface("btn_generate",button);

    page["graph_gen"]->page_draw = [](){

        DrawText("Nr noduri:",GetScreenWidth() - 120*4 - GetScreenWidth()/16,GetScreenHeight() * 0.11,32,BLACK);
        DrawText("Diviziunea grafului:",GetScreenWidth() - 120*4 - GetScreenWidth()/16,GetScreenHeight() * 0.11+120,32,BLACK);
        DrawText("Nr muchii:",GetScreenWidth() - 120*4 - GetScreenWidth()/16,GetScreenHeight() * 0.11+240,32,BLACK);

    };
  
}