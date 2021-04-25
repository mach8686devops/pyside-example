/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: mainwindow.h
\brief 主窗体头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/12 
*/

#pragma once
#include <QToolBar>
#include <QLabel>
#include <QMainWindow>
#include <QMenu>


QT_BEGIN_NAMESPACE
class QActionGroup;
class QAction;
class QLabel;
class QToolbar;
class QGraphicsScene;
class QPropertyAnimation;
QT_END_NAMESPACE

///////////////////////////////////////////////////////
class CAnimationMenu : public QMenu {
	Q_OBJECT
public:
	CAnimationMenu(const QString&, QWidget* pParent);

Q_SIGNALS:
	void sig_focusOut();

protected:
	/**
	* @brief 重写父类的focusOutEvent()，以便发射sig_focusOut信号。
	*
	* @return void
	*/
	void focusOutEvent(QFocusEvent *event);
};

///////////////////////////////////////////////////////
class CGraphView;

class CMainWindow : public QMainWindow {
	Q_OBJECT
public:
	CMainWindow(QWidget* parent);
	~CMainWindow(){;}

private slots:
#ifndef QT_NO_CLIPBOARD
	void slot_cut();
	void slot_copy();
	void slot_paste();
#endif
    void onMouseMoveInView(const QPointF&);    
    void about();
	void slot_addRect();
	void slot_addEllipse();
	void slot_fileMenu();
	void slot_openFile();
	void slot_saveFile();
	void slot_closeFile();
	void slot_exit();
	void slot_animationMenuFinished();
	void slot_hideMenu();
private:
	void createActions();		/// 构建菜单项对应的QAction。
	void createMenus();			/// 构建菜单
	void createToolBars();		/// 构建工具条
	void createStatusBar();		/// 构建状态栏
	void initialize();			/// 初始化
	
	void connectSignalAndSlot();/// 绑定信号槽
	
private:
	CAnimationMenu *m_pFileMenu;/// 文件菜单	
	QToolBar *m_pEditToolBar;	/// 编辑工具条
	QActionGroup *m_pAlignmentGroup;

	QAction *m_pFileMenuAct;	/// 文件菜单
	QAction *m_pOpenFileAct;	/// 打开文件
	QAction *m_pSaveFileAct;	/// 保存文件
	QAction *m_pCloseFileAct;	/// 关闭文件
	QAction *m_pExitAct;	    /// 退出

#ifndef QT_NO_CLIPBOARD
	QAction *m_pCutAct;			/// 剪切
	QAction *m_pCopyAct;		/// 复制
	QAction *m_pPasteAct;		/// 黏贴
#endif
    QAction *m_pRectAct;        /// 添加矩形
    QAction *m_pEllipseAct;     /// 添加椭圆

	QAction *m_pAboutAct;	    /// 关于

	QLabel *m_pInfoLabel;	    /// 信息标签
	QLabel* m_pMouseLabel;	    /// 鼠标位置显示

	CGraphView* m_pView;        /// 视图
    QGraphicsScene* m_pScene;   /// 场景(文档)
	QPropertyAnimation* m_pAnimaMenuShow; /// 菜单动画
	bool    m_bShowMenu;        /// 显示菜单
	int		m_nMenubarHeight;	/// 菜单栏高度
};
