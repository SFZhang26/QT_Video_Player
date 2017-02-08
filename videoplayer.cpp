#include "ui_myplayer.h"

#include "videoplayer.h"
#include "controller.h"
#include "widget.h"

#include <QMediaMetaData>
#include <QtWidgets>
#include <qvideowidget.h>
#include <qvideosurfaceformat.h>

VideoPlayer::VideoPlayer(QWidget *parent)
    : QWidget(parent)
	//, videoWidget(0)
	, coverLabel(0)
    //, mediaPlayer(0/*, QMediaPlayer::VideoSurface*/)
    /*, playButton(0)
    , positionSlider(0)*/
    /*, errorLabel(0)*/
	, colorDialog(0)
{
	ui.setupUi(this);
	setMouseTracking(true);
	mediaPlayer = new QMediaPlayer(this);

	playlist = new QMediaPlaylist();
	mediaPlayer->setPlaylist(playlist);

	connect(mediaPlayer, SIGNAL(durationChanged(qint64)), SLOT(durationChanged(qint64)));
	connect(mediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
	connect(mediaPlayer, SIGNAL(metaDataChanged()), SLOT(metaDataChanged()));
	connect(playlist, SIGNAL(currentIndexChanged(int)), SLOT(playlistPositionChanged(int)));//标记正在播放的视频（选中阴影）

	//针对mediaPlayer的槽函数绑定 接受者为this
	connect(mediaPlayer, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(statusChanged(QMediaPlayer::MediaStatus)));
	connect(mediaPlayer, SIGNAL(videoAvailableChanged(bool)), this, SLOT(videoAvailableChanged(bool)));

	videoWidget = new VideoWidget(/*ui, *//*this*/);
	ui.verticalLayout->insertWidget(0, videoWidget);
	//ui.verticalLayout->removeWidget(ui.playWidget);
	//videoWidget->resize(0, 0);;
	ui.playWidget->deleteLater();
	mediaPlayer->setVideoOutput(videoWidget/*ui.playWidget*//*videoWidget->qvideoWidget*/);
	/*ui.verticalLayout->addLayout(ui.horizontalLayout_6);
	ui.verticalLayout->addLayout(ui.horizontalLayout_5);*/
	//delete(ui.playWidget);
	videoWidget->show();
	playlistModel = new PlaylistModel(this);
	playlistModel->setPlaylist(playlist);

	playlistView = ui.listView;
	playlistView->setModel(playlistModel);
	playlistView->setCurrentIndex(playlistModel->index(playlist->currentIndex(), 0));

	playlistSize = playlistView->size();

	connect(playlistView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(jump(QModelIndex)));


    QAbstractButton *openButton = ui.openButton;
    connect(openButton, SIGNAL(clicked()), this, SLOT(openFile()));


    positionSlider = ui.positionSlider;
	positionSlider->setRange(0, mediaPlayer->duration() / 1000);
	//positionSlider->setTickInterval(1/1000);
	connect(positionSlider, SIGNAL(sliderMoved(int)), this, SLOT(seek(int)));
    //connect(positionSlider, SIGNAL(sliderMoved(int)),this, SLOT(setPosition(int)));
	
	labelDurationLeft = ui.lefttimeLabel;
	labelDurationRight = ui.righttimeLabel;

	QTime initTime(0, 0, 0, 0);
	QString format = "hh:mm:ss";
	QString tStr = initTime.toString(format);
	labelDurationLeft->setText(tStr);  
	labelDurationRight->setText(tStr);

	Controller *controls = new Controller(/*mediaPlayer, */ui, this);
	controls->setState(mediaPlayer->state());

	//针对controls的槽函数绑定 接受者为mediaPlayer
	connect(controls, SIGNAL(play()), mediaPlayer, SLOT(play()));
	connect(controls, SIGNAL(pause()), mediaPlayer, SLOT(pause()));
	connect(controls, SIGNAL(stop()), mediaPlayer, SLOT(stop()));
	connect(controls, SIGNAL(next()), playlist, SLOT(next()));
	connect(controls, SIGNAL(previous()), this, SLOT(previousClicked()));
	connect(controls, SIGNAL(changeMuting(bool)), mediaPlayer, SLOT(setMuted(bool)));
	connect(controls, SIGNAL(changeVolume(int)), mediaPlayer, SLOT(setVolume(int)));

	connect(controls, SIGNAL(stop()), videoWidget, SLOT(update()));

	//针对mediaPlayer的槽函数绑定 接受者为controls
	connect(mediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), controls, SLOT(setState(QMediaPlayer::State)));
	connect(mediaPlayer, SIGNAL(mutedChanged(bool)), controls, SLOT(setMuted(bool)));
	connect(mediaPlayer, SIGNAL(volumeChanged(int)), controls, SLOT(setVolume(int)));


	// 全屏按钮
	fullscreenButton = ui.fullscreenButton;
	fullscreenButton->setCheckable(true);

	/*connect(fullscreenButton, SIGNAL(clicked()), videoWidget->qvideoWidget, SLOT(setFullScreen()));
	connect(videoWidget->qvideoWidget, SIGNAL(fullScreenChanged(true)), fullscreenButton, SLOT(setChecked(true)));*/
	//if (fullscreenButton->isChecked())
	//	videoWidget->qvideoWidget->setFullScreen(true);


	//显示/关闭播放列表按钮
	playlistButton = ui.playlistButton;
	playlistIsShow = true;
	connect(playlistButton, SIGNAL(clicked()), this, SLOT(hideorshowPlaylist()));

	//settings
	settingButton = ui.settingButton;
	connect(settingButton, SIGNAL(clicked()), this, SLOT(showColorDialog()));

	//
	playlistCon = ui.playlistCon;

	closeplaylistButton = ui.closeplaylistButton;
	addButton = ui.addButton;
	minusButton = ui.deleteButton;
	playlistcontrolSpacer = ui.playlistcontrolSpacer;

	selectedIndex = 0;

	connect(addButton, SIGNAL(clicked()), this, SLOT(openFile()));
	connect(playlistView, SIGNAL(clicked(QModelIndex)), this, SLOT(changeIndex(QModelIndex)));
	connect(minusButton, SIGNAL(clicked()), this, SLOT(deleteMedia()));

	playlistcontrolSpacer_Rect = playlistcontrolSpacer->geometry();
	//playlistcontrolSpacer_width = playlistcontrolSpacer->geometry().width;
	//playlistcontrolSpacer_height = playlistcontrolSpacer->geometry().height;

	minButton = ui.minButton;
	connect(minButton, SIGNAL(clicked()), this, SLOT(minizeWin()));

	maxButton = ui.maxButton;
	connect(maxButton, SIGNAL(clicked()), this, SLOT(maxWin()));
	isMax = false;
	isPress = false;

	closeButton = ui.closeButton;
	connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

	closePlaylistButton = ui.closeplaylistButton;
	connect(closePlaylistButton, SIGNAL(clicked()), this, SLOT(closePlaylist()));

	titleLable = ui.label;//顶端label
	

	QFile file("ui/stylesheet.qss");
	file.open(QFile::ReadOnly);
	QString styleSheet = QLatin1String(file.readAll());
	/*qApp->*/setStyleSheet(styleSheet);
	file.close();

	if (!mediaPlayer->isAvailable()) {
		QMessageBox::warning(this, tr("Service not available"),
			tr("The QMediaPlayer object does not have a valid service.\n"\
			"Please check the media service plugins are installed."));

		controls->setEnabled(false);
	}

	metaDataChanged();


	//下面这段不知道是什么作用
	QStringList arguments = qApp->arguments();
	arguments.removeAt(0);
	addToPlaylist(arguments);
    
}

