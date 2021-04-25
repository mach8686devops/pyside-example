/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt 5/PyQt 5实战指南》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: main.cpp
\brief QMessageBox的使用
\author 女儿叫老白   微信公众号:软件特攻队(微信号:xingdianketang)
\Date 2018/9
*/

#include <QApplication>
#include <QMessageBox>
#include <iostream>

void example01();
void example02();
void example03();
void example04();
void example05();

using std::cout;
using std::endl;
using std::cin;

//
int main(int argc, char * argv[]) {
    Q_UNUSED(argc);
    Q_UNUSED(argv);
    QApplication app(argc, argv);

    // example01 
    if (0) {
        example01();
    }

    // example02 
    if (0) {
        example02();
    }

    // example03 
    if (0) {
        example03();
    }

    // example04
    if (0) {
        example04();
    }

    // example05
    if (1) {
        example05();
    }

	char ch = '\0';
	cin >> ch;

    return 0;
}

/**
* @brief  弹出普通提示信息
* @return 无
*/
void example01() {
    //static StandardButton information(QWidget *parent, const QString &title,
    //    const QString &text, StandardButtons buttons = Ok,
    //    StandardButton defaultButton = NoButton);

    QMessageBox::StandardButton button
        = QMessageBox::information(NULL,
            QObject::tr("Qt Gui Application"),
            QObject::tr("This is a normal information."),
            QMessageBox::StandardButtons(QMessageBox::Yes | QMessageBox::Discard),
            QMessageBox::Yes);
    if (QMessageBox::Discard == button) {
        cout << "infomation discarded." << endl;
    }
}
/**
* @brief  弹出严重错误信息
* @return 无
*/
void example02() {
    //static StandardButton critical(QWidget *parent, const QString &title,
    //    const QString &text, StandardButtons buttons = Ok,
    //    StandardButton defaultButton = NoButton);
    QMessageBox::StandardButton button =
        QMessageBox::critical(NULL,
            QObject::tr("Qt Gui Application"),
            QObject::tr("This is a critical information."),
            QMessageBox::StandardButtons(QMessageBox::Ok | QMessageBox::Discard),
            QMessageBox::Ok);
    if (QMessageBox::Ok == button) {
        cout << "i see the critical information and i will take further step to handle it."
            << endl;
    }
    else {
        cout << "it doesn't matter to me."
            << endl;
    }
}

/**
* @brief  弹出提问信息
* @return 无
*/
void example03() {
    //static StandardButton question(QWidget *parent, const QString &title,
    //    const QString &text, StandardButtons buttons = StandardButtons(Yes | No),
    //    StandardButton defaultButton = NoButton);
    QMessageBox::StandardButton button = QMessageBox::question(NULL,
                                            QObject::tr("Qt Gui Application"),
                                            QObject::tr("Do you like this lesson?")
                                            );
            //                  QMessageBox::StandardButtons(QMessageBox::Yes | QMessageBox::No),
            //                QMessageBox::Yes);
    if (QMessageBox::Yes == button) {
        cout << "I like this lesson." << endl;
    }
    else {
        cout << "I don't agree." << endl;
    }

}

/**
* @brief  弹出"关于(About)"信息
* @return 无
*/
void example04() {
    QMessageBox::about(NULL,
        QObject::tr("Qt Gui Application"),
        "copyright: 2018~2019\r\nall rights reserved.");
}

/**
* @brief  弹出警告信息
* @return 无
*/
void example05() {
    //static StandardButton warning(QWidget *parent, const QString &title,
    //    const QString &text, StandardButtons buttons = Ok,
    //    StandardButton defaultButton = NoButton);
    
    QMessageBox::StandardButton button =
        QMessageBox::warning(NULL,
            QObject::tr("Qt Gui Application"),
            QObject::tr("Something dangerous happeded, be careful!!!"));
}
