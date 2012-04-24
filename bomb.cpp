#include "bomb.h"
#include <iostream>

Bomb::Bomb()
{
	location.setX(400);
	location.setY(300);
	
	hitBox = QRect(location.x(),location.y(),50,50);
}

Bomb::Bomb(int x, int y)
{
	location.setX(x);
	location.setY(y);
	
	hitBox = QRect(x,y,50,50);
}

Bomb::~Bomb()
{
	delete this;
}

QPoint Bomb::getLocation()
{
	return location;
}
