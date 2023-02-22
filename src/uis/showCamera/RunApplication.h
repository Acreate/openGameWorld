#ifndef RUNAPPLICATION_H_H_HEAD__FILE__
#define RUNAPPLICATION_H_H_HEAD__FILE__
#pragma once
#include <QApplication>
#include <qguiapplication.h>

class RunApplication :  public QApplication {
public:
	RunApplication( int &argc, char **argv )
		: QApplication(argc, argv) {}

};
#endif // RUNAPPLICATION_H_H_HEAD__FILE__