#ifndef TYPEBASE_H_HEAD__FILE__
#define TYPEBASE_H_HEAD__FILE__

#pragma once

#include "TypeFile.h"

class TYPEFILE_EXPORT typeFile::Base {
protected:
	/// @brief 文件状态，0 为空状态
	int openStatis;
	/// @brief 文件路径
	QSharedPointer<QString> filePath;
	/// @brief 文件夹
	QSharedPointer<QDir> fileInDir;
	/// @brief 文件操作对象实例
	QSharedPointer<QFile> fileInstance;
	/// @brief 打开模式
	QIODevice::OpenMode openMode;

public:
	explicit Base( const QString &filePath, QIODevice::OpenMode openMode = QIODeviceBase::ReadWrite | QIODeviceBase::Truncate ) : openStatis(0), filePath(new QString(filePath)), fileInDir(new QDir(filePath)), fileInstance(new QFile(filePath)), openMode(openMode) { }

	/// @brief 尝试打开文件
	/// @return 失败返回 false
	bool openFile( ) {
		// 已经打开，则返回非法
		if( this->openStatis != 0 )
			return false;
		// 设置为非法打开
		this->openStatis = -1;
		if( !fileInstance->open(openMode) )
			return false;
		// 设置正常读写状态
		this->openStatis = 1;
		return true;
	}

	/// @brief 是否能打开文件，该操作会尝试打开文件
	/// @return 失败返回 false
	inline bool isCanOpen( ) {
		return this->openStatis > 0 || openFile();
	}

	/// @brief 关闭文件
	void closeFile( ) {
		if( fileInstance->isOpen() ) {
			fileInstance->close();
			openStatis = 0;
		}
	}
};

#endif // TYPEBASE_H_HEAD__FILE__