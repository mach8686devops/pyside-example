# -*- coding: utf-8 -*-
from PyQt5.QtWidgets import QApplication, QGraphicsView, QGraphicsScene, QGraphicsItem
from PyQt5.QtCore import QMimeData, QPointF, QByteArray, QTextStream
from PyQt5.QtCore import pyqtSignal, Qt, QIODevice
from PyQt5.QtXml import QDomDocument
from graphicsitem import EGraphItemType
from rectitem import CGraphRectItem
from ellipseitem import CGraphEllipseItem

class CGraphicsView(QGraphicsView):
	ptScene = QPointF()
	viewMouseMove = pyqtSignal(QPointF)
	def __init__(self, parent=None) :
		super(CGraphicsView, self).__init__(parent)
		self.setMouseTracking(True)
		
	def mouseMoveEvent(self, event):
		pt = self.mapToScene(event.localPos().toPoint())
		self.viewMouseMove.emit(pt)  # 触发信号，以便可以在状态栏显示鼠标坐标

	def mousePressEvent(self, event):
		#matx = matrix()
		#matx.m11()
		ptView = event.localPos()
		self.ptScene = self.mapToScene(ptView.toPoint())
	
	def addRect(self):
		scene = self.scene()
		item =  CGraphRectItem(None)
		item.setWidth(50)
		item.setHeight(50)
		item.setPos(self.ptScene)
		scene.addItem(item)

	def addEllipse(self):
		scene = self.scene()
		item =  CGraphEllipseItem(None)
		item.setWidth(50)
		item.setHeight(50)
		item.setPos(self.ptScene)
		scene.addItem(item)

	def drawBackground(self, painter, rect):
		QGraphicsView.drawBackground(self, painter, rect)
		# 绘制一个矩形用来表示场景(scene)的占用区域
		rct = self.sceneRect()
		pn = painter.pen()
		pn.setColor(Qt.gray)
		painter.setPen(pn)
		painter.drawRect(rct)