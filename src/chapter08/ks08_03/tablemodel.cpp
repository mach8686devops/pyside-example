/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file tablemodel.cpp
\brief  Table模型类的实现文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2019/1
*/

#include "tablemodel.h"

CTableModel::CTableModel(QObject *parent):
    QStandardItemModel(parent) {

}

CTableModel::CTableModel(int rows, int columns, QObject *parent):
                        QStandardItemModel(rows, columns, parent){

}


Qt::ItemFlags CTableModel::flags(const QModelIndex &index) const {
    // 只有第1列允许被编辑
    Qt::ItemFlags itemFlags;
    if (1 != index.column()){
        itemFlags &= (~Qt::ItemIsEditable); // Qt::ItemIsEditable表示可编辑，
                                            // ~Qt::ItemIsEditable表示取反，即不可编辑。
        return itemFlags;
    }
    else {
        return QStandardItemModel::flags(index);
    }
}


QVariant CTableModel::data(const QModelIndex &index,
                            int role) const {

    QVariant var;
    if (Qt::EditRole == role)
    {
        return QStandardItemModel::data(index, role);
    }
    else if (Qt::DisplayRole != role) {
        return QStandardItemModel::data(index, role);
    }

    var = data(index, Qt::EditRole);
    if (0 == index.column()){
        return var;
    }

    switch (index.row()){

    case CTableModel::EAttr_Checked:
        var = (var.toBool() ? "no" : "yes"); // 0:yes, 1:no
        break;
    case CTableModel::EAttr_LastOneFlag:
        var = (var.toInt() ? true : false);
        break;
    case CTableModel::Eattr_AnimateSpeed:
    {
        CTableModel::EAnimateSpeed eSpeed =
                static_cast<CTableModel::EAnimateSpeed>(var.toInt());
        switch (eSpeed) {
        case CTableModel::EAnimateSpeed_Slow:
            var = QString::fromLocal8Bit("慢速");
            break;
        case CTableModel::EAnimateSpeed_Normal:
            var = QString::fromLocal8Bit("中速");
            break;
        case CTableModel::EAnimateSpeed_Fast:
            var = QString::fromLocal8Bit("快速");
            break;
        default:
            break;
        }
    }
        break;
    default:
        break;
    }

    return var;
}


bool CTableModel::setData(const QModelIndex &index,
             const QVariant &value,
             int role) {
    if (Qt::EditRole == role) {
        return QStandardItemModel::setData(index, value, role);
    }
    else {
        return false;
    }
}



