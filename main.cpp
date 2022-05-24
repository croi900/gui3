#include <math.h>
#include "raylib.h"
#include "surface.h"
#include <vector>
#include <cstdio>
#include "pixeldraw.h"
#include "manager.h"
#include "button.h"
#include "perlin.h"
#include "pages/menu.h"
#include "pages/graph_gen.h"
//animation data point


double lerp(double t, double a, double b) { return a + t * (b - a); }


f64 offset_function(f64 ft, f64 f1, f64 s1, f64 spi, f64 se, f64 fpi, f64 t){
	return 10.0 * ft *(f1*sin(s1*t)-spi*sin(se*2.71*t)+fpi*sin(spi*3.14*t));
}

int main ()
{
	// set up the window
	InitWindow(1280, 800, "WINDOW");
	// page[0] = new Manager();


	init_menu();
	init_graph_gen();


	auto background = pdraw::init_background();
	while (!WindowShouldClose())
	{
		// drawing
		BeginDrawing();
		ClearBackground(BLACK);
		
		update_char();
		background->draw();

		if(c_pg == "menu")
			pdraw::draw_title("VIATA LUI ADELIN");

		page[c_pg]->manage_drawing();
		page[c_pg]->manage_mouse();
		
		EndDrawing();
	}

	// cleanup
	CloseWindow();
	return 0;
}


/*
AnimState tg(s.get_w(),s.get_h(),330, 330, s.get_pixel_width());
	auto lp = s.paint;
	s.reset_internal_clock();
	s.paint = [tg](Surface * sf){
		f64 clk = sf->get_internal_clock();
		for(int y = 0; y < sf->get_h(); y++)
        {
            for(int x = 0; x < sf->get_w(); x++)
            {
                
                sf->get_dcomp()->pixel(x,y,RGB(y*32+x,x*32+y,x+y));
                
            }
        }

        for(int y = 1; y <= sf->get_h(); ++y)
        {
            for(int x = 1; x <= sf->get_w(); ++x)
            {
				auto p = pdraw::cubic_bezier_offset(sf->get_x(),sf->get_y(),
                                    sf->get_x()+300 + 500*db::perlin(0.1*clk*(1)),
									sf->get_y()+  0 + 500*db::perlin(0.2*clk*(1)),
                                    sf->get_x()+300 - 500*db::perlin(0.3*clk*(1)),
									sf->get_y()+300 - 500*db::perlin(0.4*clk*(1)),
                                    GetMouseX(),GetMouseY(),clamp(0,1,clk + sin((1.0*(y+x) * sf->get_w() + x + 10)/(1.0*sf->get_h()*sf->get_w())*clk/2) )); //
                
				DrawRectangle(
					sf->get_pixel_width() * (x-1) + p.first , //+
					sf->get_pixel_width() * (y-1) + p.second, //+
					sf->get_pixel_width(),sf->get_pixel_width(),
					sf->at(x-1,y-1));
			
			}
        }

		if(clamp(0,1,clk + sin((1.0*(0) * sf->get_w() + 0 + 10)/(1.0*sf->get_h()*sf->get_w())*clk/2)) >= 1){
			sf->set_pos(GetMouseX(),GetMouseY());
		}
	};
*/