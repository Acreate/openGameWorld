#include <iostream>
#include <ProcessArgs.h>
#include <ProcessPath.h>
#include <QFile>

int main(int argc, char* argv[]) {
	ProcessArgs appProcess( argc, argv );
	auto argOptions = appProcess.getArgOptions();
	auto iterator = argOptions.begin();
	const auto& end = argOptions.end();

	QString
		// 源路径
		sourcePath = path::App::getWorkPath(),
		// 目标路径
		desPath = path::App::getWorkPath();
	// 操作的文件类型
	QVector<QString> fileType;
	// 是否进入子文件夹
	bool isToInSubDir = false;
	// 是否拷贝
	bool isCopy = false;
	// 最大选项
	qsizetype maxOption = 4;
	for( size_t parCount = 0; iterator != end && parCount < maxOption; ++iterator ) {
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
				fileType.append( tOptionParam[index].mid( 1 ) );
			// 文件类型
			++parCount;
		} else if( iterator.key() == "c" ) {
			isCopy = true;
			++parCount;
		}
	}

	QSharedPointer<QVector<QFileInfo>>
		// 存储文件路径
		files( new QVector<QFileInfo> ),
		// 存储目录路径
		dirNames( new QVector<QFileInfo> );

	// 获取文件与目录
	path::info::getPathInfo( sourcePath, nullptr, dirNames );
	if( dirNames->length() > 0 ) {
		QSharedPointer<QVector<QFileInfo>>
			// 存储文件路径
			subFiles( new QVector<QFileInfo> ),
			// 存储目录路径
			subDirNames( new QVector<QFileInfo> );
		// 查找目录
		QVector<QFileInfo> buffDirNames( *dirNames );
		do {
			for( auto itemIterator = buffDirNames.begin(), itemIteratorEnd = buffDirNames.end(); itemIterator != itemIteratorEnd; ++itemIterator )
				path::info::getPathInfo( itemIterator->absoluteFilePath(), subFiles, subDirNames );
			for( auto itemIterator = subFiles->begin(), itemIteratorEnd = subFiles->end(); itemIterator != itemIteratorEnd; ++itemIterator )
				files->append( *itemIterator );
			buffDirNames.clear();
			for( auto itemIterator = subDirNames->begin(), itemIteratorEnd = subDirNames->end(); itemIterator != itemIteratorEnd; ++itemIterator ) {
				dirNames->append( *itemIterator );
				buffDirNames.append( *itemIterator );
			}
			if( buffDirNames.length() == 0 )
				break;
			subFiles.data()->clear();
			subDirNames.data()->clear();
		} while( isToInSubDir ) ;
	}

	// 输出文件
	std::cout << QString( "文件 : " ).toLocal8Bit().data() << std::endl;

	qint64 length = files->length();
	if( length > 0 ) {
		qsizetype typeLen = fileType.length(), index = 0;
		QSharedPointer<QVector<QFileInfo>>
			// 临时存储文件路径
			buffFiles( new QVector<QFileInfo> );
		if( typeLen ) {
			for( auto itemIterator = files->begin(), itemIteratorEnd = files->end(); itemIterator != itemIteratorEnd; ++itemIterator ) {
				// 匹配尾缀
				QString suffix = itemIterator->suffix();
				for( index = 0; index < typeLen; ++index )
					if( suffix == fileType[index] ) {
						buffFiles->append( *itemIterator );
						break;
					}
			}
		} else
			for( auto itemIterator = files->begin(), itemIteratorEnd = files->end(); itemIterator != itemIteratorEnd; ++itemIterator )
				buffFiles->append( *itemIterator );
		// 设置目标
		desPath = desPath.append( QDir::separator() );
		for( index = 0, typeLen = buffFiles->length(); index < typeLen; ++index ) {
			QFileInfo currentWorkFileName = buffFiles->at( index );
			QString newName = desPath + currentWorkFileName.fileName();
			QString oldName = currentWorkFileName.absoluteFilePath();
			if( !isCopy && QFile::rename( oldName, newName ) )
				std::cout << currentWorkFileName.fileName().toLocal8Bit().data() << std::endl;
			else if( QFile::copy( oldName, newName ) )
				std::cout << currentWorkFileName.fileName().toLocal8Bit().data() << std::endl;
		}
	}
	std::cout << QString( "目录 : " ).toLocal8Bit().data() << std::endl;
	if( dirNames )
		for( auto itemIterator = dirNames->begin(), itemIteratorEnd = dirNames->end(); itemIterator != itemIteratorEnd; ++itemIterator )
			std::cout << QString( "\t" ).toLocal8Bit().data() << itemIterator->absoluteFilePath().toLocal8Bit().data() << std::endl;
	std::cout << std::endl;
	return 0;
}
