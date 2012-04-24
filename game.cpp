#include "game.h"
#include "time.h"
#include <QApplication>
#include <QPropertyAnimation>
#include <iostream>
#include <string>

Game::Game(QWidget *parent)
		: QWidget(parent)
{
	srand(time(NULL));
	setFocusPolicy(Qt::StrongFocus);
	setPalette(QPalette(QColor(250, 250, 200)));
	setAutoFillBackground(true);
	x = 400;
	y = 300;
	frameTimer = 0;
//	gameOver = false;
//	gameWon = false;
	gameStarted = false;
	canSpawnArcher = false;
//	level=0;
//	score=0;
	startTankGame();
}

Game::~Game()
{
	delete player;
	for(int i=0;i<drones.size();i++)
		delete drones.at(i);
}

void Game::paintEvent(QPaintEvent *event)
{
	///*** Setup Painter ***///
	QPainter painter(this);
	QBrush normal(painter.brush());
	QBrush manaBar(Qt::blue,Qt::SolidPattern);
	QBrush healthBar(Qt::green,Qt::SolidPattern);
	
	///*** Draw Player ***///
	if(player->getType() == TANK)
	{
		if(player->getCanAttack())
			painter.drawImage(player->getLocation().x()-9,player->getLocation().y()-5,player->getAttackFrame());
		if(player->getAttacking())
			painter.drawImage(player->getLocation().x()-10,player->getLocation().y()-10,player->getManaAttackFrame());
	} else if(player->getType() == ASSN) {
		if(player->getCanAttack())
		{
			painter.drawImage(player->getLocation().x()-20,player->getLocation().y()-17,player->getAttackFrame());
		}
		if(player->bombSet)
			painter.drawImage(player->bomb->getLocation().x(),player->bomb->getLocation().y(),player->getManaAttackFrame());
	}
	
	///*** Draw Enemies ***///
	for(int i=0;i<drones.size();i++)
	{
		painter.setBrush(healthBar);
		painter.drawRect(drones.at(i)->getLocation().x()-15,drones.at(i)->getLocation().y()-20,drones.at(i)->getHealth(), 4);
		painter.setBrush(normal);
		painter.drawImage(drones.at(i)->getLocation().x()-15,drones.at(i)->getLocation().y()-15,drones.at(i)->getAttackFrame());
	}
	for(int i=0;i<archers.size();i++)
	{
		/*painter.setBrush(healthBar);
		painter.drawRect(archers.at(i)->getLocation().x()-15,archers.at(i)->getLocation().y()-20,archers.at(i)->getHealth(), 4);*/
		painter.setBrush(normal);
		painter.drawImage(archers.at(i)->getLocation().x()-15,archers.at(i)->getLocation().y()-15,archers.at(i)->getAttackFrame());
	}
	
	///*** Draw Status Bars ***///
	painter.setBrush(healthBar);
	painter.drawRect(5,5,player->getHealth(),10);
	painter.setBrush(normal);
	painter.drawRect(5,5,player->getMaxHealth(),10);
	painter.setBrush(manaBar);
	painter.drawRect(5,20,player->getMana(),10);
	painter.setBrush(normal);
	painter.drawRect(5,20,player->getMaxMana(),10);
	
	///*** Track Player Level and Progress ***///
	if (player->getXP() < 1) 
	{
		if(player->getType() == TANK)
		{	
			QFont font("Courier", 15, QFont::DemiBold);
			QFontMetrics fm(font);
			int textWidth = fm.width("Left Click to 'Enrage', then run into an enemy!");

			painter.setFont(font);

			painter.translate(QPoint(400, 300));
			painter.drawText(-textWidth/2, 0, "Left Click to 'Enrage', then run into an enemy!");
		}
		else if(player->getType() == ASSN)
		{	
			QFont font("Courier", 15, QFont::DemiBold);
			QFontMetrics fm(font);
			int textWidth = fm.width("Left Click to Slash enemies, but don't get too close!");

			painter.setFont(font);

			painter.translate(QPoint(400, 300));
			painter.drawText(-textWidth/2, 0, "Left Click to Slash enemies, but don't get too close!");
		}
	}
	if (player->getUnlocked() && player->getXP() < 6) 
	{
		QFont font("Courier", 15, QFont::DemiBold);
		QFontMetrics fm(font);
		int textWidth = fm.width("Level Up!\nRight Click for New Skill");

		painter.setFont(font);

		painter.translate(QPoint(400, 300));
		painter.drawText(-textWidth/2, 0, "Level Up! Right Click for New Skill");
	}
	if (player->getXP() == 10)
	{
		QFont font("Courier", 15, QFont::DemiBold);
		QFontMetrics fm(font);
		int textWidth = fm.width("Level Up!");

		painter.setFont(font);

		painter.translate(QPoint(400, 300));
		painter.drawText(-textWidth/2, 0, "Level Up!");
		canSpawnArcher = true;
	}
	if (gameOver) 
	{
		QFont font("Courier", 15, QFont::DemiBold);
		QFontMetrics fm(font);
		int textWidth = fm.width("Game Over");

		painter.setFont(font);

		painter.translate(QPoint(400, 300));
		painter.drawText(-textWidth/2, 0, "Game Over");
	}
}

