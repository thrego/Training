//#pragma once
//#include "turtle.h"
//
//class Painter
//{
//        Turtle* turtle;
//public:
//        Painter( Turtle* turtle )
//                :       turtle(turtle){}
//
//        bool DrawCircle(int, int, int){
//                turtle->PenDown();
//                return true;
//        }
//
//};

#ifndef PAINTER_H
#define PAINTER_H

#pragma once
#include "turtle.h"

class Painter
{
private:
	Turtle* turtle;

public:
        Painter( Turtle* turt ); //Constructor

        bool DrawCircle(int x, int y, int h);
        int Get_Position_X(void);
        int Get_Position_Y(void);
        bool Move_Forward(int x);
        bool Move_To(int x, int y);
        bool Foo(void);

};

#endif
