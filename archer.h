#ifndef ARCHER_H
#define ARCHER_H

#include "enemy.h"

#include <QImage>
#include <QList>
#include <QPoint>
#include <QRect>

class Archer : public Enemy
{

	public:
		Archer(int, int);

	protected:
		void movement(QPoint);
		void shoot(QPoint);
		void loadAnimations();
		void attackAnimation();
};

#endif
