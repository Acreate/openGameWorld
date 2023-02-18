#ifndef DATACHECK_H_H_HEAD__FILE__
#define DATACHECK_H_H_HEAD__FILE__
#pragma once
#include <qlist.h>
#include "BitConver.h"
#include "ISerializeNormal.h"

namespace serializeNormal {
	class BITCONVER_EXPORT DataCheck : ISerializeNormal {
	protected:
		/// @brief 指定 data 的大小
		int32_t dataSize;
		/// @brief 对象数据
		QVector<char> data;
		/// @brief sizeof(dataSize)
		static size_t countSize;

	public:
		DataCheck( const DataCheck &other ) {
			this->data.clear();
			this->data.append(other.data);
			this->dataSize = other.dataSize;
		}

		DataCheck operator=( const DataCheck &other ) {
			this->data.clear();
			this->data.append(other.data);
			this->dataSize = other.dataSize;
			return *this;
		}

		DataCheck( ) {
			dataSize = 0;
		}

		/// @brief 使用一段数据初始化对象，该数据应该仅仅是数据，并不附带任何其他信息
		/// 若携带其他信息，请使用 serializeInstance
		/// @param data 转换的数据
		explicit DataCheck( const QVector<char> &data ) {
			dataSize = data.length();
		}


		size_t getSizeTypeSize( ) const {
			return this->countSize;
		}

		int32_t getSize( ) const {
			return dataSize;
		}

		QVector<char> getData( ) const {
			return data;
		}

		size_t resetData( const QVector<char> &dataBytes ) override {
			dataSize = dataBytes.length();
			this->data.clear();
			this->data.append(dataBytes);
			return dataSize;
		}

		size_t resetData( const char *dataBytes, size_t dataSize ) override {
			this->dataSize = dataSize;
			this->data.resize(dataSize);
			char *data = this->data.data();
			for( size_t index = 0; index < dataSize; ++index )
				data[index] = dataBytes[index];
			return this->dataSize;
		}

		/// @brief 对象转换为数据
		/// @return 该数据将会持有一定的附加信息，成功返回 true
		QSharedPointer<QVector<char> > serializeInstance( ) override {
			if( dataSize ) {
				QSharedPointer<QVector<char> > bytes = bitConver::get::bytes(dataSize);
				bytes.data()->resize(countSize + data.length());
				char *pointer = bytes.data()->data();
				char *data = this->data.data();
				for( size_t index = countSize; index < dataSize; ++index )
					pointer[index] = data[index];
				return bytes;
			}
			return {};
		}

		QSharedPointer<QVector<char> > serializeInstance( const char *dataBytes, size_t dataSize, size_t index ) override {
			size_t useCodeCount = bitConver::set::bytes(dataBytes, dataSize, &this->dataSize, index);

			if( this->dataSize <= (dataSize - useCodeCount) ) {
				useCodeCount += index;
				this->data.resize(this->dataSize);
				char *pointer = this->data.data();
				for( size_t orgIndex = 0; orgIndex < this->dataSize; ++orgIndex )
					pointer[orgIndex] = dataBytes[orgIndex + useCodeCount];
				qint64 resultSize = data.length() + useCodeCount - index;
				QSharedPointer<QVector<char> > result(new QVector<char>(resultSize));
				pointer = result.data()->data();
				for( size_t orgIndex = 0; orgIndex < resultSize; ++orgIndex )
					pointer[orgIndex] = dataBytes[orgIndex + index];
				return result;
			}
			return {};
		}

		QSharedPointer<QVector<char> > serializeInstance( const char *dataBytes, size_t dataSize ) override {

			return serializeInstance(dataBytes, dataSize, 0);
		}

		/// @brief 从一段数据中还原对象
		/// @param dataBytes 数据，该数据应该包含持有的附加信息
		/// @return 成功返回 true
		QSharedPointer<QVector<char> > serializeInstance( const QVector<char> &dataBytes ) override {
			const char *bytes = dataBytes.data();
			qsizetype length = dataBytes.length();
			return serializeInstance(bytes, length);
		}

		/// @brief 从一段数据中还原对象
		/// @param dataBytes 数据，该数据应该包含持有的附加信息
		/// @param index 开始下标
		/// @return 成功返回 true
		QSharedPointer<QVector<char> > serializeInstance( const QVector<char> &dataBytes, size_t index ) override {
			return serializeInstance(dataBytes.data(), dataBytes.length(), index);
		}

	};
}


#endif // DATACHECK_H_H_HEAD__FILE__