VideoPlayer::~VideoPlayer()
{
}

//打开文件
void VideoPlayer::openFile()
{
    //errorLabel->setText("");
	//playlistView->hide();//测试播放列表是否可以隐藏
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open Movie"),QDir::homePath());

	addToPlaylist(fileNames);

    //if (!fileName.isEmpty()) {
    //    mediaPlayer->setMedia(QUrl::fromLocalFile(fileName));
    //    //playButton->setEnabled(true);
    //}
}

void VideoPlayer::closePlaylist()
{
	QSize winSize = size();
	playlistSize = playlistView->size();

	playlistView->hide();
	closeplaylistButton->hide();
	addButton->hide();
	minusButton->hide();
	ui.verticalLayout_3->removeItem(playlistCon);
	//playlistCon->setSpacing(1);
	//playlistcontrolSpacer->changeSize(0,0);
	//playlistcontrolSpacer->setGeometry(QRect(0, 0, 0, 0));
	//resize(768 - 169-6, 460);
	resize(winSize.width() - playlistSize.width() - 5, winSize.height());

	playlistIsShow = !playlistIsShow;
}


void VideoPlayer::hideorshowPlaylist()
{
	QSize winSize = size();
	playlistSize = playlistView->size();
	if (playlistIsShow)
	{
		playlistView->hide();
		closeplaylistButton->hide();
		addButton->hide();
		minusButton->hide();
		ui.verticalLayout_3->removeItem(playlistCon);
		//playlistCon->setSpacing(1);
	    //playlistcontrolSpacer->changeSize(0,0);
		//playlistcontrolSpacer->setGeometry(QRect(0, 0, 0, 0));
		//resize(768 - 169-6, 460);
		resize(winSize.width() - playlistSize.width()-5, winSize.height());
	}	
	else
	{
		playlistView->show();
		closeplaylistButton->show();
		addButton->show();
		minusButton->show();
		ui.verticalLayout_3->insertItem(0,playlistCon);
		//playlistcontrolSpacer->changeSize(playlistcontrolSpacer_width, playlistcontrolSpacer_height);
		//playlistCon->addSpacerItem(playlistcontrolSpacer);
		//playlistCon->insertItem(2, playlistcontrolSpacer);
		//playlistcontrolSpacer->changeSize(80,15);
		//resize(768, 460);
		resize(winSize.width() + playlistSize.width()+5, winSize.height());
	}
		

	playlistIsShow = !playlistIsShow;
}



