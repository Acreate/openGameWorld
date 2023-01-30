#include "typeXml.h"

#include "typeXmlBuff.h"

QSharedPointer<typeFile::XmlBuff> typeFile::Xml::readContent() {
	if( !fileInDir->exists() || this->openStatis < 1 || !isCanOpen() )
		return nullptr;

	if( !this->buffInstance )
		buffInstance = QSharedPointer<XmlBuff>( new XmlBuff );

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
