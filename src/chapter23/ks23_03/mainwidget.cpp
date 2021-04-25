/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: mainwidget.cpp
\brief  CMainWidget
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9
*/

#include "mainwidget.h"
#include "projects.h"
#include <QtWidgets>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QSqlError>
#include <QSqlQuery>
#include "base/basedll/baseapi.h"
#include "projectinfo.h"
#include "burndown.h"
#include "config.h"
#include "user.h"
#include "sprint.h"
#include "addsprint.h"
#include "addsprint.h"
#include "logindialog.h"


CMainWidget::CMainWidget(QWidget* pParent) : QWidget(pParent), m_pAnimaMenuShow(NULL),
m_bShowMenu(true) {
	ui.setupUi(this);

	initialize();

	createActions();
	createMenus();
	createStatusBar();
	connectSignalAndSlot();

	setWindowTitle(tr("Scrum Bulletin Board"));
	setMinimumSize(160, 160);
	//resize(480, 320);
	showMaximized();

}

CMainWidget::~CMainWidget() {

}

void CMainWidget::initialize() {
	// 初始化数据库 
	initialize_database();
	//ui.btnLogin->setIconSize(ui.btnLogin->size()); 

	// 构建项目一览控件
	m_pWidgetProjects = new CWidgetProjects(this);

	// 构建项目信息界面
	m_pWidgetProjectInfo = new CProjectInfo(this);
	// 构建人员界面
	m_pWidgetUser = new CWidgetUser(this);
	// 构建迭代界面
	m_pWidgetSprint = new CWidgetSprint(this, 1);
	// 构建添加迭代界面
	m_pWidgetAddSprint = new CWidgetAddSprint(this);
	// 构建燃尽图界面
	m_pWidgetBurndown = new CWidgetBurndown(this);

	// 构建QStackedLayout布局对象
	m_pStackedLayout = new QStackedLayout(ui.widget);
	// 将子面对象添加到堆栈布局
	m_pStackedLayout->addWidget(m_pWidgetProjects);		// 0
	m_pStackedLayout->addWidget(m_pWidgetProjectInfo);	// 1
	m_pStackedLayout->addWidget(m_pWidgetUser);			// 2
	m_pStackedLayout->addWidget(m_pWidgetSprint);		// 3
	m_pStackedLayout->addWidget(m_pWidgetAddSprint);	// 4
	m_pStackedLayout->addWidget(m_pWidgetBurndown);		// 5
	// 设置默认页
	m_pStackedLayout->setCurrentIndex(0);
	ui.widget->setLayout(m_pStackedLayout);
}

void CMainWidget::connectSignalAndSlot() {
	connect(ui.btnMenu, &QPushButton::clicked, this, &CMainWidget::slot_menu);
	connect(ui.btnLogin, &QPushButton::clicked, this, &CMainWidget::slot_login);
	connect(m_pWidgetUser, &CWidgetUser::sig_getBack, this, &CMainWidget::slot_getBack);
	connect(m_pWidgetProjectInfo, &CProjectInfo::sig_getBack, this, &CMainWidget::slot_getBack);
	connect(m_pWidgetProjects, &CWidgetProjects::sig_pressed, this, &CMainWidget::slot_pressedProject);
	connect(m_pWidgetAddSprint, &CWidgetAddSprint::sig_getBack, this, &CMainWidget::slot_getBack);
	connect(m_pWidgetSprint, &CWidgetSprint::sig_getBack, this, &CMainWidget::slot_getBack);
	connect(m_pWidgetSprint, &CWidgetSprint::sig_burndown, this, &CMainWidget::slot_showBurndown);
	connect(m_pWidgetBurndown, &CWidgetBurndown::sig_getBackToSprint, this, &CMainWidget::slot_getBackToSprint);

}

/// 创建状态栏
void CMainWidget::createStatusBar() {
	m_pInfoLabel = new QLabel(tr(""));
	m_pInfoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
	m_pInfoLabel->setAlignment(Qt::AlignCenter);
	//statusBar()->addPermanentWidget(m_pInfoLabel);
	//statusBar()->show();
}

void CMainWidget::about() {
	m_pInfoLabel->setText(tr("Invoked <b>Help|About</b>"));
	//	QMessageBox::about(this, tr("About Menu"),
	//		tr("The <b>Menu</b> example shows how to create "
	//			"menu-bar menus and context menus."));
}

