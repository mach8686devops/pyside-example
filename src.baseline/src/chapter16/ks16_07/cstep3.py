# -*- coding: utf-8 -*-

from PyQt5.QtWidgets import QWidget
from ui_step3 import *

class CStep3(QWidget, Ui_CStep3):	
	def __init__(self, parent=None) :
		super(CStep3, self).__init__(parent)
		self.setupUi(self)