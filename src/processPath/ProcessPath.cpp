#include "ProcessPath.h"

qsizetype path::info::getPathInfo(const QString& path, QSharedPointer<QVector<QFileInfo>> fileNames, QSharedPointer<QVector<QFileInfo>> dirNames) {
	qsizetype result = 0;
	if( fileNames == nullptr && dirNames == nullptr )
		return result;
	if( fileNames == nullptr ) {
		result = getDirInPath( path, dirNames );
	} else if( dirNames == nullptr ) {
		result = getFilesInPath( path, fileNames );
	} else {
		result = getPathEntry( path, fileNames, dirNames );
	}
	return result;
}

QSharedPointer<QVector<QFileInfo>> path::info::file::getOnPathFileName(const QString& path) {
	QSharedPointer<QVector<QFileInfo>> result( new QVector<QFileInfo> );
	getFilesInPath( path, result );
	return result;
}

QSharedPointer<QVector<QFileInfo>> path::info::file::getInPathFileName(const QString& path) {
	QSharedPointer<QVector<QFileInfo>>
		// 返回的文件
		result( new QVector<QFileInfo> ),
		// 当前工作目录
		dir( new QVector<QFileInfo> ),
		// 目录缓存
		buff( new QVector<QFileInfo> ),
		// 临时交换
		cmp;

	QSharedPointer<QVector<QFileInfo>>
		// 存储目录路径
		subDirNames( new QVector<QFileInfo> );
	while( true ) {
		for( auto itemIterator = dir->begin(), itemIteratorEnd = dir->end(); itemIterator != itemIteratorEnd; ++itemIterator )
			path::info::getPathInfo( itemIterator->absoluteFilePath(), result, buff );
		if( buff->length() == 0 )
			break;
		dir.data()->clear();
		cmp = dir;
		dir = buff;
		buff = cmp;
	}
	return result;
}

QSharedPointer<QVector<QFileInfo>> path::info::dir::getOnPathDirName(const QString& path) {
	QSharedPointer<QVector<QFileInfo>> result( new QVector<QFileInfo> );
	getDirInPath( path, result );
	return result;
}

QSharedPointer<QVector<QFileInfo>> path::info::dir::getInPathDirName(const QString& path) {
	QSharedPointer<QVector<QFileInfo>> result( new QVector<QFileInfo> );
	getDirInPath( path, result );
	return result;
}