void CMainWidget::createActions() {
	// file operation action
	m_pProjectBrowserAct = new QAction(tr("projectBrowser"), this);
	m_pProjectBrowserAct->setStatusTip(tr("projectBrowser"));
	connect(m_pProjectBrowserAct, &QAction::triggered, this, &CMainWidget::slot_projectBrowser);

	m_pAddProjectAct = new QAction(tr("addProject"), this);
	m_pAddProjectAct->setStatusTip(tr("addProject"));
	connect(m_pAddProjectAct, &QAction::triggered, this, &CMainWidget::slot_addProject);

	m_pAddSprintAct = new QAction(tr("addSprint"), this);
	m_pAddSprintAct->setStatusTip(tr("addSprint"));
	connect(m_pAddSprintAct, &QAction::triggered, this, &CMainWidget::slot_addSprint);

	// file operation action
	m_pAddUserAct = new QAction(tr("addUser"), this);
	m_pAddUserAct->setStatusTip(tr("addUser"));
	connect(m_pAddUserAct, &QAction::triggered, this, &CMainWidget::slot_addUser);

	m_pModifyPasswordAct = new QAction(tr("modifyUser"), this);
	m_pModifyPasswordAct->setStatusTip(tr("modifyUser"));
	connect(m_pModifyPasswordAct, &QAction::triggered, this, &CMainWidget::slot_changePassword);

	m_pAboutAct = new QAction(tr("about"), this);
	m_pAboutAct->setStatusTip(tr("about"));
	connect(m_pAboutAct, &QAction::triggered, this, &CMainWidget::slot_about);

	m_pExitAct = new QAction(tr("exit"), this);
	m_pExitAct->setStatusTip(tr("exit"));
	connect(m_pExitAct, &QAction::triggered, this, &CMainWidget::slot_exit);
}

void CMainWidget::createMenus() {
	m_pMenu = new QMenu(tr("&File"), this);
	m_pMenu->setMouseTracking(true);  //接收鼠标事件
									  //flag设置为tool和无边框，消除qmenu的popup效果
	m_pMenu->setWindowFlags(Qt::CustomizeWindowHint | Qt::Tool | Qt::FramelessWindowHint);
	m_pMenu->addAction(m_pProjectBrowserAct);
	m_pMenu->addAction(m_pAddProjectAct);
	m_pMenu->addAction(m_pAddSprintAct);
	m_pMenu->addAction(m_pAddUserAct);
	m_pMenu->addAction(m_pModifyPasswordAct);
	m_pMenu->addAction(m_pAboutAct);
	m_pMenu->addAction(m_pExitAct);
}

void CMainWidget::slot_menu() {
	static int s_MenubarHeight = ui.btnMenu->mapToGlobal(ui.btnMenu->pos()).y() + ui.btnMenu->height();
	int s_MenuWidth = m_pMenu->width();
	if (NULL == m_pAnimaMenuShow) {
		m_pAnimaMenuShow = new QPropertyAnimation(m_pMenu, "pos");
		connect(m_pAnimaMenuShow, SIGNAL(finished()), this, SLOT(slot_animationMenuFinished()));
		m_pAnimaMenuShow->setDuration(400);
		m_pAnimaMenuShow->setEasingCurve(QEasingCurve::Linear);
	}
	if (m_bShowMenu) { // 单击时弹出菜单
		m_pMenu->show();
		int offsetY = s_MenubarHeight;
		m_pAnimaMenuShow->setStartValue(QPoint(x() + width(), y() + offsetY));
		m_pAnimaMenuShow->setEndValue(QPoint(x() + width() - s_MenuWidth, y() + offsetY));
		m_pAnimaMenuShow->start();
	}
	else { // 再次单击时隐藏菜单
		int offsetY = s_MenubarHeight;
		m_pAnimaMenuShow->setStartValue(QPoint(x() + width() - s_MenuWidth, y() + offsetY));
		m_pAnimaMenuShow->setEndValue(QPoint(x() + width(), y() + offsetY));
		m_pAnimaMenuShow->start();
	}
}

void CMainWidget::slot_animationMenuFinished() {
	if (!m_bShowMenu) {
		m_pMenu->hide();
	}
	m_bShowMenu = !m_bShowMenu;
}
void CMainWidget::slot_addUser() {
	m_pWidgetUser->clear();
	m_pStackedLayout->setCurrentIndex(2);
	m_pWidgetUser->setModifyMode(false);
	slot_animationMenuFinished();
}

void CMainWidget::slot_changePassword() {
	if (!CConfig::instance().isAuthorized()) {
		slot_animationMenuFinished();
		QMessageBox::information(this, tr("task"), tr("please login"));
		return;
	}
	m_pStackedLayout->setCurrentIndex(2);
	m_pWidgetUser->setModifyMode(true);
	m_pWidgetUser->loadUser(CConfig::instance().getUser());
	slot_animationMenuFinished();
}

