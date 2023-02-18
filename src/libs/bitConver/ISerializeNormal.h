#ifndef ISERIALIZENORMAL_H_H_HEAD__FILE__
#define ISERIALIZENORMAL_H_H_HEAD__FILE__
#pragma once

#include <QSharedPointer>

namespace serializeNormal {
	/// @brief 序列化对象接口
	class BITCONVER_EXPORT ISerializeNormal {
	public:
		virtual ~ISerializeNormal( ) = default;

		/// @brief 重新初始化对象
		/// @param dataBytes 需要提供的 data
		/// @return 使用数据个数
		virtual size_t resetData( const QVector<char> &dataBytes ) =0;
		/// @brief 重新初始化对象
		/// @param dataBytes 需要提供的 data
		/// @param dataSize data 的长度
		/// @return 使用数据个数
		virtual size_t resetData( const char *dataBytes, size_t dataSize ) =0;

		/// @brief 从该对象实例中实现转化数据
		/// @return 成功转化的数据，失败返回 nullptr
		virtual QSharedPointer<QVector<char> > serializeInstance( ) = 0;

		/// @brief 从一个数据中设置该对象实例
		/// @param dataBytes 输入数据
		/// @return 成功返回数据体的数据，失败返回 nullptr
		virtual QSharedPointer<QVector<char> > serializeInstance( const QVector<char> &dataBytes ) = 0;

		/// @brief 从一个数据中设置该对象实例
		/// @param dataBytes 输入数据
		/// @param index 开始的下标
		/// @return 成功返回数据体的数据，失败返回 nullptr
		virtual QSharedPointer<QVector<char> > serializeInstance( const QVector<char> &dataBytes, size_t index ) = 0;

		/// @brief 从一个数据中设置该对象实例
		/// @param dataBytes 输入数据
		/// @param dataSize 输入数据的大小（长度）
		/// @param index 开始的下标
		/// @return 成功返回数据体的数据，失败返回 nullptr
		virtual QSharedPointer<QVector<char> > serializeInstance( const char *dataBytes, size_t dataSize, size_t index ) = 0;
		/// @brief 从一个数据中设置该对象实例
		/// @param dataBytes 输入数据
		/// @param dataSize 输入数据的大小（长度）
		/// @return 成功返回数据体的数据，失败返回 nullptr
		virtual QSharedPointer<QVector<char> > serializeInstance( const char *dataBytes, size_t dataSize ) = 0;
	};
}


#endif // ISERIALIZENORMAL_H_H_HEAD__FILE__