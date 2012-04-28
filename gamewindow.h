#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include <QtGui>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QLCDNumber>
#include <QWidget>
#include "game.h"

class Game;

class GameWindow : public QWidget
{
	Q_OBJECT

	public:
		///*** Constructor ***///
		GameWindow();
			
	public slots:
		///*** Slots ***///
		void startGame();

	private:
		///*** Members ***///
		Game *game;		
		QWidget *field;
		QWidget *select;
		QLCDNumber *score;
		QLCDNumber *level;
		QLabel *selectLabel;
		QLabel *scoreLabel;
		QLabel *levelLabel;
		QPushButton *startTankButton;
		QPushButton *startSinButton;
 };

 #endif
