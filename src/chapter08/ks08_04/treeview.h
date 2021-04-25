/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file treeview.h
\brief treeview头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2019/1
*/
#pragma once
#include <QTreeView>

QT_BEGIN_NAMESPACE
class QWidget;
QT_END_NAMESPACE

class CTreeView : public QTreeView {
    Q_OBJECT

public:
	explicit CTreeView(QWidget *parent = nullptr):QTreeView(parent) {}

signals:

protected:
	virtual void mousePressEvent(QMouseEvent *event) override;

private:
	QModelIndex m_indexLast;
};
