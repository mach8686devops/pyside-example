# -*- coding: utf-8 -*-

from PyQt5.QtWidgets import QWidget
from ui_step2 import *

class CStep2(QWidget, Ui_CStep2):	
	def __init__(self, parent=None) :
		super(CStep2, self).__init__(parent)
		self.setupUi(self)