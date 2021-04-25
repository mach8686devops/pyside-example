# -*- coding: utf-8 -*-
from PyQt5.QtWidgets import QApplication, QGraphicsView, QGraphicsScene, QGraphicsItem, QMenu, QAction
from PyQt5.QtCore import QMimeData, QPointF, QByteArray, QTextStream
from PyQt5.QtCore import pyqtSignal, Qt, QIODevice
from PyQt5.QtXml import QDomDocument
from graphicsitem import EGraphItemType
from rectitem import CGraphRectItem
from ellipseitem import CGraphEllipseItem

class CGraphicsView(QGraphicsView):
	ptScene = QPointF()
	viewMouseMove = pyqtSignal(QPointF)
	cutAct = None					# 【剪切】子菜单
	copyAct = None				# 【拷贝】子菜单
	pasteAct = None				# 【粘贴】子菜单
	def __init__(self, parent=None) :
		super(CGraphicsView, self).__init__(parent)
		self.setMouseTracking(True)
		self.createActions()
		
	def mouseMoveEvent(self, event):
		pt = self.mapToScene(event.localPos().toPoint())
		self.viewMouseMove.emit(pt)  # 发射信号，以便可以在状态栏显示鼠标坐标
		
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

	#ifndef QT_NO_CLIPBOARD
	def cut(self):
		scene = self.scene()
		lst = scene.items(self.ptScene)
		if  len(lst) == 0:
			return
		# 剪切时采用隐藏图元、拷贝得到新图元的方法，也可以拷贝得到新图元后把原始图元删除。但是如果删除原始图元，则会影响redo/undo功能。
		for item in lst:
			item.setVisible(False)		
		self.copyItems(lst)

	def copy(self):
		scene = self.scene()
		lst = scene.items(self.ptScene)
		if  len(lst) == 0:
			return
		self.copyItems(lst)

	def copyItems(self, lst):
		# 清除剪贴板的原数据
		clipboard = QApplication.clipboard()
		clipboard.clear()
		# 如果没有图元可拷贝，则返回。 
		if len(lst) == 0:
			return
		dataArr = QByteArray()
		# 拷贝的信息写到数据流
		stream = QTextStream(dataArr, QIODevice.WriteOnly)

		# 只拷贝选中图元中第一个图元
		item = lst[0]
		type =  item.type()
		pt = item.pos()
		document = QDomDocument()
		root = document.createElement("doc")

		# 图元信息
		itemEle = document.createElement("item")
		itemEle.setAttribute("x", pt.x())
		itemEle.setAttribute("y", pt.y())

		if type == EGraphItemType.EGraphItemType_Rect: 
			itemEle.setAttribute("type", QGraphicsItem.UserType+1)
			rectItem = item
			itemEle.setAttribute("w", rectItem.getWidth())
			itemEle.setAttribute("h", rectItem.getHeight())
		elif 	type == EGraphItemType.EGraphItemType_Ellipse: 			
			itemEle.setAttribute("type", QGraphicsItem.UserType+2)
			rectItem = item
			itemEle.setAttribute("w", rectItem.getWidth())
			itemEle.setAttribute("h", rectItem.getHeight())
		else:
			pass

		root.appendChild(itemEle)
		document.appendChild(root)
		stream << document
		data =  QMimeData()
		data.setData("gp/copyItem", dataArr)
		clipboard.setMimeData(data)

	def paste(self):
		clipboard = QApplication.clipboard()
		mimeData = clipboard.mimeData()
		scene = self.scene()
		if scene is None:
			return
		if not mimeData.hasFormat("gp/copyItem"):
			return
		doc = QDomDocument()
		doc.setContent(mimeData.data("gp/copyItem"))
		root = doc.firstChildElement()
		itemEle = root.firstChildElement()
		strTagName = itemEle.tagName()
		#qDebug() << strTagName
		if strTagName != "item":
			return
		strValue = itemEle.attribute("type", "0")
		type = int(strValue)        
		type = EGraphItemType(type)
		pt = self.ptScene
		if itemEle.hasAttribute("w"): 
			w = float(itemEle.attribute("w", "0"))
			h = float(itemEle.attribute("h", "0"))
			if type == EGraphItemType.EGraphItemType_Rect: 
				#QPen pn(Qt.darkBlue)
				#QBrush brsh(Qt.darkBlue)
				item =  CGraphRectItem(None)
				item.setWidth(w)
				item.setHeight(h)
				item.setPos(pt)
				scene.addItem(item)
			elif 	type == EGraphItemType.EGraphItemType_Ellipse: 
				#QPen pn(Qt.darkBlue)
				#QBrush brsh(Qt.darkBlue)
				item =  CGraphEllipseItem(None)
				item.setWidth(w)
				item.setHeight(h)
				item.setPos(pt)
				scene.addItem(item)           

	def createActions(self):		
		self.cutAct = QAction('剪切', self)
		self.cutAct.setStatusTip("Cut the current selection's contents to the clipboard")
		self.cutAct.triggered.connect(self.cut)

		self.copyAct = QAction('复制', self)
		self.copyAct.setStatusTip("Copy the current selection's contents to the clipboard")
		self.copyAct.triggered.connect(self.copy)

		self.pasteAct = QAction('粘贴', self)
		self.pasteAct.setStatusTip("Paste the clipboard's contents into the current selection")
		self.pasteAct.triggered.connect(self.paste)
	
	def contextMenuEvent(self, event):
		popMenu =  QMenu(self)                                               
		ptScene = self.mapToScene(event.pos())                                             
		scene = self.scene() 
		lst = scene.items(ptScene) 
		if len(lst)!= 0:
			popMenu.addAction(self.cutAct) 
			popMenu.addAction(self.copyAct) 
		else  :
			popMenu.addAction(self.pasteAct)                                            
		# 判断一下有没有事先执行过剪切、复制操作 
		clipboard = QApplication.clipboard() 
		mimeData = clipboard.mimeData() 
		if  not mimeData.hasFormat("gp/copyItem"):
			self.pasteAct.setEnabled(False) 
		else:
			self.pasteAct.setEnabled(True) 
		popPt = event.globalPos() 
		popMenu.move(popPt)                                                          
		popMenu.show() 
