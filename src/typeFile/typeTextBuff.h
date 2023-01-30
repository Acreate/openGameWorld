#ifndef TEXTBUFF_H_HEAD__FILE__
#define TEXTBUFF_H_HEAD__FILE__

#pragma once
#include "typeFile_export.h"
#include <QSharedPointer>
#include <QString>

#include "typeFile.h"
#include "typeText.h"

/// @brief 文本缓冲对象
class TYPEFILE_EXPORT typeFile::TextBuff {
	/// @brief 写入内容
	QSharedPointer<QString> contents;

public:
	TextBuff() : contents( new QString() ) {
	}

	TextBuff(const QString& contents)
		: contents( new QString( contents ) ) {
	}

	/// @brief 追加一段字符
	///	@return 自身操作对象
	TextBuff& operator<<(const QString& str) {
		contents->append( str );
		return *this;
	}

	/// @brief 把字符放置到指定字符串
	///	@return 自身操作对象
	TextBuff& operator>>(QString& str) {
		str = *contents;
		return *this;
	}

	/// @brief 重新赋值
	///	@return 自身操作对象
	TextBuff& operator=(const QString& str) {
		*contents = str;
		return *this;
	}

	/// @brief 获取内容
	/// @return 缓冲内容
	const QString getContent() const {
		return *this->contents;
	}

	/// @brief 使用 QString 方式填充参数
	/// @return 新的操作对象
	TextBuff arg(const QString& str) {
		return TextBuff( contents->arg( str ) );
	}

	void clear() {
		contents->clear();
	}
};

#endif // TEXTBUFF_H_HEAD__FILE__
