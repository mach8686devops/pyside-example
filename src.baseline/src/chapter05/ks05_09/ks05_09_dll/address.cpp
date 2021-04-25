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
#include "ks05_09/address.h"
#include "ui_address.h" // 头文件名称来自: address.ui  ---> ui_address.h

CWidgetAddress::CWidgetAddress(QWidget* pParent) :
    QDialog(pParent),
    m_pUi(new Ui::CWidgetAddress) {

    m_pUi->setupUi(this);

    connect(m_pUi->m_btnSave, &QPushButton::clicked,
        this, &CWidgetAddress::slot_btnSaveClicked);
}

CWidgetAddress::~CWidgetAddress(){
    if (NULL != m_pUi) {
        delete m_pUi;
        m_pUi = NULL;
    }	
}


void CWidgetAddress::slot_btnSaveClicked(){

}

