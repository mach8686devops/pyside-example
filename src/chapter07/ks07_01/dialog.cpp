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
#include <QGridLayout>
#include <QPainter>

#include "customwidget.h"


CDialog::CDialog(QWidget* parent)
    : QDialog(parent) {
	ui.setupUi(this);

    QGridLayout* gridLayout = new QGridLayout(ui.widget);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));

    m_pWidget = new CCustomWidget(this);
    gridLayout->addWidget(m_pWidget, 0, 0);

    // 下面代码构造的QLabel对象将覆盖在 m_pWidget 的上方。因此得出结论，先创建的控件在下，后创建的控件在上。
    QLabel* pLabel = new QLabel(this);
    pLabel->setStyleSheet("color:rgb(0, 255,0)");
    pLabel->setText("Hi..................I'm label in CDialog.");
    pLabel->setGeometry(0, 45, 400, 30);

    connect(ui.buttonBox, &QDialogButtonBox::accepted,
            this, &CDialog::accept);
    connect(ui.buttonBox, &QDialogButtonBox::rejected,
            this, &CDialog::reject);	
}

void CDialog::paintEvent(QPaintEvent *event) {

    QDialog::paintEvent(event); // 先调用父类接口

    QPainter painter;
    painter.begin(this);
    QFont ft;
    ft.setPointSizeF(30);
    painter.setFont(ft);
    painter.setPen(Qt::blue);
    // 下面代码绘制的文本始终显示在本控件的底层,在m_pWidget的下层。
    painter.drawText(QPointF(0, m_pWidget->geometry().bottom()+5), "draw text in cdialog.");
    painter.end();

}
