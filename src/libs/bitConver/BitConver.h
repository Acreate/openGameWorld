#ifndef BITCONVER_H_H_HEAD__FILE__
#define BITCONVER_H_H_HEAD__FILE__
#pragma once

#include "BitConver_export.h"
#include <QSharedPointer>
#include <QVector>

namespace bitConver {
	/// @brief 从对象转换到数据类型
	namespace get {


		inline BITCONVER_EXPORT QSharedPointer<QVector<char> > bytes( const QString &value ) {
			QByteArray byteArray = value.toUtf8();
			return QSharedPointer<QVector<char> >(new QVector<char>(byteArray.data_ptr()));
		}

		inline BITCONVER_EXPORT QSharedPointer<QVector<char> > bytes( const int16_t &value ) {
			QSharedPointer<QVector<char> > result(new QVector<char>(2));
			char *list = result.data()->data();
			const char *ptr = (char *)&value;
			list[0] = ptr[0];
			list[1] = ptr[1];
			return result;
		}

		inline BITCONVER_EXPORT QSharedPointer<QVector<char> > bytes( const int32_t &value ) {
			QSharedPointer<QVector<char> > result(new QVector<char>(4));
			char *list = result.data()->data();
			const char *ptr = (char *)&value;
			list[0] = ptr[0];
			list[1] = ptr[1];
			list[2] = ptr[2];
			list[3] = ptr[3];
			return result;
		}

		inline BITCONVER_EXPORT QSharedPointer<QVector<char> > bytes( const int64_t &value ) {
			QSharedPointer<QVector<char> > result(new QVector<char>(8));
			char *list = result.data()->data();
			const char *ptr = (char *)&value;
			list[0] = ptr[0];
			list[1] = ptr[1];
			list[2] = ptr[2];
			list[3] = ptr[3];
			list[4] = ptr[4];
			list[5] = ptr[5];
			list[6] = ptr[6];
			list[7] = ptr[7];
			return result;
		}

		inline BITCONVER_EXPORT QSharedPointer<QVector<char> > bytes( const uint16_t &value ) {
			QSharedPointer<QVector<char> > result(new QVector<char>(2));
			char *list = result.data()->data();
			const char *ptr = (char *)&value;
			list[0] = ptr[0];
			list[1] = ptr[1];
			return result;
		}

		inline BITCONVER_EXPORT QSharedPointer<QVector<char> > bytes( const uint32_t &value ) {
			QSharedPointer<QVector<char> > result(new QVector<char>(4));
			char *list = result.data()->data();
			const char *ptr = (char *)&value;
			list[0] = ptr[0];
			list[1] = ptr[1];
			list[2] = ptr[2];
			list[3] = ptr[3];
			return result;
		}

		inline BITCONVER_EXPORT QSharedPointer<QVector<char> > bytes( const uint64_t &value ) {
			QSharedPointer<QVector<char> > result(new QVector<char>(8));
			char *list = result.data()->data();
			const char *ptr = (char *)&value;
			list[0] = ptr[0];
			list[1] = ptr[1];
			list[2] = ptr[2];
			list[3] = ptr[3];
			list[4] = ptr[4];
			list[5] = ptr[5];
			list[6] = ptr[6];
			list[7] = ptr[7];
			return result;
		}
	}

	/// @brief 从数据转换到类型对象
	namespace set {

		inline BITCONVER_EXPORT size_t bytes( const char *data, const size_t dataLen, int16_t *outValue, size_t index = 0 ) {
			if( dataLen < index || dataLen - index < 2 )
				return 0;
			outValue[0] = data[index];
			outValue[1] = data[index + 1];
			return 2;
		}

		inline BITCONVER_EXPORT size_t bytes( const char *data, const size_t dataLen, int32_t *outValue, size_t index = 0 ) {
			if( dataLen < index || dataLen - index < 4 )
				return 0;
			outValue[0] = data[index];
			outValue[1] = data[index + 1];
			outValue[2] = data[index + 2];
			outValue[3] = data[index + 3];
			return 4;
		}

