# -*- coding: utf-8 -*-

import sys 	
from PyQt5.QtWidgets import QApplication, QDialog
#from ui_vboxlayout import *
#from ui_hboxlayout import *
#from ui_gridlayout import *
from ui_formlayout import *

class Dialog(QDialog, Ui_Dialog) : 
	def __init__(self, parent=None) :
		super(Dialog, self).__init__(parent)
		self.setupUi(self)


if __name__ == "__main__":	
	app = QtWidgets.QApplication(sys.argv)
	widget = Dialog()
	widget.show()
	sys.exit(app.exec_())
