#include "enemy.h"
#include "bullet.h"
#include <iostream>

///*** Constructor and Destructor ***///
Enemy::Enemy(int x, int y)
{
	frameCount = 1;
	attacking = false;
	
	location.setX(x);
	location.setY(y);
	
	//hitBox.setRect(0,0,30,30);
}

Enemy::~Enemy()
{
}

///*** Member Functions***///
void Enemy::move(int x, int y)
{
	location.setX(x);
	location.setY(y);
	QPoint point(location.x()-1,location.y()-1);
	hitBox.moveCenter(point);
	attackFrame.rect().moveTo(location);	
}

void Enemy::takeDamage(int dmg)
{
	health-=dmg;
}

///*** Getters ***///
int Enemy::getHealth()
{
	return health;
}

bool Enemy::getAttacking()
{
	return attacking;
}

QPoint Enemy::getLocation()
{
	return location;
}

QImage & Enemy::getAttackFrame()
{
	return attackFrame;
}

///*** Setters ***///
void Enemy::setAttacking(bool a)
{
	attacking = a;
}
