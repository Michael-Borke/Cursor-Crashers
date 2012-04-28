#ifndef BOMB_H_
#define BOMB_H_

#include <QPoint>
#include <QImage>
#include <QRect>
#include <QList>

class Bomb
{
	public:
		///*** Constructor/Destructor ***///
		Bomb();
		Bomb(int, int);
		~Bomb();
		
		///*** Members ***///
		QRect hitBox;
		
		///*** Member Functions ***///
		QPoint getLocation();
		
	private:
		///*** Members ***///
		QPoint location;	
};

#endif
