# -*- coding: utf-8 -*-

import sys 	
from PyQt5.QtWidgets import QApplication
from delegate import *
from tableview import *
from tablemodel import *

if __name__ == "__main__":	
	app = QApplication(sys.argv)
	# 构建模型，并设置一些属性
	model = CTableModel(5,  2)
	tableView = CTableView(None)
	tableView.setModel(model)
	tableView.setAlternatingRowColors(True)
	tableView.horizontalHeader().setStretchLastSection(True);
	model.setHeaderData(0, Qt.Horizontal, '属性名')
	model.setHeaderData(1, Qt.Horizontal, '属性值')
	
	delegate = CDelegate()
	tableView.setItemDelegate(delegate)
	
	tableView.setWindowTitle("属性窗")
	tableView.show()

	indexRoot = model.invisibleRootItem().index()
	model.setData(model.index(0, 0, indexRoot), 'id', Qt.EditRole)
	model.setData(model.index(1, 0, indexRoot),  '描述', Qt.EditRole)
	model.setData(model.index(2, 0, indexRoot), '是否已验证', Qt.EditRole)
	model.setData(model.index(3, 0, indexRoot),  '是否最后一个', Qt.EditRole)
	model.setData(model.index(4, 0, indexRoot),  '动画速度', Qt.EditRole)
	
	model.setData(model.index(0, 1, indexRoot),   100, Qt.EditRole);
	model.setData(model.index(1, 1, indexRoot),  '备注', Qt.EditRole)
	model.setData(model.index(2, 1, indexRoot),   0, Qt.EditRole);
	model.setData(model.index(3, 1, indexRoot),   False, Qt.EditRole)	
	model.setData(model.index(4, 1, indexRoot),   2, Qt.EditRole);

	sys.exit(app.exec_())
