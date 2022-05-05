#pragma once

#include "surface.h"
#include "raylib.h"
#include "button.h"
#include "pixeldraw.h"
#include "manager.h"
#include "perlin.h"
#include "input_box.h"

void init_graph_gen(){
    page["graph_gen"] = new Manager();

    auto button = new Button(GetScreenWidth() - 120*4 - GetScreenWidth()/16,
                        GetScreenHeight() * 0.85,120,20,"GENERAZA",[](){
		
	});
	page["graph_gen"]->add_surface("btn_generate",button);

    auto input = new InputBox<u32>(GetScreenWidth() - 120*4 - GetScreenWidth()/16,
                                    GetScreenHeight() * 0.15,120,20);
    page["graph_gen"]->add_surface("tbx_nr_nodes", input);
}