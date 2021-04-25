# -*- coding: utf-8 -*-

import sys 	
from PyQt5.QtWidgets import QApplication, QDialog,  QMessageBox
from PyQt5.QtGui import  QIcon
from ui_dialog import *
from enum import Enum
import ks15_10_rc

class CDialog(QDialog, Ui_CDialog) : 
	
	class EUserType(Enum) :	# 用户角色枚举
		EUserType_Invalid = 0	# 无效
		EUserType_Admin =1		# 管理员
		EUserType_User = 2		# 普通用户
		EUserType_Guest = 3		# guest用户
		EUserType_Other = 4		# 其他
		EUserType_Max	= 5   	# 

	def __init__(self, parent=None) :
		super(CDialog, self).__init__(parent)
		self.setupUi(self)
		
		# addItem, 当前第0条
		self.cbRole.addItem("user", self.EUserType.EUserType_User);
		# 当前第1条
		self.cbRole.addItem("guest");
		self.cbRole.setItemData(1, self.EUserType.EUserType_Guest);    
		self.cbRole.addItem(QIcon(":/images/other.png"), "other", self.EUserType.EUserType_Other);
		strList = ["maintain",  "security", "owner"]
		self.cbRole.addItems(strList);
		# 在user之前插入一条记录。将在第0条之前插入，"admin"将变为第0条
		self.cbRole.insertItem(0,  "admin",  self.EUserType.EUserType_Admin);
		# 修改完cbRole的数据后再关联信号-槽
		self.cbRole.currentIndexChanged.connect(self.slot_cbRoleChanged)
		self.buttonBox.accepted.connect(self.accept)
		self.buttonBox.rejected.connect(self.reject)	
		self.btnPopup.clicked.connect(self.slot_popup)

	def slot_popup(self) :
		self.cbRole.showPopup();

	def slot_cbRoleChanged(self, index) :
		str = self.cbRole.currentText();
		eUserType = self.cbRole.itemData(index);
		
		if eUserType == self.EUserType.EUserType_Admin :
			strInfo = str + "," 
			str = f"idx={index}, usertype enum value={eUserType}"
			strInfo += str
			print(strInfo)
			QMessageBox.information(self,  "combobox selection change", strInfo)
			
		else :
			strInfo = str + "," 
			str = f"idx:{index}, usertype enum value:{eUserType}"
			strInfo += str
			print(strInfo)
			QMessageBox.information(self,  "combobox selection change", strInfo)
	
if __name__ == "__main__":	
	app = QApplication(sys.argv)
	widget = CDialog()
	widget.show()
	sys.exit(app.exec_())
