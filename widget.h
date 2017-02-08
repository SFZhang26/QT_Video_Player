#ifndef WIDGET_H
#define WIDGET_H

#include "ui_myplayer.h"

#include <QVideoWidget>

class VideoWidget : public QVideoWidget
//class VideoWidget : public QWidget
//class VideoWidget : public QFrame
{
	Q_OBJECT

public:
	VideoWidget(/*Ui::MyP uii, */QWidget *parent = 0);


	//QVideoWidget *qvideoWidget;
	//QFrame *xx;

protected:
	void keyPressEvent(QKeyEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);


private:
	//Ui::MyP ui;
	//QVideoWidget *qvideoWidget;
	//QPalette *p;
};

#endif // WIDGET_H