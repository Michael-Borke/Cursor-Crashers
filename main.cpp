#include "gamewindow.h"
#include <QWidget>
#include <QDesktopWidget>
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	GameWindow window;
	window.setFixedSize(800,600);
	window.show();

	return app.exec();
}
