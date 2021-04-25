# -*- coding: utf-8 -*-
"""
	案例代码
"""

import sys 	
from PyQt5.QtWidgets import QApplication, QDialog
from PyQt5.QtCore import QDir
from ui_dialog import *


class CDialog(QDialog, Ui_CDialog) : 
	def __init__(self, parent=None) :
		super(CDialog, self).__init__(parent)
		self.setupUi(self)
		self.setWindowTitle('多线程')
		trainDevHome = os.getenv('TRAINDEVHOME') 
		if None is trainDevHome:
			trainDevHome = 'usr/local/gui'
		strDir = trainDevHome + '/test/chapter22/ks22_01/'
		dir = QDir()
		if not dir.exists(strDir):
			dir.mkpath(strDir)

