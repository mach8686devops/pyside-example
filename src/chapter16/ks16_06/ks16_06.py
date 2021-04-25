# -*- coding: utf-8 -*-

import sys 	
from PyQt5.QtWidgets import QApplication, QDialog, QPushButton
from PyQt5.QtCore import QObject, QTime, QTimer, QSize, QTimerEvent, Qt
from PyQt5.QtGui import QMovie, QPixmap
from ui_maindialog import *
import ks16_06_rc

class CMainDialog(QDialog, Ui_CMainDialog) : 
	idx = 0
	movie = None
	pictures = [None, None, None, None]
	timerId = 0
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

		self.pushButton.setText("start");		

	def onStartStop(self) :
		if self.pushButton.isChecked() :
			self.timerId = self.startTimer(300, Qt.PreciseTimer); # 启动定时器，单位:毫秒			
			self.movie.start()
			self.pushButton.setText('stop')
		else :
			self.bStart = True
			self.killTimer(self.timerId); # 关闭定时器
			self.timerId = -1
			self.movie.stop()
			self.pushButton.setText('start')

	def timerEvent(self, evt) :
		if self.timerId == evt.timerId() : # 判断是否是所需的定时器，这点很重要!
			tm = QTime.currentTime()	
			strText = tm.toString("hh:mm:ss")		
			self.label.setText(strText);			
			# 更新图片
			self.label_png.setPixmap(self.pictures[self.idx])
			self.idx += 1
			if  self.idx > 3 :
				self.idx = 0

if __name__ == "__main__":	
	app = QApplication(sys.argv)
	widget = CMainDialog()
	widget.show()
	sys.exit(app.exec_())
