/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: dialog.cpp
\brief	
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9 

*/
#include "dialog.h"
#include <QGridLayout>
#include <QListWidget>

CDialog::CDialog(QWidget* parent) : QDialog(parent) {
	ui.setupUi(this);

    initialize();
}

void CDialog::initialize() {

    ui.listWidgetLeft->setSelectionMode(QAbstractItemView::SingleSelection);
    ui.listWidgetRight->setSelectionMode(QAbstractItemView::MultiSelection);

    ui.listWidgetLeft->addItem("C++");
    ui.listWidgetLeft->addItem("Python");
    ui.listWidgetLeft->addItem("java");
    ui.listWidgetLeft->addItem("C#");
    ui.listWidgetLeft->addItem("Rubby");
    ui.listWidgetLeft->addItem("Go");

    connect(ui.buttonBox, &QDialogButtonBox::accepted,
            this, &CDialog::accept);
    connect(ui.buttonBox, &QDialogButtonBox::rejected,
            this, &CDialog::reject);
    connect(ui.btn2Left, &QPushButton::clicked,
            this, &CDialog::slot_move2Left);
    connect(ui.btn2Right, &QPushButton::clicked,
            this, &CDialog::slot_move2Right);
    connect(ui.btnAscending, &QPushButton::clicked,
            this, &CDialog::slot_ascending);
    connect(ui.btnDescending, &QPushButton::clicked,
            this, &CDialog::slot_descending);

    connect(ui.listWidgetLeft, &QListWidget::itemClicked,
            this, &CDialog::slot_leftItemClicked);
    connect(ui.listWidgetLeft, &QListWidget::itemDoubleClicked,
            this, &CDialog::slot_leftItemDoubleClicked);
    connect(ui.listWidgetLeft, &QListWidget::currentItemChanged,
            this, &CDialog::slot_leftCurrentItemChanged);

}
void CDialog::slot_move2Right() {
    // 左侧列表只允许单选
    // 得到左侧列表当前选中的项
    QListWidgetItem* pItem = ui.listWidgetLeft->currentItem();
    if (nullptr == pItem)
        return;
    int idx = ui.listWidgetLeft->row(pItem); // 得到项的序号
    ui.listWidgetLeft->takeItem(idx);        // 将项从左侧列表删除
    ui.listWidgetRight->addItem(pItem);      // 将项添加到右侧列表
}

void CDialog::slot_move2Left() {
    // 右侧列表允许复选
    // 首先得到右侧列表中选中的项的集合
    QList<QListWidgetItem*> selectedItems =
            ui.listWidgetRight->selectedItems();

    int idx = 0;
    // 遍历该集合，并将项移动到左侧列表
    QList<QListWidgetItem*>::iterator iteLst = selectedItems.begin();
    for(; iteLst!=selectedItems.end(); iteLst++){
        idx = ui.listWidgetRight->row(*iteLst);  // 得到该项的行号(序号)
        ui.listWidgetRight->takeItem(idx);       // 先从右侧删除
        ui.listWidgetLeft->addItem(*iteLst);     // 将项添加到左侧
    }
}

void CDialog::slot_ascending() {
    ui.listWidgetRight->sortItems(Qt::AscendingOrder);
}

void CDialog::slot_descending() {
    ui.listWidgetRight->sortItems(Qt::DescendingOrder);
}

void CDialog::slot_leftItemClicked(QListWidgetItem* pItem) {
    QString str = "my favorite program language is ";
    str += pItem->text();
    ui.label->setText(str);

    // 同时将被选中项字体加粗
    QFont ft = pItem->font();
    ft.setBold(true);
    pItem->setFont(ft);
}

void CDialog::slot_leftItemDoubleClicked(QListWidgetItem *pItem) {
    // 双击时，将左侧列表中被单击的项移动到右侧列表
    int idx = ui.listWidgetLeft->row(pItem);
    ui.listWidgetLeft->takeItem(idx);
    ui.listWidgetRight->addItem(pItem);
}

void CDialog::slot_leftCurrentItemChanged(QListWidgetItem *current,
                                          QListWidgetItem *previous) {
    Q_UNUSED(current);
    // 将之前选中项的字体粗体恢复
    if (nullptr!=previous){
         QFont ft = previous->font();
         ft.setBold(false);
         previous->setFont(ft);
    }
}