void VideoPlayer::addToPlaylist(const QStringList& fileNames)
{
	foreach(QString const &argument, fileNames) {
		QFileInfo fileInfo(argument);
		if (fileInfo.exists()) {
			QUrl url = QUrl::fromLocalFile(fileInfo.absoluteFilePath());
			if (fileInfo.suffix().toLower() == QLatin1String("m3u")) {
				playlist->load(url);
			}
			else
				playlist->addMedia(url);
		}
		else {
			QUrl url(argument);
			if (url.isValid()) {
				playlist->addMedia(url);
			}
		}
	}
}

void VideoPlayer::deleteMedia()
{
	playlist->removeMedia(selectedIndex);
}

void VideoPlayer::previousClicked()
{
	// Go to previous track if we are within the first 5 seconds of playback
	// Otherwise, seek to the beginning.
	if (mediaPlayer->position() <= 5000)
		playlist->previous();
	else
		mediaPlayer->setPosition(0);
}

void VideoPlayer::jump(const QModelIndex &index)
{
	if (index.isValid()) {
		playlist->setCurrentIndex(index.row());
		mediaPlayer->play();
	}
}

void VideoPlayer::changeIndex(const QModelIndex &index)
{
	if (index.isValid()) {
		selectedIndex = index.row();
	}
}

void VideoPlayer::playlistPositionChanged(int currentItem)
{
	playlistView->setCurrentIndex(playlistModel->index(currentItem, 0));
}

