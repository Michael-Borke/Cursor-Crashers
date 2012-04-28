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
		///*** Constructor ***///
		Tank();
		
		///*** Member Functions ***///
		void attackAnimation();

	protected:
		///*** Member Functions ***///
		bool healthCheck();
		void manaCheck();
		void loadAnimations();
		void manaAttackAnimation();
};

#endif
