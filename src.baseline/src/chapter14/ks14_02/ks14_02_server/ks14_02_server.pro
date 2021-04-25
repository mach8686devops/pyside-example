include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= app
LANGUAGE	= C++

QT			+= widgets network
CONFIG		+= console

TEMPDIR		= $$TRAIN_OBJ_PATH/chapter14/ks14_02_server

DESTDIR     = $$TRAIN_BIN_PATH

INCLUDEPATH += $$TRAIN_INCLUDE_PATH/base/basedll

HEADERS		+=  $$TRAIN_SRC_PATH/gui_base.pri \
				ks14_02_server.pro \
				server.h
	
SOURCES    +=	main.cpp \
				server.cpp
				

OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

debug_and_release {
	CONFIG(debug, debug|release) {
	#	LIBS   += -lbasedll_d   
		TARGET = ks14_02_server_d
	}
	CONFIG(release, debug|release) {			   
	#	LIBS   += -lbasedll				   
		TARGET	= ks14_02_server
	}
} else {
	debug {
	#	LIBS   += -lbasedll_d		
		TARGET	= ks14_02_server_d
	}
	release {			   
	#	LIBS   += -lbasedll		
		TARGET 	= ks14_02_server
	}
}