/********************************************************************************
** Form generated from reading UI file 'myplayer.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYPLAYER_H
#define UI_MYPLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qvideowidget.h>

QT_BEGIN_NAMESPACE

class Ui_MyP
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *logoButton;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *lockButton;
    QPushButton *minButton;
    QPushButton *maxButton;
    QPushButton *closeButton;
    QVBoxLayout *verticalLayout;
    QVideoWidget *playWidget;
    QHBoxLayout *horizontalLayout_6;
    QLabel *lefttimeLabel;
    QSlider *positionSlider;
    QLabel *righttimeLabel;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *volumeButton;
    QSlider *volumeSlider;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout;
    QPushButton *openButton;
    QPushButton *previousButton;
    QPushButton *playButton;
    QPushButton *nextButton;
    QPushButton *stopButton;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *settingButton;
    QPushButton *fullscreenButton;
    QPushButton *playlistButton;
    QSpacerItem *horizontalSpacer_6;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *playlistCon;
    QPushButton *deleteButton;
    QPushButton *addButton;
    QSpacerItem *playlistcontrolSpacer;
    QPushButton *closeplaylistButton;
    QListView *listView;

    void setupUi(QWidget *MyP)
    {
        if (MyP->objectName().isEmpty())
            MyP->setObjectName(QStringLiteral("MyP"));
        MyP->resize(763, 443);
        MyP->setStyleSheet(QStringLiteral(""));
        gridLayout = new QGridLayout(MyP);
        gridLayout->setSpacing(2);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(5);
        gridLayout->setContentsMargins(4, 8, 4, 6);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(7);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(2);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        logoButton = new QPushButton(MyP);
        logoButton->setObjectName(QStringLiteral("logoButton"));
        logoButton->setMinimumSize(QSize(75, 15));
        logoButton->setMaximumSize(QSize(75, 15));

        horizontalLayout_7->addWidget(logoButton);

        horizontalSpacer = new QSpacerItem(18, 15, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);

        label = new QLabel(MyP);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(30, 15));
        label->setMaximumSize(QSize(16777215, 15));

        horizontalLayout_7->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(18, 15, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(2);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        lockButton = new QPushButton(MyP);
        lockButton->setObjectName(QStringLiteral("lockButton"));
        lockButton->setMinimumSize(QSize(15, 15));
        lockButton->setMaximumSize(QSize(15, 15));
        lockButton->setStyleSheet(QStringLiteral("border-image: url(:/trash.png);"));

        horizontalLayout_4->addWidget(lockButton);

        minButton = new QPushButton(MyP);
        minButton->setObjectName(QStringLiteral("minButton"));
        minButton->setMinimumSize(QSize(15, 15));
        minButton->setMaximumSize(QSize(15, 15));
        minButton->setStyleSheet(QStringLiteral("border-image: url(:/minus.png);"));

        horizontalLayout_4->addWidget(minButton);

        maxButton = new QPushButton(MyP);
        maxButton->setObjectName(QStringLiteral("maxButton"));
        maxButton->setMinimumSize(QSize(15, 15));
        maxButton->setMaximumSize(QSize(15, 15));
        maxButton->setStyleSheet(QStringLiteral("border-image: url(:/maximize.png);"));

        horizontalLayout_4->addWidget(maxButton);

        closeButton = new QPushButton(MyP);
        closeButton->setObjectName(QStringLiteral("closeButton"));
        closeButton->setMinimumSize(QSize(15, 15));
        closeButton->setMaximumSize(QSize(15, 15));
        closeButton->setStyleSheet(QStringLiteral("border-image: url(:/cross.png);"));

        horizontalLayout_4->addWidget(closeButton);


        horizontalLayout_7->addLayout(horizontalLayout_4);


        verticalLayout_2->addLayout(horizontalLayout_7);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        playWidget = new QVideoWidget(MyP);
        playWidget->setObjectName(QStringLiteral("playWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(playWidget->sizePolicy().hasHeightForWidth());
        playWidget->setSizePolicy(sizePolicy);
        playWidget->setMinimumSize(QSize(160, 90));
        playWidget->setStyleSheet(QStringLiteral(""));

        verticalLayout->addWidget(playWidget);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(2);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        lefttimeLabel = new QLabel(MyP);
        lefttimeLabel->setObjectName(QStringLiteral("lefttimeLabel"));
        lefttimeLabel->setMinimumSize(QSize(45, 15));
        lefttimeLabel->setMaximumSize(QSize(45, 15));

        horizontalLayout_6->addWidget(lefttimeLabel);

        positionSlider = new QSlider(MyP);
        positionSlider->setObjectName(QStringLiteral("positionSlider"));
        positionSlider->setMinimumSize(QSize(0, 15));
        positionSlider->setMaximumSize(QSize(16777215, 15));
        positionSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_6->addWidget(positionSlider);

        righttimeLabel = new QLabel(MyP);
        righttimeLabel->setObjectName(QStringLiteral("righttimeLabel"));
        righttimeLabel->setMinimumSize(QSize(45, 15));
        righttimeLabel->setMaximumSize(QSize(45, 15));

        horizontalLayout_6->addWidget(righttimeLabel);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(2);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_3 = new QSpacerItem(28, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        volumeButton = new QPushButton(MyP);
        volumeButton->setObjectName(QStringLiteral("volumeButton"));
        volumeButton->setMinimumSize(QSize(15, 15));
        volumeButton->setMaximumSize(QSize(15, 15));
        volumeButton->setStyleSheet(QStringLiteral("border-image: url(:/mute.png);"));

        horizontalLayout_3->addWidget(volumeButton);

        volumeSlider = new QSlider(MyP);
        volumeSlider->setObjectName(QStringLiteral("volumeSlider"));
        volumeSlider->setMinimumSize(QSize(65, 15));
        volumeSlider->setMaximumSize(QSize(65, 15));
        volumeSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(volumeSlider);


        horizontalLayout_5->addLayout(horizontalLayout_3);

        horizontalSpacer_4 = new QSpacerItem(103, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        openButton = new QPushButton(MyP);
        openButton->setObjectName(QStringLiteral("openButton"));
        openButton->setMinimumSize(QSize(15, 15));
        openButton->setMaximumSize(QSize(15, 15));
        openButton->setStyleSheet(QStringLiteral("border-image: url(:/folder.png);"));

        horizontalLayout->addWidget(openButton);

        previousButton = new QPushButton(MyP);
        previousButton->setObjectName(QStringLiteral("previousButton"));
        previousButton->setMinimumSize(QSize(15, 15));
        previousButton->setMaximumSize(QSize(15, 15));
        previousButton->setStyleSheet(QStringLiteral("border-image: url(:/skip-back.png);"));

        horizontalLayout->addWidget(previousButton);

        playButton = new QPushButton(MyP);
        playButton->setObjectName(QStringLiteral("playButton"));
        playButton->setMinimumSize(QSize(15, 15));
        playButton->setMaximumSize(QSize(15, 15));
        playButton->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(playButton);

        nextButton = new QPushButton(MyP);
        nextButton->setObjectName(QStringLiteral("nextButton"));
        nextButton->setMinimumSize(QSize(15, 15));
        nextButton->setMaximumSize(QSize(15, 15));
        nextButton->setStyleSheet(QStringLiteral("border-image: url(:/skip-forward.png);"));

        horizontalLayout->addWidget(nextButton);

        stopButton = new QPushButton(MyP);
        stopButton->setObjectName(QStringLiteral("stopButton"));
        stopButton->setMinimumSize(QSize(15, 15));
        stopButton->setMaximumSize(QSize(15, 15));
        stopButton->setStyleSheet(QStringLiteral("border-image: url(:/stop.png);"));

        horizontalLayout->addWidget(stopButton);


        horizontalLayout_5->addLayout(horizontalLayout);

        horizontalSpacer_5 = new QSpacerItem(103, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        settingButton = new QPushButton(MyP);
        settingButton->setObjectName(QStringLiteral("settingButton"));
        settingButton->setMinimumSize(QSize(15, 15));
        settingButton->setMaximumSize(QSize(15, 15));
        settingButton->setStyleSheet(QStringLiteral("border-image: url(:/cog.png);"));

        horizontalLayout_2->addWidget(settingButton);

        fullscreenButton = new QPushButton(MyP);
        fullscreenButton->setObjectName(QStringLiteral("fullscreenButton"));
        fullscreenButton->setMinimumSize(QSize(15, 15));
        fullscreenButton->setMaximumSize(QSize(15, 15));
        fullscreenButton->setStyleSheet(QStringLiteral("border-image: url(:/expand.png);"));

        horizontalLayout_2->addWidget(fullscreenButton);

        playlistButton = new QPushButton(MyP);
        playlistButton->setObjectName(QStringLiteral("playlistButton"));
        playlistButton->setMinimumSize(QSize(15, 15));
        playlistButton->setMaximumSize(QSize(15, 15));
        playlistButton->setStyleSheet(QStringLiteral("border-image: url(:/paper.png);"));

        horizontalLayout_2->addWidget(playlistButton);


        horizontalLayout_5->addLayout(horizontalLayout_2);

        horizontalSpacer_6 = new QSpacerItem(28, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_5);


        verticalLayout_2->addLayout(verticalLayout);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(7);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        playlistCon = new QHBoxLayout();
        playlistCon->setSpacing(6);
        playlistCon->setObjectName(QStringLiteral("playlistCon"));
        playlistCon->setContentsMargins(0, 0, 0, 0);
        deleteButton = new QPushButton(MyP);
        deleteButton->setObjectName(QStringLiteral("deleteButton"));
        deleteButton->setMinimumSize(QSize(15, 15));
        deleteButton->setMaximumSize(QSize(15, 15));
        deleteButton->setStyleSheet(QStringLiteral("border-image: url(:/trash.png);"));

        playlistCon->addWidget(deleteButton);

        addButton = new QPushButton(MyP);
        addButton->setObjectName(QStringLiteral("addButton"));
        addButton->setMinimumSize(QSize(15, 15));
        addButton->setMaximumSize(QSize(15, 15));
        addButton->setStyleSheet(QStringLiteral("border-image: url(:/paper.png);"));

        playlistCon->addWidget(addButton);

        playlistcontrolSpacer = new QSpacerItem(83, 13, QSizePolicy::Expanding, QSizePolicy::Minimum);

        playlistCon->addItem(playlistcontrolSpacer);

        closeplaylistButton = new QPushButton(MyP);
        closeplaylistButton->setObjectName(QStringLiteral("closeplaylistButton"));
        closeplaylistButton->setMinimumSize(QSize(15, 15));
        closeplaylistButton->setMaximumSize(QSize(15, 15));
        closeplaylistButton->setStyleSheet(QStringLiteral("border-image: url(:/cross.png);"));

        playlistCon->addWidget(closeplaylistButton);


        verticalLayout_3->addLayout(playlistCon);

        listView = new QListView(MyP);
        listView->setObjectName(QStringLiteral("listView"));

        verticalLayout_3->addWidget(listView);


        gridLayout->addLayout(verticalLayout_3, 0, 1, 1, 1);


        retranslateUi(MyP);

        QMetaObject::connectSlotsByName(MyP);
    } // setupUi

    void retranslateUi(QWidget *MyP)
    {
        MyP->setWindowTitle(QApplication::translate("MyP", "MyPlayer", 0));
        logoButton->setText(QApplication::translate("MyP", "LOGO", 0));
        label->setText(QApplication::translate("MyP", "just test test test.mp4-20160224............just test test test.mp4-20160224", 0));
        lockButton->setText(QString());
        minButton->setText(QString());
        maxButton->setText(QString());
        closeButton->setText(QString());
        lefttimeLabel->setText(QApplication::translate("MyP", "00:00:00", 0));
        righttimeLabel->setText(QApplication::translate("MyP", "00:00:00", 0));
        volumeButton->setText(QString());
        openButton->setText(QString());
        previousButton->setText(QString());
        playButton->setText(QString());
        nextButton->setText(QString());
        stopButton->setText(QString());
        settingButton->setText(QString());
        fullscreenButton->setText(QString());
        playlistButton->setText(QString());
        deleteButton->setText(QString());
        addButton->setText(QString());
        closeplaylistButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MyP: public Ui_MyP {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYPLAYER_H
