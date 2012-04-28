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
		///*** Constructor/Destructor***///
		Assassin();
		~Assassin();
		
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
