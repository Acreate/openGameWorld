#include <ProcessArgs.h>
#include <ProcessPath.h>
#include <TypeFile.h>
#include <TypeText.h>

/// @brief 统计文件大小
/// @param fileNames 文件列表
/// @return 文件大小，单位为 b
size_t statisticsFileSize( const QSharedPointer<QVector<QSharedPointer<QFileInfo> > > fileNames ) {
	size_t result = 0;
	for( auto iterator = fileNames->begin(), end = fileNames->end(); iterator != end; ++iterator )
		result += iterator->data()->size();
	return result;
}

/// @brief 文件夹/文件信息对象
class DirInfo {
	/// @brief 当前信息
	QSharedPointer<QFileInfo> currentFileInfo;

	QSharedPointer<QVector<QSharedPointer<DirInfo> > >
		/// @brief 子级文件夹
		subDirInfos,
		/// @brief 子级文件
		subFileInfos;

public:
	/// @brief 使用引用构建信息
	/// @param current_file_info 引用对象 
	explicit DirInfo( const QSharedPointer<QFileInfo> &current_file_info )
		: currentFileInfo(current_file_info) {}

	/// @brief 使用路径构建信息
	/// @param path 路径
	explicit DirInfo( const QString &path ) {
		currentFileInfo = QSharedPointer<QFileInfo>(new QFileInfo(path));
	}

	/// @brief 是否文件
	/// @return true 表示文件
	bool isFile( ) const {
		return currentFileInfo->isFile();
	}

	/// @brief 获取对象指针
	/// @return 返回对象指针
	const QSharedPointer<QFileInfo> getQFileInfo( ) const {
		return this->currentFileInfo;
	}

	/// @brief 是否文件夹
	/// @return true 表示文件夹
	bool isDir( ) const {
		return currentFileInfo->isDir();
	}

	/// @brief 信息对象是否存在，检查是否被正确初始化，或者文件/目录是否存在
	/// @return false 表示不存在，或无法构建信息系统
	bool exists( ) const {
		if( currentFileInfo == nullptr )
			return false;
		if( !currentFileInfo->exists() )
			return false;
		return true;
	}

	/// @brief 重置子目录信息，方便提取信息
	void resetSubInfo( ) {
		subDirInfos = nullptr;
		subFileInfos = nullptr;
	}

	/// @brief 获取目录的大小
	/// @return 大小
	size_t getSize( ) {
		if( !exists() )
			return 0;
		if( isFile() )
			return currentFileInfo->size();
		size_t treeSize = 0;

		if( subDirInfos == nullptr || subFileInfos == nullptr ) {
			subDirInfos = QSharedPointer<QVector<QSharedPointer<DirInfo> > >(new QVector<QSharedPointer<DirInfo> >);
			subFileInfos = QSharedPointer<QVector<QSharedPointer<DirInfo> > >(new QVector<QSharedPointer<DirInfo> >);
			QSharedPointer<QVector<QSharedPointer<QFileInfo> > >
				fileNames(new QVector<QSharedPointer<QFileInfo> >)
				, dirNames(new QVector<QSharedPointer<QFileInfo> >);
			if( path::info::getPathEntry(currentFileInfo->absoluteFilePath(), fileNames, dirNames) > 0 ) {
				for( auto iterator = fileNames->begin(), end = fileNames->end(); iterator != end; ++iterator ) {
					QSharedPointer<DirInfo> fileInfo = QSharedPointer<DirInfo>(new DirInfo(*iterator));
					subFileInfos->append(fileInfo);
					treeSize += iterator->data()->size();
				}
				for( auto iterator = dirNames->begin(), end = dirNames->end(); iterator != end; ++iterator ) {
					QSharedPointer<DirInfo> dirTreeInfo = QSharedPointer<DirInfo>(new DirInfo(*iterator));
					subDirInfos->append(dirTreeInfo);
					treeSize += dirTreeInfo->getSize();
				}
			}
		} else {
			for( auto iterator = subFileInfos->begin(), end = subFileInfos->end(); iterator != end; ++iterator )
				treeSize += iterator->get()->getSize();
			for( auto iterator = subDirInfos->begin(), end = subDirInfos->end(); iterator != end; ++iterator ) {
				treeSize += iterator->get()->getSize();
			}
		}
		return treeSize;
	}

