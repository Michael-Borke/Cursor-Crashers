#include "assassin.h"
#include <iostream>

Assassin::Assassin() 
		: Player()
{
	bomb = new Bomb();
	maxHealth = 50;
	maxMana = 50;
	type = ASSN;
	canAttack = false;
	loadAnimations();
	experience = 0;
	unlocked = false;
	frameCount = 1;
	exploding = false;
	attacking = false;
	bombSet = false;
	
	location.setX(400);
	location.setY(300);
	hitBox.setRect(0,0,11,17);
	resetState();
}

Assassin::~Assassin()
{
	delete bomb;
}

void Assassin::attackAnimation()
{
	if(canAttack)
	{
		hitBox.setHeight(attackFrame.rect().height());
		hitBox.setWidth(attackFrame.rect().width());
		QPoint point(location.x()+5,location.y()+8);
		hitBox.moveCenter(point);
		switch (frameCount%8)
		{
			case 0:
				attackFrame = attackSprite.at(7);
				canAttack = false;
				break;
			case 1:
				attackFrame = attackSprite.at(0);
				break;
			case 2:
				attackFrame = attackSprite.at(1);
				break;
			case 3:
				attackFrame = attackSprite.at(2);
				break;
			case 4:
				attackFrame = attackSprite.at(3);
				break;
			case 5:
				attackFrame = attackSprite.at(4);
				break;
			case 6:
				attackFrame = attackSprite.at(5);
				break;
			case 7:
				attackFrame = attackSprite.at(6);
				break;
		}
	}	
}

bool Assassin::healthCheck()
{
	if(health < 1)
	{
		health = 0;
		return false;
	}
	if(health > 50)
		health = 50;
	return true;
}

void Assassin::manaCheck()
{
	if(frameCount%30 == 0)	
		mana+=5;
	if(mana > 50)
		mana = 50;
	if(mana < 0)
		mana = 0;
	if(mana < 20)
		attacking = false;
}

void Assassin::loadAnimations()
{
	QImage temp;
	temp.load("Slash1.png");
	attackSprite.append(temp.scaled(50,50,Qt::KeepAspectRatio));
	attackFrame = temp;
	temp.load("Slash2.png");
	attackSprite.append(temp.scaled(50,50,Qt::KeepAspectRatio));
	temp.load("Slash3.png");
	attackSprite.append(temp.scaled(50,50,Qt::KeepAspectRatio));
	temp.load("Slash4.png");
	attackSprite.append(temp.scaled(50,50,Qt::KeepAspectRatio));
	temp.load("Slash5.png");
	attackSprite.append(temp.scaled(50,50,Qt::KeepAspectRatio));
	temp.load("Slash6.png");
	attackSprite.append(temp.scaled(50,50,Qt::KeepAspectRatio));
	temp.load("Slash7.png");
	attackSprite.append(temp.scaled(50,50,Qt::KeepAspectRatio));
	temp.load("Slash8.png");
	attackSprite.append(temp.scaled(50,50,Qt::KeepAspectRatio));
	temp.load("bomb.png");
	manaAttackFrame = temp.scaled(50,50,Qt::KeepAspectRatio);
	temp.load("Boom1.png");
	manaAttackSprite.append(temp.scaled(50,50,Qt::KeepAspectRatio));
	temp.load("Boom2.png");
	manaAttackSprite.append(temp.scaled(50,50,Qt::KeepAspectRatio));
	temp.load("Boom3.png");
	manaAttackSprite.append(temp.scaled(50,50,Qt::KeepAspectRatio));
	temp.load("Boom4.png");
	manaAttackSprite.append(temp.scaled(50,50,Qt::KeepAspectRatio));
	temp.load("Boom5.png");
	manaAttackSprite.append(temp.scaled(50,50,Qt::KeepAspectRatio));
	temp.load("Boom6.png");
	manaAttackSprite.append(temp.scaled(50,50,Qt::KeepAspectRatio));
}

void Assassin::manaAttackAnimation()
{
	if(unlocked)
	{
		if(bombSet)
		{
			exploding = true;
			switch (frameCount%12)
			{
				case 0:
					manaAttackFrame = manaAttackSprite.at(5);
					bombSet = false;
					exploding = false;
					attacking = false;
					break;
				case 2:
					manaAttackFrame = manaAttackSprite.at(0);
					break;
				case 4:
					manaAttackFrame = manaAttackSprite.at(1);
					break;
				case 6:
					manaAttackFrame = manaAttackSprite.at(2);
					break;
				case 8:
					manaAttackFrame = manaAttackSprite.at(3);
					break;
				case 10:
					manaAttackFrame = manaAttackSprite.at(4);
					break;
			}
		} else 
		{
			bomb = new Bomb(location.x()-11,location.y()-11);
			manaAttackFrame.load("bomb.png");
			bombSet = true;
			attacking = false;
		}			
	}
}
