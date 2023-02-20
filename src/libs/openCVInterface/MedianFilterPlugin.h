#ifndef MEDIANFILTERPLUGIN_H_H_HEAD__FILE__
#define MEDIANFILTERPLUGIN_H_H_HEAD__FILE__
#pragma once

#include <qobject.h>
#include "CvPluginInterface.h"

namespace openCVInterface {
	class OPENCVINTERFACE_EXPORT MedianFilterPlugin : public QObject, public CvPluginInterface {
		Q_OBJECT
		Q_PLUGIN_METADATA(IID  "com.amin.cvplugininterfce")
		Q_INTERFACES(openCVInterface::CvPluginInterface)

	public:
		explicit MedianFilterPlugin( QObject *parent = nullptr );

		~MedianFilterPlugin( ) override;

		QString description( ) override;

		void processImage( const cv::Mat &inputImage, cv::Mat &outputImage ) override;
	};
}


#endif // MEDIANFILTERPLUGIN_H_H_HEAD__FILE__