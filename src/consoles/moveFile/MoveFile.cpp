/******
 * 2023.02.16.21.56.24 : 修复移动工具的已知bug(上级相同目录不做功的情况)
 */

#include <iostream>
#include <ProcessArgs.h>
#include <ProcessPath.h>
#include <QFile>
#include <QTime>
#include <QThreadPool>

void debugOutQFileInfo( const QSharedPointer<QVector<QFileInfo> > fileInfos ) {
	QDateTime currentTime = QDateTime::currentDateTime();
	qDebug() << ">>>>>>>>>>>>>" << currentTime.toString("yyyy-MM-dd hh:mm:ss");
	for( auto &fileInfo : *fileInfos.data() )
		qDebug() << fileInfo.absoluteFilePath();
	auto milliseconds = QDateTime::currentDateTime() - currentTime;
	qDebug() << milliseconds.count() << "<<<<<<<<<<<<";
}

class FileContrnRunnable : public QRunnable {
	QString oldName, newName;
	bool isCopy;

public:
	FileContrnRunnable( const QString &oldName, const QString &newName, const bool isCopy ) : QRunnable(),
		oldName(oldName),
		newName(newName),
		isCopy(isCopy) { }

	void run( ) override;

	~FileContrnRunnable( ) override = default;
};

void FileContrnRunnable::run( ) {
	if( !isCopy ) {
		bool isRename = QFile::rename(oldName, newName);
		if( isRename )
			std::cout << oldName.toLocal8Bit().data() << std::endl;
	} else if( QFile::copy(oldName, newName) )
		std::cout << oldName.toLocal8Bit().data() << std::endl;
}

class App : public ProcessArgs, public QCoreApplication {
public:
	App( int &argc, char **argv )
		: ProcessArgs(argc, argv), QCoreApplication(argc, argv) {}
};

/// @brief 把 oldPath 下的所有文件与目录移动到 newPath 当中，当 newPtah 当中出现重叠文件内容时，返回 false
/// @param oldPath 旧的路径
/// @param newPath 新的路径
/// @return 成功返回 true
bool moveDirContentToPath( QString oldPath, QString newPath ) {
	QDir oldInfo(oldPath), newInfo(newPath);
	{
		oldPath = oldInfo.absolutePath();
		newPath = newInfo.absolutePath();
		QFileInfoList oldFileInfoList = oldInfo.entryInfoList(QDir::AllDirs | QDir::AllEntries | QDir::NoDotAndDotDot);
		qsizetype oldPathNameCount = oldFileInfoList.length();
		if( oldPathNameCount != 0 ) {
			QDir changeDir;
			QFileInfoList existsFileInfoList = newInfo.entryInfoList(QDir::AllDirs | QDir::AllEntries | QDir::NoDotAndDotDot);
			QMap<QString, QString> changeMap;
			qsizetype existsPathNameCount = existsFileInfoList.length();
			qsizetype oldIndex = 0;
			if( existsPathNameCount > 0 ) {
				qsizetype newIndex = 0;
				QString oldBaseName = oldInfo.dirName().remove(oldPath);
				for( oldIndex = 0; oldIndex < oldPathNameCount; ++oldIndex ) {
					QFileInfo oldFileInfo = oldFileInfoList[oldIndex];
					QString oldName = oldFileInfo.fileName();
					for( newIndex = 0; newIndex < existsPathNameCount; ++newIndex ) {
						QFileInfo existsFileInfo = existsFileInfoList[newIndex];
						QString existsName = existsFileInfo.fileName();
						if( oldBaseName != existsName && existsName == oldName ) {
							// todo:若一方为文件夹与文件的相对存在？
							return false;
						}
					}
					QString orgPath = oldFileInfo.absoluteFilePath(),
						movePath = oldFileInfo.absoluteFilePath().replace(oldPath, newPath);
					changeMap.insert(orgPath, movePath);
				}
				QMap<QString, QString>::iterator
					iterator = changeMap.begin(),
					end = changeMap.end();
				QFileInfo changeFileInfo;
				for( ; iterator != end; ++iterator ) {
					QString orgPath = iterator.key();
					QString targetPath = iterator.value();
					changeFileInfo.setFile(orgPath);
					if( changeFileInfo.isFile() ) {
						QFile::rename(orgPath, targetPath);
					} else if( changeFileInfo.isDir() ) {
						changeDir.rename(orgPath, targetPath);
					}
				}

			} else {
				QFileInfo changeFileInfo;
				for( oldIndex = 0; oldIndex < oldPathNameCount; ++oldIndex ) {
					QFileInfo oldFileInfo = oldFileInfoList[oldIndex];
					QString orgPath = oldFileInfo.absoluteFilePath(),
						targetPath = oldFileInfo.absoluteFilePath().replace(oldPath, newPath);
					changeFileInfo.setFile(orgPath);
					if( changeFileInfo.isFile() ) {
						QFile::rename(orgPath, targetPath);
					} else if( changeFileInfo.isDir() ) {
						changeDir.rename(orgPath, targetPath);
					}
				}
			}
		} else
			return false;

	}

	bool remove = oldInfo.removeRecursively();
	return remove;
}


