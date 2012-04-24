#ifndef DRONE_H
#define DRONE_H

#include "enemy.h"

#include <QImage>
#include <QList>
#include <QPoint>
#include <QRect>

class Drone : public Enemy
{

	public:
		Drone(int, int);

	protected:
		void movement(QPoint);
		void loadAnimations();
		void attackAnimation();
};

#endif
