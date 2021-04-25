# -*- coding: utf-8 -*-

import sys 	
import platform
from PyQt5.QtWidgets import QApplication, QDialog,  QFileDialog, QMessageBox, QSystemTrayIcon, QMenu, QAction 
from PyQt5.QtGui import QIcon
from PyQt5.Qt import qApp
from PyQt5.QtCore import Qt
from ui_dialog import *
from ks15_16_rc import *

class CDialog(QDialog, Ui_CDialog) : 
	tray = None 	# 系统托盘对象
	icon = None		# 应用程序图标
	tray_menu = None # 托盘中的菜单
	RestoreAction = None # 托盘菜单项
	QuitAction = None # 托盘菜单项
	def __init__(self, parent=None) :
		super(CDialog, self).__init__(parent)
		self.setupUi(self)
		self.btnGetFileName.clicked.connect(self.getFileName)
		self.addSystemTray()
		self.setWindowFlags(self.windowFlags()|Qt.WindowMinimizeButtonHint)
	
	def addSystemTray(self):
		# 添加到托盘
		self.tray = QSystemTrayIcon(self) 	#创建系统托盘对象	
	#	self.icon = QIcon(':/images/my.ico')#创建图标
		self.icon = QIcon(':/pic/images/my.ico')#创建图标
		self.tray.setIcon(self.icon) #设置系统托盘图标
		self.setWindowIcon(self.icon)# 设置应用程序的图标
		self.tray.activated.connect(self.slot_iconActivated) #设置托盘点击事件处理函数
		#右击托盘中图标时弹出的菜单
		self.tray_menu = QMenu(QApplication.desktop()) 
		self.RestoreAction = QAction(u'还原', self, triggered=self.show) #添加一级菜单动作选项(还原主窗口)
		self.QuitAction = QAction(u'退出', self, triggered=qApp.quit) #添加一级菜单动作选项(退出程序)
		self.tray_menu.addAction(self.RestoreAction) #为菜单添加动作
		self.tray_menu.addAction(self.QuitAction)
		self.tray.setContextMenu(self.tray_menu) #设置系统托盘菜单
		self.tray.show()
		self.tray.messageClicked.connect(self.slot_messageClicked) #当单击提示信息时，给出反馈，也可以不给。

	def changeEvent(self, event):
		if not event.WindowStateChange:
			QDialog.changeEvent(event)
			return
		if Qt.WindowMinimized == self.windowState():  #点击“最小化”按钮
			self.hide()
			self.setWindowFlags(Qt.Tool)#隐藏任务栏上图标 
			self.tray.show() #显示托盘 
			self.tray.showMessage(self.windowTitle(),"请单击")#提示 
			event.ignore()	
	
	def closeEvent(self, event):
		if (not event.spontaneous()) or (not self.isVisible()):
			return
		if self.tray.isVisible():
			QMessageBox.information(self, u"系统托盘应用",
									u"程序将最小化到系统托盘中运行。如果希望恢复界面，\n请单击或右击托盘中的图标并选择相应的菜单项。")
			self.hide()
			event.ignore()
	
	def slot_iconActivated(self, reason):
		if QSystemTrayIcon.Trigger == reason:
			self.show()
		elif QSystemTrayIcon.DoubleClick == reason:
			self.show()
	
	def showMessage(self, info):
		self.tray.showMessage(u"标题", info, self.icon, 5000)

	def slot_messageClicked(self):
		QMessageBox.information(None, u"标题", u"看来您已经阅读了软件发送的提示信息。")
	
	def getFileName(self) :
		strFilter  = "text file(*.txt);;XML File(*.xml);;*(*.*)"
		sys = platform.system()
		if sys == "Windows":
			fileName, _	= QFileDialog.getOpenFileName(self,  'select file to open', 'c:\\', strFilter, "XML File(*.xml)")
		else:
			fileName, _	= QFileDialog.getOpenFileName(self,  'select file to open', '/usr/local/', strFilter, "XML File(*.xml)", QFileDialog.DontUseNativeDialog)
			
		QMessageBox.information(None,
												"文件名",
												fileName)
		info = u'打开的文件为：' + fileName
		self.showMessage(info)

if __name__ == "__main__":	
	app = QApplication(sys.argv)
	widget = CDialog()
	widget.show()
	sys.exit(app.exec_())
