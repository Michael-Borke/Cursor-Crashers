#include "drone.h"
#include <iostream>

Drone::Drone(int x, int y) 
	 : Enemy(x, y)
{
	health = 30;
	loadAnimations();
}

void Drone::updateEnemy(QPoint playerXY)
{
	frameCount++;
	if(frameCount > 400)
		frameCount = 1;
	movement(playerXY);
	if(attacking)
	{
		attackAnimation();
	}
}

void Drone::movement(QPoint playerXY)
{
	if(frameCount%5 == 0)
	{
		if(playerXY.x() > location.x())
			location.setX(location.x()+5);
		if(playerXY.x() < location.x())
			location.setX(location.x()-5);
		if(playerXY.y() > location.y())
			location.setY(location.y()+5);
		if(playerXY.y() < location.y())
			location.setY(location.y()-5);
	}
	move(location.x(),location.y());
}

void Drone::loadAnimations()
{
	QImage temp;
	temp.load("drone.png");
	attackSprite.append(temp.scaled(30,30,Qt::KeepAspectRatio));
	attackFrame = temp;
	hitBox = temp.rect();
}

void Drone::attackAnimation()
{
	attackFrame = attackSprite.at(0);
}
