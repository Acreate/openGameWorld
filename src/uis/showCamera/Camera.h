#ifndef CAMERA_H_H_HEAD__FILE__
#define CAMERA_H_H_HEAD__FILE__
#pragma once


#include <QMainWindow>
#include <QCamera>
#include <QVideoWidget>
#include <QMediaCaptureSession>
#include <QMediaDevices>
#include <QImageCapture>
#include <QMediaRecorder>


QT_BEGIN_NAMESPACE

namespace Ui {
	class Camera;
}

QT_END_NAMESPACE


class Camera : public QMainWindow {
	Q_OBJECT

public:
	Camera( QWidget *parent = nullptr );
	~Camera( );

private:
	Ui::Camera *ui;
	QScopedPointer<QCamera> my_camera;
	QScopedPointer<QMediaRecorder> my_mediaRecorder;
	QMediaCaptureSession my_captureSession;

	static bool checkCameraAvailability( void );

};

#endif // CAMERA_H_H_HEAD__FILE__