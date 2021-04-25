# -*- coding: utf-8 -*-
"""
    本案例需要提前设置环境变量TRAINDEVHOME，
	并准备'$TRAINDEVHOME/test/chapter19/ks19_01/input.txt'文件。
"""

import sys 	
from PyQt5.QtWidgets import QApplication, QMainWindow 
from PyQt5.QtCore import QFile, QTextStream
import os
from textedit import CTextEdit


if __name__ == "__main__":	
	app = QApplication(sys.argv)
	mainWindow = QMainWindow(None)
	textEdit = CTextEdit(mainWindow)
	file = QFile()
	trainDevHome = os.getenv('TRAINDEVHOME') 
	if None is trainDevHome:
		trainDevHome = 'usr/local/gui'
	strFile = trainDevHome + '/test/chapter19/ks19_02/input.txt'
	file.setFileName(strFile)    
	strText = str()
	if (file.open(QFile.ReadOnly | QFile.Text)) :
		input = QTextStream(file)
		input.setCodec('UTF-8') 
		strText = input.readAll()    

	textEdit.setText(strText)
	mainWindow.setCentralWidget(textEdit)
	mainWindow.show()
	
	sys.exit(app.exec_())
