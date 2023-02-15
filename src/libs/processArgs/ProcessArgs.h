#ifndef PROCESSARGS_H
#define PROCESSARGS_H

#include <memory>
#include <mutex>
#include <QCoreApplication>
#include <QStandardPaths>
#include <QDir>
#include <QVector>
#include <QSharedPointer>
#include <QMap>
#include <QString>
#include "ProcessArgs_export.h"

/// @brief 程序参数信息使用类，包含关于进程的所有信息功能
class PROCESSARGS_EXPORT ProcessArgs {
public:
	ProcessArgs( int &argc, char **argv );
	virtual ~ProcessArgs( );
	/// @brief 根据环境变量获取对应的映射列表
	/// @return 返回一个映射列表
	static const QSharedPointer<QMap<QString, QVector<QString> > > getEnvsToMap( );
	/// @brief 获取所有的选项，其中选项包含参数
	/// @return 变量列表
	const QMap<QString, QVector<QString> > &getArgOptions( ) const;

	/// @brief 根据名称获取选项内容
	/// @return 选项内容
	QVector<QString> getArgValue( const QString &name ) const;

	/// @brief 根据名称设置选项内容
	/// @param name 选项名称
	/// @param values 选项内容
	/// @param clearFlag 是否清除旧内容
	void setArgValue( const QString &name, const QVector<QString> &values, const bool clearFlag = false );
	/// @brief 清空指定的参数名
	/// @param name 参数名
	void clearArg( const QString &name );
	/// @brief 根据名称返回环境变量
	/// @param name 环境变量名称
	/// @return 变量列表
	QVector<QString> getEnvValue( const QString &name ) const;

	/// @brief 根据名称设置环境变量
	/// @param name 环境变量名称
	/// @param values 环境变量列表
	/// @param clearFlag 是否清除旧内容
	void setEnvValue( const QString &name, const QVector<QString> &values, const bool clearFlag = false );

	/// @brief 获取所有环境变量名称
	///	@return 所有环境变量名称
	QVector<QString> getEnvNames( ) const;

	/// @brief 获取所有环境变量，它是实例本身的环境变量
	///	即时请使用 
	/// @return 所有环境变量及其配置列表
	const QMap<QString, QVector<QString> > &getEnvs( ) const;

	/// @brief 清空指定的环境变量
	/// @param name 环境变量名
	void clearEnv( const QString &name ) const;

	/// @brief 查找所有存在指定字符的选项，它并不会查找选项参数
	/// @param subStr 查找字符串
	/// @return 包含字符的字符串
	const QMap<QString, QVector<QString> > findArgOptionForTheSubStr( const QString &subStr ) const;

	/// @brief 查找所有存在指定字符的选项参数，它并不会查找选项名称
	/// @param subStr 查找字符串
	/// @return 包含字符的字符串
	const QMap<QString, QVector<QString> > findArgParamForTheSubStr( const QString &subStr ) const;

	/// @brief 查找所有存在指定字符的环境变量，它并不会查找变量内容
	/// @param subStr 查找字符串
	/// @return 包含字符的字符串
	const QMap<QString, QVector<QString> > findEnvNameForTheSubStr( const QString &subStr ) const;

	/// @brief 查找所有存在指定字符的环境变量值，它并不会查找变量名称
	/// @param subStr 查找字符串
	/// @return 包含字符的字符串
	const QMap<QString, QVector<QString> > findEnvValueForTheSubStr( const QString &subStr ) const;

private:
	/// @brief 进程参数
	static QMap<QString, QVector<QString> > processArgs;
	/// @brief 当前进程的环境变量
	static QMap<QString, QVector<QString> > processEnvs;
};

#endif // PROCESSARGS_H