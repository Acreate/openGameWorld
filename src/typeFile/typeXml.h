#ifndef XML_H_HEAD__FILE__
#define XML_H_HEAD__FILE__

#pragma once

#include "typeBase.h"
#include "typeFile.h"

class TYPEFILE_EXPORT typeFile::Xml : public typeFile::Base {
	QSharedPointer<XmlBuff> buffInstance;

public:
	Xml(const QString& filePath)
		: Base( filePath ), buffInstance( nullptr ) {
	}

	/// @brief 读取内容，并且生成缓冲对象，若是读取失败，可以考虑关闭对象之后重新读取
	///	@param buffLen 建议读取长度，小于 1 表示一次性全部读取
	/// @return 缓冲对象
	QSharedPointer<XmlBuff> readContent(const qsizetype & buffLen = 0);
	/// @brief 获取缓冲对象
	/// @return 缓冲对象
	QSharedPointer<XmlBuff> getXmlBuff();
	/// @brief 使用缓冲对象进行内容写入
	/// @return 成功返回写入节点个数，小于 0 表示失败
	qsizetype writeContent();
};

#endif // XML_H_HEAD__FILE__
