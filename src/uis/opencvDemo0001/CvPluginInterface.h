#ifndef CVPLUGININTERFACE_H_H_HEAD__FILE__
#define CVPLUGININTERFACE_H_H_HEAD__FILE__
#pragma once
#include <qobject.h>
#include <opencv2/opencv.hpp>
#include "OpenCVInterface_export.h"
#include <QString>

namespace openCVInterface {
	class OPENCVINTERFACE_EXPORT CvPluginInterface {
	public:
		virtual ~CvPluginInterface( ) = default;
		virtual QString description( ) = 0;
		virtual void processImage( const cv::Mat &inputImage, cv::Mat &outputImage ) = 0;
	};
}

#define CVPLUGININTERFACE_IID "com.amin.cvplugininterfce"
Q_DECLARE_INTERFACE(openCVInterface::CvPluginInterface, CVPLUGININTERFACE_IID)

#endif // CVPLUGININTERFACE_H_H_HEAD__FILE__