
#include "videoplayer.h"
#include "ui_myplayer.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    VideoPlayer player;
	player.setWindowFlags(Qt::FramelessWindowHint);
    //player.resize(320, 240);
    player.show();

    return app.exec();
}
