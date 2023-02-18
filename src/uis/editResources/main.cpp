#include "EditorWidget.h"
#include "RunApplication.h"
#include <QApplication>
#include <BitConver.h>
#include <DataCheck.h>
#include <TypeBytes.h>
#include <Node.h>

int main( int argc, char *argv[] ) {
	RunApplication app(argc, argv);
	typeFile::Byte byte("text.bin");
	serializeNormal::Node<serializeNormal::DataCheck, serializeNormal::DataCheck> node1;
	QSharedPointer<QVector<char> > fileBytes = byte.readFile();
	if( fileBytes.get() ) {
		qDebug() << "获取到文本了";
		QSharedPointer<QVector<char> > list = node1.serializeInstance(*fileBytes);
		if( list->length() > 0 ) {
			qDebug() << "转化实现";
			auto propertys = node1.getIndex(0);
			QString msg;
			bitConver::set::bytes(propertys->left->getData(), &msg);
			qDebug() << "propertys.left : " << msg;
			bitConver::set::bytes(propertys->right->getData(), &msg);
			qDebug() << "propertys.right : " << msg;
		}
	}

	//serializeNormal::Node<serializeNormal::DataCheck, serializeNormal::DataCheck> dNode1;
	//serializeNormal::Node<int, int> node2; // error
	// serializeNormal::Node<DemoDataCheck, DemoDataCheck> dNode2; // error
	//using DataCheckNode = serializeNormal::Node<serializeNormal::DataCheck, serializeNormal::DataCheck>;
	//serializeNormal::Node<DataCheckNode, DataCheckNode> node3;

	serializeNormal::DataCheck data({12, 31, 57});
	QSharedPointer<QVector<char> > list = bitConver::get::bytes(22);
	char *pointer = list->data();
	EditorWidget w;
	w.show();
	return app.exec();
}