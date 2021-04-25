/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: CMainWindow.cpp
\brief	主窗体实现文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9 
*/
#include <QtWidgets>
#include <QGraphicsScene>

#include "base/basedll/baseapi.h"
#include "mainwindow.h"
#include "graphview.h"

CAnimationMenu::CAnimationMenu(const QString& str, QWidget* pParent) :
	QMenu(str, pParent) {
	setMouseTracking(true);  // 处理鼠标跟踪
}

void CAnimationMenu::focusOutEvent(QFocusEvent *event) {
	QMenu::focusOutEvent(event);
	emit sig_focusOut();
}

/////////////////////////////////////////////////////////////////////////
CMainWindow::CMainWindow(QWidget* parent) : 
	QMainWindow(parent),
	m_pAnimaMenuShow(NULL),
	m_bShowMenu(false) {

	initialize();
	createActions();
	createMenus();
	createToolBars();
	createStatusBar();
	connectSignalAndSlot();

	setWindowTitle(tr("Demo"));
	setMinimumSize(160, 160);
	//resize(480, 320);    
	showMaximized(); // 方便计算坐标
	m_nMenubarHeight = menuBar()->height();
}


void CMainWindow::initialize() {
    m_pScene = new QGraphicsScene(this);
    m_pView = new CGraphView(this);
    m_pView->setScene(m_pScene);
    QRectF rct(0, 0, 400,400);
    m_pScene->setSceneRect(rct);
	setCentralWidget(m_pView);
}

void CMainWindow::connectSignalAndSlot() {
    connect(m_pView, SIGNAL(viewMouseMove(const QPointF&)),
        this, SLOT(onMouseMoveInView(const QPointF&)));
}

/// 鼠标位置更新
void CMainWindow::onMouseMoveInView(const QPointF& pt) {
	QString str;
	str.sprintf("%.2f, %.2f", pt.x(), pt.y());
	m_pMouseLabel->setText(str);
}

void CMainWindow::slot_addRect() {
    m_pView->addRect();
}

void CMainWindow::slot_addEllipse() {
    m_pView->addEllipse();
}

/// 创建状态栏
void CMainWindow::createStatusBar() {
	m_pInfoLabel = new QLabel(tr(""));
	m_pInfoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
	m_pInfoLabel->setAlignment(Qt::AlignCenter);
	statusBar()->addPermanentWidget(m_pInfoLabel);

	m_pMouseLabel = new QLabel("", statusBar());
	m_pMouseLabel->setMinimumWidth(100);
	statusBar()->addPermanentWidget(m_pMouseLabel);

	statusBar()->setStyleSheet("color:white");

	statusBar()->show();
}

#ifndef QT_NO_CLIPBOARD
void CMainWindow::slot_cut() {
    m_pView->cut();
}

void CMainWindow::slot_copy() {
    m_pView->copy();
}

void CMainWindow::slot_paste() {
    m_pView->paste();
}
#endif

void CMainWindow::about() {
	m_pInfoLabel->setText(tr("Invoked <b>Help|About</b>"));
	QMessageBox::about(this, tr("About Menu"),
		tr("The <b>Menu</b> example shows how to create "
			"menu-bar menus and context menus."));
}

void CMainWindow::createActions() {
#ifndef QT_NO_CLIPBOARD
    m_pCutAct = new QAction(QIcon(":/images/cut.png"), tr("Cu&t"), this);
	m_pCutAct->setShortcuts(QKeySequence::Cut);
	m_pCutAct->setStatusTip(tr("Cut the current selection's contents to the "
		"clipboard"));
	connect(m_pCutAct, &QAction::triggered, this, &CMainWindow::slot_cut);

	m_pCopyAct = new QAction(QIcon(":/images/copy.png"), tr("&Copy"), this);
	m_pCopyAct->setShortcuts(QKeySequence::Copy);
	m_pCopyAct->setStatusTip(tr("Copy the current selection's contents to the "
		"clipboard"));
	connect(m_pCopyAct, &QAction::triggered, this, &CMainWindow::slot_copy);

	m_pPasteAct = new QAction(QIcon(":/images/paste.png"), tr("&Paste"), this);
	m_pPasteAct->setShortcuts(QKeySequence::Paste);
	m_pPasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
		"selection"));
	connect(m_pPasteAct, &QAction::triggered, this, &CMainWindow::slot_paste);
