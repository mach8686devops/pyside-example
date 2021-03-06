/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: graphview.h
\brief 演示用头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/8 
*/

#pragma once
#include <QGraphicsView>

QT_BEGIN_NAMESPACE
class QMouseEvent;
QT_END_NAMESPACE

class CGraphView : public QGraphicsView
{
	Q_OBJECT
public:
	CGraphView(QWidget* parent);
    ~CGraphView();

public:
    QPointF getMousePressPoint() { return m_ptView; }///获取鼠标单击点的坐标
    void addEllipse();
    void addRect();

Q_SIGNALS:
    void viewMouseMove(const QPointF&);
protected:
    void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *e) override;
    virtual void drawBackground(QPainter *painter, const QRectF &rect);

Q_SIGNALS:

private:
    QPointF m_ptView;
    QPointF m_ptScene;
};
