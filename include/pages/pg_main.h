#pragma once

#include <iostream>

#include "surface.h"
#include "raylib.h"
#include "button.h"
#include "pixeldraw.h"
#include "manager.h"
#include "perlin.h"

struct point{
	double x, y;
};

void init_menu(){
	page["menu"] = new Manager();
    auto heart = new Surface(0,0,GetScreenWidth()/4,GetScreenHeight()/4);
	heart->set_pixel_width(4);

	page["menu"]->add_surface("heart",heart);
}

double eq_heart(double phi){
	return ((std::sin(phi)*std::sqrt(std::abs(std::cos(phi))))/(std::sin(phi) + 7./5.0)) - 2 * std::sin(phi) + 2;
}

double get_y_by(double i, double clk, double t)
{
	double phi = (3.14159)*(i/(GetScreenHeight()/4. * clk * t));
	phi += 3.14159/2;

	point p ;
	point p2 ;
	if(((int)(t*10))%2 == 1){
		p = {GetScreenWidth()/4/2 + std::cos(phi) * clk * t * eq_heart(phi),
			GetScreenHeight()/4/2 + std::sin(phi) * clk * -t * eq_heart(phi) };
	}else{
		p = {GetScreenWidth()/4/2 + std::cos(phi) * clk * t * eq_heart(phi),
			GetScreenHeight()/4/2 + std::sin(phi) * clk * t * eq_heart(phi)};
	}

	return p.y;
}

point draw_heart(Surface* sf, point sprout, double t)
{
	point end;
	for(int i = GetScreenHeight()/4 * t; i >= 0 ; i--){
		double phi = (3.14159)*(i/(GetScreenHeight()/4. * t));
		phi += 3.14159/2;

		point p ;
		point p2 ;
		
		p = {cos(phi)  * t * eq_heart(phi),
			 sin(phi)  * t * eq_heart(phi)};
		p2 = {cos(phi) *-t * eq_heart(phi),
			  sin(phi) * t * eq_heart(phi)};
		
		auto offy = sin(3.14159/2  + (PI)*(1)) *t*
					eq_heart(3.14159/2 + (PI)*(1));
		sf->get_dcomp()->pixel(sprout.x - p.x,sprout.y - p.y - 4*t,RED);
		sf->get_dcomp()->pixel(sprout.x - p2.x,sprout.y - p2.y - 4*t,RED);
		//sf->get_dcomp()->pixel(GetScreenWidth()/4/2, offy + GetScreenWidth()/4/2,ORANGE);//
		end = {sprout.x - p.x,sprout.y - p.y - 4*t};
	}//07

	return end;
}
point draw_heart_r(Surface* sf, point sprout, double t)
{
	point end;
	for(int i = GetScreenHeight()/4 * t; i >= 0 ; i--){
		double phi = (3.14159)*(i/(GetScreenHeight()/4. * t));
		phi += 3.14159/2;

		point p ;
		point p2 ;
		
		p = {cos(phi)  * t * eq_heart(phi),
			 sin(phi)  * t * eq_heart(phi)};
		p2 = {cos(phi) *-t * eq_heart(phi),
			  sin(phi) * t * eq_heart(phi)};
		
		auto offy = sin(3.14159/2  + (PI)*(1)) *t*
					eq_heart(3.14159/2 + (PI)*(1));
		sf->get_dcomp()->pixel(sprout.x - p.x,sprout.y + p.y + 4*t,RED);
		sf->get_dcomp()->pixel(sprout.x - p2.x,sprout.y + p2.y + 4*t,RED);
		//sf->get_dcomp()->pixel(GetScreenWidth()/4/2, offy + GetScreenWidth()/4/2,ORANGE);//
		end = {sprout.x - p.x,sprout.y + p.y + 4*t};
	}//07

	return end;
}

void draw_menu(){
	Surface* heart = page["menu"]->get("heart");
	heart->paint = [](Surface* sf){
        float clk = sf->get_dcomp()->clk  * 0.21;
		double min_y, max_y = 0;
		double lt = 1;
		point pt = {GetScreenWidth()/4./2,3*GetScreenHeight()/4./4};
		bool rev = false;
		for (int t = 1; t < 100; t+=2)
		{
			// if((int)t%2 == 0)
			// pt.y += -4*t*clk;
			if(!rev)
				pt = draw_heart(sf,pt,2*t*clk);
			else
				pt = draw_heart_r(sf,pt,2*t*clk);
			rev = !rev;
			// else
				// pt = draw_heart_r(sf,pt,2*t*clk);
			// sf->get_dcomp()->pixel(p.x,p.y,ORANGE);
			// std::cout<<p.x<<" "<<p.y<<std::endl;
			// double lclk = clk;
			// lt = t;
			// min_y = get_y_by(0,lclk,lt);
			// max_y = get_y_by(GetScreenHeight()/4 * lclk * lt,lclk,lt);
		}
		// pt = {GetScreenWidth()/4./2,GetScreenHeight()/4./4};
		// for (double t = 9; t >= 1; t-=2)
		// {
		// 	// if((int)t%2 == 0)
		// 		pt = draw_heart_r(sf,pt,2*t*1);
		// 	// else
		// 		// pt = draw_heart_r(sf,pt,2*t*clk);
		// 	// sf->get_dcomp()->pixel(p.x,p.y,ORANGE);
		// 	// std::cout<<p.x<<" "<<p.y<<std::endl;
		// 	// double lclk = clk;
		// 	// lt = t;
		// 	// min_y = get_y_by(0,lclk,lt);
		// 	// max_y = get_y_by(GetScreenHeight()/4 * lclk * lt,lclk,lt);
		// }
        
        for(int y = 0; y < sf->get_h(); ++y)
        {
            for(int x = 0; x < sf->get_w(); ++x)
            {
        
                DrawRectangle(
                            sf->get_x() + sf->get_pixel_width() * x ,
                            sf->get_y() + sf->get_pixel_width() * y ,
                            sf->get_pixel_width(),sf->get_pixel_width(),
                            sf->at(x,y));
            }
        }
    };

}