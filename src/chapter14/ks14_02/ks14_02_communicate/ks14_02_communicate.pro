include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= lib
LANGUAGE	= C++

CONFIG		+= dll 
QT			+= xml network

TEMPDIR		= $$TRAIN_OBJ_PATH/base/basedll

DESTDIR     = $$TRAIN_LIB_PATH
DLLDESTDIR  = $$TRAIN_BIN_PATH

INCLUDEPATH += $$TRAIN_INCLUDE_PATH/ks14_02

win32{
	DEFINES *= __KS14_02_COMMUNICATE_SOURCE__ 
}

HEADERS		+= $$TRAIN_SRC_PATH/gui_base.pri \
				ks14_02_communicate.pro  \
				$$TRAIN_INCLUDE_PATH/ks14_02/task.h \
				$$TRAIN_INCLUDE_PATH/ks14_02/clientconnection.h
				
SOURCES    	+=  task.cpp \
				clientconnection.cpp

OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

debug_and_release {
	CONFIG(debug, debug|release) {
		   
		TARGET = ks14_02_commuinicate_d
	}
	CONFIG(release, debug|release) {			   
				   
		TARGET	= ks14_02_commuinicate
	}
} else {
	debug {				  
				   
		TARGET	= ks14_02_commuinicate_d
	}
	release {				  
				   
		TARGET 	= ks14_02_commuinicate
	}
}