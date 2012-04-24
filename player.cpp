#include "player.h"
#include <iostream>

///*** Constructor and Destructor ***///
Player::Player()
{	

}

Player::~Player()
{

}

///*** Member Functions***///
void Player::move(int x, int y)
{
	location.setX(x);
	location.setY(y);
	hitBox.moveTo(location);
	attackFrame.rect().moveTo(location);
	manaAttackFrame.rect().moveTo(location);	
}

void Player::resetState()
{
	health = 100;
	mana = 50;
	hitBox.moveTo(400, 300);
}

void Player::takeDamage(int dmg)
{
	health-=dmg;
}

void Player::giveExperience(int xp)
{
	experience += xp;
}

void Player::restartFrameCount()
{
	frameCount = 1;
}

///*** Keep player updated (including life and mana) ***///
bool Player::updatePlayer()
{
	frameCount++;
	if(frameCount > 400)
		frameCount = 1;
	if(attacking)
	{
		canAttack = false;
		manaAttackAnimation();
	}
	else
	{
		hitBox.setWidth(11);
		hitBox.setHeight(17);
	}
	attackAnimation();
	if(experience > 4)
		unlocked = true;
	if(!healthCheck())
		return false;
	manaCheck();
	return true;
}

///*** Getters ***///
int Player::getMana()
{
	return mana;
}

int Player::getMaxMana()
{
	return maxMana;
}

int Player::getHealth()
{
	return health;
}

int Player::getMaxHealth()
{
	return maxHealth;
}

int Player::getType()
{
	return type;
}

int Player::getXP()
{
	return experience;
}

bool Player::getUnlocked()
{
	return unlocked;
}

bool Player::getCanAttack()
{
	return canAttack;
}

bool Player::getAttacking()
{
	return attacking;
}

QPoint Player::getLocation()
{
	return location;
}

QImage & Player::getAttackFrame()
{
	return attackFrame;
}

QImage & Player::getManaAttackFrame()
{
	return manaAttackFrame;
}

///*** Setters ***///
void Player::setCanAttack(bool a)
{
	canAttack = a;
}

void Player::setAttacking(bool a)
{
	attacking = a;
}
