#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include "widget.h"
#include "playlistmodel.h"

#include <qmediaplayer.h>
#include "ui_myplayer.h"

#include <QtGui/QMovie>
#include <QtWidgets/QWidget>
#include <QMediaPlaylist>

enum ResizeRegion
{
	Default,
	North,
	NorthEast,
	East,
	SouthEast,
	South,
	SouthWest,
	West,
	NorthWest,
	Middle
};

QT_BEGIN_NAMESPACE
class QAbstractItemView;
class QLabel;
class QMediaPlayer;
class QModelIndex;
class QPushButton;
class QSlider;
class QVideoProbe;
class QVideoWidget;
QT_END_NAMESPACE

class VideoPlayer : public QWidget
{
    Q_OBJECT
public:
    VideoPlayer(QWidget *parent = 0);
    ~VideoPlayer();
	//void keyPressEvent(QKeyEvent *event);

signals:
	void fullScreenChanged(bool fullScreen);

private slots:
	void openFile();
	void hideorshowPlaylist();

	void previousClicked();

	void seek(int seconds);
	void jump(const QModelIndex &index);
	void playlistPositionChanged(int);

	
	void mediaStateChanged(QMediaPlayer::State state);
	void statusChanged(QMediaPlayer::MediaStatus status);
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);
	void metaDataChanged();
	
	void setPosition(int position);
    
	/*void handleError();*/
	void videoAvailableChanged(bool available);
	void addToPlaylist(const QStringList &fileNames);

	void minizeWin();
	void maxWin();

	void closePlaylist();
	void deleteMedia();
	void changeIndex(const QModelIndex &index);

	void showColorDialog();

protected:
	void mousePressEvent(QMouseEvent *);
	void mouseMoveEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);

private:
	void updateDurationInfo(qint64 currentInfo);
	void setTrackInfo(const QString &info);
	void setStatusInfo(const QString &info);

	void setResizeCursor(ResizeRegion region);
	ResizeRegion getResizeRegion(QPoint clientPos);
	void handleMove(QPoint pt);
	void handleResize();

	Ui::MyP ui;   //sf

	QMediaPlayer *mediaPlayer;
	VideoWidget *videoWidget;
	QMediaPlaylist *playlist;
	PlaylistModel *playlistModel;
	QAbstractItemView *playlistView;

	QBoxLayout *playlistCon;
	QRect playlistcontrolSpacer_Rect;
	int playlistcontrolSpacer_width;
	int playlistcontrolSpacer_height;

    //QAbstractButton *playButton;
	QPushButton *fullscreenButton;
	QPushButton *playlistButton;
	QPushButton *closeplaylistButton;
	QPushButton *addButton;
	QPushButton *minusButton;
	QSpacerItem * playlistcontrolSpacer;
	QPushButton *settingButton;
	QDialog *colorDialog;


	QPushButton *minButton;
	QPushButton *maxButton;
	bool isMax;
	QPushButton *closeButton;
	bool isPress;
	QPoint startPos;
	QPoint clickPos;

	QPushButton *closePlaylistButton;
	int selectedIndex;

	QLabel *labelDurationLeft;
	QLabel *labelDurationRight;
	QSize playlistSize;

	QSlider *positionSlider;
	//QLabel *coverLabel;
	//QLabel *errorLabel;
	QString trackInfo;
	QString statusInfo;
	bool playlistIsShow;
	qint64 duration;

	QLabel *coverLabel;
	QLabel *titleLable;

	bool m_drag, m_move;
	QPoint dragPos, resizeDownPos;
	const int resizeBorderWidth = 4;
	ResizeRegion resizeRegion;
	QRect mouseDownRect;
};

#endif
