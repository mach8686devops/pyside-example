/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: ellipseitem.h
\brief 演示用头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/8
*/

#pragma once
#include "itembase.h"

class  CGraphEllipseItem : public CGraphItemBase
{
public:
    CGraphEllipseItem(QGraphicsItem * parent = 0);
    virtual int type() const { return QGraphicsItem::UserType + 2; }

	virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
	/**
		 * @brief boundingRect()获取外接矩形(图元坐标系)
		 * @return 外接矩形
	*/
	virtual QRectF  boundingRect() const;
    /**
    * @brief 获取几何矩形(图元坐标系)
    * @return 几何矩形
    */
    virtual QRectF  getItemRect() const;
    /**
		 * @brief 获取形状
		 * 用来进行碰撞检测
		 * @return 形状
	*/
	virtual QPainterPath  shape() const;


protected:
	/// 析构函数
	virtual ~CGraphEllipseItem();
private:
};


