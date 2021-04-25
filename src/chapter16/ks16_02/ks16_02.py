# -*- coding: utf-8 -*-

import sys 	
from PyQt5.QtCore import QObject, pyqtSignal

# 对象A
class CObjectA(QObject) : 
	# 定义一个信号
	sig_message = pyqtSignal()
	def __init__(self) :
		super(CObjectA, self).__init__()
		
	# 模拟发射信号	
	def emission_simulate (self) :
		print("emit signal sig_message")
		# 发射信号
		self.sig_message.emit()
			
# 对象B
class CObjectB(QObject) : 
	def __init__(self) :
		super(CObjectB, self).__init__()
		
	# 槽函数
	def slot_receive(self) :
		print("receive signal sig_message and slot_receive called")
	
if __name__ == "__main__":	
	print("\nstart working...")
	objectA = CObjectA()
	objectB = CObjectB()
	
	# 将信号关联到槽函数
	objectA.sig_message.connect(objectB.slot_receive)
	
	# 模拟信号发射
	objectA.emission_simulate()
	
	print("exit.")
