#include "typeFile.h"
#include "typeText.h"
#include "typeXml.h"
#include <QFile>
#include <QDir>

QSharedPointer<typeFile::Text> typeFile::generate::textInstance(const QString& fileExisPath) {
	return QSharedPointer<Text>( new Text( fileExisPath ) );
}

QSharedPointer<typeFile::Xml> typeFile::generate::xmlInstance(const QString& fileExisPath) {
	return QSharedPointer<Xml>( new Xml( fileExisPath ) );
}
