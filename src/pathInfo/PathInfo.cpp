#include "PathInfo.h"
#include <ProcessArgs.h>
#include <ProcessPath.h>

/// @brief 统计文件大小
/// @param fileNames 文件列表
/// @return 文件大小，单位为 b
size_t statisticsFileSize( const QSharedPointer<QVector<QSharedPointer<QFileInfo> > > fileNames ) {
	size_t result = 0;
	for( auto iterator = fileNames->begin(), end = fileNames->end(); iterator != end; ++iterator )
		result += iterator->data()->size();
	return result;
}

class DirInfo {
	QSharedPointer<QFileInfo> currentFileInfo;
	QSharedPointer<QVector<QSharedPointer<QFileInfo> > > subFileInfo;

public:
	explicit DirInfo( const QSharedPointer<QFileInfo> &current_file_info )
		: currentFileInfo(current_file_info) {}
};

int main( int argc, char *argv[] ) {
	ProcessArgs app(argc, argv);

	auto appArg = app.getArgOptions();
	QSharedPointer<QVector<QSharedPointer<QFileInfo> > > fileNames(new QVector<QSharedPointer<QFileInfo> >),
		dirNames(new QVector<QSharedPointer<QFileInfo> >);
	QList<QString> list = appArg[""];
	QString currentWorkPath;
	if( list.length() == 1 )
		currentWorkPath = path::App::getWorkPath();
	else
		currentWorkPath = list[1];

	path::info::getPathEntry(currentWorkPath, fileNames, dirNames);
	auto statistics_file_size = statisticsFileSize(fileNames);
	if( dirNames->length() > 0 ) {
		// 开始遍历子目录

	}
	return 0;
}