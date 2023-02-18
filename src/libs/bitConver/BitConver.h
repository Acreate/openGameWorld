#ifndef BITCONVER_H_H_HEAD__FILE__
#define BITCONVER_H_H_HEAD__FILE__
#pragma once

#include <bitset>

#include "BitConver_export.h"
#include <QSharedPointer>
#include <QVector>

namespace bitConver {

	class Endian {
	public:
		/// @brief 是否小端
		/// @return true 表示小端
		bool static BITCONVER_EXPORT isLittleEndian( );
	};

	/// @brief 从对象转换到数据类型
	class get {
	public:
		inline static BITCONVER_EXPORT QSharedPointer<QVector<char> > bytes( const QString &value ) {
			QByteArray byteArray = value.toUtf8();
			return QSharedPointer<QVector<char> >(new QVector<char>(byteArray.data_ptr()));
		}

		inline static BITCONVER_EXPORT QSharedPointer<QVector<char> > bytes( const int16_t &value ) {
			QSharedPointer<QVector<char> > result(new QVector<char>(2));
			char *list = result.data()->data();
			const char *ptr = (char *)&value;
			list[0] = ptr[0];
			list[1] = ptr[1];
			return result;
		}

		inline static BITCONVER_EXPORT QSharedPointer<QVector<char> > bytes( const int32_t &value ) {
			QSharedPointer<QVector<char> > result(new QVector<char>(4));
			char *list = result.data()->data();
			const char *ptr = (char *)&value;
			list[0] = ptr[0];
			list[1] = ptr[1];
			list[2] = ptr[2];
			list[3] = ptr[3];
			return result;
		}

