/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: config.h
\brief exe+dll编程示例，单体类的定义头文件
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9 
* 
*/

#pragma once

#include <QString>
#include <QSqlDatabase>

class  CConfig {
public:
    /**
    * @brief  单体对象访问接口
    * @return 单体对象的引用
    */
    static CConfig& instance();

    /**
    * @brief  获取左侧控件样式
    * @return 样式
    */
	QString getStyleSheetLeft() { return m_styleSheetLeft; }
    /**
    * @brief  获取左侧控件样式
    * @return 样式
    */
	QString getStyleSheetLeftDark() { return m_styleSheetLeftDark; }
    /**
    * @brief  获取右侧控件样式
	* @return 样式
	*/
	QString getStyleSheetRight() { return m_styleSheetRight; }
    /**
    * @brief  获取右侧控件样式
	* @return 样式
	*/
	QString getStyleSheetRightDark() { return m_styleSheetRightDark; }
    /**
    * @brief  获取基准控件样式
	* @return 样式
	*/
	QString getStyleSheetBase() { return m_styleSheetBase; }
    /**
    * @brief  获取基准控件样式
	* @return 样式
	*/
	QString getStyleSheetBaseDark() { return m_styleSheetBaseDark; }
    /**
    * @brief  获取普通控件样式A
	* @return 样式
	*/
	QString getStyleSheetA() { return m_styleSheetA; }
    /**
    * @brief  获取普通控件样式B
	* @return 样式
	*/
	QString getStyleSheetB() { return m_styleSheetB; }

    /**
    * @brief  连接到数据库
	* @return true:成功,false:失败
	*/
	bool connectToDatabase();
    /**
    * @brief  是否已登录
	* @return true:已登录,false:未登录
	*/
	void setAuthorized(bool b){
		m_bAuthorized = b;
	}
    /**
    * @brief  是否已登录
	* @return true:已登录,false:未登录
	*/
	bool isAuthorized(){
		return m_bAuthorized;
	}
    /**
    * @brief  设置登录人员
	* @param[in] strUser 登录人员
	*/
	void setUser(const QString& strUser){
		m_strUser = strUser;
	}
    /**
    * @brief  获取登录人员
	* @return 登录人员
	*/
	QString getUser(){
		return m_strUser;
	}

private:    
    /**
    * @brief  构造函数，定义为私有的目的是防止他人使用该类构造对象。
    * @return 无
    */
    CConfig();

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
    ~CConfig() { 
		m_database.close();
	}


 private:
   static CConfig m_config;		/// 静态对象
   QString m_styleSheetLeft;	/// 左侧样式
   QString m_styleSheetRight;	/// 右侧样式
   QString m_styleSheetBase;	/// 基准部件样式
   QString m_styleSheetLeftDark;	/// 左侧样式Dark
   QString m_styleSheetRightDark;	/// 右侧样式Dark
   QString m_styleSheetBaseDark;	/// 基准部件样式Dark
   QString m_styleSheetA;		/// 普通样式A
   QString m_styleSheetB;		/// 普通样式B
   QSqlDatabase m_database;		/// 数据库连接对象
   bool	m_bAuthorized;		/// 已授权
   QString m_strUser;			/// 登录人员
};

