include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= app
LANGUAGE	= C++

QT			+= widgets

TEMPDIR		= $$TRAIN_OBJ_PATH/chapter05/ks05_09/exe

DESTDIR         = $$TRAIN_BIN_PATH

INCLUDEPATH     += $$TRAIN_INCLUDE_PATH/base/basedll \
                    $$TRAIN_INCLUDE_PATH/ks05_09
HEADERS		+=  $$TRAIN_SRC_PATH/gui_base.pri \
                    ks05_09_exe.pro \
                    dialog.h \
                    $$TRAIN_INCLUDE_PATH/ks05_09/customevent.h
	
SOURCES         +=  main.cpp \
                    dialog.cpp
				
FORMS		+= dialog.ui

OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

debug_and_release {
	CONFIG(debug, debug|release) {
		LIBS   += -lbasedll_d  \
                          -lks05_09_dll_d
		
		TARGET = ks05_09_exe_d
	}
	CONFIG(release, debug|release) {			   
		LIBS   += -lbasedll		  \
                          -lks05_09_dll
				  
		TARGET	= ks05_09_exe
	}
} else {
	debug {
		LIBS   += -lbasedll_d	  \
                          -lks05_09_dll_d
				  
		TARGET	= ks05_09_exe_d
	}
	release {			   
		LIBS   += -lbasedll		  \
                          -lks05_09_dll
				  
		TARGET 	= ks05_09_exe
	}
}