	/// @brief 更新树节点，该功能将会更新 subDirInfos 与 subFileInfos
	void updateTree( ) {
		if( currentFileInfo == nullptr || currentFileInfo->exists() ) {
			if( currentFileInfo->isFile() ) {
				subDirInfos = nullptr;
				subFileInfos = nullptr;
			} else {
				if( subDirInfos == nullptr || subFileInfos == nullptr ) {
					subDirInfos = QSharedPointer<QVector<QSharedPointer<DirInfo> > >(new QVector<QSharedPointer<DirInfo> >);
					subFileInfos = QSharedPointer<QVector<QSharedPointer<DirInfo> > >(new QVector<QSharedPointer<DirInfo> >);
				} else {
					subDirInfos.data()->clear();
					subFileInfos.data()->clear();
				}
				QSharedPointer<QVector<QSharedPointer<QFileInfo> > >
					fileNames(new QVector<QSharedPointer<QFileInfo> >)
					, dirNames(new QVector<QSharedPointer<QFileInfo> >);
				if( path::info::getPathEntry(currentFileInfo->absoluteFilePath(), fileNames, dirNames) > 0 ) {
					for( auto iterator = fileNames->begin(), end = fileNames->end(); iterator != end; ++iterator )
						subFileInfos->append(QSharedPointer<DirInfo>(new DirInfo(*iterator)));
					for( auto iterator = dirNames->begin(), end = dirNames->end(); iterator != end; ++iterator ) {
						QSharedPointer<DirInfo> dirTreeInfo = QSharedPointer<DirInfo>(new DirInfo(*iterator));
						subDirInfos->append(dirTreeInfo);
						dirTreeInfo->updateTree();
					}
				}
			}
		}
	}

	/// @brief 输出当前路径名，若为文件，末尾不带 QDir::separator()， 否则将会存在 QDir::separator()
	explicit operator QString( ) const {
		if( exists() ) {
			if( isDir() )
				return QDir::separator() + currentFileInfo->fileName() + QDir::separator();
			return QDir::separator() + currentFileInfo->fileName();
		}
		return "";
	}

	QString toQString( ) const {
		if( exists() ) {
			if( isDir() )
				return QDir::separator() + currentFileInfo->fileName() + QDir::separator();
			return QDir::separator() + currentFileInfo->fileName();
		}
		return "";
	}

	QStringList toSubTreeString( ) {
		QStringList result;
		// 检测是否需要更新树结构
		if( subDirInfos == nullptr || subFileInfos == nullptr ) {
			subDirInfos = QSharedPointer<QVector<QSharedPointer<DirInfo> > >(new QVector<QSharedPointer<DirInfo> >);
			subFileInfos = QSharedPointer<QVector<QSharedPointer<DirInfo> > >(new QVector<QSharedPointer<DirInfo> >);
			QSharedPointer<QVector<QSharedPointer<QFileInfo> > >
				fileNames(new QVector<QSharedPointer<QFileInfo> >)
				, dirNames(new QVector<QSharedPointer<QFileInfo> >);
			if( path::info::getPathEntry(currentFileInfo->absoluteFilePath(), fileNames, dirNames) > 0 ) {
				for( auto iterator = fileNames->begin(), end = fileNames->end(); iterator != end; ++iterator ) {
					QSharedPointer<DirInfo> fileInfo = QSharedPointer<DirInfo>(new DirInfo(*iterator));
					subFileInfos->append(fileInfo);
					result.append("\t" + fileInfo->toQString());
				}
				for( auto iterator = dirNames->begin(), end = dirNames->end(); iterator != end; ++iterator ) {
					QSharedPointer<DirInfo> dirTreeInfo = QSharedPointer<DirInfo>(new DirInfo(*iterator));
					subDirInfos->append(dirTreeInfo);
					result.append("\t" + dirTreeInfo->toQString());
					QStringList list = dirTreeInfo->toSubTreeString();
					for( auto listBeg = list.begin(), listEnd = list.end(); listBeg != listEnd; ++listBeg )
						result.append("\t" + *listBeg);
				}
			}
		} else {
			for( auto iterator = subFileInfos->begin(), end = subFileInfos->end(); iterator != end; ++iterator )
				result.append("\t" + iterator->data()->toQString());
			for( auto iterator = subDirInfos->begin(), end = subDirInfos->end(); iterator != end; ++iterator ) {
				result.append("\t" + iterator->data()->toQString());
				QStringList list = iterator->data()->toSubTreeString();
				for( auto listBeg = list.begin(), listEnd = list.end(); listBeg != listEnd; ++listBeg )
					result.append("\t" + *listBeg);
			}
		}
		return result;
	}

