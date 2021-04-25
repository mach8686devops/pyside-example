include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= lib
LANGUAGE	= C++

QT		+= widgets
CONFIG          += dll


TEMPDIR		= $$TRAIN_OBJ_PATH/chapter05/ks05_09/dll

DESTDIR     = $$TRAIN_LIB_PATH
DLLDESTDIR  = $$TRAIN_BIN_PATH

win32{
	DEFINES *= __ks05_09_DLL_SOURCE__ 
}


SOURCES    	+= address.cpp

FORMS           += address.ui

OBJECTS_DIR     = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

INCLUDEPATH *= $$TRAIN_INCLUDE_PATH/ks05_09/
INCLUDEPATH *= $$UI_DIR

HEADERS		+= $$TRAIN_SRC_PATH/gui_base.pri \
                    ks05_09_dll.pro \
                    $$TRAIN_INCLUDE_PATH/ks05_09/address.h
				
debug_and_release {
	CONFIG(debug, debug|release) {
		   
		TARGET = ks05_09_dll_d
	}
	CONFIG(release, debug|release) {			   
				   
		TARGET	= ks05_09_dll
	}
} else {
	debug {				  
				   
		TARGET	= ks05_09_dll_d
	}
	release {				  
				   
		TARGET 	= ks05_09_dll
	}
}
