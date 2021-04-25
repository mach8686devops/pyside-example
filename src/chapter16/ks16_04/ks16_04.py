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
	def slot_one_parameter(self,  strValue) :
		print('slot_one_parameter called. strValue={}'.format(strValue))
	

if __name__ == "__main__":	
	print("\nstart working...")
	objectA = CObjectA()
	objectB = CObjectB()
	# 将信号关联到槽函数
#	objectA.sig_no_parameter.connect(lambda : objectB.slot_one_parameter('some info'))	
	objectA.sig_no_parameter.connect(partial(objectB.slot_one_parameter, 'some info'))	
	
	# 模拟信号发射	
	objectA.sig_no_parameter.emit()
	print("exit.")
