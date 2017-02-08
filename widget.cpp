#include "widget.h"

#include <QKeyEvent>
#include <QMouseEvent>

VideoWidget::VideoWidget(/*Ui::MyP uii, */QWidget *parent)
: QVideoWidget(parent)
//: QWidget(parent)
//, qvideoWidget(0)
{
	//resize(0, 0);
	//setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	//setSizeIncrement(QSize(0,0));
	//uii.playWidget = this;
	//QVideoWidget *qvw= new QVideoWidget(uii.playWidget);
	//qvw->show();
	//VideoWidget::hide();
	//xx->
	//qvideoWidget = new QVideoWidget(parent);
	//ui = uii;
	//ui.playWidget=new QVideoWidget(this);
	//qvideoWidget = ui.playWidget;
	//qvideoWidget->show();
	/*setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

	QPalette p = palette();
	p.setColor(QPalette::Window, Qt::black);
	setPalette(p);

	setAttribute(Qt::WA_OpaquePaintEvent);*/
}

void VideoWidget::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Escape && isFullScreen()) {
		setFullScreen(false);
		event->accept();
	}
	else if (event->key() == Qt::Key_Enter && event->modifiers() & Qt::Key_Alt) {
		setFullScreen(!isFullScreen());
		event->accept();
	}
	else {
		QVideoWidget::keyPressEvent(event);
	}
	/*if (Qt::Key_1 == event->key())
	{
		emit hide();
	}*/
}



void VideoWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
	setFullScreen(!isFullScreen());
	event->accept();
}

void VideoWidget::mousePressEvent(QMouseEvent *event)
{
	QVideoWidget::mousePressEvent(event);
}

