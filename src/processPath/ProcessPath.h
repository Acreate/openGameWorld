#ifndef PROCESSPATH_H_HEAD__FILE__
#define PROCESSPATH_H_HEAD__FILE__
#pragma once

#include <QCoreApplication>
#include <QStandardPaths>
#include <QDir>
#include <QVector>
#include <QSharedPointer>
#include <QMap>
#include <QString>
#include "ProcessPath_export.h"

/// @brief 路径对象
namespace path {
	/// @brief 基于私有的程序路径
	class PROCESSPATH_EXPORT App {
	public:
		/// @brief 获取进程的完整路径
		/// @return 进程的完整路径
		static QString getAppPath() {
			return qApp->applicationFilePath();
		}

		/// @brief 获取进程的所在目录（不包含进程名称的目录）
		/// @return 进程目录
		static QString getAppExisPath() {
			return qApp->applicationDirPath();
		}

		/// @brief 获取当前进程的工作目录，它与命令行有关联，与进程所在目录无关
		/// @return 工作目录
		static QString getWorkPath() {
			return QDir::currentPath();
		}

		/// @brief 获取 app 临时目录
		/// @return 软件临时目录
		static QString getAppAppLocalPath() {
			return QStandardPaths::writableLocation( QStandardPaths::AppLocalDataLocation );
		}

		/// @brief 获取 app 临时缓冲目录
		/// @return 软件临时缓冲目录
		static QString getAppCachePath() {
			return QStandardPaths::writableLocation( QStandardPaths::CacheLocation );
		}

		/// @brief 获取 app 临时数据目录
		/// @return 软件临时数据目录
		static QString getAppGenericCachePath() {
			return QStandardPaths::writableLocation( QStandardPaths::GenericCacheLocation );
		}

		/// @brief 获取 app 的配置目录
		/// @return 软件的配置目录
		static QString getAppConfigPath() {
			return QStandardPaths::writableLocation( QStandardPaths::ConfigLocation );
		}

		/// @brief 获取 app 的运行数据产生目录
		/// @return 软件的运行数据产生目录
		static QString getRunAppDataPath() {
			return QStandardPaths::writableLocation( QStandardPaths::AppDataLocation );
		}

		/// @brief 获取 app 的运行配置产生目录
		/// @return 软件的运行配置产生目录
		QString getRunAppConfigPath() {
			return QStandardPaths::writableLocation( QStandardPaths::AppConfigLocation );
		}
	};

	/// @brief 基于私有的用户路径
	class PROCESSPATH_EXPORT User {
	public:
		/// @brief 获取用户桌面所在目录
		/// @return 用户桌面路径
		static QString getUserDesktopPath() {
			return QStandardPaths::writableLocation( QStandardPaths::DesktopLocation );
		}

		/// @brief 获取用户文档所在目录
		/// @return 用户文档路径
		static QString getUserDocumentsPath() {
			return QStandardPaths::writableLocation( QStandardPaths::DocumentsLocation );
		}

		/// @brief 获取用户字体路径
		/// @return 用户字体路径
		static QString getUserFontsPath() {
			return QStandardPaths::writableLocation( QStandardPaths::FontsLocation );
		}

		/// @brief 应用程序快速启动目录路径。
		///	目录下的程序很可能不存在冗余的文件，而是一个基于程序生成的快捷方式、软链接、硬链接或者别名
		/// 安装应用程序可能需要额外的、特定于平台的操作。此目录中的文件、文件夹或快捷方式是特定于平台的。
		/// win 将返回 "C:/Users/<USER>/AppData/Roaming/Microsoft/Windows/Start Menu/Programs"
		/// @return 应用程序快速启动目录
		static QString getUserApplicationsPath() {
			return QStandardPaths::writableLocation( QStandardPaths::ApplicationsLocation );
		}

		/// @brief 获取音乐目录
		/// @return 音乐目录
		static QString getUserMusicPath() {
			return QStandardPaths::writableLocation( QStandardPaths::MusicLocation );
		}

		/// @brief 获取影音目录
		/// @return 影音目录
		static QString getUserMoviesPath() {
			return QStandardPaths::writableLocation( QStandardPaths::MoviesLocation );
		}

