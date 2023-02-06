#include "TypeXml.h"

#include "TypeXmlBuff.h"

QSharedPointer<typeFile::XmlBuff> typeFile::Xml::readContent(const qsizetype& buffLen) {
	if( !fileInDir->exists() || this->openStatis < 1 || !isCanOpen() )
		return nullptr;

	if( !this->buffInstance )
		buffInstance = QSharedPointer<XmlBuff>( new XmlBuff );

	if( buffLen < 1 ) {
		QByteArray readAll = fileInstance->readAll();
		typeFile::generate::obj::xmlNodeInstance( readAll );
	}

	return buffInstance;
}

QSharedPointer<typeFile::XmlBuff> typeFile::Xml::getXmlBuff() {
	if( !this->buffInstance )
		buffInstance = QSharedPointer<XmlBuff>( new XmlBuff );
	return buffInstance;
}

qsizetype typeFile::Xml::writeContent() {
	return 0;
}
