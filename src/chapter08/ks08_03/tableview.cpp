/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file tableview.cpp
\brief tableview实现文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2019/1
*/

#include "tableview.h"
#include <QtWidgets>

void CTableView::mousePressEvent(QMouseEvent* event) {

    QPoint pt = event->pos();
    QPersistentModelIndex index =  indexAt(pt);
    // 如果本次选择和上次不一样，需要关闭上次的编辑器
    if ((index != m_indexLast) && m_indexLast.isValid()) {
        closePersistentEditor(m_indexLast);
    }

    m_indexLast = index;
    // 新的序号有效，且是允许编辑的列
    if (index.isValid() && (1== index.column())){
        openPersistentEditor(index);
    }
    QTableView::mousePressEvent(event);
}


