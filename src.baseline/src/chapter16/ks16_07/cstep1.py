# -*- coding: utf-8 -*-

from PyQt5.QtWidgets import QWidget
from ui_step1 import *

class CStep1(QWidget, Ui_CStep1):	
	def __init__(self, parent=None) :
		super(CStep1, self).__init__(parent)
		self.setupUi(self)