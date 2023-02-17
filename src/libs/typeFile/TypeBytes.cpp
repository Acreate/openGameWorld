#include "TypeBytes.h"

QSharedPointer<QVector<char> > typeFile::Byte::readFile( ) {
	QFileInfo info(*filePath);
	if( info.exists() && isCanOpen() ) {
		QByteArray byteArray = fileInstance->readAll();
		QString absoluteFilePath = info.absoluteFilePath();
		qsizetype length = byteArray.length();
		if( length == 0 )
			return nullptr;
		QSharedPointer<QVector<char> > result(new QVector<char>);
		char *data = byteArray.data();
		for( qsizetype index = 0; index < length; ++index )
			result->append(data[index]);
		return result;
	}

	return nullptr;
}

QSharedPointer<QString> typeFile::Byte::readFileStr( ) {
	if( isCanOpen() )
		return QSharedPointer<QString>(new QString(QString::fromUtf8(fileInstance->readAll())));
	return nullptr;
}

size_t typeFile::Byte::writeFile( const QVector<char> &contents ) {
	if( isCanOpen() )
		return fileInstance->write(contents.data(), contents.length());
	return 0;
}

size_t typeFile::Byte::writeFile( const char *data, const size_t dataSize ) {
	if( isCanOpen() )
		return fileInstance->write(data, dataSize);
	return 0;

}

size_t typeFile::Byte::writeFile( const QString &str ) {
	if( isCanOpen() ) {
		QByteArray byteArray = str.toUtf8();
		return fileInstance->write(byteArray.data(), byteArray.length());
	}
	return 0;
}