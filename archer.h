#ifndef ARCHER_H
#define ARCHER_H

#include "enemy.h"
#include "bullet.h"

#include <QImage>
#include <QList>
#include <QPoint>
#include <QRect>

class Archer : public Enemy
{

	public:
		///*** Constructor/Destructor ***///
		Archer(int, int, int, int);
		
		///*** Members ***///
		Bullet *bullet;
		
		///*** Member Functions ***///
		void makeBullet(QPoint);
		void updateEnemy(QPoint);

	protected:
		///*** Members ***///
		bool canShoot;
		
		///*** Member Functions ***///
		void movement(QPoint);
		void loadAnimations();
		void attackAnimation();
};

#endif
