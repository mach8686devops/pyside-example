/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: previewwindow.h
\brief  对话框编程示例, 预览窗口类定义头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/10
*/

#include <QtWidgets>
#include "ctrlwindow.h"

CCtrlWindow::CCtrlWindow() {
    ui.setupUi(this);
    connectHintsGroupBox();
    connectTypeGroupBox();

    m_pPreviewWindow = new CPreviewWindow(this);

    connect(ui.quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));

    setWindowTitle(tr("Window Flags"));
    slot_updatePreview();
}

void CCtrlWindow::slot_updatePreview() {
    Qt::WindowFlags flags = 0;

    if (ui.windowRadioButton->isChecked()) {
        flags = Qt::Window;
    } else if (ui.dialogRadioButton->isChecked()) {
        flags = Qt::Dialog;
    } else if (ui.sheetRadioButton->isChecked()) {
        flags = Qt::Sheet;
    } else if (ui.drawerRadioButton->isChecked()) {
        flags = Qt::Drawer;
    } else if (ui.popupRadioButton->isChecked()) {
        flags = Qt::Popup;
    } else if (ui.toolRadioButton->isChecked()) {
        flags = Qt::Tool;
    } else if (ui.toolTipRadioButton->isChecked()) {
        flags = Qt::ToolTip;
    } else if (ui.splashScreenRadioButton->isChecked()) {
        flags = Qt::SplashScreen;
    }

    if (ui.msWindowsFixedSizeDialogCheckBox->isChecked())
        flags |= Qt::MSWindowsFixedSizeDialogHint;
    if (ui.x11BypassWindowManagerCheckBox->isChecked())
        flags |= Qt::X11BypassWindowManagerHint;
    if (ui.framelessWindowCheckBox->isChecked())
        flags |= Qt::FramelessWindowHint;
    if (ui.windowNoShadowCheckBox->isChecked())
        flags |= Qt::NoDropShadowWindowHint;
    if (ui.windowTitleCheckBox->isChecked())
        flags |= Qt::WindowTitleHint;
    if (ui.windowSystemMenuCheckBox->isChecked())
        flags |= Qt::WindowSystemMenuHint;
    if (ui.windowMinimizeButtonCheckBox->isChecked())
        flags |= Qt::WindowMinimizeButtonHint;
    if (ui.windowMaximizeButtonCheckBox->isChecked())
        flags |= Qt::WindowMaximizeButtonHint;
    if (ui.windowCloseButtonCheckBox->isChecked())
        flags |= Qt::WindowCloseButtonHint;
    if (ui.windowContextHelpButtonCheckBox->isChecked())
        flags |= Qt::WindowContextHelpButtonHint;
    if (ui.windowShadeButtonCheckBox->isChecked())
        flags |= Qt::WindowShadeButtonHint;
    if (ui.windowStaysOnTopCheckBox->isChecked())
        flags |= Qt::WindowStaysOnTopHint;
    if (ui.windowStaysOnBottomCheckBox->isChecked())
        flags |= Qt::WindowStaysOnBottomHint;
    if (ui.customizeWindowHintCheckBox->isChecked())
        flags |= Qt::CustomizeWindowHint;

    m_pPreviewWindow->setWindowFlags(flags);


    QPoint pos = m_pPreviewWindow->pos();
    if (pos.x() < 0)
        pos.setX(0);
    if (pos.y() < 0)
        pos.setY(0);
    m_pPreviewWindow->move(pos);
    m_pPreviewWindow->show();
}

void CCtrlWindow::connectTypeGroupBox() {
    connect(ui.windowRadioButton, SIGNAL(clicked()), this, SLOT(slot_updatePreview()));
    connect(ui.dialogRadioButton, SIGNAL(clicked()), this, SLOT(slot_updatePreview()));
    connect(ui.sheetRadioButton, SIGNAL(clicked()), this, SLOT(slot_updatePreview()));
    connect(ui.drawerRadioButton, SIGNAL(clicked()), this, SLOT(slot_updatePreview()));
    connect(ui.popupRadioButton, SIGNAL(clicked()), this, SLOT(slot_updatePreview()));
    connect(ui.toolRadioButton, SIGNAL(clicked()), this, SLOT(slot_updatePreview()));
    connect(ui.toolTipRadioButton, SIGNAL(clicked()), this, SLOT(slot_updatePreview()));
    connect(ui.splashScreenRadioButton, SIGNAL(clicked()), this, SLOT(slot_updatePreview()));

    ui.windowRadioButton->setChecked(true);

}

void CCtrlWindow::connectHintsGroupBox() {
    connect(ui.msWindowsFixedSizeDialogCheckBox, SIGNAL(clicked()), this, SLOT(slot_updatePreview()));
    connect(ui.x11BypassWindowManagerCheckBox, SIGNAL(clicked()), this, SLOT(slot_updatePreview()));
    connect(ui.framelessWindowCheckBox, SIGNAL(clicked()), this, SLOT(slot_updatePreview()));
    connect(ui.windowNoShadowCheckBox, SIGNAL(clicked()), this, SLOT(slot_updatePreview()));
    connect(ui.windowTitleCheckBox, SIGNAL(clicked()), this, SLOT(slot_updatePreview()));
    connect(ui.windowSystemMenuCheckBox, SIGNAL(clicked()), this, SLOT(slot_updatePreview()));
    connect(ui.windowMinimizeButtonCheckBox, SIGNAL(clicked()), this, SLOT(slot_updatePreview()));
    connect(ui.windowMaximizeButtonCheckBox, SIGNAL(clicked()), this, SLOT(slot_updatePreview()));
    connect(ui.windowCloseButtonCheckBox, SIGNAL(clicked()), this, SLOT(slot_updatePreview()));
    connect(ui.windowContextHelpButtonCheckBox, SIGNAL(clicked()), this, SLOT(slot_updatePreview()));
    connect(ui.windowShadeButtonCheckBox, SIGNAL(clicked()), this, SLOT(slot_updatePreview()));
    connect(ui.windowStaysOnTopCheckBox, SIGNAL(clicked()), this, SLOT(slot_updatePreview()));
    connect(ui.windowStaysOnBottomCheckBox, SIGNAL(clicked()), this, SLOT(slot_updatePreview()));
    connect(ui.customizeWindowHintCheckBox, SIGNAL(clicked()), this, SLOT(slot_updatePreview()));

}

