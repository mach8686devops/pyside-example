# -*- coding: utf-8 -*-

import sys 	
from PyQt5.QtWidgets import QApplication, QDialog, QAbstractItemView
from PyQt5.QtCore import Qt
from ui_dialog import *

class CDialog(QDialog, Ui_CDialog) : 	
	def __init__(self, parent=None) :
		super(CDialog, self).__init__(parent)
		self.setupUi(self)
		
		self.listWidgetLeft.setSelectionMode(QAbstractItemView.SingleSelection)
		self.listWidgetRight.setSelectionMode(QAbstractItemView.MultiSelection)
		self.listWidgetLeft.addItem("C++")
		self.listWidgetLeft.addItem("Python")
		self.listWidgetLeft.addItem("java")
		self.listWidgetLeft.addItem("C#")
		self.listWidgetLeft.addItem("Rubby")
		self.listWidgetLeft.addItem("Go")

		self.buttonBox.accepted.connect(self.accept)
		self.buttonBox.rejected.connect(self.reject)
		self.btn2Left.clicked.connect(self.slot_move2Left)
		self.btn2Right.clicked.connect(self.slot_move2Right)
		self.btnAscending.clicked.connect(self.slot_ascending)
		self.btnDescending.clicked.connect(self.slot_descending)
		self.listWidgetLeft.itemClicked.connect(self.slot_leftItemClicked)
		self.listWidgetLeft.itemDoubleClicked.connect(self.slot_leftItemDoubleClicked)
		self.listWidgetLeft.currentItemChanged.connect(self.slot_leftCurrentItemChanged)
			
	def slot_move2Right(self) :
		# 左侧列表只允许单选
		# 得到左侧列表当前选中的项
		pItem = self.listWidgetLeft.currentItem()
		if  pItem is None  :
			return
			
		idx = self.listWidgetLeft.row(pItem)  # 得到项的序号
		self.listWidgetLeft.takeItem(idx)        # 将项从左侧列表删除
		self.listWidgetRight.addItem(pItem)  # 将项添加到右侧列表
		
	def slot_move2Left(self) :
		# 右侧列表允许复选
		# 首先得到右侧列表中选中的项的集合
		selectedItems = self.listWidgetRight.selectedItems()
		idx = 0
		# 遍历该集合，并将项移动到左侧列表
		for item in selectedItems :
			idx = self.listWidgetRight.row(item)  # 得到该项的行号(序号)
			self.listWidgetRight.takeItem(idx)       # 先从右侧删除
			self.listWidgetLeft.addItem(item)     # 将项添加到左侧
	
	def slot_ascending(self) :
		self.listWidgetRight.sortItems(Qt.AscendingOrder)
	
	def slot_descending(self) :
		self.listWidgetRight.sortItems(Qt.DescendingOrder)

	def slot_leftItemClicked(self, item) :
		str = "my favorite program language is "
		str += item.text()
		self.label.setText(str)
		# 同时将被选中项字体加粗
		ft = item.font()
		ft.setBold(True)
		item.setFont(ft)

	def slot_leftItemDoubleClicked(self, item) :
		# 双击时，将左侧列表中被单击的项移动到右侧列表
		idx = self.listWidgetLeft.row(item)
		self.listWidgetLeft.takeItem(idx)
		self.listWidgetRight.addItem(item)

	def slot_leftCurrentItemChanged(self, current, previous)  :
		# 将之前选中项的字体粗体恢复
		if not (previous is None) :
			 ft = previous.font()
			 ft.setBold(False)
			 previous.setFont(ft)
		
if __name__ == "__main__":	
	app = QApplication(sys.argv)
	widget = CDialog()
	widget.show()
	sys.exit(app.exec_())