void VideoPlayer::seek(int seconds)
{
	mediaPlayer->setPosition(seconds * 1000);
}
void VideoPlayer::durationChanged(qint64 duration)
{
	this->duration = duration / 1000;
	positionSlider->setMaximum(duration / 1000);
}

void VideoPlayer::positionChanged(qint64 progress)
{
	if (!positionSlider->isSliderDown()) {
		positionSlider->setValue(progress / 1000);
	}
	updateDurationInfo(progress / 1000);
}
void VideoPlayer::updateDurationInfo(qint64 currentInfo)
{
	QString tStr1;
	QString tStr2;
	if (currentInfo || duration) {
		QTime currentTime((currentInfo / 3600) % 60, (currentInfo / 60) % 60, currentInfo % 60, (currentInfo * 1000) % 1000);
		QTime totalTime((duration / 3600) % 60, (duration / 60) % 60, duration % 60, (duration * 1000) % 1000);
		QString format = "hh:mm:ss";
		/*if (duration > 3600)
			format = "hh:mm:ss";*/
		tStr1 = currentTime.toString(format) ;
		tStr2 = totalTime.toString(format);
	}
	labelDurationLeft->setText(tStr1);
	labelDurationRight->setText(tStr2);
}

void VideoPlayer::videoAvailableChanged(bool available)
{
	/*if (!available) {
		disconnect(fullscreenButton, SIGNAL(clicked(bool)), videoWidget->qvideoWidget, SLOT(setFullScreen(bool)));
		disconnect(videoWidget->qvideoWidget, SIGNAL(fullScreenChanged(bool)), fullscreenButton, SLOT(setChecked(bool)));
		videoWidget->qvideoWidget->setFullScreen(false);
	}
	else {
		connect(fullscreenButton, SIGNAL(clicked(bool)), videoWidget->qvideoWidget, SLOT(setFullScreen(bool)));
		connect(videoWidget->qvideoWidget, SIGNAL(fullScreenChanged(bool)), fullscreenButton, SLOT(setChecked(bool)));

		if (fullscreenButton->isChecked())
			videoWidget->qvideoWidget->setFullScreen(true);
	}*/
	if (!available) {
		disconnect(fullscreenButton, SIGNAL(clicked(bool)), videoWidget, SLOT(setFullScreen(bool)));
		disconnect(videoWidget, SIGNAL(fullScreenChanged(bool)), fullscreenButton, SLOT(setChecked(bool)));
		videoWidget->setFullScreen(false);
	}
	else {
		connect(fullscreenButton, SIGNAL(clicked(bool)), videoWidget, SLOT(setFullScreen(bool)));
		connect(videoWidget, SIGNAL(fullScreenChanged(bool)), fullscreenButton, SLOT(setChecked(bool)));

		if (fullscreenButton->isChecked())
			videoWidget->setFullScreen(true);
	}
}

void VideoPlayer::mediaStateChanged(QMediaPlayer::State state)
{
    switch(state) {
    case QMediaPlayer::PlayingState:
        //playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        break;
    default:
        //playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        break;
    }
}

void VideoPlayer::setTrackInfo(const QString &info)
{
	trackInfo = info;
	if (!statusInfo.isEmpty())
		titleLable->setText(QString("%1 | %2").arg(trackInfo).arg(statusInfo));
		//setWindowTitle(QString("%1 | %2").arg(trackInfo).arg(statusInfo));
	else
		titleLable->setText(trackInfo);
		//setWindowTitle(trackInfo);
}

void VideoPlayer::setStatusInfo(const QString &info)
{
	statusInfo = info;
	if (!statusInfo.isEmpty())
		titleLable->setText(QString("%1 | %2").arg(trackInfo).arg(statusInfo));
		//setWindowTitle(QString("%1 | %2").arg(trackInfo).arg(statusInfo));
	else
		titleLable->setText(trackInfo);
		//setWindowTitle(trackInfo);
}

