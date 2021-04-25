/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: projects.h
\brief  CWidgetProjects 类定义头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9
*/

#pragma once

#include "ui_projects.h" // 头文件名称来自: xxx.ui  ---> ui_xxx.h
#include <QString>

class QCustomPlot;
// 父类的名称来自ui文件中对话框的类名：对象查看器中的类名
class CWidgetProjects : public QWidget {
    Q_OBJECT
public:
    CWidgetProjects(QWidget* pParent);
    ~CWidgetProjects();

	/*
	*  @brief 加载指定编号的项目
	*  @param[in] strProjectId 项目编号
	*  @return void
	*/
    void add(const QString& strProjectId);

Q_SIGNALS:
	void sig_pressed(const QString&);

private slots:
	void slot_enterProject(const QString&);
	void slot_leaveProject(const QString&);
private:
	/*
	*  @brief 为燃尽图控件设置数据。
	*  @param[in] pCustomPlot 燃尽图控件
	*  @param[in] strProjectId 项目编号
	*  @param[in] nSpinrtCycle 迭代周期（周）
	*  @return void
	*/
	void setBurnDown(QCustomPlot* pCustomPlot, const QString& strProjectCode, int nSprintCycle);

	/*
	*  @brief 获取指定项目已完成工作量
	*  @param[in] strProjectId 项目编号
	*  @return 已完成的工作量
	*/
	int getFinishedWorkload(const QString& strProject);
private:
    Ui::CWidgetProjects ui;
	int m_nProjectIndex;
};
