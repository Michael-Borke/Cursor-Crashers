#ifndef ASSASSIN_H
#define ASSASSIN_H

#include "player.h"
#include "bomb.h"

#include <QImage>
#include <QList>
#include <QPoint>
#include <QRect>

class Assassin : public Player
{

	public:
		Assassin();
		~Assassin();
		
		void attackAnimation();
		
		//void resetState();
		//int getHealth();
		//void updatePlayer();

	protected:
		bool exploding;
		bool healthCheck();
		void manaCheck();
		void loadAnimations();
		void manaAttackAnimation();
};

#endif
