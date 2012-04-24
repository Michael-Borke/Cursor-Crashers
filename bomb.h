#ifndef BOMB_H_
#define BOMB_H_

#include <QPoint>
#include <QImage>
#include <QRect>
#include <QList>

class Bomb
{
	public:
		Bomb();
		Bomb(int, int);
		~Bomb();
		
		QRect hitBox;
		QPoint getLocation();
		
	private:
		QPoint location;	
};

#endif
