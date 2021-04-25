# -*- coding: utf-8 -*-

import sys 	
from PyQt5.QtWidgets import QApplication, QDialog
from ui_dialog import *

class CDialog(QDialog, Ui_CDialog) : 
	def __init__(self, parent=None) :
		super(CDialog, self).__init__(parent)
		self.setupUi(self)
					
			
if __name__ == "__main__":	
	app = QApplication(sys.argv)
	widget = CDialog()
	widget.show()
	sys.exit(app.exec_())
