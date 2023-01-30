#ifndef TYPEFILE_H
#define TYPEFILE_H
#include <mutex>
#include <QDir>
#include <qfile.h>
#include <QSharedPointer>
#include <QString>
#include "typeFile_export.h"

/// @brief 类型操作对象名称空间
namespace typeFile {
	class TYPEFILE_EXPORT Base;
	class TYPEFILE_EXPORT Text;
	class TYPEFILE_EXPORT TextBuff;
	class TYPEFILE_EXPORT Xml;
	class TYPEFILE_EXPORT XmlBuff;

	/// @brief 类型操作对象生成名称空间
	namespace generate {
		/// @brief 尝试使用文本格式生成操作对象
		/// @param fileExisPath 文件路径
		/// @return 文本类型操作对象
		TYPEFILE_EXPORT QSharedPointer<Text> textInstance(const QString& fileExisPath);

		/// @brief 尝试使用xml格式生成操作对象
		/// @param fileExisPath 文件路径
		/// @return Xml类型操作对象
		TYPEFILE_EXPORT QSharedPointer<Xml> xmlInstance(const QString& fileExisPath);
	}
}

#endif // TYPEFILE_H
