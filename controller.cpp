#include "controller.h"

#include <QBoxLayout>
#include <QSlider>
#include <QStyle>
#include <QToolButton>
#include <QComboBox>

Controller::Controller(/*QMediaPlayer *mediaPlayer,*/ Ui::MyP uii, QWidget *parent)
: QWidget(parent)
, playerState(QMediaPlayer::StoppedState)
, playerMuted(false)
//, playButton(0)
, stopButton(0)
, nextButton(0)
, previousButton(0)
, muteButton(0)
, volumeSlider(0)
, rateBox(0)
{
	//mPlayer = mediaPlayer;
	ui = uii;

	playButton = ui.playButton;
	//playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
	playButton->setEnabled(true);
	connect(playButton, SIGNAL(clicked()), this, SLOT(playClicked()));
	connect(playButton, SIGNAL(QHoverEvent), this, SLOT(playClicked()));

	stopButton = ui.stopButton;
	//stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
	stopButton->setEnabled(true);
	connect(stopButton, SIGNAL(clicked()), this, SIGNAL(stop()));
	

	nextButton = ui.nextButton;
	//nextButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
	connect(nextButton, SIGNAL(clicked()), this, SIGNAL(next()));
	
	previousButton = ui.previousButton;
	//previousButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
	connect(previousButton, SIGNAL(clicked()), this, SIGNAL(previous()));
	

	muteButton = ui.volumeButton;
	//muteButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
	muteButton->setEnabled(true);
	connect(muteButton, SIGNAL(clicked()), this, SLOT(muteClicked()));
	

	volumeSlider = ui.volumeSlider;
	volumeSlider->setRange(0, 100);
	volumeSlider->setValue(100);
	connect(volumeSlider, SIGNAL(sliderMoved(int)), this, SIGNAL(changeVolume(int)));


	//fullscreenButton = ui.fullscreenButton;
	////fullscreenButton->setEnabled(true);
	//fullscreenButton->setCheckable(true);


}

//�õ�Ŀǰ�Ĳ���״̬playerState
QMediaPlayer::State Controller::state() const
{
	return playerState;
}


//���ò���״̬ ���ҿ�����֮������ť���
void Controller::setState(QMediaPlayer::State state)
{
	if (state != playerState) {
		playerState = state;

		switch (state) {
		case QMediaPlayer::StoppedState:
			stopButton->setEnabled(false);
			//playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
			break;
		case QMediaPlayer::PlayingState:
			stopButton->setEnabled(true);
			//playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
			break;
		case QMediaPlayer::PausedState:
			stopButton->setEnabled(true);
			//playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
			break;
		}
	}
}

int Controller::volume() const
{
	return volumeSlider ? volumeSlider->value() : 0;
}

void Controller::setVolume(int volume)
{
	if (volumeSlider)
		volumeSlider->setValue(volume);
}

//�����Ƿ��ھ���״̬
bool Controller::isMuted() const
{
	return playerMuted;
}

//���þ��� ͬʱ���Ը���������ť���
void Controller::setMuted(bool muted)
{
	if (muted != playerMuted) {
		playerMuted = muted;

		muteButton->setIcon(style()->standardIcon(muted ? QStyle::SP_MediaVolumeMuted : QStyle::SP_MediaVolume));
	}
}

//���Ű�ť���º�
void Controller::playClicked()
{
	switch (playerState) {
	//case QMediaPlayer::StoppedState:
    case QMediaPlayer::PlayingState:
		emit pause();
        break;
    default:
		emit play();
		//playButton->setStyleSheet(QStringLiteral("border-image: url(:/play_hover.png);"));
        break;
    }
}

//����
void Controller::muteClicked()
{
	emit changeMuting(!playerMuted);
}