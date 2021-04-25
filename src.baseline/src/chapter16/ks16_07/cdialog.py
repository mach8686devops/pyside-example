# -*- coding: utf-8 -*-

from PyQt5.QtWidgets import QDialog
from ks16_07_rc import *
from ui_dialog import *

class CDialog(QDialog, Ui_CDialog):	
	def __init__(self, parent=None) :
		super(CDialog, self).__init__(parent)
		self.setupUi(self)