#endif

    m_pRectAct = new QAction(tr("addRect"), this);
    m_pRectAct->setStatusTip(tr("add rect to view"));
    connect(m_pRectAct, &QAction::triggered, this, &CMainWindow::slot_addRect);

    m_pEllipseAct = new QAction(tr("addEllipse"), this);
    m_pEllipseAct->setStatusTip(tr("add ellipse to view"));
    connect(m_pEllipseAct, &QAction::triggered, this, &CMainWindow::slot_addEllipse);

    m_pAboutAct = new QAction(tr("&About"), this);
	m_pAboutAct->setStatusTip(tr("Show the application's About box"));
	connect(m_pAboutAct, &QAction::triggered, this, &CMainWindow::about);

	// file operation action
	m_pFileMenuAct = new QAction(tr("file Menu"), this);
	m_pFileMenuAct->setStatusTip(tr("file Menu"));
	connect(m_pFileMenuAct, &QAction::triggered, this, &CMainWindow::slot_fileMenu);
	// file operation action
	m_pOpenFileAct = new QAction(tr("openFile"), this);
	m_pOpenFileAct->setStatusTip(tr("openFile"));
	connect(m_pOpenFileAct, &QAction::triggered, this, &CMainWindow::slot_openFile);
	connect(m_pOpenFileAct, &QAction::triggered, this, &CMainWindow::slot_hideMenu); // 单击菜单项后应该隐藏主菜单
	
	m_pSaveFileAct = new QAction(tr("saveFile"), this);
	m_pSaveFileAct->setStatusTip(tr("saveFile"));
	connect(m_pSaveFileAct, &QAction::triggered, this, &CMainWindow::slot_saveFile);
	connect(m_pSaveFileAct, &QAction::triggered, this, &CMainWindow::slot_hideMenu); // 单击菜单项后应该隐藏主菜单

	m_pCloseFileAct = new QAction(tr("closeFile"), this);
	m_pCloseFileAct->setStatusTip(tr("closeFile"));
	connect(m_pCloseFileAct, &QAction::triggered, this, &CMainWindow::slot_closeFile);
	connect(m_pCloseFileAct, &QAction::triggered, this, &CMainWindow::slot_hideMenu); // 单击菜单项后应该隐藏主菜单

	m_pExitAct = new QAction(tr("exit"), this);
	m_pExitAct->setStatusTip(tr("exit"));
	connect(m_pExitAct, &QAction::triggered, this, &CMainWindow::slot_exit);
	connect(m_pExitAct, &QAction::triggered, this, &CMainWindow::slot_hideMenu); // 单击菜单项后应该隐藏主菜单

}

void CMainWindow::createToolBars() {
	m_pEditToolBar = addToolBar(tr("edit tool bar"));
	m_pEditToolBar->setObjectName("edit tool bar");
	m_pEditToolBar->addAction(m_pFileMenuAct);
#ifndef QT_NO_CLIPBOARD
    m_pEditToolBar->addAction(m_pCutAct);
	m_pEditToolBar->addAction(m_pCopyAct);
	m_pEditToolBar->addAction(m_pPasteAct);
#endif

    m_pEditToolBar->addAction(m_pRectAct);
	m_pEditToolBar->addAction(m_pEllipseAct);
	m_pEditToolBar->setStyleSheet("color:white");
}
void CMainWindow::createMenus() {
	m_pFileMenu = new CAnimationMenu(tr("&File"), this);
	connect(m_pFileMenu, &CAnimationMenu::sig_focusOut, 
			this, &CMainWindow::slot_hideMenu); // 当主菜单失去焦点时，应该隐藏主菜单
	// flag设置为tool和无边框，消除qmenu的popup效果，如果带有二级菜单，则需要进行本设置。如果只有一级菜单，可以不设置。
	m_pFileMenu->setWindowFlags(Qt::CustomizeWindowHint | Qt::Tool | Qt::FramelessWindowHint);

	m_pFileMenu->addAction(m_pOpenFileAct);
	m_pFileMenu->addAction(m_pCloseFileAct);
	m_pFileMenu->addAction(m_pSaveFileAct);
	m_pFileMenu->addAction(m_pExitAct);
}

void CMainWindow::slot_hideMenu() {
	m_bShowMenu = false;
	int s_MenuWidth = m_pFileMenu->width();
	int offsetY = m_nMenubarHeight + m_pEditToolBar->height();
	m_pAnimaMenuShow->setStartValue(QPoint(x(), y() + offsetY));
	m_pAnimaMenuShow->setEndValue(QPoint(x() - s_MenuWidth, y() + offsetY));
	m_pAnimaMenuShow->start();
}
void CMainWindow::slot_fileMenu() {
	int s_MenuWidth = m_pFileMenu->width();
	if (NULL == m_pAnimaMenuShow) {
		m_pAnimaMenuShow = new QPropertyAnimation(m_pFileMenu, "pos");
		connect(m_pAnimaMenuShow, SIGNAL(finished()), this, SLOT(slot_animationMenuFinished()));
		m_pAnimaMenuShow->setDuration(400);
		m_pAnimaMenuShow->setEasingCurve(QEasingCurve::Linear);
	}
	m_bShowMenu = !m_bShowMenu;
	int offsetY = m_nMenubarHeight + m_pEditToolBar->height();
	if (m_bShowMenu) { // 单击时弹出菜单
		m_pFileMenu->show();
		m_pFileMenu->activateWindow();
		m_pFileMenu->setFocus(Qt::ActiveWindowFocusReason);
		m_pAnimaMenuShow->setStartValue(QPoint(x() - s_MenuWidth, y() + offsetY));
		m_pAnimaMenuShow->setEndValue(QPoint(x(), y() + offsetY));
		m_pAnimaMenuShow->start();
	}
	else { // 再次单击时隐藏菜单
		m_pAnimaMenuShow->setStartValue(QPoint(x(), y() + offsetY));
		m_pAnimaMenuShow->setEndValue(QPoint(x() - s_MenuWidth, y() + offsetY));
		m_pAnimaMenuShow->start();
	}
}

void CMainWindow::slot_animationMenuFinished() {
	if (!m_bShowMenu && m_pFileMenu->isVisible()) {
		m_pFileMenu->hide();
	}
}
void CMainWindow::slot_openFile() {
	QMessageBox::information(this, "menu", "openFile triggered!");
}

void CMainWindow::slot_saveFile() {

}

void CMainWindow::slot_closeFile() {

}

void CMainWindow::slot_exit() {

}