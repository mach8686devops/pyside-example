/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: address.cpp
\brief  CWidgetAddress类的实现文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9
*/
#include "address.h"


CWidgetAddress::CWidgetAddress(QWidget* pParent) : QWidget(pParent) {
    ui.setupUi(this);

	//connect(ui.m_btnSave, SIGNAL(clicked()), this, SLOT(slot_addressSaved()));
	connect(ui.m_btnSave, &QPushButton::clicked,
        this, &CWidgetAddress::slot_btnSaveClicked);
}

CWidgetAddress::~CWidgetAddress(){
	
}


void CWidgetAddress::slot_btnSaveClicked(){
    QString str = ui.m_lineEdit->text();
    emit sig_addressSaved(str);
}

