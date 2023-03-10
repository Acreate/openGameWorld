#ifndef TEXT_H_HEAD__FILE__
#define TEXT_H_HEAD__FILE__

#pragma once

#include <QDir>
#include <QFile>
#include <QString>

#include "TypeBase.h"
#include "TypeFile.h"

/// @brief 文本类型
class TYPEFILE_EXPORT typeFile::Text : public typeFile::Base {
	/// @brief 缓冲对象
	QSharedPointer<typeFile::TextBuff> buffInstance;

public:
	QSharedPointer<typeFile::TextBuff> getTextBuff( );

	/// @brief 打开一个文件对象
	/// @param filePath 文本路径
	/// @param openMode 打开模式
	explicit Text( const QString &filePath, QIODevice::OpenMode openMode = QIODeviceBase::ReadWrite | QIODeviceBase::Text )
		: Base(filePath, openMode), buffInstance(nullptr) { }

	/// @brief 当字符串赋值给对象时候，对象直接写入内容到文件
	/// @param str 写入文件内容的字符串
	/// @return 文本操作对象
	Text &operator=( const QString &str ) {
		writeContents(str);
		return *this;
	}

	/// @brief 把文本内容读取到该对象，他会受到读写位置影响
	/// @param left 内容写入的字符串
	/// @param textInstance 文件操作对象
	/// @return 一个字符串
	friend Text &operator<<( QString &left, Text &textInstance ) {
		left = textInstance.readContents();
		return textInstance;
	}

	/// @brief 读取文件内容
	/// @param size 读取数量
	/// @return 末尾返回空
	QString readContents( const uint64_t size = 1024 );
	/// @brief 往文件写入内容
	/// @param strContent 写入的内容
	/// @param writeCount 写入个数，小于 1 为一次性全部写入
	/// @return 写入个数
	qsizetype writeContents( const QString &strContent, const qsizetype writeCount = 0 );

	/// @brief 使用缓冲对象进行写入
	///	@param  writeCount 建议写入个数
	///	@return 写入个数
	qsizetype writeContentsAtTextBuffInstance( const qsizetype writeCount = 0 );

	/// @brief 设置当前文件的读取下标位置
	/// @param index 下标位置
	/// @return 设置好的下标位置
	qsizetype setTextPointIndex( const qsizetype &index ) {

		if( !fileInstance->isOpen() ) {
			QFileInfo info(*filePath);
			if( info.exists() && isCanOpen() ) {
				fileInstance->seek(index);
				return fileInstance->pos();
			}
		} else {
			fileInstance->seek(index);
			return fileInstance->pos();
		}
		return 0;
	}

	/// @brief 在原有的下标位置下增量读取下标位置
	/// @param len 增量
	/// @return 当前下标位置
	qsizetype addTextPointIndex( const qsizetype &len ) {

		if( !fileInstance->isOpen() ) {
			QFileInfo info(*filePath);
			if( info.exists() && isCanOpen() ) {
				fileInstance->seek(len + fileInstance->pos());
				return fileInstance->pos();
			}
		} else {
			fileInstance->seek(len + fileInstance->pos());
			return fileInstance->pos();
		}

		return 0;
	}

	/// @brief 获取文件大小
	/// @return 文件的大小
	qsizetype getTextSize( ) {
		QFileInfo info(*filePath);
		if( info.exists() && isCanOpen() )
			return fileInstance->size();
		return 0;
	}

	/// @brief 参数文件，不存在则会删除失败
	/// @return true 表示删除成功，否则失败
	bool reamove( ) {
		QFileInfo info(*filePath);
		if( info.exists() )
			if( isCanOpen() ) {
				bool fileStatisResult = fileInstance->remove();
				fileInstance->close();
				openStatis = 0;
				return fileStatisResult;
			}
		return false;
	}

	/// @brief 重命名文件，不存在文件则失败
	/// @param newName 新的文件名
	/// @return 成功返回 true
	bool reNameFile( const QString &newName ) {
		QFileInfo info(*filePath);
		if( info.exists() )
			if( isCanOpen() ) {
				bool fileStatisResult = fileInstance->rename(newName);
				return fileStatisResult;
			}
		return false;
	}

	~Text( ) override {
		closeFile();
	}
};

#endif // TEXT_H_HEAD__FILE__