int main( int argc, char *argv[] ) {
	App appProcess(argc, argv);
	auto argOptions = appProcess.getArgOptions();
	auto iterator = argOptions.begin();
	const auto &end = argOptions.end();

	QString
		// 源路径
		sourcePath,
		// 目标路径
		desPath;
	// 操作的文件类型
	QVector<QString> fileType;
	// 是否进入子文件夹
	bool isToInSubDir = false;
	// 是否拷贝
	bool isCopy = false;
	int maxThreadCount = 8;
	// 最大选项
	size_t maxOption = 6;
	for( size_t parCount = 0; iterator != end && (parCount < maxOption); ++iterator ) {
		if( iterator.key() == "d" ) {
			// 目标目录
			desPath = iterator.value()[0];
			++parCount;
		} else if( iterator.key() == "s" ) {
			// 源目录
			sourcePath = iterator.value()[0];
			++parCount;
		} else if( iterator.key() == "i" ) {
			// 是否递归
			isToInSubDir = true;
			++parCount;
		} else if( iterator.key() == "t" ) {
			auto tOptionParam = iterator.value();
			qsizetype length = tOptionParam.length(), index = 0;
			for( ; index < length; ++index )
				fileType.append(tOptionParam[index].mid(1));
			// 文件类型
			++parCount;
		} else if( iterator.key() == "c" ) {
			isCopy = true;
			++parCount;
		} else if( iterator.key() == "w" ) {
			bool isOk = false;
			int converInt = iterator.value()[0].toInt(&isOk);
			if( isOk )
				maxThreadCount = converInt;
			++parCount;
		}
	}
	if( sourcePath.isEmpty() )
		sourcePath = path::App::getWorkPath();
	if( desPath.isEmpty() )
		desPath = sourcePath;
	// 存储目录路径
	QSharedPointer<QVector<QSharedPointer<QFileInfo> > > dirsInCurrentPathNames(new QVector<QSharedPointer<QFileInfo> >);

	// 获取文件与目录
	path::info::getPathInfo(sourcePath, nullptr, dirsInCurrentPathNames);
	if( dirsInCurrentPathNames->length() > 0 ) {
		// 存储文件路径
		QSharedPointer<QVector<QSharedPointer<QFileInfo> > > filesInCurrentPathNames(new QVector<QSharedPointer<QFileInfo> >);
		if( isToInSubDir ) {
			// 对所有文件进行操作
			// 发现需要把所有包含的文件操作到当前目录中

			QSharedPointer<QVector<QSharedPointer<QFileInfo> > >
				// 存储文件路径
				subFiles(new QVector<QSharedPointer<QFileInfo> >),
				// 存储目录路径
				subDirNames(new QVector<QSharedPointer<QFileInfo> >);
			// 查找目录
			QVector<QSharedPointer<QFileInfo> > buffDirNames(*dirsInCurrentPathNames.data());
			do {
				for( auto itemIterator = buffDirNames.begin(), itemIteratorEnd = buffDirNames.end(); itemIterator !=
				     itemIteratorEnd; ++itemIterator )
					path::info::getPathInfo(itemIterator->data()->absoluteFilePath(), subFiles, subDirNames);
				for( auto itemIterator = subFiles->begin(), itemIteratorEnd = subFiles->end(); itemIterator !=
				     itemIteratorEnd; ++itemIterator )
					filesInCurrentPathNames->append(*itemIterator);
				buffDirNames.clear();
				for( auto itemIterator = subDirNames->begin(), itemIteratorEnd = subDirNames->end(); itemIterator !=
				     itemIteratorEnd; ++itemIterator ) {
					dirsInCurrentPathNames->append(*itemIterator);
					buffDirNames.append(*itemIterator);
				}
				if( buffDirNames.length() == 0 )
					break;
				subFiles.data()->clear();
				subDirNames.data()->clear();
			} while( true ) ;
		} else {
			// 移动的目录
			QSharedPointer<QVector<QSharedPointer<QFileInfo> > > buffDirNames(new QVector<QSharedPointer<QFileInfo> >);
			// 发现只需要吧子级文件与子级目录移动到当前目录中
			for( auto iter = dirsInCurrentPathNames->begin(), iterEnd = dirsInCurrentPathNames->end(); iter != iterEnd;
			     ++iter )
				path::info::getPathInfo(iter->data()->absoluteFilePath(), filesInCurrentPathNames, buffDirNames);
			QDir qdir;
			auto savePath = desPath + QDir::separator();
			for( auto iter = buffDirNames->begin(), iterEnd = buffDirNames->end(); iter != iterEnd; ++iter ) {
				QString oldName = iter->data()->absoluteFilePath();
				QString newName = savePath + iter->data()->fileName();
				if( QFile::exists(newName) ) {
					if( moveDirContentToPath(oldName, newName) )
						std::cout << oldName.toLocal8Bit().data() << std::endl;
				} else {
					bool isDirReName = qdir.rename(oldName, newName);
					if( isDirReName )
						std::cout << oldName.toLocal8Bit().data() << std::endl;
				}

			}
			dirsInCurrentPathNames.clear();
			dirsInCurrentPathNames = buffDirNames;
		}
		qint64 length = filesInCurrentPathNames->length();
		if( length > 0 ) {
			qsizetype typeLen = fileType.length(), index = 0;
			QSharedPointer<QVector<QSharedPointer<QFileInfo> > >
				// 临时存储文件路径
				buffFiles(new QVector<QSharedPointer<QFileInfo> >);
			if( typeLen ) {
				for( auto itemIterator = filesInCurrentPathNames->begin(), itemIteratorEnd = filesInCurrentPathNames->
						     end(); itemIterator != itemIteratorEnd; ++itemIterator ) {
					// 匹配尾缀
					QString suffix = itemIterator->data()->suffix();
					for( index = 0; index < typeLen; ++index )
						if( suffix == fileType[index] ) {
							buffFiles->append(*itemIterator);
							break;
						}
				}
			} else
				for( auto itemIterator = filesInCurrentPathNames->begin(), itemIteratorEnd = filesInCurrentPathNames->
						     end(); itemIterator != itemIteratorEnd; ++itemIterator )
					buffFiles->append(*itemIterator);
			// 设置目标
			desPath = desPath.append(QDir::separator());
			// 线程池
			QThreadPool threadPool;
			// 设置线程池线程工作数量
			threadPool.setMaxThreadCount(maxThreadCount);
			for( index = 0, typeLen = buffFiles->length(); index < typeLen; ++index ) {
				auto currentWorkFileName = buffFiles.data()->at(index);
				QString newName = desPath + currentWorkFileName->fileName();
				QString oldName = currentWorkFileName->absoluteFilePath();
				threadPool.start(new FileContrnRunnable(oldName, newName, isCopy));
			}
			threadPool.waitForDone();
		}

		// 输出文件
		std::cout << QString("文件 : ").toLocal8Bit().data() << std::endl;
	}
	std::cout << QString("目录 : ").toLocal8Bit().data() << std::endl;
	if( dirsInCurrentPathNames )
		for( auto itemIterator = dirsInCurrentPathNames->begin(), itemIteratorEnd = dirsInCurrentPathNames->end();
		     itemIterator != itemIteratorEnd; ++itemIterator )
			std::cout << QString("\t").toLocal8Bit().data() << itemIterator->data()->absoluteFilePath().toLocal8Bit().data() <<
				std::endl;
	std::cout << std::endl;
	return 0;
}