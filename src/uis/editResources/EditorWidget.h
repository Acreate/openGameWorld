#ifndef EDITORWIDGET_H
#define EDITORWIDGET_H

#include <QWidget>

class EditorWidget : public QWidget {
	Q_OBJECT

public:
	explicit EditorWidget( QWidget *parent = nullptr );
	~EditorWidget( ) override;
};
#endif // EDITORWIDGET_H