		/// @brief 获取图片目录
		/// @return 图片目录
		static QString getUserPicturesPath() {
			return QStandardPaths::writableLocation( QStandardPaths::PicturesLocation );
		}

		/// @brief 获取用户临时目录
		/// @return 用户临时目录
		static QString getUserTempPath() {
			return QStandardPaths::writableLocation( QStandardPaths::TempLocation );
		}

		/// @brief 获取用户目录
		/// @return 用户目录
		static QString getUserHomePath() {
			return QStandardPaths::writableLocation( QStandardPaths::HomeLocation );
		}

		/// @brief 获取当前运行程序的用户目录
		/// @return 当前运行程序的用户目录
		static QString getUserRuntimePath() {
			return QStandardPaths::writableLocation( QStandardPaths::RuntimeLocation );
		}

		/// @brief 获取用户的下载目录
		/// @return 用户的下载目录
		static QString getUserDownloadPath() {
			return QStandardPaths::writableLocation( QStandardPaths::DownloadLocation );
		}

		/// @brief 获取用户的数据目录
		/// @return 用户的数据目录
		static QString getUserGenericConfigPath() {
			return QStandardPaths::writableLocation( QStandardPaths::GenericConfigLocation );
		}

		/// @brief 所有用户的公共目录
		/// @return 公共目录
		static QString getPublicSharePath() {
			return QStandardPaths::writableLocation( QStandardPaths::PublicShareLocation );
		}

		/// @brief 返回用户的模板目录
		/// @return 模板目录
		static QString getUserTemplatesPath() {
			return QStandardPaths::writableLocation( QStandardPaths::TemplatesLocation );
		}
	};

	/// @brief 基于全局的
	class PROCESSPATH_EXPORT Global {
	public:
		/// @brief 基于全局的程序路径
		class PROCESSPATH_EXPORT App {
		public:
			/// @brief 获取 app 临时目录
			/// @return 软件临时目录
			static QStringList getAppAppLocalPath() {
				return QStandardPaths::standardLocations( QStandardPaths::AppLocalDataLocation );
			}

			/// @brief 获取 app 临时缓冲目录
			/// @return 软件临时缓冲目录
			static QStringList getAppCachePath() {
				return QStandardPaths::standardLocations( QStandardPaths::CacheLocation );
			}

			/// @brief 获取 app 临时数据目录
			/// @return 软件临时数据目录
			static QStringList getAppGenericCachePath() {
				return QStandardPaths::standardLocations( QStandardPaths::GenericCacheLocation );
			}

			/// @brief 获取 app 的配置目录
			/// @return 软件的配置目录
			static QStringList getAppConfigPath() {
				return QStandardPaths::standardLocations( QStandardPaths::ConfigLocation );
			}

			/// @brief 获取 app 的运行数据产生目录
			/// @return 软件的运行数据产生目录
			static QStringList getRunAppDataPath() {
				return QStandardPaths::standardLocations( QStandardPaths::AppDataLocation );
			}

			/// @brief 获取 app 的运行配置产生目录
			/// @return 软件的运行配置产生目录
			static QStringList getRunAppConfigPath() {
				return QStandardPaths::standardLocations( QStandardPaths::AppConfigLocation );
			}
		};

		/// @brief 基于私有的用户路径
		class PROCESSPATH_EXPORT User {
		public:
			/// @brief 获取用户桌面所在目录
			/// @return 用户桌面路径
			static QStringList getUserDesktopPath() {
				return QStandardPaths::standardLocations( QStandardPaths::DesktopLocation );
			}

			/// @brief 获取用户文档所在目录
			/// @return 用户文档路径
			static QStringList getUserDocumentsPath() {
				return QStandardPaths::standardLocations( QStandardPaths::DocumentsLocation );
			}

			/// @brief 获取用户字体路径
			/// @return 用户字体路径
			static QStringList getUserFontsPath() {
				return QStandardPaths::standardLocations( QStandardPaths::FontsLocation );
			}

			/// @brief 应用程序快速启动目录路径。
			///	目录下的程序很可能不存在冗余的文件，而是一个基于程序生成的快捷方式、软链接、硬链接或者别名
			/// 安装应用程序可能需要额外的、特定于平台的操作。此目录中的文件、文件夹或快捷方式是特定于平台的。
			/// win 将返回 "C:/Users/<USER>/AppData/Roaming/Microsoft/Windows/Start Menu/Programs"
			/// @return 应用程序快速启动目录
			static QStringList getUserApplicationsPath() {
				return QStandardPaths::standardLocations( QStandardPaths::ApplicationsLocation );
			}

