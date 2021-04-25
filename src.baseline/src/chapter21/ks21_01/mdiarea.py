# -*- coding: utf-8 -*-
from PyQt5.QtWidgets import QMdiArea, QAction, QGraphicsScene,QWidget, QFileDialog, QMdiSubWindow
from PyQt5.QtGui import QIcon, QKeySequence
from PyQt5.QtCore import Qt, pyqtSignal, QRectF, QPointF, QFileInfo
from graphicsview import CGraphicsView
class CEditMdiArea(QMdiArea):
	lastActivatedMdiChild = None# 上一个活动子窗口
	mainWindow = None			# 父窗口
	graphicsView = None			# 视图
	sig_editViewChanged = pyqtSignal(QWidget)
	sig_viewMouseMove = pyqtSignal(QPointF)
	sig_viewClose = pyqtSignal(QWidget)

	def __init__(self, parent=None) :
		super(CEditMdiArea, self).__init__(parent)
		self.subWindowActivated.connect(self.slot_subWindowActivate)
		self.slot_subWindowActivate(None)
	
	def openFile(self, fileName):
		bSucceeded = False
		if len(fileName) != 0:  
			existing = self.findMdiChild(fileName)
			if existing:
				self.setActiveSubWindow(existing)
				return True
			child = self.createMdiChild(fileName)
			succeeded = child.isValid()
			if succeeded:
				child.showMaximized()
			else:
				if child.parent():
					subWindow = QMdiSubWindow(child.parent())
					subWindow and subWindow.close() or child.close()            
				else:
					child.close()
		return bSucceeded

	def slot_subWindowActivate(self, mdiChild):
		hasMdiChild = ((mdiChild is None) and False or True)
		if hasMdiChild:
			if mdiChild != self.lastActivatedMdiChild:
				if self.lastActivatedMdiChild:
					view = self.getActiveEditView(self.lastActivatedMdiChild)
					if view:   
						# 需要把槽函数跟旧视图解除关联，防止旧视图信号继续触发槽函数
						self.disconnectEditViewWithSlot_whenInActivate(view)
			
				view = self.getActiveEditView(mdiChild)
				if view:
					self.sig_editViewChanged.emit(view) # 发出信号
         			# 将编辑视图挂接到多窗口区域的槽函数
					self.connectEditViewWithSlot(view)            
			self.lastActivatedMdiChild = mdiChild
		#m_pPasteAct.setEnabled(hasMdiChild)

	def getMainWindow(self):
		return self.mainWindow		 

	def activeMdiChild(self):
		view = None
		tActiveSubWindow = self.activeSubWindow()
		if tActiveSubWindow is None:
			tActiveSubWindow = self.lastActivatedMdiChild 
		if tActiveSubWindow:
			view = self.getActiveEditView(tActiveSubWindow)   
		return view

	def createMdiChild(self, fileName):
		view = CGraphicsView(fileName, self)
		if view and view.isValid():
			subWindow1 = QMdiSubWindow()
			subWindow1.setWidget(view)
			subWindow1.setAttribute(Qt.WA_DeleteOnClose)
			self.addSubWindow(subWindow1)
			view.setParent(subWindow1)  
		return view

	def findMdiChild(self, fileName):
		strFileName = QFileInfo(fileName).fileName()
		for window in self.subWindowList():
			view = self.getActiveEditView(window)
			if view and (view.getFileName() == strFileName):
				return window	          		   
		return None
	
	def getActiveEditView(self, mdiChild):
		if not mdiChild:
			return None
		view = None
		if mdiChild.widget():
			view = mdiChild.widget()
		return view
		

	def slot_viewClose(self, child):
		if child == None:
			return	   
		view = CGraphView(child)
		if view:   
			self.disconnectEditViewWithSlot(view) # 将编辑视图与多窗口区域的槽函数断开连接
		self.lastActivatedMdiChild = None
		self.sig_editViewClose.emit(child)
		self.lastActivatedMdiChild = None # 防止其他对象对于 editViewClose 信号的处理导致触发activeSubWindow从而使self.lastActivatedMdiChild重新被赋值（为已关闭的窗口）

	def connectEditViewWithSlot(self, view):
		view.sig_viewMouseMove.connect(self.sig_viewMouseMove);
		view.sig_viewClose.connect(self.slot_viewClose)


	def disconnectEditViewWithSlot(self, view):
		self.disconnectEditViewWithSlot_whenInActivate(view)
		view.sig_viewClose.disconnect(self.slot_viewClose)

	def disconnectEditViewWithSlot_whenInActivate(self, view)	:
		view.sig_viewMouseMove.disconnect(self.sig_viewMouseMove)

	def createActions(self):
		pass

	def createToolBars(self):
		pass

	def new(self):
		child = self.createMdiChild("")
		if child is None:    
			return
		bSucceeded = child.isValid()
		if bSucceeded:    
			child.showMaximized()
		else:
			child.close()     

	def open(self):
		strFilter  = "text file(*.txt);;XML File(*.xml);;*(*.*)"
		fileName, _ = QFileDialog.getOpenFileName(self,  'select file to open', 'c:\\', strFilter, "Txt File(*.txt)")       
		self.openFile(fileName)

	#ifndef QT_NO_CLIPBOARD
	def cut(self):
		view = self.activeMdiChild()
		if view is None:
			return
		view.cut()

	def copy(self):
		view = self.activeMdiChild()
		if view is None:
			return
		view.copy()	 

	def paste(self):
		view = self.activeMdiChild()
		if view is None:
			return
		view.paste()	 
	#endif
	def addRect(self):
		view = self.activeMdiChild()
		if view is None:
			return
		view.addRect()	 	  
	
	def addEllipse(self):
		view = self.activeMdiChild()
		if view is None:
			return
		view.addEllipse()	