///*** Keep hitBox on Mouse ***///
void Game::mouseMoveEvent(QMouseEvent *event)
{
	player->move(event->x()-2,event->y()-2);
}

void Game::mousePressEvent(QMouseEvent *event)
{
	///*** When the left mouse is clicked, the primary attack is activatied. When the right mouse is clicked, the magic attack is activated ***///
	if(event->button() == Qt::RightButton)
	{
		if(player->getType() == TANK)
		{
			if(!player->getAttacking() && player->getMana() > 20)
				player->setAttacking(true);
			else
				player->setAttacking(false);
		} else if(player->getType() == ASSN && player->getUnlocked()) {
			player->restartFrameCount();
			player->setAttacking(true);
		}
	}
	if(event->button() == Qt::LeftButton)
	{
		if(player->getType() == TANK)
		{
			player->setCanAttack(true);
			for(int i=0;i<drones.size();i++)
			{
				if(player->hitBox.intersects(drones.at(i)->hitBox))
					player->setCanAttack(false);
			}
		} 
		else if(player->getType() == ASSN){
			if(!player->getCanAttack())	
			{
				player->restartFrameCount();
				frameTimer = 1;
				player->setCanAttack(true);
			}
		}
	}
}

///*** Run this such that there are 30 runs in a second, emulating frames ***///
void Game::timerEvent(QTimerEvent *event)
{
	frameTimer++;
	if(!player->updatePlayer())
	{
		gameOver = true;
		repaint();
		killTimer(timerId);
	}
	for(int i=0;i<drones.size();i++)
	{
		drones.at(i)->updateEnemy(player->getLocation());
	}
	checkCollision();
	checkEnemyDeath();
	spawnEnemies();
	repaint();
}

///*** Keep track of keypresses ***///
void Game::keyPressEvent(QKeyEvent *event)
{
	switch (event->key()) 
	{
		case Qt::Key_Space:
			
			break;
		case Qt::Key_Escape:
			qApp->exit();
			break;
//		default:
//			QObject::keyPressEvent(event);
	}
}

