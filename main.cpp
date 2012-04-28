#include "gamewindow.h"
#include <QWidget>
#include <QDesktopWidget>
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	GameWindow window;

	return app.exec();
}
