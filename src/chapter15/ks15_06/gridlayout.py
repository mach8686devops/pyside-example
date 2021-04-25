# -*- coding: utf-8 -*-

import sys 
from PyQt5 import QtCore, QtGui, QtWidgets
from ui_gridlayout import *

class Ui_Dialog(object):
	gridLayoutWidget = None
	gridLayout = None
	label_1 = None
	label_2 = None
	label_3 = None
	label_4 = None
	def setupUi(self, Dialog):
		Dialog.setObjectName("Dialog")
		Dialog.resize(348, 154)
		self.gridLayoutWidget = QtWidgets.QWidget(Dialog)
		self.gridLayoutWidget.setGeometry(QtCore.QRect(20, 10, 311, 131))
		self.gridLayoutWidget.setObjectName("gridLayoutWidget")
		self.gridLayout = QtWidgets.QGridLayout(self.gridLayoutWidget)
		self.gridLayout.setContentsMargins(0, 0, 0, 0)
		self.gridLayout.setObjectName("gridLayout")
		self.label_2 = QtWidgets.QLabel(self.gridLayoutWidget)
		self.label_2.setObjectName("label_2")
		self.label_4 = QtWidgets.QLabel(self.gridLayoutWidget)
		self.label_4.setObjectName("label_4")
		self.gridLayout.addWidget(self.label_4, 0, 1, 2, 1)
		self.label_1 = QtWidgets.QLabel(self.gridLayoutWidget)
		self.label_1.setObjectName("label_1")
		self.gridLayout.addWidget(self.label_1, 0, 0, 1, 1)
		self.label_3 = QtWidgets.QLabel(self.gridLayoutWidget)
		self.label_3.setObjectName("label_3")
		self.gridLayout.addWidget(self.label_3, 2, 0, 1, 2)
		self.retranslateUi(Dialog)
		QtCore.QMetaObject.connectSlotsByName(Dialog)
		
	def retranslateUi(self, Dialog):
		_translate = QtCore.QCoreApplication.translate
		Dialog.setWindowTitle(_translate("Dialog", "Dialog"))
		self.label_2.setText(_translate("Dialog", "第2行，第1列"))
		self.label_4.setText(_translate("Dialog", "第1行，第1列"))
		self.label_1.setText(_translate("Dialog", "第1行，第1列"))
		self.label_3.setText(_translate("Dialog", "第3行，第1列"))
