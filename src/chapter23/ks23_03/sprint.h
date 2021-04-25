/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: sprint.h
\brief  CWidgetSprint 类定义头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9
*/

#pragma once

#include "ui_sprint.h" // 头文件名称来自: xxx.ui  ---> ui_xxx.h


// 父类的名称来自ui文件中对话框的类名：对象查看器中的类名
class CWidgetSprint : public QWidget {
    Q_OBJECT
public:
    CWidgetSprint(QWidget* pParent, int sprintId);
    ~CWidgetSprint();

	/*
	*  @brief 设置迭代所属的项目编号、迭代id
	*  @param[in] strProjectNo 项目编号
	*  @param[in] sprintId 迭代id
	*  @return void
	*/
	void setSprintInfo(const QString& strProjectCode, int sprintId);
	/*
	*  @brief 获取迭代所属的项目编号
	*  @return 项目编号
	*/
	QString getSprintCode() {
		return m_strProjectCode;
	}
	/*
	*  @brief 获取迭代序号
	*  @return 迭代序号
	*/
	int getSprintIndex() {
		return m_nSprintIndex;
	}

	/*
	*  @brief 初始化
	*  @return void
	*/
	void initialize();
Q_SIGNALS:
	void sig_getBack();
	void sig_burndown(const QString& strProjectCode, int sprintId);
private:
	/*
	*  @brief 加载指定编号的用户故事
	*  @param[in] backlogId 用户故事编号
	*  @return void
	*/
	void add(int backlogId);
	/*
	*  @brief 清空backlog控件
	*  @return void
	*/	
	void clear();
private slots:
	void slot_addBacklog();
	void slot_finish();
	void slot_showBurndown();
private:
    Ui::CWidgetSprint ui;
	QString m_strProjectCode;
	int m_nSprintIndex;
	int m_nIndex;
};
