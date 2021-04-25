# -*- coding: utf-8 -*-
import sys 	
from PyQt5.QtCore import QObject, pyqtSignal
from functools import partial

# 对象A
class CObjectA(QObject) : 
	# 带1个int参数的信号
	sig_no_parameter = pyqtSignal()
	
	def __init__(self) :
		super(CObjectA, self).__init__()
	

# 对象B
class CObjectB(QObject) : 
	def __init__(self) :
		super(CObjectB, self).__init__()
	
	# 槽函数	
	def slot_one_parameter_str(self,  strValue) :
		print('slot_one_parameter_str called. strValue={}'.format(strValue))
	

if __name__ == "__main__":	
	print("\nstart working...")
	objectA = CObjectA()
	objectB = CObjectB()
	# 将信号关联到槽函数
	# todo
	
	# 模拟信号发射	
	objectA.sig_no_parameter.emit()
	print("exit.")
