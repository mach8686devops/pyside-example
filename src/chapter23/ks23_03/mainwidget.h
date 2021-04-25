/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: mainwidget.h
\brief  CMainWidget 类定义头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9
*/

#pragma once

#include "ui_mainwidget.h" // 头文件名称来自: xxx.ui  ---> ui_xxx.h

#include <QLabel>
QT_BEGIN_NAMESPACE
class QMenu;
class QActionGroup;
class QAction;
class QLabel;
class QPropertyAnimation;
class QStackedLayout;
QT_END_NAMESPACE

class CWidgetProjects;
class CProjectInfo;
class CWidgetUser;
class CWidgetSprint;
class CWidgetAddSprint;
class CWidgetBurndown;
// 父类的名称来自ui文件中对话框的类名：对象查看器中的类名
class CMainWidget : public QWidget {
    Q_OBJECT
public:
    explicit CMainWidget(QWidget* pParent);
    ~CMainWidget();

private slots:
    void about();
    void slot_menu();
    void slot_projectBrowser();
    void slot_addUser();
    void slot_changePassword();
    void slot_addProject();
    void slot_addSprint();
    void slot_about();
    void slot_exit();
	void slot_login();
    void slot_animationMenuFinished();
	void slot_getBack();
	void slot_getBackToSprint();
	void slot_showBurndown(const QString& strProjectCode, int sprintId);
private:
    void createActions();		    /// 构建菜单项对应的QAction。
    void createMenus();			    /// 构建菜单
    void createStatusBar();		    /// 构建状态栏
    void initialize();			    /// 初始化	
    void connectSignalAndSlot();    /// 绑定信号槽
    void initialize_database();     /// 初始化数据库
	void updateLoginIcon();			/// 更新登录人员的图标
	void slot_pressedProject(const QString&);     /// 显示项目的迭代信息
private:
    QMenu * m_pMenu;                /// 主菜单
    QMenu *m_pUserMenu;             /// 人员管理菜单(二级菜单)

    QAction *m_pProjectBrowserAct;  /// 项目总览
    QAction *m_pAddProjectAct;      /// 添加项目
    QAction *m_pAddSprintAct;		/// 添加迭代
    QAction *m_pAddUserAct;         /// 添加人员
    QAction *m_pModifyPasswordAct;	/// 修改密码
    QAction *m_pAboutAct;	        /// 关于
    QAction *m_pExitAct;	        /// 退出
    QLabel *m_pInfoLabel;	        /// 信息标签
    QPropertyAnimation* m_pAnimaMenuShow;   /// 菜单动画
    bool     m_bShowMenu;                   /// 显示菜单
    CWidgetProjects* m_pWidgetProjects;     /// 主窗体
    QStackedLayout* m_pStackedLayout;       /// 布局对象
    CProjectInfo*   m_pWidgetProjectInfo;   /// 项目信息界面   
    CWidgetUser*    m_pWidgetUser;          /// 人员界面 
    CWidgetSprint*  m_pWidgetSprint;        /// 迭代界面
	CWidgetAddSprint*		m_pWidgetAddSprint;	/// 添加迭代界面
	CWidgetBurndown*		m_pWidgetBurndown;	/// 燃尽图界面
	Ui::CMainWidget ui;
};
