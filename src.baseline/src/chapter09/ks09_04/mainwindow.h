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
#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QMenu;
class QAction;
class QActionGroup;
class QLabel;
QT_END_NAMESPACE

class CMainWindow : public QMainWindow
{
	Q_OBJECT
public:
	CMainWindow(QWidget* parent);
	~CMainWindow(){;}

public slots:
	void open();
	void save();
	void cut();
	void copy();
	void paste();
	void bold();
	void italic();
	void about();
	void leftAlign();
	void rightAlign();
	void center();
	void setLineSpacing();
	void setParagraphSpacing();
private:
	/**
	* @brief 构建菜单
	* @return void
	*/
	void createMenus();
	/**
	* @brief 构建各个菜单项
	* @return void
	*/
	void createActions();
private:
	QMenu* m_pFileMenu;		/// 文件菜单
	QMenu *m_pEditMenu;		/// 编辑菜单
	QMenu* m_pFormatMenu;	/// 格式菜单
	QMenu *m_pHelpMenu;		/// 帮助菜单
	QActionGroup* m_pAlignmentGroup; /// 菜单分组
	QAction* m_pOpenAct;	/// 打开文件菜单项
	QAction *m_pSaveAct;	/// 保存
	QAction *m_pExitAct;	/// 退出
	QAction *m_pCutAct;		/// 剪切
	QAction *m_pCopyAct;	/// 复制
	QAction *m_pPasteAct;	/// 粘贴
	QAction *m_pBoldAct;	/// 粗体
	QAction *m_pItalicAct;	/// 斜体
	QAction *m_pAboutAct;	/// 帮助
	QAction *m_pLeftAlignAct;	/// 左对齐
	QAction *m_pRightAlignAct;	/// 右对齐
	QAction *m_pCenterAct;		/// 居中对齐
	QAction *m_pSetLineSpacingAct;	/// 设置行间距
	QAction *m_pSetParagraphSpacingAct;/// 设置段间距
	QLabel* m_pInfoLabel;	/// 信息提示框
};
