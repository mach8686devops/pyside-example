﻿/*! 
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
#include <QLineF>
#include <QMovie>
#include <QPainter>
#include <QPaintEvent>
#include <QPointF>


CCustomWidget::CCustomWidget(QWidget* parent) : QWidget(parent) {
	ui.setupUi(this);
	initialize();
}
void CCustomWidget::initialize() {
    m_img = QImage(":/images/rainman.gif");
}


void CCustomWidget::resizeEvent(QResizeEvent *event) {
	QWidget::resizeEvent(event);
}

void CCustomWidget::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);

    QPainter painter;
    painter.begin(this);

    // 画笔
    QPen pn;
    pn.setColor(Qt::darkGray);  // 颜色
    pn.setStyle(Qt::DashLine);  // 画笔样式
    pn.setWidthF(10);           // 画笔宽度
    pn.setCapStyle(Qt::RoundCap);// 画笔顶端样式
    pn.setJoinStyle(Qt::RoundJoin); // 拐点样式
    painter.setPen(pn);

    // 头顶的帽子
    QLineF linef(QPointF(100, 20), QPointF(400, 20));
    painter.drawLine(linef);

    QLinearGradient linearGradient(QPointF(120, 50),
                                   QPointF(120, 170));

    linearGradient.setSpread(QGradient::PadSpread);
    linearGradient.setColorAt(0, Qt::yellow);
    linearGradient.setColorAt(1, Qt::red);
    painter.setBrush(linearGradient);

    pn.setStyle(Qt::SolidLine);
    pn.setColor(Qt::black);
    pn.setWidthF(3);
    painter.setPen(pn);

    // 脸
    QRectF rctf(120, 50, 260, 120);
    painter.drawRect(rctf);

    QBrush brsh(Qt::blue, Qt::CrossPattern);
    brsh.setColor(Qt::gray);
    brsh.setStyle(Qt::SolidPattern);
    painter.setBrush(brsh);

    // 左侧耳朵
    QPolygonF polygonLeft;
    polygonLeft << QPointF(84, 70)
                << QPointF(64, 100)
                << QPointF(84, 130)
                << QPointF(104, 100);
    painter.drawPolygon(polygonLeft);

    // 右侧耳朵
    QPolygonF polygonRight;
    polygonRight << QPointF(422, 66)
                << QPointF(402, 96)
                << QPointF(422, 126)
                << QPointF(442, 96);
    painter.drawPolygon(polygonRight);

    // 嘴巴
    QPolygonF polyline;
    polyline<< QPointF(154, 146)
            << QPointF(172, 156)
            << QPointF(325, 154)
            << QPointF(344, 135);
    painter.drawPolyline(polyline);

    brsh.setColor(Qt::blue);
    painter.setBrush(brsh);

    // 眼睛
    painter.drawEllipse(154, 79, 32, 33); // 左眼
        // 小试牛刀，体验一下坐标变换
        painter.save(); // 保存当前配置，包括画笔、画刷、字体、矩阵等。

        brsh.setColor(Qt::black);
        painter.setBrush(brsh);

        pn.setColor(Qt::green);
        pn.setWidthF(2);
        painter.setPen(pn);

        painter.translate(170, 95); // 把瞳孔画在眼睛(椭圆)的中心位置
        painter.rotate(45);
        painter.drawRect(-5, -5, 10, 10);

        painter.restore();// 恢复(这次save)之前的配置

    painter.drawEllipse(300, 79, 32, 33); // 右眼
        // 右边也来一下
        painter.save();

        brsh.setColor(Qt::black);
        painter.setBrush(brsh);

        pn.setColor(Qt::green);
        pn.setWidthF(2);
        painter.setPen(pn);

        painter.translate(316, 95); // 把瞳孔画在眼睛(椭圆)的中心位置
        painter.rotate(45);
        painter.drawRect(-5, -5, 10, 10);
        painter.restore();

    QFont ft(QString::fromLocal8Bit("宋体"));
    //ft.setFamily(QString::fromLocal8Bit("宋体"));
    ft.setPointSizeF(26);
    painter.setFont(ft);
    painter.setPen(Qt::red);

    // 打招呼
    painter.drawText(QPointF(142, 296), "Hi, I'm ROBO!");

    // 鼻子
    QRectF rctChord(219,110,45,60);
    painter.drawChord(rctChord,
                      40*16,    // 起始角度，需要把角度(40)转换为弧度
                      103*16);  // 跨度

    brsh.setColor(Qt::darkMagenta);
    painter.setBrush(brsh);

    // 左脚
    QRectF rctPieLeft(20.5,200.5,269,85);
    painter.drawPie(rctPieLeft,
                    90*16,  // 起始弧度
                    90*16); // 跨度

    // 右脚
    QRectF rctPieRight(221,200.5,269,85);
    painter.drawPie(rctPieRight,
                    0*16,
                    90*16);


    // 来张动图? 其实显示的是张静态图片
    QRectF rctImage(51,300.5,300,300);
    painter.drawImage(rctImage, m_img);

    painter.end();
}

