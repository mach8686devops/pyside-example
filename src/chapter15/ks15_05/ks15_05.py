# -*- coding: utf-8 -*-

import sys 	
from PyQt5.QtWidgets import QApplication, QDialog
from ui_dialog_a import *
from ui_dialog_b import *
class CDialogA(QDialog, Ui_CDialogA) : 
	def __init__(self, parent=None) :
		super(CDialogA, self).__init__(parent)
		self.setupUi(self)
		self.btnDialogB.clicked.connect(self.slot_invokeDialogB)
		self.btnExit.clicked.connect(self.close)

	def slot_invokeDialogB(self) :
		sender = self.sender()
		print( sender.text() + '按下')
		dialogB = CDialogB()
		dialogB.exec()		

class CDialogB(QDialog, Ui_CDialogB) : 
	def __init__(self, parent=None):
		super(CDialogB, self).__init__(parent)
		self.setupUi(self)
		self.btnExit.clicked.connect(self.close)		

if __name__ == "__main__":	
	app = QtWidgets.QApplication(sys.argv)
	widget = CDialogA()
	widget.show()
	sys.exit(app.exec_())
