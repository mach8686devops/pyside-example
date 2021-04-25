# -*- coding: utf-8 -*-

import sys 	
from PyQt5.QtWidgets import QApplication, QDialog
from PyQt5.QtCore import QSize
from PyQt5.QtGui import QMovie
from ui_dialog import *
class CDialog(QDialog, Ui_CDialog) : 
	def __init__(self, parent=None):
		super(CDialog, self).__init__(parent)
		self.setupUi(self)
		self.show()
		
		movie = QtGui.QMovie(":pic/images/rainman.gif");
		size = QSize(self.label.geometry().size())
		movie.setScaledSize(size);
		print("w=%d, h=%d" %(size.width(), size.height()))
		self.label.setMovie(movie);
		movie.start();
	
if __name__ == "__main__":	
	app = QtWidgets.QApplication(sys.argv)
	widget = CDialog()
	widget.show()
	sys.exit(app.exec_())
