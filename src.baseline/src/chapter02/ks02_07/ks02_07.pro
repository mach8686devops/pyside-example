
TEMPLATE	= app
LANGUAGE	= C++

CONFIG += console


DESTDIR     = $$(TRAINDEVHOME)/bin

HEADERS		+= ks02_07.pro 
	
SOURCES    +=  main.cpp 

TEMPDIR		= $$(TRAINDEVHOME)/obj/chapter02/ks02_07
OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui


TARGET = ks02_07_d