void VideoPlayer::statusChanged(QMediaPlayer::MediaStatus status)
{
	//handleCursor(status);

	// handle status message
	switch (status) {
	case QMediaPlayer::UnknownMediaStatus:
	case QMediaPlayer::NoMedia:
	case QMediaPlayer::LoadedMedia:
	case QMediaPlayer::BufferingMedia:
	case QMediaPlayer::BufferedMedia:
		setStatusInfo(QString());
		break;
	case QMediaPlayer::LoadingMedia:
		setStatusInfo(tr("Loading..."));
		break;
	case QMediaPlayer::StalledMedia:
		setStatusInfo(tr("Media Stalled"));
		break;
	case QMediaPlayer::EndOfMedia:
		QApplication::alert(this);
		break;
	default:
		break;
	}
}

void VideoPlayer::metaDataChanged()
{
	if (mediaPlayer->isMetaDataAvailable()) {
		setTrackInfo(QString("%1 - %2")
			.arg(mediaPlayer->metaData(QMediaMetaData::AlbumArtist).toString())
			.arg(mediaPlayer->metaData(QMediaMetaData::Title).toString()));

		if (coverLabel) {
			QUrl url = mediaPlayer->metaData(QMediaMetaData::CoverArtUrlLarge).value<QUrl>();

			coverLabel->setPixmap(!url.isEmpty()
				? QPixmap(url.toString())
				: QPixmap());
		}
	}
}

void VideoPlayer::setPosition(int position)
{
    mediaPlayer->setPosition(position);
}

void VideoPlayer::minizeWin()
{
	this->showMinimized();
}

void VideoPlayer::maxWin()
{
	if (isMax) {
		this->showNormal();
	}
	else {
		this->showMaximized();
	}
	isMax = !isMax;
}

//void VideoPlayer::mousePressEvent(QMouseEvent *e)
//{
//	startPos = e->globalPos();
//	clickPos = e->pos();
//
//	if (e->button() == Qt::LeftButton) {
//		if (e->type() == QEvent::MouseButtonPress) {
//			isPress = true;
//		}
//		else if (e->type() == QEvent::MouseButtonDblClick /*&& e->pos().y() <= TITLE_HEIGHT*/) {
//			this->maxWin();
//		}
//	}
//}
//
//void VideoPlayer::mouseMoveEvent(QMouseEvent *e)
//{
//	if (isMax || !isPress) {
//		return;
//	}
//	this->move(e->globalPos() - clickPos);
//}
//
//void VideoPlayer::mouseReleaseEvent(QMouseEvent *)
//{
//	isPress = false;
//}


void VideoPlayer::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		this->m_drag = true;
		this->dragPos = event->pos();
		this->resizeDownPos = event->globalPos();
		this->mouseDownRect = this->rect();
	}
}
void VideoPlayer::mouseMoveEvent(QMouseEvent * event)
{
	if (resizeRegion != Default)
	{
		handleResize();
		return;
	}
	if (m_move) {
		move(event->globalPos() - dragPos);
		return;
	}
	QPoint clientCursorPos = event->pos();
	QRect r = this->rect();
	QRect resizeInnerRect(resizeBorderWidth, resizeBorderWidth, r.width() - 2 * resizeBorderWidth, r.height() - 2 * resizeBorderWidth);//内圈的大小


	//QSize winSize = size();
	playlistSize = playlistView->size();
	QRect resizePlayWidgetRect(resizeBorderWidth,                                   resizeBorderWidth,   resizeBorderWidth + videoWidget->size().width(),   r.height() - 2 * resizeBorderWidth);
	QRect resizePlayListRect  (resizeBorderWidth + videoWidget->size().width() + 5, resizeBorderWidth,   playlistSize.width(),                              r.height() - 2 * resizeBorderWidth);

	// 如果鼠标位置在外圈里面 但不在内圈里面
	if (r.contains(clientCursorPos) && !resizeInnerRect.contains(clientCursorPos)) 
	{ //调整窗体大小
		ResizeRegion resizeReg = getResizeRegion(clientCursorPos);
		setResizeCursor(resizeReg);
		if (m_drag && (event->buttons() & Qt::LeftButton)) {
			resizeRegion = resizeReg;
			handleResize();
		}
	}
	else if (r.contains(clientCursorPos) && !resizePlayWidgetRect.contains(clientCursorPos) && !resizePlayListRect.contains(clientCursorPos))
	{
		ResizeRegion resizeReg = Middle;
		setResizeCursor(East);
		if (m_drag && (event->buttons() & Qt::LeftButton)) {
			resizeRegion = resizeReg;
			handleResize();
		}
	}
	else //否则在内圈里面的话就做移动窗体的操作
	{ //移动窗体
		setCursor(Qt::ArrowCursor);
		if (m_drag && (event->buttons() & Qt::LeftButton)) {
			m_move = true;
			move(event->globalPos() - dragPos);
		}
	}
}

