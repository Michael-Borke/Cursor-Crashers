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
	frameTimer = 0;
	paused = false;
	gameOver = false;
	gameStarted = false;
	canSpawnArcher = false;
	level=1;
	score=0;
}

Game::~Game()
{
	delete player;
	for(int i=0;i<drones.size();i++)
		delete drones.at(i);
	for(int i=0;i<archers.size();i++)
		delete archers.at(i);
}

void Game::paintEvent(QPaintEvent *event)
{
	if(gameStarted)
	{
		///*** Setup Painter ***///
		QPainter painter(this);
		QBrush normal(painter.brush());
		QBrush manaBar(Qt::blue,Qt::SolidPattern);
		QBrush healthBar(Qt::green,Qt::SolidPattern);
		
		///*** Prevent painter from drawing if the game is over ***///
		if (gameOver) 
		{
			painter.end();
			QPainter painter(this);
		
			QFont font("Courier", 15, QFont::DemiBold);
			QFontMetrics fm(font);
			int textWidth = fm.width("Game Over!");
			int textWidth2 = fm.width("Press ESC to close window");

			painter.setFont(font);

			painter.translate(QPoint(400, 300));
			painter.drawText(-textWidth/2, 0, "Game Over!");
			painter.drawText(-textWidth2/2, 15, "Press ESC to close window");
			killTimer(timerId);
			std::cout << "BLAHBLAHBLAH\n";
		}
	
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
				painter.drawImage(player->bomb->getLocation().x()-20,player->bomb->getLocation().y()-17,player->getManaAttackFrame());
		}
	
		///*** Draw Enemies ***///
		for(int i=0;i<drones.size();i++)
		{
			painter.setBrush(healthBar);
			painter.drawRect(drones.at(i)->getLocation().x()-15,drones.at(i)->getLocation().y()-20,drones.at(i)->getHealth(), 4);
			painter.setBrush(normal);
			painter.drawImage(drones.at(i)->getLocation().x()-15,drones.at(i)->getLocation().y()-15,drones.at(i)->getAttackFrame());
		}
		if(canSpawnArcher)
		{
			for(int i=0;i<archers.size();i++)
			{
				painter.setBrush(normal);
				painter.drawImage(archers.at(i)->getLocation().x()-15,archers.at(i)->getLocation().y()-15,archers.at(i)->getAttackFrame());
				if(archers.at(i)->getAttacking())
				{
					painter.setBrush(manaBar);
					painter.drawEllipse(archers.at(i)->bullet->getLocation().x(),archers.at(i)->bullet->getLocation().y(),10,10);

				}
			}
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
	
		///*** Give player tips at appropriate levels ***///
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
		if (player->getXP() == 5) 
		{
			QFont font("Courier", 15, QFont::DemiBold);
			QFontMetrics fm(font);
			int textWidth = fm.width("Level Up!\nRight Click for New Skill");

			painter.setFont(font);

			painter.translate(QPoint(400, 300));
			painter.drawText(-textWidth/2, 0, "Level Up! Right Click for New Skill");
			level=2;
			emit levelChanged(level);
			canSpawnArcher = true;
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
			level=3;
			emit levelChanged(level);
		}
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
		} else if(player->getType() == ASSN && player->getUnlocked() && !player->exploding) {
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
	score = player->getXP()*10;
	emit scoreChanged(score);
	
	if(!player->updatePlayer())
	{
		gameOver = true;
		std::cout << "SNATHOEUSANOTH.\n";
		repaint();
	}
	for(int i=0;i<drones.size();i++)
	{
		drones.at(i)->updateEnemy(player->getLocation());
	}
	for(int i=0;i<archers.size();i++)
	{
		archers.at(i)->updateEnemy(player->getLocation());
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
		case Qt::Key_P:
			paused = !paused;
			if(paused)
				killTimer(timerId);
			else
				timerId = startTimer(33);
			break;
		case Qt::Key_Escape:
			qApp->exit();
			break;
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
					if(level >= 3)
						drones.at(i)->takeDamage(20);
					else
						drones.at(i)->takeDamage(12);
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
					drones.at(i)->takeDamage(5);
			}
		}
	}
	for(int i=0;i<archers.size();i++)
	{
		if(player->hitBox.intersects(archers.at(i)->bullet->hitBox))
		{
			player->takeDamage(5);
			archers.at(i)->makeBullet(player->getLocation());
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
	if(player->getXP() > 10)
	{
		while(drones.size() < player->getXP())
		{
			drones.append(new Drone(rand()%800 + 1,rand()%600 + 1));
		}
	}
	else
	{
		while(drones.size() < 10)
		{
			drones.append(new Drone(rand()%800 + 1,rand()%600 + 1));
		}
	}
	if(canSpawnArcher)
	{
		while(archers.size()<4)
		{
			archers.append(new Archer(rand()%700 + 51,rand()%500 + 51, player->getLocation().x(), player->getLocation().y()));
		}
	}
}

///*** If the player chooses to be a barbarian, spawn a barbarian ***///
void Game::startTankGame()
{
	player = new Tank();
	if (!gameStarted)
	{
		gameStarted = true;
		emit scoreChanged(score);
		emit levelChanged(level);
		gameOver = false;
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
		gameStarted = true;
		emit scoreChanged(score);
		emit levelChanged(level);
		gameOver = false;
    	setMouseTracking(true);
		timerId = startTimer(33);
		spawnEnemies();
	}
}