		inline BITCONVER_EXPORT size_t bytes( const char *data, const size_t dataLen, int64_t *outValue, size_t index = 0 ) {
			if( dataLen < index || dataLen - index < 4 )
				return 0;
			outValue[0] = data[index];
			outValue[1] = data[index + 1];
			outValue[2] = data[index + 2];
			outValue[3] = data[index + 3];
			outValue[4] = data[index + 4];
			outValue[5] = data[index + 5];
			outValue[6] = data[index + 6];
			outValue[7] = data[index + 7];
			return 8;
		}


		inline BITCONVER_EXPORT size_t bytes( const char *data, const size_t dataLen, uint16_t *outValue, size_t index = 0 ) {
			if( dataLen < index || dataLen - index < 2 )
				return 0;
			outValue[0] = data[index];
			outValue[1] = data[index + 1];
			return 2;
		}

		inline BITCONVER_EXPORT size_t bytes( const char *data, const size_t dataLen, uint32_t *outValue, size_t index = 0 ) {
			if( dataLen < index || dataLen - index < 4 )
				return 0;
			outValue[0] = data[index];
			outValue[1] = data[index + 1];
			outValue[2] = data[index + 2];
			outValue[3] = data[index + 3];
			return 4;
		}

		inline BITCONVER_EXPORT size_t bytes( const char *data, const size_t dataLen, uint64_t *outValue, size_t index = 0 ) {
			if( dataLen < index || dataLen - index < 4 )
				return 0;
			outValue[0] = data[index];
			outValue[1] = data[index + 1];
			outValue[2] = data[index + 2];
			outValue[3] = data[index + 3];
			outValue[4] = data[index + 4];
			outValue[5] = data[index + 5];
			outValue[6] = data[index + 6];
			outValue[7] = data[index + 7];
			return 8;
		}


		inline BITCONVER_EXPORT size_t bytes( const char *data, const size_t dataLen, QString *outValue, size_t index = 0, size_t count = 0 ) {
			if( dataLen == 0 || dataLen <= index )
				return 0;
			bool cond = index == 0 && count == 0;

			// 是否存在 \0 结束符
			size_t forIndex = 0;
			while( forIndex < dataLen )
				if( data[forIndex] == 0 ) {
					if( cond )
						*outValue = QString::fromUtf8(data);
					else {
						// 转换个数
						size_t converCount = dataLen - index;
						// 最小转换个数
						if( count > 0 && count < converCount )
							converCount = count;
						auto converChar = new char[converCount]{0};
						for( ; index < dataLen; ++index )
							converChar[index] = data[index];
						*outValue = QString::fromUtf8(converChar);
						delete[] converChar;
					}
					return dataLen;
				}
			return 0;
		}


		inline BITCONVER_EXPORT size_t bytes( const QVector<char> &data, int16_t *outValue, size_t index = 0 ) {
			return bytes(data.data(), data.length(), outValue, index);
		}

		inline BITCONVER_EXPORT size_t bytes( const QVector<char> &data, int32_t *outValue, size_t index = 0 ) {
			return bytes(data.data(), data.length(), outValue, index);
		}

		inline BITCONVER_EXPORT size_t bytes( const QVector<char> &data, int64_t *outValue, size_t index = 0 ) {
			return bytes(data.data(), data.length(), outValue, index);
		}

		inline BITCONVER_EXPORT size_t bytes( const QVector<char> &data, uint16_t *outValue, size_t index = 0 ) {
			return bytes(data.data(), data.length(), outValue, index);
		}

		

		inline BITCONVER_EXPORT size_t bytes( const QVector<char> &data, uint32_t *outValue, size_t index = 0 ) {
			return bytes(data.data(), data.length(), outValue, index);
		}

		inline BITCONVER_EXPORT size_t bytes( const QVector<char> &data, uint64_t *outValue, size_t index = 0 ) {
			return bytes(data.data(), data.length(), outValue, index);
		}


		inline BITCONVER_EXPORT size_t bytes( const QVector<char> &data, QString *outValue, size_t index = 0, size_t count = 0 ) {
			return bytes(data.data(), data.length(), outValue, index, count);
		}
	}

}

#endif // BITCONVER_H_H_HEAD__FILE__