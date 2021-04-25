/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: itembase.h
\brief 演示用头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/8
*/

#pragma once
#include <QGraphicsItem>

class  CGraphItemBase : public QGraphicsItem {
public:
    CGraphItemBase(QGraphicsItem * parent = 0):QGraphicsItem(parent) { ; }
    virtual int type() const { return QGraphicsItem::UserType; }

    /**
    * @brief 获取几何矩形(图元坐标系)
    * @return 几何矩形
    */
    virtual QRectF  getItemRect() const =0 ;
    
    /**
    * @brief setWidth重设置矩形宽
    *
    * @param[in] dW  宽
    */
    void setWidth(qreal dW) { m_width = dW; }
    /**
    * @brief getWidth() 获取矩形宽
    *
    * @return 宽
    */
    qreal getWidth() const { return m_width; }

    /**
    * @brief setHeight重设置矩形高
    *
    * @param dH  高
    */
    void setHeight(qreal dH) { m_height = dH; }
    /**
    * @brief getHeight() 获取矩形高
    *
    * @return 高
    */
    qreal getHeight() const { return m_height; }

protected:
	/// 析构函数
    virtual ~CGraphItemBase() { ; }
private:
    qreal m_width;
    qreal m_height;
};


