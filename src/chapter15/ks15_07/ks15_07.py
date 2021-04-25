# -*- coding: utf-8 -*-

import sys 	
from PyQt5.QtWidgets import QApplication, QDialog, QWidget
from ui_dialog import *
from ui_widget import *

class CDialog(QDialog, Ui_CDialog) : 
	def __init__(self, parent=None):
		super(CDialog, self).__init__(parent)
		self.setupUi(self)
		self.btnExit.clicked.connect(self.close)
	
		gridLayout = QtWidgets.QGridLayout(self.placeHolderwidget)
		gridLayout.setObjectName("widgetGridLayoutWidget")		
		widget = CWidget(self.placeHolderwidget);
		widget.setObjectName("widget")
		widget.setMinimumHeight(200)
		gridLayout.addWidget(widget, 0, 0)

class CWidget(QWidget, Ui_CWidget) : 
	def __init__(self, parent=None):
		super(CWidget, self).__init__(parent)
		self.setupUi(self)
				
if __name__ == "__main__":	
	app = QtWidgets.QApplication(sys.argv)
	dialog = CDialog()
	dialog.show()
	sys.exit(app.exec_())
