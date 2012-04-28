#include "archer.h"
#include <iostream>

Archer::Archer(int x, int y, int xx, int yy) 
	 : Enemy(x, y)
{
	health = 30;
	bullet = new Bullet(x, y, xx, yy);
	attacking = true;
	
	loadAnimations();
}

void Archer::makeBullet(QPoint playerXY)
{
	bullet = new Bullet(location.x(), location.y(), playerXY.x(), playerXY.y());
}

void Archer::updateEnemy(QPoint playerXY)
{
	frameCount++;
	if(frameCount > 400)
		frameCount = 1;
	movement(playerXY);
	if(attacking)
	{
		attackAnimation();
		if(frameCount%5 == 0)
			bullet->move(playerXY);
	}
}

void Archer::movement(QPoint playerXY)
{
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
