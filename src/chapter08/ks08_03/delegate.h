/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file delegate.h
\brief delegate头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2019/1
*/
#pragma once

#include <QStyledItemDelegate>

class CDelegate : public QStyledItemDelegate{
    Q_OBJECT
public:
    explicit CDelegate(QObject *parent = nullptr);
    virtual ~CDelegate(){}

    // editing
    /*
     * @brief 为指定数据项创建编辑器
     * @param[in] parent 待创建编辑器的父窗口
     * @param[in] option 样式选项
     * @param[in] index 数据项序号
     * @return 创建好的编辑器
     */
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;
    /**
    * @brief 为指定数据项的编辑器设置值。从模型获取数据并设置到编辑器控件。
    *
    * @param[in|out] editor 指定数据项的编辑器
    * @param[in] index 制定数据项的序号
    * @return 无
    */
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    /**
    * @brief 从编辑器读取指定数据项的值并设置到模型。
    *           用户用编辑器控件修改完数据后，触发该接口。
    *
    * @param[in|out] editor 指定数据项的编辑器
    * @param[in|out] model 模型
    * @param[in] index 数据项序号
    * @return 无
    */
    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override;
    /**
    * @brief 更新指定数据项的编辑器尺寸。
    *
    * @param[in|out] editor 指定数据项的编辑器
    * @param[in] option 样式选项
    * @param[in] index 数据项序号
    * @return 无
    */
    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;

    /**
    *	@brief	重写父类该接口，实现bool类型时显示是或者否。
    *	@param[in] value    数值
    *	@param[in] locale   本地对象
    *	return 显示的字符串
    */
    virtual QString displayText(const QVariant &value,
                                const QLocale &locale) const override;
private slots:
    /**
    *	@brief	属性“lastoneflag”完成编辑时对应的槽函数
    *	return void
    */
    void slot_commitAndCloseEditor();
private:
    QStringList m_strListYesNo;/// 用来存储yes、no字符串
    QStringList m_strListSpeed;/// 用来存储速度字符串
};





