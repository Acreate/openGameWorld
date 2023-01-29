#ifndef TYPEFILE_H
#define TYPEFILE_H
#include <QDir>
#include <qfile.h>
#include <QSharedPointer>
#include <QString>
#include "typeFile_export.h"

class TYPEFILE_EXPORT TypeFile {
public:
	TypeFile();
	virtual ~TypeFile();

	/// @brief 文本类型
	class TYPEFILE_EXPORT Text {
		/// @brief 文件操作对象实例
		QFile fileInstance;
		/// @brief 文件状态，0 为空状态
		int openStatis = 0;
		/// @brief 文件路径
		QString filePath;
		/// @brief 文件夹
		QDir fileInDir;

	private:
		/// @brief 是否能打开文件，该操作会尝试打开文件
		/// @return 失败返回 false
		inline bool isCanOpen() {
			return this->openStatis > 0 || openTextFile();
		}

	public:
		explicit Text(const QString& filePath)
			: fileInstance( filePath ), filePath( filePath ), fileInDir( filePath ) {
		}

		/// @brief 尝试打开文件
		/// @return 失败返回 false
		bool openTextFile();

		/// @brief 读取文件内容
		/// @param size 读取数量
		/// @return 末尾返回空
		QString readTextContents(const uint64_t& size = 1024);
		/// @brief 往文件写入内容
		/// @param strContent 写入的内容
		/// @param writeCount 写入个数，小于 1 为一次性全部写入
		/// @return 写入个数
		qsizetype writeTextContents(const QString& strContent, const qsizetype& writeCount = 0);

		/// @brief 设置当前文件的读取下标位置
		/// @param index 下标位置
		/// @return 设置好的下标位置
		qsizetype setTextPointIndex(const qsizetype& index) {
			if( isCanOpen() ) {
				fileInstance.seek( index );
				return fileInstance.pos();
			}
			return 0;
		}

		/// @brief 在原有的下标位置下增量读取下标位置
		/// @param len 增量
		/// @return 当前下标位置
		qsizetype addTextPointIndex(const qsizetype& len) {
			if( isCanOpen() ) {
				fileInstance.seek( len + fileInstance.pos() );
				return fileInstance.pos();
			}
			return 0;
		}

		/// @brief 获取文件大小
		/// @return 文件的大小
		qsizetype getTextSize() {
			if( isCanOpen() )
				return fileInstance.size();
			return 0;
		}

		/// @brief 参数文件，不存在则会删除失败
		/// @return true 表示删除成功，否则失败
		bool reamove() {
			if( fileInDir.exists() && !isCanOpen() )
				return false;
			bool fileStatisResult = fileInstance.remove();
			fileInstance.close();
			openStatis = 0;
			return fileStatisResult;
		}

		/// @brief 重命名文件，不存在文件则失败
		/// @param newName 新的文件名
		/// @return 成功返回 true
		bool reNameFile(const QString& newName) {
			if( fileInDir.exists() && !isCanOpen() )
				return false;
			bool fileStatisResult = fileInstance.rename( newName );
			return fileStatisResult;
		}

		/// @brief 关闭文件
		void closeTextFile() {
			if( fileInstance.isOpen() ) {
				fileInstance.close();
				openStatis = 0;
			}
		}

		virtual ~Text() {
			closeTextFile();
		}
	};

	/// @brief 尝试使用文本格式
	/// @return 文本类型操作对象
	QSharedPointer<Text> getTextInstance(const QString& fileExisPath);

	class TYPEFILE_EXPORT Xml {
	};
};

#endif // TYPEFILE_H
