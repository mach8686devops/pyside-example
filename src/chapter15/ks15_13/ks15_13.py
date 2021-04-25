# -*- coding: utf-8 -*-

import sys 	
from PyQt5.QtWidgets import QApplication, QMessageBox

# 弹出普通提示信息
def example01() :
    #static StandardButton information(QWidget *parent, const QString &title,
    #    const QString &text, StandardButtons buttons = Ok,
    #    StandardButton defaultButton = NoButton);
	button = QMessageBox.information(None,
									"Qt Gui Application",
									"This is a normal information.",
									QMessageBox.StandardButtons(QMessageBox.Yes | QMessageBox.Discard),
									QMessageBox.Yes);
	if QMessageBox.Discard == button :
		print ("infomation discarded." )
    
#  弹出严重错误信息
def example02() :
    #static StandardButton critical(QWidget *parent, const QString &title,
    #    const QString &text, StandardButtons buttons = Ok,
    #    StandardButton defaultButton = NoButton);
	button = QMessageBox.critical(None, 
									"Qt Gui Application", 
									"This is a critical information.",            
									QMessageBox.StandardButtons(QMessageBox.Ok | QMessageBox.Discard),
									QMessageBox.Ok);
	if QMessageBox.Ok == button :
		print("i see the critical information and i will take further step to handle it.")
	else :
		print("it doesn't matter to me.")
		

# 弹出提问信息
def example03() :
    #static StandardButton question(QWidget *parent, const QString &title,
    #    const QString &text, StandardButtons buttons = StandardButtons(Yes | No),
    #    StandardButton defaultButton = NoButton);
	button = QMessageBox.question(None,
									"Qt Gui Application",
									"Do you like this lesson?")
	if QMessageBox.Yes == button :
		print("I like this lesson." )
	else :
		print("I don't agree.")


# 弹出"关于(About)"信息
def example04() :
	QMessageBox.about(None,
						"Qt Gui Application",
						"copyright: 2018~2019\r\nall rights reserved.")


# 弹出警告信息
def example05() :
    #static StandardButton warning(QWidget *parent, const QString &title,
    #    const QString &text, StandardButtons buttons = Ok,
    #    StandardButton defaultButton = NoButton);
    QMessageBox.warning(None,
						"Qt Gui Application",
						"Something dangerous happeded, be careful!!!")


if __name__ == "__main__":	
	app = QApplication(sys.argv)
	
	# example01
	if True :
		example01()

    # example02 
	if True :
		example02()

    # example03 
	if True :
		example03()

    # example04
	if True :
		example04()

    # example05
	if True : 
		example05()
	
	sys.exit()


