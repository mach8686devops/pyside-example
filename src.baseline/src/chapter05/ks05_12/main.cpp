/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: dialog.h
\brief main()函数的实现文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2019/7
*/
#include <QApplication>
#include <QMessageBox>

#include "dialog.h"

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);
    
    QMessageBox::question(NULL,
        QString::fromLocal8Bit("提问:"),
        QString::fromLocal8Bit("把大象装冰箱里一共分几步？"),
        QMessageBox::Ok);

	CDialog dialog(NULL);
	dialog.show();
    return app.exec();
}
