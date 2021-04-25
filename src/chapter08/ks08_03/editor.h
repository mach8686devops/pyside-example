/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file editor.h
\brief CEditor头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2019/1
*/

#pragma once

#include <QLabel>

class CEditor : public QLabel {
    Q_OBJECT
public:
    explicit CEditor(QWidget* parent=nullptr);
signals:
    void sig_editFinished();
protected:
    /*
     * @brief 重写父类的 paintEvent()
     * @param[in] event 绘制事件
     * @return void
    */
    virtual void paintEvent(QPaintEvent* event) override;

    /*
     * @brief 重写父类的 mousePressEvent()
     * @param[in] event 鼠标事件
     * @return void
    */
    virtual void mousePressEvent(QMouseEvent* event) override;



};
