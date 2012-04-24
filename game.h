#ifndef GAME_H
#define GAME_H

//#include "ball.h"
//#include "brick.h"
#include "drone.h"
#include "archer.h"
#include "player.h"
#include "assassin.h"
#include "tank.h"
#include <QWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QBrush>
#include <QGraphicsScene>
#include <QPropertyAnimation>

class Game : public QWidget
{
	Q_OBJECT

	public:
		Game(QWidget *parent = 0);
		~Game();

	protected:
		void paintEvent(QPaintEvent *event);
		void timerEvent(QTimerEvent *event);
		void frameEvent();
		void keyPressEvent(QKeyEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mousePressEvent(QMouseEvent *event);
//		void victory();
		void checkCollision();
		void checkEnemyDeath();

	public slots:
		void startTankGame();
		void startAssassinGame();
//		void pauseGame();
//		void stopGame();

	signals:
		/*void scoreChanged(int score);
		void levelChanged(int level);*/

	private:
		int x;
		int y;
		int frameTimer;
		int timerId;
		bool canSpawnArcher;
		Player *player;
		//Drone *drone;
		QList<Archer *> archers;
		QList<Drone *> drones;
		bool gameStarted;
		void spawnEnemies();
//		Brick * bricks[30];
		int level;
		int score;
		bool gameOver;
		bool gameWon;
//		bool paused;
//		Ball *ball;

};

#endif