//做鼠标释放后的工作
void VideoPlayer::mouseReleaseEvent(QMouseEvent *event)
{
	m_drag = false;
	if (m_move) {
		m_move = false;
		handleMove(event->globalPos()); //  移动窗口 且若鼠标放开后若超出屏幕区域自动吸附于屏幕顶部/左侧/右侧
	}
	resizeRegion = Default;
	setCursor(Qt::ArrowCursor);
}

//设置鼠标显示的图案 上下左右等方向
void VideoPlayer::setResizeCursor(ResizeRegion region)
{
	switch (region)
	{
	case North:
	case South:
		setCursor(Qt::SizeVerCursor);
		break;
	case East:
	case West:
		setCursor(Qt::SizeHorCursor);
		break;
	case NorthWest:
	case SouthEast:
		setCursor(Qt::SizeFDiagCursor);
		break;
	default:
		setCursor(Qt::SizeBDiagCursor);
		break;
	}
}

//判断鼠标应该显示的方位
ResizeRegion VideoPlayer::getResizeRegion(QPoint clientPos)
{
	if (clientPos.y() <= resizeBorderWidth) {
		if (clientPos.x() <= resizeBorderWidth)
			return NorthWest;
		else if (clientPos.x() >= this->width() - resizeBorderWidth)
			return NorthEast;
		else
			return North;
	}
	else if (clientPos.y() >= this->height() - resizeBorderWidth) {
		if (clientPos.x() <= resizeBorderWidth)
			return SouthWest;
		else if (clientPos.x() >= this->width() - resizeBorderWidth)
			return SouthEast;
		else
			return South;
	}
	else {
		if (clientPos.x() <= resizeBorderWidth)
			return West;
		else
			return East;
	}
}

//移动窗口 并确保窗口显示在屏幕以内
void VideoPlayer::handleMove(QPoint pt)
{
	QPoint currentPos = pt - dragPos;
	if (currentPos.x()<QApplication::desktop()->x()) { //吸附于屏幕左侧
		currentPos.setX(QApplication::desktop()->x());
	}
	else if (currentPos.x() + this->width()>QApplication::desktop()->width()) { //吸附于屏幕右侧
		currentPos.setX(QApplication::desktop()->width() - this->width());
	}
	if (currentPos.y()<QApplication::desktop()->y()) { //吸附于屏幕顶部
		currentPos.setY(QApplication::desktop()->y());
	}
	else if (currentPos.y() + this->height()>QApplication::desktop()->height()) { //吸附于屏幕右侧
		currentPos.setY(QApplication::desktop()->height() - this->height());
	}
	move(currentPos);
}

