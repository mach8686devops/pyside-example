# -*- coding: utf-8 -*-

import sys 	
from PyQt5 import QtCore, QtGui, QtWidgets
from ui_formlayout import *

class Ui_Dialog(object):
	formLayoutWidget = None
	formLayout = None
	label_1 = None
	label_2 = None
	label_3 = None
	lineEdit = None
	lineEdit_2 = None
	lineEdit_3 = None
	def setupUi(self, Dialog):
		Dialog.setObjectName("Dialog")
		Dialog.resize(306, 154)
		self.formLayoutWidget = QtWidgets.QWidget(Dialog)
		self.formLayoutWidget.setGeometry(QtCore.QRect(30, 20, 271, 91))
		self.formLayoutWidget.setObjectName("formLayoutWidget")
		self.formLayout = QtWidgets.QFormLayout(self.formLayoutWidget)
		self.formLayout.setContentsMargins(0, 0, 0, 0)
		self.formLayout.setObjectName("formLayout")
		self.label = QtWidgets.QLabel(self.formLayoutWidget)
		self.label.setObjectName("label")
		self.formLayout.setWidget(0, QtWidgets.QFormLayout.LabelRole, self.label)
		self.lineEdit = QtWidgets.QLineEdit(self.formLayoutWidget)
		self.lineEdit.setObjectName("lineEdit")
		self.formLayout.setWidget(0, QtWidgets.QFormLayout.FieldRole, self.lineEdit)
		self.label_2 = QtWidgets.QLabel(self.formLayoutWidget)
		self.label_2.setObjectName("label_2")
		self.formLayout.setWidget(1, QtWidgets.QFormLayout.LabelRole, self.label_2)
		self.lineEdit_2 = QtWidgets.QLineEdit(self.formLayoutWidget)
		self.lineEdit_2.setObjectName("lineEdit_2")
		self.formLayout.setWidget(1, QtWidgets.QFormLayout.FieldRole, self.lineEdit_2)
		self.label_3 = QtWidgets.QLabel(self.formLayoutWidget)
		self.label_3.setObjectName("label_3")
		self.formLayout.setWidget(2, QtWidgets.QFormLayout.LabelRole, self.label_3)
		self.lineEdit_3 = QtWidgets.QLineEdit(self.formLayoutWidget)
		self.lineEdit_3.setObjectName("lineEdit_3")
		self.formLayout.setWidget(2, QtWidgets.QFormLayout.FieldRole, self.lineEdit_3)
		self.retranslateUi(Dialog)
		QtCore.QMetaObject.connectSlotsByName(Dialog)
		
	def retranslateUi(self, Dialog):
		_translate = QtCore.QCoreApplication.translate
		Dialog.setWindowTitle(_translate("Dialog", "Dialog"))
		self.label.setText(_translate("Dialog", "label_1"))
		self.label_2.setText(_translate("Dialog", "label_2"))
		self.label_3.setText(_translate("Dialog", "label_3"))