			/// @brief 获取音乐目录
			/// @return 音乐目录
			static QStringList getUserMusicPath() {
				return QStandardPaths::standardLocations( QStandardPaths::MusicLocation );
			}

			/// @brief 获取影音目录
			/// @return 影音目录
			static QStringList getUserMoviesPath() {
				return QStandardPaths::standardLocations( QStandardPaths::MoviesLocation );
			}

			/// @brief 获取图片目录
			/// @return 图片目录
			static QStringList getUserPicturesPath() {
				return QStandardPaths::standardLocations( QStandardPaths::PicturesLocation );
			}

			/// @brief 获取用户临时目录
			/// @return 用户临时目录
			static QStringList getUserTempPath() {
				return QStandardPaths::standardLocations( QStandardPaths::TempLocation );
			}

			/// @brief 获取用户目录
			/// @return 用户目录
			static QStringList getUserHomePath() {
				return QStandardPaths::standardLocations( QStandardPaths::HomeLocation );
			}

			/// @brief 获取当前运行程序的用户目录
			/// @return 当前运行程序的用户目录
			static QStringList getUserRuntimePath() {
				return QStandardPaths::standardLocations( QStandardPaths::RuntimeLocation );
			}

			/// @brief 获取用户的下载目录
			/// @return 用户的下载目录
			static QStringList getUserDownloadPath() {
				return QStandardPaths::standardLocations( QStandardPaths::DownloadLocation );
			}

			/// @brief 获取用户的数据目录
			/// @return 用户的数据目录
			static QStringList getUserGenericConfigPath() {
				return QStandardPaths::standardLocations( QStandardPaths::GenericConfigLocation );
			}

			/// @brief 所有用户的公共目录
			/// @return 公共目录
			static QStringList getPublicSharePath() {
				return QStandardPaths::standardLocations( QStandardPaths::PublicShareLocation );
			}

			/// @brief 返回用户的模板目录
			/// @return 模板目录
			static QStringList getUserTemplatesPath() {
				return QStandardPaths::standardLocations( QStandardPaths::TemplatesLocation );
			}
		};
	};

	/// @brief 全局路径
	using globalPath = Global;
	/// @brief 用户私有路径
	using privateUserPath = User;
	/// @brief 程序私有路径
	using privateAppPath = App;

	/// @brief 基于路径的信息
	namespace info {
		/// @brief 获取路径信息
		/// @param path 路径
		/// @param fileNames 文件路径容器 
		/// @param dirNames 目录路径
		/// @return 获取个数
		qsizetype PROCESSPATH_EXPORT getPathInfo(const QString& path, QSharedPointer<QVector<QFileInfo>> fileNames = nullptr, QSharedPointer<QVector<QFileInfo>> dirNames = nullptr);

		/// @brief 文件类
		namespace file {
			/// @brief 获取路径下的所有文件名
			/// @param path 路径
			/// @return 所有基于 path 路径的文件名
			QSharedPointer<QVector<QFileInfo>> PROCESSPATH_EXPORT getOnPathFileName(const QString& path);

			/// @brief 获取路径下的所有文件名，递归查找
			/// @param path 路径
			/// @return 所有基于 path 路径的文件名
			QSharedPointer<QVector<QFileInfo>> PROCESSPATH_EXPORT getInPathFileName(const QString& path);
		}

		/// @brief 文件夹类
		namespace dir {
			/// @brief 获取路径下的所有文件名
			/// @param path 路径
			/// @return 所有基于 path 路径的文件名
			QSharedPointer<QVector<QFileInfo>> PROCESSPATH_EXPORT getOnPathDirName(const QString& path);

			/// @brief 获取路径下的所有文件名，递归查找
			/// @param path 路径
			/// @return 所有基于 path 路径的文件名
			QSharedPointer<QVector<QFileInfo>>PROCESSPATH_EXPORT getInPathDirName(const QString& path);
		}

		/// @brief 大小类
		namespace size {
		}

		/// @brief 日期类
		namespace time {
		}
	}
};

#endif // PROCESSARGS_H
