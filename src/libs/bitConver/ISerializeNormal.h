#ifndef ISERIALIZENORMAL_H_H_HEAD__FILE__
#define ISERIALIZENORMAL_H_H_HEAD__FILE__
#pragma once

#include <QSharedPointer>

namespace serializeNormal {
	/// @brief 序列化对象接口
	class BITCONVER_EXPORT ISerializeNormal {
	public:
		virtual ~ISerializeNormal( ) = default;

		/// @brief 从该对象实例中实现转化数据
		/// @return 成功转化的数据，失败返回 nullptr
		virtual QSharedPointer<QVector<char> > serializeInstance( ) = 0;

		/// @brief 从一个数据中设置该对象实例
		/// @param dataBytes 输入数据
		/// @return 成功返回 true
		virtual size_t serializeInstance( const QVector<char> &dataBytes ) = 0;

	};
}


#endif // ISERIALIZENORMAL_H_H_HEAD__FILE__