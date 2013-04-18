
#include "mainwindow.h"

#include <QApplication>

#include <cstdlib>

int main(int argc, char **argv)
{
	// TODO initialize random seed
	/*
	unsigned int seed = THE_SEED;
	srandom(seed);
	*/
	
	QApplication application(argc, argv);
	MainWindow mainwindow;

	mainwindow.show();
	return application.exec();
}
