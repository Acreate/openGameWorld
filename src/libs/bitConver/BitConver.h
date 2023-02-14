#ifndef BITCONVER_H_H_HEAD__FILE__
#define BITCONVER_H_H_HEAD__FILE__
#pragma once

#include "BitConver_export.h"
#include <QSharedPointer>
#include <QVector>

namespace bitConver {
	/// @brief 从对象转换到数据类型
	namespace get {
		inline QSharedPointer<QVector<char> > bytes( const int &value ) {
			QSharedPointer<QVector<char> > result(new QVector<char>(4));
			auto list = result.data();
			const char *ptr = (char *)&value;
			list->operator[](0) = ptr[0];
			list->operator[](1) = ptr[1];
			list->operator[](2) = ptr[2];
			list->operator[](3) = ptr[3];
			return {};
		}

		inline QSharedPointer<QVector<char> > bytes( const QString &value ) {
			return {};
		}

		inline QSharedPointer<QVector<char> > bytes( const short &value ) {
			return {};
		}

		inline QSharedPointer<QVector<char> > bytes( const long &value ) {
			return {};
		}

		inline QSharedPointer<QVector<char> > bytes( const long long &value ) {
			return {};
		}
	}

	/// @brief 从数据转换到类型对象
	namespace set {
		inline bool bytes( const QVector<char> &data, int *outValue, size_t index = 0 ) {
			return false;
		}

		inline bool bytes( const QVector<char> &data, QString *value, size_t index = 0 ) {
			return false;
		}

		inline bool bytes( const QVector<char> &data, short *value, size_t index = 0 ) {
			return false;
		}

		inline bool bytes( const QVector<char> &data, long *value, size_t index = 0 ) {
			return false;
		}

		inline bool bytes( const QVector<char> &data, long long *value, size_t index = 0 ) {
			return false;
		}
	}

}

#endif // BITCONVER_H_H_HEAD__FILE__