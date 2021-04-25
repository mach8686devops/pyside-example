# -*- coding: utf-8 -*-
import sys
import os
from PyQt5.QtCore import QMutex, QMutexLocker, QThread, QFile
from config import CConfig

class CRecvThread(QThread): 
	bWorking = False
	bFinished = True
	mtxRunning = QMutex()
	def __init__(self) :
		super(CRecvThread, self).__init__()
	
	def run(self):	 
		self.bFinished = False
		self.bWorking = True
		trainDevHome = os.getenv('TRAINDEVHOME') 
		if None is trainDevHome:
			trainDevHome = 'usr/local/gui'
		strFileName = trainDevHome + '/test/chapter22/ks22_02/recv.txt'
		strContent = str()
		config = CConfig()
		while self.isWorking():
			QThread.sleep(1)
			file = open(strFileName, 'r')
			strContent = file.read()
			file.close()
			print(strContent)
			strList = strContent.split(",");
			print(strList)
			if 2 == len(strList):
				config.setTeacherNumber(int(strList[0]))
				print(config.getTeacherNumber())
				config.setStudentNumber(int(strList[1]))
				print(config.getStudentNumber())
		self.bFinished = True

	def isWorking(self):
		locker = QMutexLocker(self.mtxRunning)
		return self.bWorking
	
	def exitThread(self):
		self.mtxRunning.lock()
		self.bWorking = False
		self.mtxRunning.unlock()
		while not self.bFinished:
			QThread.msleep(10)