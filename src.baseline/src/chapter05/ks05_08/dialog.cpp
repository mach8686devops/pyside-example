/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: dialog.cpp
\brief  CDialog 类的实现文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9
*/

#include "address.h"
#include "dialog.h"

#include "myobject.h"


CDialog::CDialog(QWidget* pParent) : QDialog(pParent) {
    ui.setupUi(this);

	initialDialog();
}

CDialog::~CDialog(){

}
void CDialog::initialDialog() {
	
	// 生成自定义控件对象
	CWidgetAddress* pWidgetAddress = new CWidgetAddress(this);
	

	connect(pWidgetAddress, &CWidgetAddress::sig_addressSaved, this, &CDialog::slot_addressSaved);

	// 需要进行自动布局
	QGridLayout *gridLayout_2;
	gridLayout_2 = new QGridLayout(this);
	gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
	gridLayout_2->addWidget(pWidgetAddress, 0, 0, 1, 1);

}


void CDialog::slot_addressSaved(const QString& strAddress){
	
	if (NULL != ui.m_plainTextEdit->document()) {
		QString str = "The Address is:" + strAddress;
        ui.m_plainTextEdit->document()->setPlainText(str);
	}
}

