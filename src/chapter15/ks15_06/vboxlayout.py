# -*- coding: utf-8 -*-

import sys 	
from PyQt5 import QtCore, QtGui, QtWidgets
from ui_vboxlayout import *

class Ui_Dialog(object):
	verticalLayoutWidget = None
	verticalLayout = None
	label_1 = None
	label_2 = None
	label_3 = None

	def setupUi(self, Dialog):
		Dialog.setObjectName("Dialog")
		Dialog.resize(311, 158)
		self.verticalLayoutWidget = QtWidgets.QWidget(Dialog)
		self.verticalLayoutWidget.setGeometry(QtCore.QRect(10, 10, 291, 131))
		self.verticalLayoutWidget.setObjectName("verticalLayoutWidget")
		self.verticalLayout = QtWidgets.QVBoxLayout(self.verticalLayoutWidget)
		self.verticalLayout.setContentsMargins(0, 0, 0, 0)
		self.verticalLayout.setObjectName("verticalLayout")
		self.label_1 = QtWidgets.QLabel(self.verticalLayoutWidget)
		self.label_1.setObjectName("label_1")
		self.verticalLayout.addWidget(self.label_1)
		self.label_2 = QtWidgets.QLabel(self.verticalLayoutWidget)
		self.label_2.setObjectName("label_2")
		self.verticalLayout.addWidget(self.label_2)
		self.label_3 = QtWidgets.QLabel(self.verticalLayoutWidget)
		self.label_3.setObjectName("label_3")
		self.verticalLayout.addWidget(self.label_3) 
		self.retranslateUi(Dialog)
		QtCore.QMetaObject.connectSlotsByName(Dialog)
		
	def retranslateUi(self, Dialog):
		_translate = QtCore.QCoreApplication.translate
		Dialog.setWindowTitle(_translate("Dialog", "Dialog"))
		self.label_1.setText(_translate("Dialog", "label_1"))
		self.label_2.setText(_translate("Dialog", "label_2"))
		self.label_3.setText(_translate("Dialog", "label_3"))
