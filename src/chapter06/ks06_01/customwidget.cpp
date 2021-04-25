/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: customwidget.cpp
\brief	
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9 

*/
#include "customwidget.h"
#include <QLabel>
#include <QMovie>
#include <QPainter>
#include <QPaintEvent>


CCustomWidget::CCustomWidget(QWidget* parent) 
    : QWidget(parent), m_movie(NULL), m_transparentLabel(NULL) {
	ui.setupUi(this);
    initialize();

}
void CCustomWidget::initialize() {
    // 构建QMovie对象
    QString imgStr = QString(":/images/rainman.gif");
    m_movie = new QMovie(imgStr);
    m_movie->setScaledSize(QSize(ui.label_gif->geometry().size()));
    m_movie->start();
    ui.label_gif->setMovie(m_movie); // 为文本标签设置movie。就能显示动画了。

    // 显示透明文本
    m_transparentLabel = new QLabel(this);
    m_transparentLabel->setText("Can you see me?");
    m_transparentLabel->setGeometry(100, 250, 100, 20);
    m_transparentLabel->setStyleSheet("color:rgb(255, 48, 190);border:none"); // 设置标签为透明,border:none
}


void CCustomWidget::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);

    m_movie->setScaledSize(QSize(ui.label_gif->geometry().size()));

    QRect rctGif = ui.label_gif->geometry();
    int x = rctGif.x() ;    // 调整x，y保证透明文本标签可以覆盖到gif
    int y = rctGif.y() + rctGif.height() / 6;
    m_transparentLabel->setGeometry(x, y, 100, 20);
}
