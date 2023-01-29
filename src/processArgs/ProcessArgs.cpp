#include "ProcessArgs.h"
#include <stdlib.h>
#include <mutex>
#include <thread>
#include <qDebug>
#include <vector>
/// @brief 进程参数
QMap<QString, QVector<QString>> ProcessArgs::processArgs;
/// @brief 进程环境变量
QMap<QString, QVector<QString>> ProcessArgs::processEnvs;
/// @brief 定义是否被初始化
static bool isInitVal = false;
#ifdef _WIN32
static QString envSep = ";";
#else
	static QString envSep = ":";
#endif

/// @brief 把运行参数填充到映射当中
/// @param argc 指针参数列表个数
/// @param argv 指针列表对象
/// @param args 填充对象
static void fullProcessArgs(int argc, char* argv[], QMap<QString, QVector<QString>>& args) {
	// 复原参数
	QString arg, optionName;
	QVector<QString> params;
	const QString sep = "-";
	const size_t sepLen = sep.length();
	for( int index = 1; index < argc; ) {
		arg = argv[index];
		if( arg.startsWith( sep ) ) {
			// 发现是间隔符
			optionName = arg.mid( sepLen );
			QMap<QString, QList<QString>>::iterator resultParams = args.find( optionName );
			if( resultParams == args.end() )
				resultParams = args.insert( optionName, params );
			for( index += 1; index < argc; ++index ) {
				arg = argv[index];
				//  -p abc -d ggt -t.cpp.h
				if( arg.startsWith( sep ) )
					break;
				resultParams.value().append( arg );
			}
		} else
			++index;
	}
}

/// @brief 环境变量填充函数
/// @param args 填充对象
static void fullEnv(QMap<QString, QVector<QString>>& envMap) {
	char** envir = environ;
	QString equ = "=", envList, envName;

	while( *envir ) {
		envList = QString::fromLocal8Bit( *envir );
		qsizetype indexOf = envList.indexOf( equ );
		// 找到等号
		if( indexOf > 0 ) {
			envName = envList.mid( 0, indexOf );
			QMap<QString, QList<QString>>::iterator find = envMap.find( envName );
			if( find == envMap.end() )
				envMap.insert( envName, envList.mid( indexOf ).split( envSep ) );
			else
				for( auto& value : envList.mid( indexOf ).split( envSep ) )
					find.value().append( value );
		}
		envir++;
	}
}

ProcessArgs::ProcessArgs(int& argc, char** argv) : QCoreApplication( argc, argv ) {
	if( !isInitVal ) {
		isInitVal = true;
		/// 填充环境变量
		fullEnv( processEnvs );
		/// 填充进程参数
		if( argc > 1 )
			fullProcessArgs( argc, argv, processArgs );
	}
}

ProcessArgs::~ProcessArgs() {
}

const QSharedPointer<QMap<QString, QVector<QString>>> ProcessArgs::getEnvsToMap() {
	QSharedPointer<QMap<QString, QVector<QString>>> result{new QMap<QString, QVector<QString>>()};

	fullEnv( *result );

	return result;
}

const QMap<QString, QVector<QString>>& ProcessArgs::getArgOptions() const {
	return processArgs;
}

QVector<QString> ProcessArgs::getArgValue(const QString& name) const {
	const auto& find = processArgs.find( name );
	if( find != processArgs.end() )
		return find.value();
	else
		return {};
}

void ProcessArgs::setArgValue(const QString& name, const QVector<QString>& values, const bool clearFlag) {
	auto iterator = processArgs.find( name );
	if( iterator == processArgs.end() || clearFlag )
		iterator = processArgs.insert( name, values );
	else
		for( auto& value : values )
			iterator.value().append( value );
}

QVector<QString> ProcessArgs::getEnvValue(const QString& name) const {
	const auto& find = processEnvs.find( name );
	if( find != processEnvs.end() )
		return find.value();
	else
		return {};
}

void ProcessArgs::setEnvValue(const QString& name, const QVector<QString>& values, const bool clearFlag) {
	auto iterator = processEnvs.find( name );
	QByteArray varName = name.toLocal8Bit();
	if( iterator == processEnvs.end() || clearFlag ) {
		iterator = processEnvs.insert( name, values );
		qunsetenv( varName );
	} else
		for( auto& value : values )
			iterator.value().append( value );
	QByteArray setValues;
	auto sepByteArray = envSep.toLocal8Bit();
	for( auto& value : iterator.value() )
		setValues.append( value.toLocal8Bit() ).append( sepByteArray );
	qputenv( varName, setValues );
}

QVector<QString> ProcessArgs::getEnvNames() const {
	return processEnvs.keys();
}

const QMap<QString, QVector<QString>>& ProcessArgs::getEnvs() const {
	return processEnvs;
}

void ProcessArgs::clearArg(const QString& name) {
	processArgs.remove( name );
}

void ProcessArgs::clearEnv(const QString& name) const {
	if( processEnvs.remove( name ) )
		qunsetenv( name.toLocal8Bit() );
}

const QMap<QString, QVector<QString>> ProcessArgs::findArgOptionForTheSubStr(const QString& subStr) const {
	QMap<QString, QVector<QString>> result;
	QMap<QString, QVector<QString>>::iterator iterator = processArgs.begin(), end = processArgs.end();
	for( ; iterator != end; ++iterator )
		if( iterator.key().indexOf( subStr ) != -1 )
			result.insert( iterator.key(), iterator.value() );
	return result;
}

const QMap<QString, QVector<QString>> ProcessArgs::findArgParamForTheSubStr(const QString& subStr) const {
	QMap<QString, QVector<QString>> result;

	QMap<QString, QVector<QString>>::iterator iterator = processArgs.begin(), end = processArgs.end();
	for( ; iterator != end; ++iterator ) {
		QVector<QString> valueVector = iterator.value();
		for( size_t index = 0, maxLen = valueVector.length(); index < maxLen; ++index ) {
			if( valueVector[index].indexOf( subStr ) != -1 ) {
				result.insert( iterator.key(), iterator.value() );
				break;
			}
		}
	}
	return result;
}

const QMap<QString, QVector<QString>> ProcessArgs::findEnvNameForTheSubStr(const QString& subStr) const {
	QMap<QString, QVector<QString>> result;

	QMap<QString, QVector<QString>>::iterator iterator = processEnvs.begin(), end = processEnvs.end();
	for( ; iterator != end; ++iterator )
		if( iterator.key().indexOf( subStr ) != -1 )
			result.insert( iterator.key(), iterator.value() );
	return result;
}

const QMap<QString, QVector<QString>> ProcessArgs::findEnvValueForTheSubStr(const QString& subStr) const {
	QMap<QString, QVector<QString>> result;

	QMap<QString, QVector<QString>>::iterator iterator = processEnvs.begin(), end = processEnvs.end();
	for( ; iterator != end; ++iterator ) {
		QVector<QString> valueVector = iterator.value();
		for( size_t index = 0, maxLen = valueVector.length(); index < maxLen; ++index ) {
			if( valueVector[index].indexOf( subStr ) != -1 ) {
				result.insert( iterator.key(), iterator.value() );
				break;
			}
		}
	}
	return result;
}
