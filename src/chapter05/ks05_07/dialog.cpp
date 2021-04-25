/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: dialog.cpp
\brief  CDialog
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9
*/

#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "dialog.h"


CDialog::CDialog(QWidget* pParent) : QDialog(pParent), m_pCurrentLabel(NULL){
	ui.setupUi(this);

	connect(ui.btnDefault, &QPushButton::clicked, this, &CDialog::slot_setDefaultFont);

	connect(ui.fontComboBox, SIGNAL(currentFontChanged(const QFont &)), this, SLOT(slot_fontFamilyChanged(const QFont &)));
	connect(ui.cbFontSize, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_fontSizeChanged(int)));

	connect(ui.lineEdit, &QLineEdit::selectionChanged, this, &CDialog::slot_selectionChanged);
	connect(ui.lineEdit_2, &QLineEdit::selectionChanged, this, &CDialog::slot_selectionChanged2);
}

CDialog::~CDialog(){
	
}


void CDialog::slot_fontFamilyChanged(const QFont &font){
	if (NULL == m_pCurrentLabel) {
		return;
	}

	int fontSize = ui.cbFontSize->currentText().toInt();
	QFont ft = font;
	ft.setPointSize(fontSize);

	setTextFont(m_pCurrentLabel, ft);
}

void CDialog::slot_fontSizeChanged(int /*idx*/){
	if (NULL == m_pCurrentLabel) {
		return;
	}	
	
	int fontSize = ui.cbFontSize->currentText().toInt();
	QFont ft = ui.fontComboBox->currentFont();
	ft.setPointSize(fontSize);

	setTextFont(m_pCurrentLabel, ft);
}

void CDialog::setTextFont(QLineEdit* pLabel, const QFont& newFont) {
	qDebug() << "setTextFont: " << pLabel;
	if (NULL != pLabel) {
		pLabel->setFont(newFont);
		updateFontWidget();
	}
}

void CDialog::slot_selectionChanged(){
	m_pCurrentLabel = ui.lineEdit;
	updateFontWidget();
}

void CDialog::slot_selectionChanged2() {
	m_pCurrentLabel = ui.lineEdit_2;
	updateFontWidget();
}

/// 用来反显，也就是取得文本标签的字体家族、字号并反显到字体、字号的控件中。
void CDialog::updateFontWidget() {

	if (NULL == m_pCurrentLabel) {
		return;
	}
    // 阻塞信号, 防止信号触发槽函数
    ui.cbFontSize->blockSignals(true);
    ui.fontComboBox->blockSignals(true);

	QFont ft = m_pCurrentLabel->font();
	QString str;
	str.sprintf("%d", ft.pointSize());
    ui.cbFontSize->setCurrentText(str);
    ui.fontComboBox->setCurrentFont(ft);

    // 解除阻塞。解除时顺序要跟阻塞时相反。
    ui.fontComboBox->blockSignals(false);
    ui.cbFontSize->blockSignals(false);

}

void CDialog::slot_setDefaultFont() {
	QFont defaultFont("songti", 12);
	setTextFont(ui.lineEdit, defaultFont);
	setTextFont(ui.lineEdit_2, defaultFont);
}