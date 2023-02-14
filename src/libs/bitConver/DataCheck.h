﻿#ifndef DATACHECK_H_H_HEAD__FILE__
#define DATACHECK_H_H_HEAD__FILE__
#pragma once
#include <qlist.h>
#include "BitConver.h"
#include "ISerializeNormal.h"

namespace dataChecks {
	class DataCheck : serializeNormal::ISerializeNormal {
	private:
		/// @brief 指定 data 的大小
		qsizetype dataSize;
		/// @brief 对象数据
		QSharedPointer<QVector<char> > data;
		/// @brief sizeof(dataSize)
		static size_t countSize;

	public:
		DataCheck( ) {
			dataSize = 0;
			data = nullptr;
		}
		/// @brief 使用一段数据初始化对象，该数据应该仅仅是数据，并不附带任何其他信息
		/// 若携带其他信息，请使用 @code ['{' bool serializeInstance( const QVector<char> &dataBytes ) '}'];
		/// @param data 转换的数据
		explicit DataCheck( const QVector<char> &data ) {
			dataSize = data.length();
			if( dataSize > 0 ) {
				QList<char> *list = new QList<char>;
				this->data = QSharedPointer<QVector<char> >(list);
				for( qsizetype index = 0; index < dataSize; ++index )
					list->append(data[index]);
			}

		}
		/// @brief 对象转换为数据
		/// @return 该数据将会持有一定的附加信息，成功返回 true
		QSharedPointer<QVector<char> > serializeInstance( ) override {
			if( dataSize ) {
				QSharedPointer<QVector<char> > bytes = bitConver::get::bytes(dataSize);
				QVector<char> *list = bytes.data();
				QList<char> *data = this->data.data();
				for( qsizetype index = 0; index < dataSize; ++index )
					list->append(data->at(index));
				return bytes;
			}
			return nullptr;
		}

		/// @brief 从一段数据中还原对象
		/// @param dataBytes 数据，该数据应该包含持有的附加信息
		/// @return 成功返回 true
		bool serializeInstance( const QVector<char> &dataBytes ) override {
			if( bitConver::set::bytes(dataBytes, &dataSize) ) {
				QVector<char> *list = new QVector<char>(dataSize);
				this->data = QSharedPointer<QVector<char> >(list);
				for( qsizetype index = 0; index < dataSize; ++index )
					list->operator[](index) = data->at(index);
				return true;
			}
			return false;
		}
	};
}


#endif // DATACHECK_H_H_HEAD__FILE__