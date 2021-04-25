# -*- coding: utf-8 -*-

import sys 	
from PyQt5.QtWidgets import QApplication, QMessageBox, QInputDialog, QLineEdit

# 获取文本
def example01() :
	strText,  ok = QInputDialog.getText(None,
										"QInputDialog 示例",
										"请输入文本") 
	if ok :
		QMessageBox.information(None,
								"您输入的文本是",
								strText)
	else :
		QMessageBox.information(None,
								"您输入的文本是",
								"您选择了放弃。")
	
	strText = QInputDialog.getText(None,
									"QInputDialog 示例",
									"请输入密码",
									QLineEdit.Password)
	QMessageBox.information(None,
							"您输入的密码是",
							"我不告诉你!")
    
#  获取多行文本
def example02() :
	strText,  ok = QInputDialog.getMultiLineText(None,
												"QInputDialog 示例",
												u"请输入多行文本")

	QMessageBox.information(None,
							"您输入的文本是:",
							strText)
    # 将多行文本拆分
	strList = strText.split("\n")
	for strText in strList :
		QMessageBox.information(None,
								"您输入的文本是:", 
								strText);     
		

# 获取条目
def example03() :
	strList = ["苹果",  "香蕉",  "orange",  "pear"]
	strText,  ok = QInputDialog.getItem(None, 
										"QInputDialog 示例",
										"请选择你喜欢的水果",
										strList,
										2,
										True);
	if ok :
		QMessageBox.information(None,
								"您的选择是:",
								strText);
	else :
		QMessageBox.information(None,
								"您输入的文本是",
								"您选择了放弃。")
    

# 获取整数
def example04() :
	data,  ok = QInputDialog.getInt(None,
									"QInputDialog 示例",
									"请输入整数:",
									20,
									-100,
									200,
									10)
	if ok :
		QMessageBox.information(None,
								"QInputDialog 示例",
								"您输入的整数是:%d"%data)
	else :
		QMessageBox.information(None,
								"您输入的文本是",
								"您选择了放弃。")
											
# 获取浮点数
def example05() :
	data,  ok = QInputDialog.getDouble(None,
										"QInputDialog 示例",
										"请输入浮点数:",
										100.32,
										-12.4,
										200.5,
										5)
	if ok :
		QMessageBox.information(None,
								"QInputDialog 示例",
								"您输入的浮点数是:{:g}".format(data))
	else :
		QMessageBox.information(None,
								"您输入的文本是",
								"您选择了放弃。")


if __name__ == "__main__":	
	app = QApplication(sys.argv)
	
	# example01
	if True :
		example01()

    # example02 
	if True :
		example02()

    # example03 
	if True  :
		example03()

    # example04
	if True  :
		example04()

    # example05
	if True  : 
		example05()
	
	sys.exit()


