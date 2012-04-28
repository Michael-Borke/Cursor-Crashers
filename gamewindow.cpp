#include <QtGui>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDesktopWidget>
#include <QPushButton>
#include <QApplication>
#include "game.h"
#include "gamewindow.h"

GameWindow::GameWindow()
{
	game = new Game(this);
	select = new QWidget();
	field = new QWidget();
	select->setPalette(QPalette(QColor(200,200,200)));
	select->setAutoFillBackground(true);
	
	///*** Set Buttons for Select Window ***///
	selectLabel = new QLabel(QString("CHOOSE YOUR DESTINY!"));
	selectLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	selectLabel->setAlignment(Qt::AlignCenter);
	startTankButton = new QPushButton(tr("&Barbarian"));
	startTankButton->setFocusPolicy(Qt::NoFocus);
	startTankButton->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	startSinButton = new QPushButton(tr("&Assassin"));
	startSinButton->setFocusPolicy(Qt::NoFocus);
	startSinButton->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	
	///*** Assign connections to the buttons ***///
	connect(startTankButton, SIGNAL(clicked()), game, SLOT(startTankGame()));
	connect(startTankButton, SIGNAL(clicked()), this, SLOT(startGame()));
	connect(startTankButton, SIGNAL(clicked()), select, SLOT(close()));
	connect(startSinButton, SIGNAL(clicked()), game, SLOT(startAssassinGame()));
	connect(startSinButton, SIGNAL(clicked()), this, SLOT(startGame()));
	connect(startSinButton, SIGNAL(clicked()), select, SLOT(close()));
	
	///*** Set Things for Game Window ***///
	score = new QLCDNumber(this);
    score->setSegmentStyle(QLCDNumber::Filled);
    level = new QLCDNumber(this);
    level->setSegmentStyle(QLCDNumber::Filled);
	
	///*** Setup Select Window ***///
	QGridLayout *layout = new QGridLayout;
	layout->addWidget(selectLabel, 0, 0);
	layout->addWidget(startTankButton, 1, 0);
	layout->addWidget(startSinButton, 2, 0);
	select->setLayout(layout);
	select->show();

	///*** Setup Game Windew ***///
	scoreLabel = new QLabel(QString("Score"));
	scoreLabel->setAlignment(Qt::AlignCenter);
	levelLabel = new QLabel(QString("Level"));
	levelLabel->setAlignment(Qt::AlignCenter);
	
	connect(game, SIGNAL(scoreChanged(int)), score, SLOT(display(int)));
	connect(game, SIGNAL(levelChanged(int)), level, SLOT(display(int)));
	
	QGridLayout *layout2 = new QGridLayout;
	layout2->addWidget(game,0,0,5,4);
	layout2->addWidget(levelLabel, 6, 0);
    layout2->addWidget(level, 6, 1);
	layout2->addWidget(scoreLabel, 6, 2);
	layout2->addWidget(score, 6, 3);
	field->setLayout(layout2);
	field->resize(800, 700);
	
	setWindowTitle(tr("Cursor Crashers"));
}

void GameWindow::startGame()
{
	field->show();
}
