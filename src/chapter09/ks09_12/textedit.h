/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: textedit.h
\brief 演示用头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/8 
*/

#pragma once
#include <QTextEdit>


class CTextEdit : public QTextEdit {
	Q_OBJECT
public:
	CTextEdit(QWidget* parent);
	~CTextEdit(){;}

public:
	/**
	* @brief 打开指定文件。
	* @param[in] strFileName 全路径文件名，支持环境变量
	* @return true:成功，false:失败
	*/
	bool openFile(const QString& strFileName);
	/**
	* @brief 获取当前打开的文件的名字。
	* @reutrn 当前打开的文件的名字，全路径。
	*/
	QString currentFileName() { return m_strFileName; }

protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void mousePressEvent(QMouseEvent *e) override;
	virtual void mouseMoveEvent(QMouseEvent *e) override;
	virtual void mouseReleaseEvent(QMouseEvent *e) override;

Q_SIGNALS:
	void viewMouseMove(QMouseEvent *event);

private:
	QString m_strFileName;
	bool	m_bDrag;
	QPoint  m_ptMousePress;
};
