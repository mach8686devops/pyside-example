# -*- coding: utf-8 -*-

import sys 	
from PyQt5.QtWidgets import QApplication 
from cdialog import *

if __name__ == "__main__":	
	app = QtWidgets.QApplication(sys.argv)
	widget = CDialog()
	widget.show()
	sys.exit(app.exec_())
