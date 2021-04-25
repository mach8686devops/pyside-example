# -*- coding: utf-8 -*-
"""
	案例代码
"""

import sys 	
from PyQt5.QtWidgets import QDialog
from ui_dialog import *

class CDialog(QDialog, Ui_CDialog) : 
	def __init__(self, parent=None) :
		super(CDialog, self).__init__(parent)
		self.setupUi(self)
		self.setWindowTitle('matplotlib')