///*** If enemies get too close to one another, or hit the user, damage is dealt accordingly ***///
void Game::checkCollision()
{
	for(int i=0;i<drones.size();i++)
	{
		if((drones.at(i)->getLocation().x()+25 < player->getLocation().x() 
		|| drones.at(i)->getLocation().x()-25 > player->getLocation().x()) 
		&& (drones.at(i)->getLocation().y()+25 < player->getLocation().y()
		|| drones.at(i)->getLocation().y()-25 > player->getLocation().y()))
		{
			for(int j=0;j<drones.size();j++)
			{
				if(i == j)
					continue;
				else
				{
					if(drones.at(i)->getLocation().x() <= drones.at(j)->getLocation().x() 
					&& drones.at(i)->getLocation().x()+31 > drones.at(j)->getLocation().x())
						drones.at(i)->move(drones.at(i)->getLocation().x()-(10),drones.at(i)->getLocation().y());
					if(drones.at(i)->getLocation().x() >= drones.at(j)->getLocation().x() 
					&& drones.at(i)->getLocation().x()+31 < drones.at(j)->getLocation().x())
						drones.at(i)->move(drones.at(i)->getLocation().x()+(10),drones.at(i)->getLocation().y());
					if(drones.at(i)->getLocation().y() <= drones.at(j)->getLocation().y() 
					&& drones.at(i)->getLocation().y()+31 > drones.at(j)->getLocation().y())
						drones.at(i)->move(drones.at(i)->getLocation().x(),drones.at(i)->getLocation().y()-(10));
					if(drones.at(i)->getLocation().y() <= drones.at(j)->getLocation().y() 
					&& drones.at(i)->getLocation().y()+31 > drones.at(j)->getLocation().y())
						drones.at(i)->move(drones.at(i)->getLocation().x(),drones.at(i)->getLocation().y()+(10));
				}
			}
		}
		if(player->hitBox.intersects(drones.at(i)->hitBox))
		{
			if(player->getType() == TANK)
			{	
				if(!player->getAttacking() && !player->getCanAttack() && frameTimer%30 == 0){
					player->takeDamage(5);
				} else if(player->getCanAttack() && !player->getAttacking()){
					drones.at(i)->takeDamage(20);
					player->setCanAttack(false);
				} else if(player->getAttacking() && !player->getCanAttack() && frameTimer%15 == 0){
					drones.at(i)->takeDamage(5);
				}
			} else if(player->getType() == ASSN)
			{
				if(frameTimer%10 == 0){
					player->takeDamage(5);
				}
				if(player->getCanAttack() && !player->getAttacking() && frameTimer%4 == 0){
					drones.at(i)->takeDamage(8);
				}
			}
		}
		if(player->getType() == ASSN)
		{
			if(player->getAttacking() && player->bombSet)
			{
				if(drones.at(i)->hitBox.intersects(player->bomb->hitBox))
					drones.at(i)->takeDamage(15);
			}
		}
	}
}

///*** If an enemy is killed, give the player XP ***///
void Game::checkEnemyDeath()
{
	for(int i=0;i<drones.size();i++)
	{
		if(drones.at(i)->getHealth() < 1)
		{
			drones.removeAt(i);
			player->giveExperience(1);
		}
	}
}

///*** Keep the playing field populated ***///
void Game::spawnEnemies()
{
	while(drones.size() < 10)
	{
		drones.append(new Drone(rand()%800 + 1,rand()%600 + 1));
	}
	if(canSpawnArcher)
	{
		while(archers.size()<4)
		{
			archers.append(new Archer(rand()%800 + 1,rand()%600 + 1));
		}
	}
}

///*** If the player chooses to be a barbarian, spawn a barbarian ***///
void Game::startTankGame()
{
	player = new Tank();
	if (!gameStarted)
	{
		player->resetState();
		//gameOver = FALSE;
		//gameWon = FALSE;
		gameStarted = true;
		//emit scoreChanged(score);
		//emit levelChanged(level);
		setMouseTracking(true);
		timerId = startTimer(33);
		spawnEnemies();
	}
}

///*** If a player chooses to be an Assn, spawn it ***///
void Game::startAssassinGame()
{
	player = new Assassin();
	if (!gameStarted)
	{
		player->resetState();
		//gameOver = FALSE;
		//gameWon = FALSE;
		gameStarted = true;
		//emit scoreChanged(score);
		//emit levelChanged(level);
    	setMouseTracking(true);
		timerId = startTimer(33);
		spawnEnemies();
	}
}
