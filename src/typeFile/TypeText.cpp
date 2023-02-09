#include "TypeText.h"
#include "TypeTextBuff.h"

QSharedPointer<typeFile::TextBuff> typeFile::Text::getTextBuff( ) {
	if( !buffInstance )
		buffInstance = QSharedPointer<typeFile::TextBuff>(new typeFile::TextBuff());
	return buffInstance;
}

QString typeFile::Text::readContents( const uint64_t &size ) {
	// 未初始化，则自动初始化
	if( ! isCanOpen() )
		return "";
	return fileInstance->readLine(size);
}

qsizetype typeFile::Text::writeContents( const QString &strContent, const qsizetype &writeCount ) {
	// 保存写入个数
	qsizetype overWriteCount = 0;
	// 字符串长度
	auto strLen = strContent.length();
	// 未初始化，则自动初始化
	if( strLen > 0 && isCanOpen() ) {
		if( writeCount <= strLen ) {
			QByteArray byteArray = strContent.toLocal8Bit();
			fileInstance->write(byteArray, byteArray.length());
			fileInstance->flush();
			return strLen;
		}
		while( overWriteCount <= strLen ) {
			QString writeStr = strContent.mid(overWriteCount, writeCount);
			QByteArray byteArray = writeStr.toLocal8Bit();
			qint64 length = writeStr.length();
			if( length == 0 )
				return overWriteCount;
			overWriteCount += length;
			fileInstance->write(byteArray, byteArray.length());
		}
	}
	return overWriteCount;
}

qsizetype typeFile::Text::writeContentsAtTextBuffInstance( const qsizetype &writeCount ) {
	qint64 textContentsLen = writeContents(buffInstance->getContent(), writeCount);
	buffInstance->clear();
	return textContentsLen;
}