		inline static BITCONVER_EXPORT QSharedPointer<QVector<char> > bytes( const int64_t &value ) {
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

		inline static BITCONVER_EXPORT QSharedPointer<QVector<char> > bytes( const uint16_t &value ) {
			QSharedPointer<QVector<char> > result(new QVector<char>(2));
			char *list = result.data()->data();
			const char *ptr = (char *)&value;
			list[0] = ptr[0];
			list[1] = ptr[1];
			return result;
		}

		inline static BITCONVER_EXPORT QSharedPointer<QVector<char> > bytes( const uint32_t &value ) {
			QSharedPointer<QVector<char> > result(new QVector<char>(4));
			char *list = result.data()->data();
			const char *ptr = (char *)&value;
			list[0] = ptr[0];
			list[1] = ptr[1];
			list[2] = ptr[2];
			list[3] = ptr[3];
			return result;
		}

		inline static BITCONVER_EXPORT QSharedPointer<QVector<char> > bytes( const uint64_t &value ) {
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
	};

	/// @brief 从数据转换到类型对象
	class set {
	public:
		inline static BITCONVER_EXPORT int32_t bytes( const char *data, const int32_t dataLen, int16_t *outValue, int32_t index = 0 ) {
			if( dataLen < index || dataLen - index < 2 )
				return 0;
			if( Endian::isLittleEndian() )
				*outValue = data[index] | data[index + 1] << 8;
			else
				*outValue = data[index] << 8 | data[index + 1];
			return 2;
		}

		inline static BITCONVER_EXPORT int32_t bytes( const char *data, const int32_t dataLen, int32_t *outValue, int32_t index = 0 ) {
			if( dataLen < index || dataLen - index < 4 )
				return 0;
			if( Endian::isLittleEndian() )
				*outValue = data[index] | data[index + 1] << 8 | data[index + 2] << 16 | data[index + 3] << 24;
			else
				*outValue = data[index] << 24 | data[index + 1] << 16 | data[index + 2] << 8 | data[index + 3];
			return 4;
		}

		inline static BITCONVER_EXPORT int32_t bytes( const char *data, const int32_t dataLen, int64_t *outValue, int32_t index = 0 ) {
			if( dataLen < index || dataLen - index < 4 )
				return 0;
			if( Endian::isLittleEndian() )
				*outValue = data[index] | data[index + 1] << 8 | data[index + 2] << 16 | data[index + 3] << 24 | data[index + 4] << 32 | data[index + 5] << 40 | data[index + 6] << 48 | data[index + 7] << 56;
			else
				*outValue = data[index] << 56 | data[index + 1] << 48 | data[index + 2] << 40 | data[index + 3] << 32 | data[index + 4] << 24 | data[index + 5] << 16 | data[index + 6] << 8 | data[index + 7];
			return 8;
		}


		inline static BITCONVER_EXPORT int32_t bytes( const char *data, const int32_t dataLen, uint16_t *outValue, int32_t index = 0 ) {
			if( dataLen < index || dataLen - index < 2 )
				return 0;
			if( Endian::isLittleEndian() )
				*outValue = data[index] | data[index + 1] << 8 | data[index + 2] << 16;
			else
				*outValue = data[index] << 16 | data[index + 1] << 8 | data[index + 2];
			return 2;
		}

		inline static BITCONVER_EXPORT int32_t bytes( const char *data, const int32_t dataLen, uint32_t *outValue, int32_t index = 0 ) {
			if( dataLen < index || dataLen - index < 4 )
				return 0;
			if( Endian::isLittleEndian() )
				*outValue = data[index] | data[index + 1] << 8 | data[index + 2] << 16 | data[index + 3] << 24;
			else
				*outValue = data[index] << 24 | data[index + 1] << 16 | data[index + 2] << 8 | data[index + 3];
			return 4;
		}

		inline static BITCONVER_EXPORT int32_t bytes( const char *data, const int32_t dataLen, uint64_t *outValue, int32_t index = 0 ) {
			if( dataLen < index || dataLen - index < 4 )
				return 0;
			if( Endian::isLittleEndian() )
				*outValue = data[index] | data[index + 1] << 8 | data[index + 2] << 16 | data[index + 3] << 24 | data[index + 4] << 32 | data[index + 5] << 40 | data[index + 6] << 48 | data[index + 7] << 56;
			else
				*outValue = data[index] << 56 | data[index + 1] << 48 | data[index + 2] << 40 | data[index + 3] << 32 | data[index + 4] << 24 | data[index + 5] << 16 | data[index + 6] << 8 | data[index + 7];
			return 8;
		}


		inline static BITCONVER_EXPORT int32_t bytes( const char *data, const int32_t dataLen, QString *outValue, int32_t index = 0, int32_t count = 0 ) {
			if( dataLen == 0 || dataLen <= index || count > (dataLen - index) )
				return 0;

			if( count > 0 ) {
				// 装填数据
				char *converData = new char[count + 1]{0};
				for( size_t orgIndex = 0; orgIndex < count; ++orgIndex )
					converData[orgIndex] = data[index + orgIndex];
				*outValue = QString::fromUtf8(converData);
				delete[] converData;
				return count;
			}
			// 装填数据
			char *converData = new char[dataLen + 1]{0};
			for( size_t orgIndex = 0; orgIndex < dataLen; ++orgIndex )
				converData[orgIndex] = data[index + orgIndex];
			*outValue = QString::fromUtf8(converData);
			delete[] converData;
			return dataLen;
		}


		inline static BITCONVER_EXPORT int32_t bytes( const QVector<char> &data, int16_t *outValue, int32_t index = 0 ) {
			return bytes(data.data(), data.length(), outValue, index);
		}

		inline static BITCONVER_EXPORT int32_t bytes( const QVector<char> &data, int32_t *outValue, int32_t index = 0 ) {
			return bytes(data.data(), data.length(), outValue, index);
		}

		inline static BITCONVER_EXPORT int32_t bytes( const QVector<char> &data, int64_t *outValue, int32_t index = 0 ) {
			return bytes(data.data(), data.length(), outValue, index);
		}

		inline static BITCONVER_EXPORT int32_t bytes( const QVector<char> &data, uint16_t *outValue, int32_t index = 0 ) {
			return bytes(data.data(), data.length(), outValue, index);
		}


		inline static BITCONVER_EXPORT int32_t bytes( const QVector<char> &data, uint32_t *outValue, int32_t index = 0 ) {
			return bytes(data.data(), data.length(), outValue, index);
		}

		inline static BITCONVER_EXPORT int32_t bytes( const QVector<char> &data, uint64_t *outValue, int32_t index = 0 ) {
			return bytes(data.data(), data.length(), outValue, index);
		}


		inline static BITCONVER_EXPORT int32_t bytes( const QVector<char> &data, QString *outValue, int32_t index = 0, int32_t count = 0 ) {
			return bytes(data.data(), data.length(), outValue, index, count);
		}
	};

}

#endif // BITCONVER_H_H_HEAD__FILE__