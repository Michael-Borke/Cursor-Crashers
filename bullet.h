#ifndef BULLET_H_
#define BULLET_H_

#include <QPoint>
#include <QImage>
#include <QRect>
#include <QList>

class Bullet
{
	public:
		///*** Constructor/Destructor ***///
		Bullet();
		Bullet(int, int, int, int);
		~Bullet();
		
		///*** Members ***///
		QRect hitBox;
		QPoint destination;
		
		///*** Member Functions ***///
		void move(QPoint);
		QPoint getLocation();
		
	private:
		///*** Members ***///
		QPoint location;	
};

#endif
