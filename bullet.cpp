#include "bullet.h"
#include <iostream>

Bullet::Bullet()
{
	location.setX(400);
	location.setY(300);
	
	destination.setX(400);
	destination.setY(200);
	
	hitBox = QRect(location.x(),location.y(),10,10);
}

Bullet::Bullet(int x, int y, int xx, int yy)
{
	location.setX(x);
	location.setY(y);
	
	destination.setX(xx);
	destination.setY(yy);
	
	hitBox = QRect(x,y,10,10);
}

Bullet::~Bullet()
{
	delete this;
}

QPoint Bullet::getLocation()
{
	return location;
}

void Bullet::move(QPoint playerXY)
{
	if(playerXY.x() > location.x())
		location.setX(location.x()+10);
	if(playerXY.x() < location.x())
		location.setX(location.x()-10);
	if(playerXY.y() > location.y())
		location.setY(location.y()+10);
	if(playerXY.y() < location.y())
		location.setY(location.y()-10);
	hitBox = QRect(location.x(),location.y(),10,10);
}
