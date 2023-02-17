#ifndef TYPEBITYS_H_H_HEAD__FILE__
#define TYPEBITYS_H_H_HEAD__FILE__
#pragma once

#include "TypeBase.h"
#include "TypeFile.h"

/// @brief 二进制内容对象
class TYPEFILE_EXPORT typeFile::Byte : public Base {

public:
	explicit Byte( const QString &filePath, const QIODevice::OpenMode &openMode = QIODeviceBase::ReadWrite )
		: Base(filePath, openMode) {}

	~Byte( ) override {
		closeFile();
	}

	/// @brief 读取文件
	/// @return 文件内容
	QSharedPointer<QVector<char> > readFile( );

	/// @brief 读取文件
	/// @return 文件内容
	QSharedPointer<QString> readFileStr( );

	/// @brief 使一个容器的内容写入到文件
	/// @param contents 容器内容
	/// @return 写入个数
	size_t writeFile( const QVector<char> &contents );

	/// @brief 写入一个二进制数据，它并不保证被读取的内容是否可读
	/// @param data 指向二进制数据的指针
	/// @param dataSize 写入大小
	/// @return 写入个数
	size_t writeFile( const char *data, const size_t dataSize );

	/// @brief 写入一段字符串
	/// @param str 字符串
	/// @return 写入个数
	size_t writeFile( const QString &str );
};


#endif // TYPEBITYS_H_H_HEAD__FILE__