#include "EditorWidget.h"
#include "RunApplication.h"
#include <QApplication>
#include <BitConver.h>
#include <DataCheck.h>
int main( int argc, char *argv[] ) {
	RunApplication app(argc, argv);

	dataChecks::DataCheck data({12,31,57});
	QSharedPointer<QVector<char>> list = bitConver::get::bytes(22);
	char * pointer = list->data();
	EditorWidget w;
	w.show();
	return app.exec();
}