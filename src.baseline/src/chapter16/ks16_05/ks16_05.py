# -*- coding: utf-8 -*-

import sys 	
from PyQt5.QtWidgets import QApplication, QDialog
from ui_maindialog import *

class CMainDialog(QDialog, Ui_CMainDialog) : 
	def __init__(self, parent=None) :
		super(CMainDialog, self).__init__(parent)
		self.setupUi(self)	
			
	
	
if __name__ == "__main__":	
	app = QApplication(sys.argv)
	widget = CMainDialog()
	widget.show()
	sys.exit(app.exec_())
