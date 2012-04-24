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
	select = new QWidget(this);
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
	
	connect(startTankButton, SIGNAL(clicked()), game, SLOT(startTankGame()));
	connect(startTankButton, SIGNAL(clicked()), select, SLOT(close()));
	connect(startSinButton, SIGNAL(clicked()), game, SLOT(startAssassinGame()));
	connect(startSinButton, SIGNAL(clicked()), select, SLOT(close()));
	
	///*** Setup Select Window ***///
	QVBoxLayout *layout = new QVBoxLayout;
	layout->setSpacing(10);
	layout->addWidget(selectLabel);
	layout->addWidget(startTankButton);
	layout->addWidget(startSinButton);
	select->setLayout(layout);
	resize(800,600);
	select->show();

	///*** Setup Game Windew ***///
	/*scoreLabel = new QLabel(QString("Score"));
	//scoreLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	scoreLabel->setAlignment(Qt::AlignCenter);
	levelLabel = new QLabel(QString("Level"));
	//levelLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	levelLabel->setAlignment(Qt::AlignCenter);*/
	
	//connect(game, SIGNAL(scoreChanged(int)), score, SLOT(display(int)));
	//connect(game, SIGNAL(levelChanged(int)), level, SLOT(display(int)));
	
	
	QGridLayout *layout2 = new QGridLayout;
	layout2->addWidget(game,0,0);
	//layout2->
	/*layout2->addWidget(levelLabel, 1, 0);
    layout2->addWidget(level, 1, 1);
	layout2->addWidget(scoreLabel, 1, 2);
	layout2->addWidget(score, 1, 3);*/
	setLayout(layout2);
	setWindowTitle(tr("Cursor Crashers"));
	resize(800, 600);
}

void GameWindow::center(QWidget &widget)
{
	int x, y;
	int screenWidth;
	int screenHeight;

	int WIDTH = 800;
	int HEIGHT = 600;


	QDesktopWidget *desktop = QApplication::desktop();

	screenWidth = desktop->width();
	screenHeight = desktop->height();

	x = (screenWidth - WIDTH) / 4;
	y = (screenHeight - HEIGHT) / 2;

	widget.setGeometry(x, y, WIDTH, HEIGHT);
	widget.setFixedSize(WIDTH, HEIGHT);
}
