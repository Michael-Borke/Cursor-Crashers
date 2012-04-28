#ifndef ENEMY_H
#define ENEMY_H

#include "bullet.h"

#include <QImage>
#include <QList>
#include <QPoint>
#include <QRect>

class Enemy
{

	public:
		///*** Constructor and Deconstructor ***///
		Enemy(int, int);
		~Enemy();
		
		///*** Members ***///
		QRect hitBox;
		
		///*** Member Functions ***///
		void move(int, int);
		void takeDamage(int);
		virtual void updateEnemy(QPoint) = 0;
		
		///*** Getters ***///
		int getHealth();
		bool getAttacking();
		QPoint getLocation();
		QImage &getAttackFrame();
		
		///***Setters***///
		void setAttacking(bool);

	protected:
		///*** Members ***///
		int health;
		int direction;
		int frameCount;
		bool attacking;
		QPoint location;
		QImage attackFrame;
		QList<QImage> attackSprite;
		
		///*** Virtual Member Functions ***///
		virtual void movement(QPoint) = 0;
		virtual void loadAnimations() = 0;
		virtual void attackAnimation() = 0;
};

#endif
