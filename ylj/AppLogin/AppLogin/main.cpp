#include "applogin.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QSplashScreen>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QSplashScreen* splash = new QSplashScreen();
	splash->setPixmap(QPixmap("image/splash.png"));
	splash->show();

	AppLogin w;

	// 加载分厂和用户信息
	w.loadFactoryDatas();
	w.loadUserDatas();

	w.show();

	splash->finish(&w);
	delete splash;

	return a.exec();
}
