#include "archer.h"
#include <iostream>

Archer::Archer(int x, int y) 
	 : Enemy(x, y)
{
	health = 30;
	loadAnimations();
}

void Archer::movement(QPoint playerXY)
{
	if(frameCount%45 == 0)
	{
		/*if(playerXY.x() > location.x())
			location.setX(location.x()+5);
		if(playerXY.x() < location.x())
			location.setX(location.x()-5);
		if(playerXY.y() > location.y())
			location.setY(location.y()+5);
		if(playerXY.y() < location.y())
			location.setY(location.y()-5);*/
	}
}

void Archer::shoot(QPoint playerXY)
{
	if(frameCount%45 == 0)
	{
		
	}
}

void Archer::loadAnimations()
{
	QImage temp;
	temp.load("archer.png");
	attackSprite.append(temp.scaled(30,30,Qt::KeepAspectRatio));
	attackFrame = temp;
	hitBox = temp.rect();
}

void Archer::attackAnimation()
{
	attackFrame = attackSprite.at(0);
}
