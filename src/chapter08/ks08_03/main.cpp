/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file main.cpp
\brief delegate example main()函数
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2019/1
*/


#include <QApplication>
#include <QHeaderView>

#include "tablemodel.h"
#include "delegate.h"
#include "tableview.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    CTableModel model(CTableModel::Eattr_Max, 2, nullptr);
    CTableView tableView(nullptr);

    tableView.setAlternatingRowColors(true);//
    tableView.horizontalHeader()->setStretchLastSection(true);
    tableView.setModel(&model);

    CDelegate delegate;
    tableView.setItemDelegate(&delegate);

    // 为模型设置数据
    QModelIndex index;
    QModelIndex indexRoot = model.invisibleRootItem()->index();
    for (int row=0; row<CTableModel::Eattr_Max; row++){
        // 先设置第0列
        index = model.index(row, 0, indexRoot);
        if (CTableModel::EAttr_Id == row){
            model.setData(index, "id");
        }
        else if (CTableModel::EAttr_Descrition == row ){
            model.setData(index, QString::fromLocal8Bit("描述"));
        }
        else if (CTableModel::EAttr_Checked == row ){
            model.setData(index, QString::fromLocal8Bit("验证"));
        }
        else if (CTableModel::EAttr_LastOneFlag == row ){
            model.setData(index, QString::fromLocal8Bit("是最后一个"));
        }
        else if (CTableModel::Eattr_AnimateSpeed == row ){
            model.setData(index, QString::fromLocal8Bit("动画速度"));
        }
        // 再设置第1列
        index = model.index(row, 1, indexRoot);
        if (CTableModel::EAttr_Id == row){
            model.setData(index, 0);
        }
        else if (CTableModel::EAttr_Descrition == row ){
            model.setData(index, QString::fromLocal8Bit("备注"));
        }
        else if (CTableModel::EAttr_Checked == row ){
            model.setData(index, 0);// 0:yes, 1:no
        }
        else if (CTableModel::EAttr_LastOneFlag == row ){
            model.setData(index, true);
        }
        else if (CTableModel::Eattr_AnimateSpeed == row ){
            model.setData(index, static_cast<int>(CTableModel::EAnimateSpeed_Slow));
        }
    }

    tableView.setWindowTitle("Delegate Example");
    tableView.show();
    return app.exec(); // 将app运行起来
}





