/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file delegate.cpp
\brief delegate实现文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2019/1
*/

#include "delegate.h"

#include <QComboBox>
#include <QSpinBox>

#include "tablemodel.h"
#include "editor.h"

CDelegate::CDelegate(QObject* parent):
    QStyledItemDelegate (parent) {

    m_strListYesNo << "yes" << "no"; // 0：yes, 1:no
    m_strListSpeed << QString::fromLocal8Bit("慢速") // tr("")
                   << QString::fromLocal8Bit("中速")
                   << QString::fromLocal8Bit("快速");
}

QWidget *CDelegate::createEditor(QWidget *parent,
                      const QStyleOptionViewItem &option,
                      const QModelIndex &index) const {
    // 只有第1列允许编辑
    if (1 != index.column()){
        return QStyledItemDelegate::createEditor(parent,
                                                 option,
                                                 index);
    }

    if (CTableModel::EAttr_Id == index.row()) {
        QSpinBox* pEditor = new QSpinBox(parent);
        pEditor->setFrame(false);
        pEditor->setMinimum(0);
        pEditor->setMaximum(100);
        return pEditor;
    }
    else if (CTableModel::EAttr_Checked == index.row()) {
        QComboBox* pEditor = new QComboBox(parent);
        pEditor->addItems(m_strListYesNo);
        pEditor->setItemData(0, 0); // 0:yes,序号=0，对应的值=0
        pEditor->setItemData(1, 1); // 1:no,序号=1，对应的值=1
        return pEditor;
    }
    else if(CTableModel::EAttr_LastOneFlag == index.row()) {
        CEditor *pEditor = new CEditor(parent);
        connect(pEditor, &CEditor::sig_editFinished,
                this, &CDelegate::slot_commitAndCloseEditor);
        return pEditor;

    }
    else if (CTableModel::Eattr_AnimateSpeed == index.row()){
        QComboBox* pEditor = new QComboBox(parent);
        pEditor->addItems(m_strListSpeed);
        pEditor->setItemData(0, CTableModel::EAnimateSpeed_Slow);
        pEditor->setItemData(1, CTableModel::EAnimateSpeed_Normal);
        pEditor->setItemData(2, CTableModel::EAnimateSpeed_Fast);
        return pEditor;
    }
    else {
        return QStyledItemDelegate::createEditor(parent,
                                                 option,
                                                 index);
    }
}

void CDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const{
    if (1 != index.column()) {
        return QStyledItemDelegate::setEditorData(editor, index);
    }
    if (CTableModel::EAttr_Id == index.row()){
        QSpinBox* pEditor = dynamic_cast<QSpinBox*>(editor);
        int value = index.model()->data(index, Qt::EditRole).toInt();
        pEditor->setValue(value);
    }
    else if (CTableModel::EAttr_Checked == index.row()){
        QComboBox* pEditor = dynamic_cast<QComboBox*>(editor);
        //      index  value(data())
        // yes  0        0
        // no   1        1
        int idx = (index.model()->data(index, Qt::EditRole).toBool() ? 1 : 0);
        pEditor->setCurrentIndex(idx);
    }
    else if (CTableModel::EAttr_LastOneFlag == index.row()) {
        CEditor* pEditor = dynamic_cast<CEditor*>(editor);
        QVariant var = index.model()->data(index, Qt::EditRole);
        Qt::CheckState checkState = static_cast<Qt::CheckState>(var.toInt());
        if (checkState) {
            pEditor->setText(QString::fromLocal8Bit("是"));
        }
        else {
            pEditor->setText(QString::fromLocal8Bit("否"));
        }
    }
    else if (CTableModel::Eattr_AnimateSpeed == index.row()){
        QComboBox* pEditor = static_cast<QComboBox*>(editor);
        int value = index.model()->data(index, Qt::EditRole).toInt(); //
       // CTableModel::EAnimateSpeed eSpeed =
       //         static_cast<CTableModel::EAnimateSpeed>(value);
        pEditor->setCurrentIndex(value);
    }
    else {
        QStyledItemDelegate::setEditorData(editor, index);
    }

}

void CDelegate::setModelData(QWidget *editor,
                  QAbstractItemModel *model,
                  const QModelIndex &index) const {
    if (1 != index.column()){
        return QStyledItemDelegate::setModelData(editor, model, index);
    }
    QVariant var;
    if (CTableModel::EAttr_Id == index.row()){
        QSpinBox* pEditor = qobject_cast<QSpinBox*>(editor);
        pEditor->interpretText();
        model->setData(index, pEditor->value(), Qt::EditRole);
    }
    else if (CTableModel::EAttr_Checked == index.row()){
        QComboBox* pEditor = qobject_cast<QComboBox*>(editor);
        var = pEditor->currentData();// 0:yes, 1:no
        model->setData(index, var.toBool());
    }
    else if (CTableModel::EAttr_LastOneFlag == index.row()) {
        CEditor* pEditor = qobject_cast<CEditor*>(editor);
        var.setValue((pEditor->text()==QString::fromLocal8Bit("是")) ? true : false);
        model->setData(index, var);
    }
    else if (CTableModel::Eattr_AnimateSpeed == index.row()){
        QComboBox* pEditor = qobject_cast<QComboBox*>(editor);
        var = pEditor->currentData();
        model->setData(index, var);
    }
    else {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}

void CDelegate::updateEditorGeometry(QWidget *editor,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const {

    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}


void CDelegate::slot_commitAndCloseEditor() {

    CEditor* pEditor = dynamic_cast<CEditor*>(sender());

    emit commitData(pEditor); // 提交数据
    emit closeEditor(pEditor);// 关闭编辑器控件

}

QString CDelegate::displayText(const QVariant &value,
                                const QLocale &locale) const {

    switch (value.userType()) {
    case QMetaType::Bool:
        {
            QString str = (value.toBool() ?
                               QString::fromLocal8Bit("是") :
                               QString::fromLocal8Bit("否"));
            return str;
        }
        break;
    default:
        return QStyledItemDelegate::displayText(value, locale);
    }
}