//重新调整窗口大小
void VideoPlayer::handleResize()
{
	int xdiff = QCursor::pos().x() - resizeDownPos.x(); //改变的宽度
	int ydiff = QCursor::pos().y() - resizeDownPos.y(); //改变的高度
	switch (resizeRegion) //根据不同的方向确定不同的改变方式
	{
	case East:
	{
				 resize(mouseDownRect.width() + xdiff, this->height());
				 videoWidget->resize(500, videoWidget->height());
				 break;
	}
	case West:
	{
				 resize(mouseDownRect.width() - xdiff, this->height());
				 move(resizeDownPos.x() + xdiff, this->y());
				 break;
	}
	case South:
	{
				  resize(this->width(), mouseDownRect.height() + ydiff);
				  break;
	}
	case North:
	{
				  resize(this->width(), mouseDownRect.height() - ydiff);
				  move(this->x(), resizeDownPos.y() + ydiff);
				  break;
	}
	case SouthEast:
	{
					  resize(mouseDownRect.width() + xdiff, mouseDownRect.height() + ydiff);
					  break;
	}
	case NorthEast:
	{
					  resize(mouseDownRect.width() + xdiff, mouseDownRect.height() - ydiff);
					  move(this->x(), resizeDownPos.y() + ydiff);
					  break;
	}
	case NorthWest:
	{
					  resize(mouseDownRect.width() - xdiff, mouseDownRect.height() - ydiff);
					  move(resizeDownPos.x() + xdiff, resizeDownPos.y() + ydiff);
					  break;
	}
	case SouthWest:
	{
					  resize(mouseDownRect.width() - xdiff, mouseDownRect.height() + ydiff);
					  move(resizeDownPos.x() + xdiff, this->y());
					  break;
	}
	case Middle:
	{
				   videoWidget->resize(videoWidget->width() + xdiff, videoWidget->height());
				   playlistView->resize(playlistView->width() - xdiff, playlistView->height());
	}
	}
}

void VideoPlayer::showColorDialog()
{
	if (!colorDialog) {
		QSlider *brightnessSlider = new QSlider(Qt::Horizontal);
		brightnessSlider->setRange(-100, 100);
		brightnessSlider->setValue(videoWidget->brightness());
		connect(brightnessSlider, SIGNAL(sliderMoved(int)), videoWidget, SLOT(setBrightness(int)));
		connect(videoWidget, SIGNAL(brightnessChanged(int)), brightnessSlider, SLOT(setValue(int)));

		QSlider *contrastSlider = new QSlider(Qt::Horizontal);
		contrastSlider->setRange(-100, 100);
		contrastSlider->setValue(videoWidget->contrast());
		connect(contrastSlider, SIGNAL(sliderMoved(int)), videoWidget, SLOT(setContrast(int)));
		connect(videoWidget, SIGNAL(contrastChanged(int)), contrastSlider, SLOT(setValue(int)));

		QSlider *hueSlider = new QSlider(Qt::Horizontal);
		hueSlider->setRange(-100, 100);
		hueSlider->setValue(videoWidget->hue());
		connect(hueSlider, SIGNAL(sliderMoved(int)), videoWidget, SLOT(setHue(int)));
		connect(videoWidget, SIGNAL(hueChanged(int)), hueSlider, SLOT(setValue(int)));

		QSlider *saturationSlider = new QSlider(Qt::Horizontal);
		saturationSlider->setRange(-100, 100);
		saturationSlider->setValue(videoWidget->saturation());
		connect(saturationSlider, SIGNAL(sliderMoved(int)), videoWidget, SLOT(setSaturation(int)));
		connect(videoWidget, SIGNAL(saturationChanged(int)), saturationSlider, SLOT(setValue(int)));

		QFormLayout *layout = new QFormLayout;
		layout->addRow(tr("Brightness"), brightnessSlider);
		layout->addRow(tr("Contrast"), contrastSlider);
		layout->addRow(tr("Hue"), hueSlider);
		layout->addRow(tr("Saturation"), saturationSlider);

		QPushButton *button = new QPushButton(tr("Close"));
		layout->addRow(button);

		colorDialog = new QDialog(this);
		colorDialog->setWindowTitle(tr("Color Options"));
		colorDialog->setLayout(layout);

		connect(button, SIGNAL(clicked()), colorDialog, SLOT(close()));
	}
	colorDialog->show();
}