#include "TypeFile.h"
#include <QFile>
#include <QDir>

TypeFile::TypeFile() {
}

TypeFile::~TypeFile() {
}

bool TypeFile::Text::openTextFile() {
	// 已经打开，则返回非法
	if( this->openStatis != 0 )
		return false;
	// 设置为非法打开
	this->openStatis = -1;
	if( !fileInstance.open( QIODeviceBase::ReadWrite | QIODeviceBase::Text ) )
		return false;
	// 设置正常读写状态
	this->openStatis = 1;
	return true;
}

QString TypeFile::Text::readTextContents(const uint64_t& size) {
	// 未初始化，则自动初始化
	if( ! isCanOpen() )
		return "";
	return fileInstance.readLine( size );
}

qsizetype TypeFile::Text::writeTextContents(const QString& strContent, const qsizetype& writeCount) {
	// 保存写入个数
	qsizetype overWriteCount = 0;
	// 字符串长度
	auto strLen = strContent.length();
	// 未初始化，则自动初始化
	if( strLen > 0 && isCanOpen() ) {
		if( writeCount <= strLen ) {
			QByteArray byteArray = strContent.toLocal8Bit();
			fileInstance.write( byteArray, byteArray.length() );
			fileInstance.flush();
			return strLen;
		} else {
			for( ; !(overWriteCount > strLen); ) {
				QString writeStr = strContent.mid( overWriteCount, writeCount );
				QByteArray byteArray = writeStr.toLocal8Bit();
				qint64 length = writeStr.length();
				if( length == 0 )
					return overWriteCount;
				overWriteCount += length;
				fileInstance.write( byteArray, byteArray.length() );
			}
		}
	}
	return 0;
}

QSharedPointer<TypeFile::Text> TypeFile::getTextInstance(const QString& fileExisPath) {
	return QSharedPointer<Text>( new Text( fileExisPath ) );
}
