/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: projectinfo.h
\brief  CProjectInfo 类定义头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2019/11
*/

#pragma once

#include "ui_projectinfo.h" // 头文件名称来自: xxx.ui  ---> ui_xxx.h

// 父类的名称来自ui文件中对话框的类名：对象查看器中的类名
class CProjectInfo : public QWidget {
    Q_OBJECT
public:
    CProjectInfo(QWidget* pParent);
    ~CProjectInfo();
	// 设置为修改模式.true:修改模式，false:添加模式
	void setModifyMode(bool b);
	// 清空所有控件的内容
	void clear();
	// 加载指定项目的信息
	void load(const QString&);
	// 初始化界面
	void initialize();
	// 获取所有项目编号
	static QStringList getProjects();
	/*
	*  @brief 获取指定项目当前迭代
	*  @param[in] strProjectCode 项目编号
	*  @return void
	*/
	static int getCurrentSprint(const QString& strProjectCode);
	/*
	*  @brief 获取指定项目的迭代周期，单位为周。
	*  @param[in] strProjectCode 项目编号
	*  @return 迭代周期
	*/	
	static int getSprintCycle(const QString& strProjectCode);
	/*
	*  @brief 获取指定项目、指定迭代的燃尽图数据
	*  @param[in] strProjectCode 项目编号
	*  @param[in] sprintId 迭代序号
	*  @param[out] lstDate 日期
	*  @param[out] lstData 对应的燃尽图数据
	*  @return 数据个数
	*/
	static int getBurndownData(const QString& strProjectCode, int sprintId, QList<QDate>& lstDate, QList<int>& lstData);

Q_SIGNALS:
	void sig_getBack();
private slots:
	void slot_save();
private:
	bool m_bModify;
    Ui::CProjectInfo ui;
};
