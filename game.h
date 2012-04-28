#ifndef GAME_H
#define GAME_H

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
		///*** Constructor/Destructor ***///
		Game(QWidget *parent = 0);
		~Game();

	protected:
		///*** Runtime Events ***///
		void paintEvent(QPaintEvent *event);
		void timerEvent(QTimerEvent *event);
		void keyPressEvent(QKeyEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mousePressEvent(QMouseEvent *event);
		
		///*** Member Functions ***///
		void checkCollision();
		void checkEnemyDeath();

	public slots:
		///*** Slots ***///
		void startTankGame();
		void startAssassinGame();

	signals:
		///*** Signals ***///
		void scoreChanged(int score);
		void levelChanged(int level);

	private:
		///*** Members ***///	
		int level;
		int score;
		int frameTimer;
		int timerId;
		bool paused;
		bool canSpawnArcher;
		bool gameOver;
		bool gameStarted;
		Player *player;
		QList<Archer *> archers;
		QList<Drone *> drones;
		
		///*** Member Functions ***///
		void spawnEnemies();


};

#endif