	/// @brief 获取树形结构的信息
	/// @return 失败返回空字符串
	QString toTreeString( ) {
		QStringList result;
		if( exists() ) {
			if( isFile() )
				return QDir::separator() + currentFileInfo->fileName();
			result.append(toQString());
			// 检测是否需要更新树结构
			if( subDirInfos == nullptr || subFileInfos == nullptr ) {
				subDirInfos = QSharedPointer<QVector<QSharedPointer<DirInfo> > >(new QVector<QSharedPointer<DirInfo> >);
				subFileInfos = QSharedPointer<QVector<QSharedPointer<DirInfo> > >(new QVector<QSharedPointer<DirInfo> >);
				QSharedPointer<QVector<QSharedPointer<QFileInfo> > >
					fileNames(new QVector<QSharedPointer<QFileInfo> >)
					, dirNames(new QVector<QSharedPointer<QFileInfo> >);
				if( path::info::getPathEntry(currentFileInfo->absoluteFilePath(), fileNames, dirNames) > 0 ) {
					for( auto iterator = fileNames->begin(), end = fileNames->end(); iterator != end; ++iterator ) {
						QSharedPointer<DirInfo> fileInfo = QSharedPointer<DirInfo>(new DirInfo(*iterator));
						subFileInfos->append(fileInfo);
						result.append("\t" + fileInfo->toQString());
					}
					for( auto iterator = dirNames->begin(), end = dirNames->end(); iterator != end; ++iterator ) {
						QSharedPointer<DirInfo> dirTreeInfo = QSharedPointer<DirInfo>(new DirInfo(*iterator));
						subDirInfos->append(dirTreeInfo);
						result.append("\t" + dirTreeInfo->toQString());
						QStringList list = dirTreeInfo->toSubTreeString();
						for( auto listBeg = list.begin(), listEnd = list.end(); listBeg != listEnd; ++listBeg ) {
							result.append("\t" + *listBeg);
						}
					}
				}
			} else {
				for( auto iterator = subFileInfos->begin(), end = subFileInfos->end(); iterator != end; ++iterator )
					result.append("\t" + iterator->data()->toQString());
				for( auto iterator = subDirInfos->begin(), end = subDirInfos->end(); iterator != end; ++iterator ) {
					result.append("\t" + iterator->data()->toQString());
					QStringList list = iterator->data()->toSubTreeString();
					for( auto listBeg = list.begin(), listEnd = list.end(); listBeg != listEnd; ++listBeg )
						result.append("\t" + *listBeg);
				}
			}
		}
		return result.join("\n");
	}

};

int main( int argc, char *argv[] ) {
	ProcessArgs app(argc, argv);

	auto appArg = app.getArgOptions();
	QList<QString> list = appArg[""];
	QString currentWorkPath;
	if( list.length() == 1 )
		currentWorkPath = path::App::getWorkPath();
	else
		currentWorkPath = list[1];

	QString writePath;
	QFileInfo info(currentWorkPath);
	// 如果是文件，则检查对应的写入文件
	if( info.isDir() )
		writePath = info.absoluteFilePath() + QDir::separator() + "读我获取所有文件名.txt";
	else {
		writePath = info.absolutePath() + QDir::separator() + "读我获取所有文件名.txt";
		QString absoluteFilePath = info.absoluteFilePath();
		info.setFile(writePath);
		writePath = info.absoluteFilePath();
		// 存在对应的文件，则直接退出程序
		if( absoluteFilePath == writePath )
			return -1;
	}
	DirInfo dirInfo(currentWorkPath);
	size_t size = dirInfo.getSize();
	size_t kb = size / 1024;
	size_t mb = kb / 1024;
	size_t gb = mb / 1024;
	size_t tb = gb / 1024;

	size_t modSize = size % 1024;
	size_t modKb = kb % 1024;
	size_t modMb = mb % 1024;
	size_t modGb = gb % 1024;
	size_t modTb = tb % 1024;


	dirInfo.updateTree();
	list.clear();
	list << "============";
	list << QString("统计大小 : %1 TB %2 GB %3 MB %4 KB %5 B").arg(modTb).arg(modGb).arg(modMb).arg(modKb).arg(modSize);
	list << "============";
	list << "单位统计，每个单位独立统计整个路径的占用存储 : ";
	list << QString("\t%1 TB").arg(tb);
	list << QString("\t%1 GB").arg(gb);
	list << QString("\t%1 MB").arg(mb);
	list << QString("\t%1 KB").arg(kb);
	list << QString("\t%1 B").arg(size);
	QString chars = list.join("\n");
	list.clear();
	list << chars;
	list << "============";
	list << dirInfo.toTreeString();
	list << chars;
	list << "============";
	auto textInstance = typeFile::generate::file::textInstance(writePath);
	qsizetype writeContents = textInstance->writeContents(list.join("\n"));
	return 0;
}