# -*- coding: utf-8 -*-
"""
    本案例需要提前设置环境变量TRAINDEVHOME，
	并准备'$TRAINDEVHOME/test/chapter22/ks22_02/recv.txt'文件。
	格式为:xxx,yyy
	其中，xxx表示教师人数，yyy表示学生人数
"""

import sys 	
from PyQt5.QtWidgets import QApplication
from cdialog import *

if __name__ == "__main__":	
	app = QApplication(sys.argv)
	widget = CDialog()
	widget.show() 	 
	sys.exit(app.exec_())