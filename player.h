#ifndef PLAYER_H
#define PLAYER_H

#include "bomb.h"

#include <QImage>
#include <QList>
#include <QPoint>
#include <QRect>

enum type{TANK=1, ASSN, WARLK};

class Player
{

	public:
		///*** Constructor and Deconstructor ***///
		Player();
		~Player();
		
		///*** Members ***///
		QRect hitBox;
		Bomb *bomb;
		bool bombSet;
		
		///*** Member Functions ***///
		void move(int, int);
		void resetState();
		void takeDamage(int);
		void giveExperience(int);
		void restartFrameCount();
		bool updatePlayer();
		virtual void attackAnimation() = 0;
		
		///*** Getters ***///
		int getMana();
		int getMaxMana();
		int getHealth();
		int getMaxHealth();
		int getType();
		int getXP();
		bool getUnlocked();
		bool getCanAttack();
		bool getAttacking();
		QPoint getLocation();
		QImage &getAttackFrame();
		QImage &getManaAttackFrame();
		
		///***Setters***///
		void setCanAttack(bool);
		void setAttacking(bool);

	protected:
		///*** Members ***///
		int mana;
		int maxMana;
		int health;
		int maxHealth;
		int type;
		bool unlocked;
		int experience;
		int frameCount;
		bool canAttack;
		bool attacking;
		QPoint location;
		QImage attackFrame;
		QImage manaAttackFrame;
		QList<QImage> attackSprite;
		QList<QImage> manaAttackSprite;
		
		///*** Member Functions ***///
		virtual bool healthCheck() = 0;
		virtual void manaCheck() = 0;
		
		///*** Virtual Member Functions ***///
		virtual void loadAnimations() = 0;
		virtual void manaAttackAnimation() = 0;
};

#endif
