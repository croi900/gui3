#pragma once

#include "surface.h"
#include "raylib.h"
#include "button.h"
#include "pixeldraw.h"
#include "manager.h"
#include "perlin.h"

void init_menu(){
    page["menu"] = new Manager();
    auto button = new Button(GetScreenWidth()/2 - 60*4,300,120,20,"MERGI LA SCOALA",[](){
		
	});
	page["menu"]->add_surface("btn_start",button);

	button = new Button(GetScreenWidth()/2 - 60*4,300 + 2 * 20 * 3,120,20,"GENEREAZA ORAS NOU",[](){
		c_pg = "graph_gen";
	});
	page["menu"]->add_surface("btn_generate",button);

	button = new Button(GetScreenWidth()/2 - 60*4,300 + 4 * 20 * 3,120,20,"RAMAI CORIGENT",[](){
		exit(0);
	});
	page["menu"]->add_surface("btn_leave",button);
}