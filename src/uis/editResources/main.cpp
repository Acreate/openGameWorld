#include "EditorWidget.h"
#include "RunApplication.h"
#include <QApplication>

int main( int argc, char *argv[] ) {
	RunApplication app(argc, argv);



	EditorWidget w;
	w.show();
	return app.exec();
}