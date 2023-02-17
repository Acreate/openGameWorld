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
		qsizetype dataSize;
		/// @brief 对象数据
		QSharedPointer<QVector<char> > data;
		/// @brief sizeof(dataSize)
		static size_t countSize;

	public:
		DataCheck( ) {
			dataSize = 0;
			data = QSharedPointer<QVector<char> >(new QList<char>());
		}

		/// @brief 使用一段数据初始化对象，该数据应该仅仅是数据，并不附带任何其他信息
		/// 若携带其他信息，请使用 serializeInstance
		/// @param data 转换的数据
		explicit DataCheck( const QVector<char> &data ) {
			dataSize = data.length();
			this->data = QSharedPointer<QVector<char> >(new QList<char>(data));
		}

		/// @brief 对象转换为数据
		/// @return 该数据将会持有一定的附加信息，成功返回 true
		QSharedPointer<QVector<char> > serializeInstance( ) override {
			if( dataSize ) {
				QSharedPointer<QVector<char> > bytes = bitConver::get::bytes(dataSize);
				QVector<char> *list = bytes.data();
				char *data = this->data->data();
				for( size_t index = 0; index < dataSize; ++index )
					list->append(data[index]);
				return bytes;
			}
			return nullptr;
		}

		size_t serializeInstance( const char *dataBytes, size_t dataSize ) override {
			size_t useCodeCount = bitConver::set::bytes(dataBytes, dataSize, &this->dataSize);
			if( this->dataSize <= (dataSize - useCodeCount) ) {
				data.clear();
				for( size_t index = useCodeCount; index < this->dataSize; ++index )
					data->append(dataBytes[index]);
			}

			return 0;
		}

		/// @brief 从一段数据中还原对象
		/// @param dataBytes 数据，该数据应该包含持有的附加信息
		/// @return 成功返回 true
		size_t serializeInstance( const QVector<char> &dataBytes ) override {
			size_t useCodeCount = bitConver::set::bytes(dataBytes, &this->dataSize);
			qsizetype length = dataBytes.length();
			if( this->dataSize <= (length - useCodeCount) ) {
				QVector<char> *list = new QVector<char>(dataSize);
				this->data.clear();
				size_t index = 0;
				char *pointer = list->data();
				for( ; index < length; ++index )
					pointer[index] = data->at(index);
				return index;
			}
			return 0;
		}
	};
}


#endif // DATACHECK_H_H_HEAD__FILE__