# -*- coding: utf-8 -*-

import sys 	
from PyQt5 import QtCore, QtGui, QtWidgets
from ui_hboxlayout import *

class Ui_Dialog(object):
	horizontalLayoutWidget = None
	horizontalLayout = None
	pushButton_1 = None
	pushButton_2 = None
	pushButton_3 = None
	def setupUi(self, Dialog):
		Dialog.setObjectName("Dialog")
		Dialog.resize(352, 160)
		self.horizontalLayoutWidget = QtWidgets.QWidget(Dialog)
		self.horizontalLayoutWidget.setGeometry(QtCore.QRect(10, 10, 319, 131))
		self.horizontalLayoutWidget.setObjectName("horizontalLayoutWidget")
		self.horizontalLayout = QtWidgets.QHBoxLayout(self.horizontalLayoutWidget)
		self.horizontalLayout.setContentsMargins(0, 0, 0, 0)
		self.horizontalLayout.setObjectName("horizontalLayout")
		self.pushButton_1 = QtWidgets.QPushButton(self.horizontalLayoutWidget)
		self.pushButton_1.setObjectName("pushButton_1")
		self.horizontalLayout.addWidget(self.pushButton_1)
		self.pushButton_2 = QtWidgets.QPushButton(self.horizontalLayoutWidget)
		self.pushButton_2.setObjectName("pushButton_2")
		self.horizontalLayout.addWidget(self.pushButton_2)
		self.pushButton_3 = QtWidgets.QPushButton(self.horizontalLayoutWidget)
		self.pushButton_3.setObjectName("pushButton_3")
		self.horizontalLayout.addWidget(self.pushButton_3)
		self.retranslateUi(Dialog)
		QtCore.QMetaObject.connectSlotsByName(Dialog)
		
	def retranslateUi(self, Dialog):
		_translate = QtCore.QCoreApplication.translate
		Dialog.setWindowTitle(_translate("Dialog", "Dialog"))
		self.pushButton_1.setText(_translate("Dialog", "PushButton"))
		self.pushButton_2.setText(_translate("Dialog", "pushButton_2"))
		self.pushButton_3.setText(_translate("Dialog", "pushButton_3"))
