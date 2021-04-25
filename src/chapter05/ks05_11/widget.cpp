/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: widget.cpp
\brief  CWidget
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9
*/

#include "widget.h"


CWidget::CWidget(QWidget* pParent) : QWidget(pParent) {
    ui.setupUi(this);
    ui.plainTextEdit->setPlainText("file detected:");

    //ui.buttonBox->setStyleSheet("color: rgb(0, 255, 255);   \
    //    background-color: rgb(0, 170, 0); ");

    initialStyleSheet();

	connect(ui.cbFontSize, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_fontSizeChanged(int)));

	connect(ui.fontComboBox, &QFontComboBox::currentFontChanged, this, &CWidget::slot_fontFamilyChanged);
}

CWidget::~CWidget(){
	
}


void CWidget::slot_fontFamilyChanged(const QFont &font){
	int fontSize = ui.cbFontSize->currentText().toInt();
	QFont ft = font;
	ft.setPointSize(fontSize);
    ui.plainTextEdit->setFont(ft);
}

void CWidget::slot_fontSizeChanged(int /*idx*/){
	int fontSize = ui.cbFontSize->currentText().toInt();
	QFont ft = ui.fontComboBox->currentFont();
	ft.setPointSize(fontSize);
    ui.plainTextEdit->setFont(ft);
}

void CWidget::initialStyleSheet() {
    QFile file(":/qss/coffee.qss");
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        return;
    }

    QString strStyleSheet = file.readAll();
    setStyleSheet(strStyleSheet);
}