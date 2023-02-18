#ifndef NODE_H_H_HEAD__FILE__
#define NODE_H_H_HEAD__FILE__
#pragma once


#include "DataCheck.h"
#include "qDebug.h"

namespace serializeNormal {

	template< class lDataCheck, class rDataCheck >
	class BITCONVER_EXPORT Node : public DataCheck {
	private:
		/// @brief 新的类型需要重新实现特例化
		Node( ) = default;
		~Node( ) override { }
	};

	template< >
	class BITCONVER_EXPORT Node<DataCheck, DataCheck> : public DataCheck {
	public:
		class BITCONVER_EXPORT Propertys {
			QSharedPointer<DataCheck> left;
			QSharedPointer<DataCheck> right;

		public:
			friend class Node<DataCheck, DataCheck>;
			virtual ~Propertys( ) { }

			explicit Propertys( const QSharedPointer<DataCheck> left, const QSharedPointer<DataCheck> right ) {
				if( left )
					this->left = left;
				else
					this->left = QSharedPointer<DataCheck>(new DataCheck);
				if( right )
					this->right = right;
				else
					this->right = QSharedPointer<DataCheck>(new DataCheck);
			}

		protected:
			/// @brief 从数据中获取一个 Propertys 对象
			/// @param data 数据
			/// @param dataLen 数据长度
			/// @param outValue 获取到的 Propertys 对象，若是失败，则为 nullptr
			/// @param startIndex 获取的开始下标
			/// @return 成功返回非 nullptr
			virtual size_t generatePropertys( const char *data, size_t dataLen, Propertys *outValue, size_t startIndex = 0 ) {
				return 0;
			}
		};

	protected:
		/// @brief 节点名称
		QString name;
		QVector<Propertys> subChilder;

	public:
		/// @brief 追加一个成员到子节点当中
		void append( const QSharedPointer<DataCheck> left, const QSharedPointer<DataCheck> right ) {
			subChilder.append(Propertys(left, right));
			dataSize += 1;
		}

		explicit Node( ) : DataCheck() { }

		explicit Node( const QString &name )
			: name(name), DataCheck() {}

		QSharedPointer<QVector<char> > serializeInstance( ) override {

			// 名称字节码
			QSharedPointer<QVector<char> > bytes;

			QSharedPointer<QVector<char> > nameCharVector = bitConver::get::bytes(name);
			// 名称消费长度
			bytes->append(*bitConver::get::bytes(nameCharVector->length()));
			// 追加名称
			bytes->append(*nameCharVector);
			// 追加子节点个数
			bytes->append(*bitConver::get::bytes(this->dataSize));
			if( dataSize )
				for( decltype(dataSize) index = 0; index < dataSize; ++index ) {
					QVector<Propertys>::Type propertys = subChilder[index];
					bytes->append(*propertys.left->serializeInstance());
					bytes->append(*propertys.right->serializeInstance());
				}
			// 已经确定的字节码长度
			QSharedPointer<QVector<char> > targetBitys = bitConver::get::bytes(bytes->length());
			// 追加整个字节码
			targetBitys.data()->append(*bytes);
			// 返回整个序列化
			return targetBitys;
		}

		QSharedPointer<QVector<char> > serializeInstance( const char *dataBytes, size_t dataSize ) override {
			return serializeInstance(dataBytes, dataSize, 0);
		}

		QSharedPointer<QVector<char> > serializeInstance( const char *dataBytes, size_t dataSize, size_t index ) override {
			// 获取已经确定的字节码长度
			int32_t instanceLen = 0;
			int32_t useCodeCount = bitConver::set::bytes(dataBytes, dataSize, &instanceLen, index);
			// 数据不和规则则退出
			if( useCodeCount == 0 || instanceLen == 0 || instanceLen > dataSize )
				return {};
			useCodeCount += index;
			// 获取名称长度
			int32_t nameLen = 0;
			useCodeCount += bitConver::set::bytes(dataBytes, dataSize, &nameLen, useCodeCount);
			// 获取名称
			useCodeCount += bitConver::set::bytes(dataBytes, dataSize, &this->name, useCodeCount, nameLen);
			// 获取子对象大小
			useCodeCount += bitConver::set::bytes(dataBytes, dataSize, &this->dataSize, useCodeCount);
			if( this->dataSize ) {
				decltype(useCodeCount) buffCount = useCodeCount;
				subChilder.clear();
				for( int32_t orgIndex = 0; orgIndex < this->dataSize; ++orgIndex ) {
					QSharedPointer<DataCheck> left(new DataCheck);
					DataCheck *dataCheck = left.data();
					QSharedPointer<QVector<char> > list = dataCheck->serializeInstance(dataBytes, dataSize, useCodeCount);
					buffCount += list->length();
					if( buffCount == useCodeCount )
						break;
					useCodeCount = buffCount;
					QSharedPointer<DataCheck> right(new DataCheck);
					dataCheck = right.data();
					list = dataCheck->serializeInstance(dataBytes, dataSize, useCodeCount);
					buffCount += list->length();
					if( buffCount == useCodeCount )
						break;
					useCodeCount = buffCount;
					subChilder.append(Propertys(left, right));
				}
			}
			if( this->dataSize != subChilder.length() ) {
				this->dataSize = 0;
				subChilder.clear();
				return {};
			}
			QSharedPointer<QVector<char> > result(new QVector<char>(useCodeCount));
			char *pointer = result.data()->data();
			for( int32_t orgIndex = 0; orgIndex < useCodeCount; ++orgIndex )
				pointer[orgIndex] = dataBytes[orgIndex];
			return result;
		}

		QSharedPointer<QVector<char> > serializeInstance( const QVector<char> &dataBytes ) override {
			return serializeInstance(dataBytes.data(), dataBytes.length(), 0);
		}

		QSharedPointer<QVector<char> > serializeInstance( const QVector<char> &dataBytes, size_t index ) override {
			return serializeInstance(dataBytes.data(), dataBytes.length(), index);
		}

		~Node( ) override { }

	};

}

#endif // NODE_H_H_HEAD__FILE__