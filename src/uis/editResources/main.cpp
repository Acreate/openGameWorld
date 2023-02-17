#include "EditorWidget.h"
#include "RunApplication.h"
#include <QApplication>
#include <BitConver.h>
#include <DataCheck.h>
#include <TypeBytes.h>

int main( int argc, char *argv[] ) {
	RunApplication app(argc, argv);
	typeFile::Byte byte("text.bin");
	QSharedPointer<QList<char> > fileBytes = byte.readFile();
	if( fileBytes.get() ) {
		// todo : 获取到的文件内容
		qDebug() << "获取到文本了";
	}
	serializeNormal::DataCheck data({12, 31, 57});
	QSharedPointer<QVector<char> > list = bitConver::get::bytes(22);
	char *pointer = list->data();
	EditorWidget w;
	w.show();
	return app.exec();
}