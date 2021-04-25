﻿/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: myclass.h
\brief exe+dll编程示例，引出类的定义头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9 
* please import ks05_02_dll.dll
*/

#pragma once 

#include "ks05_02_export.h"


class KS05_02_Export CModel {
public:
    CModel(){}
	~CModel(){}

public:
    bool initialize();
};

