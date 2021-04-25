/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: dialog.cpp
\brief	
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9 
*/
#include "dialog.h"
#include <QtWidgets>

CDialog::CDialog(QWidget* parent) : QDialog(parent), m_currentDirectory("")
{
	ui.setupUi(this);
	initialDialog();
}

void CDialog::initialDialog()
{
	// 初始化控件
	initialControls();

	// 连接信号槽
	connectSignalsAndSlots();

	// 设置按钮状态
	slot_updateButtons();

	setWindowTitle(tr("GIF Player"));
	resize(500, 500);
}


void CDialog::slot_open()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open a GIF"),
		m_currentDirectory);
	if (!fileName.isEmpty())
		openFile(fileName);
}

void CDialog::openFile(const QString &fileName)
{
	m_currentDirectory = QFileInfo(fileName).path();

	m_movie->stop();
	ui.m_movieLabel->setMovie(m_movie);
	m_movie->setFileName(fileName);
	m_movie->start();
    ui.m_pauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    ui.m_pauseButton->setToolTip(tr("Pause"));
	// 更新按钮状态
	slot_updateButtons();
}


void CDialog::slot_updateButtons()
{
	ui.m_pauseButton->setChecked(m_movie->state() == QMovie::Paused);
	ui.m_stopButton->setEnabled(m_movie->state() != QMovie::NotRunning);
}

void CDialog::initialControls()
{
	m_movie = new QMovie(this);
	// 当动画播放完一遍后，就完成了缓存，可以通过滑动条来调整视频播放进度。
	m_movie->setCacheMode(QMovie::CacheAll);

	// 为标签设置对齐方式和尺寸策略
	ui.m_movieLabel->setAlignment(Qt::AlignCenter);
	ui.m_movieLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	ui.m_movieLabel->setBackgroundRole(QPalette::Dark);

	// 初始化滑动条


	// 设置label，将内容缩放以填满控件
	ui.m_movieLabel->setScaledContents(true);

	// 设置按钮
	ui.m_openButton->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));
	ui.m_openButton->setToolTip(tr("Open File"));

	ui.m_pauseButton->setCheckable(true);
    ui.m_pauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay)); // 默认为播放按钮
	ui.m_pauseButton->setToolTip(tr("Pause"));

	ui.m_stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
	ui.m_stopButton->setToolTip(tr("Stop"));

	ui.m_quitButton->setIcon(style()->standardIcon(QStyle::SP_DialogCloseButton));
	ui.m_quitButton->setToolTip(tr("Quit"));
}
void CDialog::slot_pause(bool bPause)
{
    m_movie->setPaused(bPause);
    if (bPause)
    {
        ui.m_pauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        ui.m_pauseButton->setToolTip(tr("Play"));
    }
    else   {
        ui.m_pauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        ui.m_pauseButton->setToolTip(tr("Pause"));
    }
}
void CDialog::connectSignalsAndSlots()
{
	connect(ui.m_openButton, SIGNAL(clicked()), this, SLOT(slot_open()));
    connect(ui.m_pauseButton, SIGNAL(clicked(bool)), this, SLOT(slot_pause(bool)));
	connect(ui.m_stopButton, SIGNAL(clicked()), m_movie, SLOT(stop()));
	connect(ui.m_quitButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(m_movie, SIGNAL(stateChanged(QMovie::MovieState)),
		this, SLOT(slot_updateButtons()));
}
