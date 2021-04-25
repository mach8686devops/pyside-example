# -*- coding: utf-8 -*-

import sys 	
from PyQt5.QtWidgets import QApplication, QDialog
from ui_dialog import *

class CDialog(QDialog, Ui_CDialog) : 
	def __init__(self, parent=None):
		super(CDialog, self).__init__(parent)
		self.setupUi(self)
		self.btnExit.clicked.connect(self.close)
		
if __name__ == "__main__":	
	app = QtWidgets.QApplication(sys.argv)
	dialog = CDialog()
	dialog.show()
	sys.exit(app.exec_())
