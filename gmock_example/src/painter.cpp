#pragma once

#include "painter.h"

// Constructor

Painter::Painter( Turtle* turt ) : turtle(turt){}

bool Painter::DrawCircle(int x, int y, int h){
	    turtle->PenDown();
		return true;
}

int Painter::Get_Position_X(void) {
	return turtle->GetX();
}

int Painter::Get_Position_Y(void) {
	return turtle->GetY();
}

bool Painter::Move_Forward(int x){
	turtle->Forward(x);
	return true;
}

bool Painter::Move_To(int x, int y) {
	turtle->GoTo(x,y);
	return true;
}

bool Painter::Foo(void) {
	turtle->PenDown();
	turtle->Forward(100);
	turtle->PenUp();
	return true;
}
