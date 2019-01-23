#include "datastatic.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	DataStatic w;
	w.show();
	return a.exec();
}
