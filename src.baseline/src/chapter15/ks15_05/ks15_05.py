# -*- coding: utf-8 -*-

import sys 	
from PyQt5.QtWidgets import QApplication, QDialog
from ui_dialog_a import *
class CDialogA(QDialog, Ui_CDialogA) : 
	def __init__(self, parent=None):
		super(CDialogA, self).__init__(parent)
		self.setupUi(self)
	
if __name__ == "__main__":	
	app = QtWidgets.QApplication(sys.argv)
	widget = CDialogA()
	widget.show()
	sys.exit(app.exec_())
