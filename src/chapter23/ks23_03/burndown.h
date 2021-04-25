/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: burndown.h
\brief  CWidgetBurndown 类定义头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2019/11
*/

#pragma once

#include "ui_burndown.h" // 头文件名称来自: burndown.ui  ---> ui_burndown.h
class QCustomPlot;

// 父类的名称来自ui文件中对话框的类名：对象查看器中的类名
class CWidgetBurndown : public QWidget {
	Q_OBJECT
public:
	CWidgetBurndown(QWidget* pParent);
    ~CWidgetBurndown();

    // 清空所有数据
    void clear();
	/*
	*  @brief 设置迭代所属的项目编号、迭代id
	*  @param[in] strProjectNo 项目编号
	*  @param[in] sprintId 迭代id
	*  @return void
	*/
	void setSprintInfo(const QString& strProjectCode, int sprintId);
	/*
	*  @brief 加载指定项目、指定迭代的数据
	*  @param[in] strProjectCode 项目编号
	*  @param[in] sprintId 迭代序号
	*  @return void
	*/
    void load(const QString& strProjectCode, int sprintId);

Q_SIGNALS:
	void sig_getBackToSprint();

private:
	/*
	*  @brief 为燃尽图控件设置数据。
	*  @param[in] pCustomPlot 燃尽图控件
	*  @param[in] strProjectCode 项目编号
	*  @param[in] sprintId 迭代序号
	*  @return void
	*/
	void setBurnDown(QCustomPlot* pCustomPlot, const QString& strProjectCode, int sprintId);
	/*
	*  @brief 初始化。
	*  @return void
	*/
	void initialize();
private:
    Ui::CWidgetBurndown ui;
    QString m_strProjectCode;
	int		m_nSprintIndex;
	QCustomPlot* m_pPlotBurnDown;
};
