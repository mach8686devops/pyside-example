TEMPLATE	= app
LANGUAGE	= C++

#CONFIG += console
QT		+= widgets

TARGET     	= ks02_02
DESTDIR     = $$(TRAINDEVHOME)/bin
OBJECTS_DIR = $$(TRAINDEVHOME)/obj/chapter02/ks02_02
MOC_DIR		= $$OBJECTS_DIR/moc
UI_DIR		= $$OBJECTS_DIR/ui

FORMS		+= dialog.ui

HEADERS		+= ks02_02.pro  \
				dialog.h
	
	
SOURCES    +=  main.cpp \
				dialog.cpp