void CMainWidget::updateLoginIcon() {
	QIcon icon;
	if (!CConfig::instance().isAuthorized()) {
		icon = QIcon(":/images/login.png");
		ui.btnLogin->setIcon(icon);
		return;
	}

	QString strId;
	QString strName;
	QString strPassword;
	QByteArray byteArray;
	QSqlQuery sql_query;
	QString strSql;
	strSql = "select photo from users where name = \'";
	strSql += CConfig::instance().getUser();
	strSql += "\'";
	if (sql_query.exec(strSql)) {
		//int role = 0;
		if (sql_query.first()) {
			byteArray = sql_query.value(0).toByteArray();
		}
		else {
			qDebug() << sql_query.lastError();
		}
	}
	else {
		qDebug() << sql_query.lastError();
	}

	QPixmap pixmap;
	pixmap.loadFromData(byteArray);
	icon = pixmap.scaled(ui.btnLogin->width(), ui.btnLogin->height());
	ui.btnLogin->setIcon(icon);
}
void CMainWidget::slot_addProject() {
	if (!CConfig::instance().isAuthorized()) {
		slot_animationMenuFinished();
		QMessageBox::information(this, tr("task"), tr("please login"));
		return;
	}
	m_pStackedLayout->setCurrentIndex(1);
	m_pWidgetProjectInfo->initialize();
	slot_animationMenuFinished();
}
void CMainWidget::slot_addSprint() {
	if (!CConfig::instance().isAuthorized()) {
		slot_animationMenuFinished();
		QMessageBox::information(this, tr("task"), tr("please login"));
		return;
	}
	m_pStackedLayout->setCurrentIndex(4);
	m_pWidgetSprint->initialize();
	slot_animationMenuFinished();
}
void CMainWidget::slot_login() {
	CLoginDialog dlg(this);
	dlg.exec();
	CConfig::instance().setAuthorized(dlg.isAuthorized());
	CConfig::instance().setUser(dlg.getUser());
	updateLoginIcon();
}
void CMainWidget::slot_about() {
	QMessageBox::information(this, tr("Agile"), ("Scrum Bulletin Board"));
}
void CMainWidget::slot_exit() {
	close();
}
void CMainWidget::slot_getBack() {
	m_pStackedLayout->setCurrentIndex(0);
}
void CMainWidget::slot_getBackToSprint() {
	m_pStackedLayout->setCurrentIndex(3);
}
void CMainWidget::slot_showBurndown(const QString& strProjectCode, int sprintId) {
	m_pWidgetBurndown->setSprintInfo(strProjectCode, sprintId);
	m_pStackedLayout->setCurrentIndex(5);
}

void CMainWidget::slot_projectBrowser() {
	m_pStackedLayout->setCurrentIndex(0);
	slot_animationMenuFinished();
}

void CMainWidget::initialize_database() {
	// 创建表
	// 创建项目表
	QSqlQuery sql_query;
	if (!sql_query.exec("create table if not exists projects(id integer primary key autoincrement, name text unique, code text unique,startdate text, enddate text, sprintcycle int, workloade  integer,workloadfinished integer, po text, sm text, tester text,currentsprint integer, devteam text)")) {
		qDebug() << sql_query.lastError();
	}
	// 创建人员表
	if (!sql_query.exec("create table if not exists users(id integer primary key autoincrement, name text unique, password text, role int, photo blob)")) {
		qDebug() << sql_query.lastError();
	}

	// 创建迭代表
	if (!sql_query.exec("create table if not exists sprints( id integer primary key autoincrement, projectcode text, startdate text, enddate text, workloade integer, completion_date text)")) {
		qDebug() << sql_query.lastError();
	}
	// 创建燃尽图表
	if (!sql_query.exec("create table if not exists burndown(projectcode text, sprintid integer, date text, workload integer)")) {
		qDebug() << sql_query.lastError();
	}
	// 创建待办事项表
	if (!sql_query.exec("create table if not exists backlogs(id integer primary key autoincrement, projectcode text, sprintid integer, backlog text, workloade int, workloadr integer, state integer, info text)")) {
		qDebug() << sql_query.lastError();
	}
	// 创建分解任务表
	if (!sql_query.exec("create table if not exists tasks(id integer primary key autoincrement, task text, projectcode text,  backlogid integer, developer text, workloade integer, workloadr integer, state integer)")) {
		qDebug() << sql_query.lastError();
	}

}

void CMainWidget::slot_pressedProject(const QString& strProjectCode) {

	int nSprintId = 1;
	m_pWidgetSprint->setSprintInfo(strProjectCode, nSprintId);
	m_pWidgetSprint->initialize();
	// 找到项目的当前迭代，初始化后显示。
	m_pStackedLayout->setCurrentIndex(3);

}