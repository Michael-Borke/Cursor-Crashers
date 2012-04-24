#ifndef TANK_H
#define TANK_H

#include "player.h"

#include <QImage>
#include <QList>
#include <QPoint>
#include <QRect>

class Tank : public Player
{

	public:
		Tank();
		
		void attackAnimation();
		
		//void resetState();
		//int getHealth();
		//void updatePlayer();

	protected:
		bool healthCheck();
		void manaCheck();
		void loadAnimations();
		void manaAttackAnimation();
};

#endif
