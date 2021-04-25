# -*- coding: utf-8 -*-
"""
	pyqt 5 demo
"""

from PyQt5.QtWidgets import QWidget
from ui_customwidget import *

class CCustomWidget(QWidget, Ui_CCustomWidget) : 
	def __init__(self, parent=None) :
		super(CCustomWidget, self).__init__(parent)
		self.setupUi(self)

