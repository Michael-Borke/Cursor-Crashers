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
		///*** Constructor/Destructor ***///
		Drone(int, int);
		
		///*** Member Function ***///
		void updateEnemy(QPoint);

	protected:
		///*** Member Functions ***///
		void movement(QPoint);
		void loadAnimations();
		void attackAnimation();
};

#endif
