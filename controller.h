#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ui_myplayer.h"

#include <QMediaPlayer>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QAbstractButton;
class QAbstractSlider;
class QComboBox;
QT_END_NAMESPACE

class Controller : public QWidget
{
	Q_OBJECT

public:
	Controller(/*QMediaPlayer *mediaPlayer,*/ Ui::MyP uii, QWidget *parent = 0);

	QMediaPlayer::State state() const;
	bool isMuted() const;
	int volume() const;


public slots:
	void setState(QMediaPlayer::State state);
	void setMuted(bool muted);
	void setVolume(int volume);

signals:
	void play();
	void pause();
	void stop();
	void previous();
	void next();
	void changeMuting(bool muting);
	void changeVolume(int volume);

private slots:
	void playClicked();
	void muteClicked();

private:
	Ui::MyP ui;
	//QMediaPlayer *mPlayer;

	QMediaPlayer::State playerState;
	bool playerMuted;
	QAbstractButton *playButton;     //ok
	QAbstractButton *stopButton;     //ok
	QAbstractButton *nextButton;
	QAbstractButton *previousButton;
	QAbstractButton *muteButton;     //ok

	//QAbstractButton *fullscreenButton;

	QAbstractSlider *volumeSlider;    //ok
	QComboBox *rateBox;
};

#endif // CONTROLLER_H