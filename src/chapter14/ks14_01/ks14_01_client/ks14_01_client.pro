include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= app
LANGUAGE	= C++

QT			+= widgets network

TEMPDIR		= $$TRAIN_OBJ_PATH/chapter14/ks14_01_client

DESTDIR     = $$TRAIN_BIN_PATH

INCLUDEPATH += $$TRAIN_INCLUDE_PATH/base/basedll

HEADERS		+=  $$TRAIN_SRC_PATH/gui_base.pri \
				ks14_01_client.pro \
				client.h
	
SOURCES    +=  main.cpp \
				client.cpp
				
FORMS		+= client.ui

OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

debug_and_release {
	CONFIG(debug, debug|release) {
	#	LIBS   += -lbasedll_d   
		TARGET = ks14_01_client_d
	}
	CONFIG(release, debug|release) {			   
	#	LIBS   += -lbasedll				   
		TARGET	= ks14_01_client
	}
} else {
	debug {
	#	LIBS   += -lbasedll_d		
		TARGET	= ks14_01_client_d
	}
	release {			   
	#	LIBS   += -lbasedll		
		TARGET 	= ks14_01_client
	}
}