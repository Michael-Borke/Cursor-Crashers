#include "tank.h"
#include <iostream>

Tank::Tank() 
	 : Player()
{
	health = 100;
	mana = 50;
	maxHealth = 100;
	maxMana = 50;
	type = TANK;
	canAttack = false;
	loadAnimations();
	experience = 0;
	unlocked = false;
	frameCount = 1;
	attacking = false;
	
	location.setX(400);
	location.setY(300);
	hitBox.setRect(0,0,11,17);
}

void Tank::attackAnimation()
{

}



bool Tank::healthCheck()
{
	if(health < 1)
	{
		health = 0;
		return false;
	}
	if(health > 100)
		health = 100;
	return true;
}

void Tank::manaCheck()
{
	if(frameCount%30 == 0)	
		mana+=5;
	if(mana > 50)
		mana = 50;
	if(mana < 0)
		mana = 0;
	if(mana < 10)
		attacking = false;
}

void Tank::loadAnimations()
{
	QImage temp;
	temp.load("Nova1.png");
	manaAttackSprite.append(temp.scaled(50,50,Qt::KeepAspectRatio));
	temp.load("Nova2.png");
	manaAttackSprite.append(temp.scaled(50,50,Qt::KeepAspectRatio));
	temp.load("Nova3.png");
	manaAttackSprite.append(temp.scaled(50,50,Qt::KeepAspectRatio));
	temp.load("Nova4.png");
	manaAttackSprite.append(temp.scaled(50,50,Qt::KeepAspectRatio));
	temp.load("Rage.gif");
	attackFrame = temp;
}

void Tank::manaAttackAnimation()
{
	if(unlocked)
	{	
		hitBox.setHeight(manaAttackFrame.rect().height());
		hitBox.setWidth(manaAttackFrame.rect().width());
		QPoint point(location.x()+3,location.y()+6);
		hitBox.moveCenter(point);
		switch (frameCount%16)
		{
			case 0:
				manaAttackFrame = manaAttackSprite.at(3);
				break;
			case 4:
				manaAttackFrame = manaAttackSprite.at(0);
				break;
			case 8:
				manaAttackFrame = manaAttackSprite.at(1);
				break;
			case 12:
				manaAttackFrame = manaAttackSprite.at(2);
				break;
		}
		if(frameCount%30 == 0)
			mana-=10;
	}
	else
		attacking = false;
}
