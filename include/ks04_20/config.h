﻿/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: config.h
\brief exe+dll编程示例，单体类的定义头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9 
* please import ks04_20_config_dll.dll
*/

#pragma once

// 动态库导出宏定义
#ifdef WIN32		// windows platform
#	if defined __KS04_20_CONFIG_DLL_SOURCE__
#		define KS04_20_CONFIG_Export __declspec(dllexport)
#	else
#		define KS04_20_CONFIG_Export __declspec(dllimport)
#	endif

#else				// other platform
#  define KS04_20_CONFIG_Export
#endif // WIN32

#include <qglobal.h>

class KS04_20_CONFIG_Export CConfig {
public:
    /**
    * @brief  单体对象访问接口
    * @return 单体对象的引用
    */
    static CConfig& instance();

    /**
    * @brief  设置鼠标点选图元时的碰撞半径
    * @param[in] dR  半径
    */
    void setSelectRadius(qreal dR) { m_dSelectRadius = dR; }
    /**
    * @brief  获取鼠标点选图元时的碰撞半径
    * @return 半径
    */
    qreal getSelectRadius() const { return m_dSelectRadius; }
private:    
    /**
    * @brief  构造函数，定义为私有的目的是防止他人使用该类构造对象。
    * @return 无
    */
    CConfig():m_dSelectRadius(1.f){}

    /**
    * @brief  拷贝构造函数，定义为私有的目的是防止编译器调用默认的拷贝构造
    *         函数隐式构造该类的对象。
    * @return 无
    */
    CConfig(const CConfig&);
    
    /**
    * @brief  析构造函数，定义为私有的目的是防止他人用delete语句删除单体对象。
    * @return 无
    */
    ~CConfig() {}


 private:
   static CConfig m_config;   /// 静态对象
   qreal m_dSelectRadius;     /// 鼠标监测半径

};

