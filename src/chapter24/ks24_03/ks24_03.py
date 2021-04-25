# -*- coding: utf-8 -*-

import sys 	
from PyQt5.QtWidgets import QApplication
from PyQt5.QtCore import QTranslator
from cmainwidget import *
import os
			
if __name__ == "__main__":	
	app = QApplication(sys.argv)

	# 安装我们项目的翻译文件
	trainDevHome = os.getenv('TRAINDEVHOME') 
	if None is trainDevHome:
		trainDevHome = 'usr/local/gui'
	strDir = trainDevHome + '/system/lang/' # $TRAINDEVHOME/system/lang/ksxx_xx.qm 
	trans = QTranslator(None) 
	trans.load('ks24_03', strDir)
	_app = QApplication.instance()
	_app.installTranslator(trans) 

	
	mainwidget = CMainWidget(None)
	mainwidget.show()
	
	sys.exit(app.exec_())
