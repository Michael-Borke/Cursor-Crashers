#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include <QtGui>
#include <QFrame>
#include <QLabel>
#include <QWidget>
#include "game.h"

class QLCDNumber;
class QLabel;
class QPushButton;

class Game;

class GameWindow : public QWidget
{
	Q_OBJECT

	public:	
		GameWindow();
		void center(QWidget &widget);

	private:
//		QLabel *createLabel(const QString &text);
		QWidget *select;
		Game *game;
		/*QLCDNumber *score;
		QLCDNumber *level;*/
		QLabel *selectLabel;
		/*QLabel *scoreLabel;
		QLabel *levelLabel;*/
		QPushButton *startTankButton;
		QPushButton *startSinButton;
//		QPushButton *quitButton;
//		QPushButton *pauseButton;
//		QPushButton *rulesButton;
 };

 #endif
