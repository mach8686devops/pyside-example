/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: dialog.h
\brief 演示用头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/8 
*/
#pragma once
#include "ui_dialog.h"
#include <QDialog>


class CDialog : public QDialog {
	Q_OBJECT
public:
	CDialog(QWidget* parent);
	~CDialog(){;}
private:
    /*
     * @brief 初始化
     * @return void
    */
    void initialize();

private slots:
    /*
     * @brief 将选中的项目移动到右侧列表
     * @return void
    */
    void slot_move2Right();
    /*
     * @brief 将选中的项目移动到左侧列表
     * @return void
    */
    void slot_move2Left();
    /*
     * @brief 将右侧列表升序排列
     * @return void
    */
    void slot_ascending();
    /*
     * @brief 将右侧列表降序排列
     * @return void
    */
    void slot_descending();
    /*
     * @brief 左侧的项被单击
     * @param[in] pItem 被单击的项
     * @return void
    */
    void slot_leftItemClicked(QListWidgetItem* pItem);
    /*
     * @brief 左侧的项被双击
     * @param[in] pItem 被双击的项
     * @return void
    */
    void slot_leftItemDoubleClicked(QListWidgetItem *pItem);
    /*
     * @brief 左侧选中的项发生变化
     * @param[in] current 新选中的项
     * @param[in] previous 之前选中的项
     * @return void
    */
    void slot_leftCurrentItemChanged(QListWidgetItem *current,
                                     QListWidgetItem *previous);
private:
	Ui::CDialog ui;
};
