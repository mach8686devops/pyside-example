/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: user.h
\brief  CWidgetUser 类定义头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9
*/

#pragma once

#include "ui_user.h" // 头文件名称来自: user.ui  ---> ui_user.h

// 父类的名称来自ui文件中对话框的类名：对象查看器中的类名
class CWidgetUser : public QWidget {
	Q_OBJECT
public:
    CWidgetUser(QWidget* pParent);
    ~CWidgetUser();

    // 设置为修改模式.true:修改模式，false:添加模式
    void setModifyMode(bool b);
    // 清空所有控件的内容
    void clear();
    // 加载指定用户的信息
    void loadUser(const QString&);
	// 获取所有用户
	static QStringList getUsers();
Q_SIGNALS:
	void sig_getBack();

private slots:
    void slot_save();
    void slot_selectphoto();
private:
    Ui::CWidgetUser ui;
    bool m_bModify;
    QString m_strFileName;
};
