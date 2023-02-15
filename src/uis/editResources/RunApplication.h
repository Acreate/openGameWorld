#ifndef RUNAPPLICATION_H_H_HEAD__FILE__
#define RUNAPPLICATION_H_H_HEAD__FILE__
#pragma once
#include <ProcessArgs.h>
#include <qguiapplication.h>

class RunApplication : public ProcessArgs, public QGuiApplication {
public:
	RunApplication( int &argc, char **argv )
		: ProcessArgs(argc, argv), QGuiApplication(argc, argv) {}

};
#endif // RUNAPPLICATION_H_H_HEAD__FILE__