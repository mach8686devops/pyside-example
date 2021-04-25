# -*- coding: utf-8 -*-

import sys 	
import platform
from PyQt5.QtWidgets import QApplication, QDialog,  QFileDialog, QMessageBox
from ui_dialog import *

class CDialog(QDialog, Ui_CDialog) : 
	def __init__(self, parent=None) :
		super(CDialog, self).__init__(parent)
		self.setupUi(self)
		self.btnGetFileName.clicked.connect(self.getFileName)
					
			
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
	
if __name__ == "__main__":	
	app = QApplication(sys.argv)
	widget = CDialog()
	widget.show()
	sys.exit(app.exec_())
