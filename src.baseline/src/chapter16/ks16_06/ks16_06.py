# -*- coding: utf-8 -*-

import sys 	
from PyQt5.QtWidgets import QApplication, QDialog, QPushButton
from PyQt5.QtCore import QTime, QTimer, QSize
from PyQt5.QtGui import QMovie, QPixmap
from ui_maindialog import *
import ks16_06_rc

class CMainDialog(QDialog, Ui_CMainDialog) : 
	idx = 0
	movie = None
	pictures = [None, None, None, None]
	def __init__(self, parent=None) :
		super(CMainDialog, self).__init__(parent)
		self.setupUi(self)
		self.pushButton.toggled.connect(self.onStartStop)
		self.movie = QMovie(":/images/rainman.gif")
		self.movie.setScaledSize(QSize(300, 300))
		self.label_gif.setMovie(self.movie)
		self.movie.start()

		self.pictures[0] = QPixmap(":/images/pic1.png").scaled(300, 300)
		self.pictures[1] = QPixmap(":/images/pic2.png").scaled(300, 300)
		self.pictures[2] = QPixmap(":/images/pic3.png").scaled(300, 300)
		self.pictures[3] = QPixmap(":/images/pic4.png").scaled(300, 300)
		self.label_png.setPixmap(self.pictures[0])



if __name__ == "__main__":	
	app = QApplication(sys.argv)
	widget = CMainDialog()
	widget.show()
	sys.exit(app.exec_())
