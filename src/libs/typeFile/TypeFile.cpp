#include "TypeFile.h"
#include "TypeText.h"
#include "TypeXml.h"
#include <QFile>
#include <QDir>

QSharedPointer<typeFile::Text> typeFile::generate::file::textInstance(const QString& fileExisPath) {
	return QSharedPointer<Text>( new Text( fileExisPath ) );
}

QSharedPointer<typeFile::Xml> typeFile::generate::file::xmlInstance(const QString& fileExisPath) {
	return QSharedPointer<Xml>( new Xml( fileExisPath ) );
}

QSharedPointer<typeFile::XmlBuff> typeFile::generate::obj::xmlNodeInstance(const QString& str) {
	return nullptr;
}
