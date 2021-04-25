#########################################################################################
# ע�⣺���ļ����ڷ��ù����ļ��Ĺ���(����)���ã�
# �ڸ� QT �����ļ���ͨ�� include ������������Ӧ����ʹ�ã�
# ������Ա��Ҫ�������漸��ϵͳ����������
# TRAINDEVHOME		ϵͳ������Ŀ¼�������뿪����صĸ�����ģ�� (���붨��)
# TRAINBUILDTYPE	ϵͳ����汾���壬ָ������汾���ͣ�debug|release|all
# TRAINBUILDBIT		ϵͳ�������λ�����壬ָ������λ����32|64
#########################################################################################

# ����ͨ���������� TRAINDEVHOME ָ������Ŀ¼
# ���� isEmpty ��������ֱ�ӶԻ������������жϣ������Ƚ������һ����ʱ������
isEmpty(PROJECT_HOME) {
	DEVHOME = $$(TRAINDEVHOME)
}
!isEmpty(PROJECT_HOME) {
	DEVHOME = $$PROJECT_HOME
}
isEmpty(DEVHOME) {
	error('TRAINDEVHOME'�����������뱻����.)
}
# ����ϵͳִ���ļ�·�������ļ�·����ͷ�ļ�����·������
TRAIN_BIN_PATH = $$DEVHOME/bin
TRAIN_LIB_PATH = $$DEVHOME/lib
TRAIN_OBJ_PATH = $$DEVHOME/obj
TRAIN_SRC_PATH = $$DEVHOME/src
TRAIN_UIC_PATH = $$DEVHOME/obj/uic
TRAIN_INCLUDE_PATH = $$DEVHOME/include

QMAKE_LIBDIR *= $$TRAIN_LIB_PATH
DEPENDPATH *=  .\
		$$TRAIN_INCLUDE_PATH
INCLUDEPATH *=  .\
		$$TRAIN_INCLUDE_PATH

# ���ر���汾����
#########################################################################################
#
# ͨ���������� TRAINBUILDTYPE ָ������汾���ͣ�debug|release
# �ֱ��Ӧ ���԰桢���а�
#
# ͨ���������� TRAINBUILDBIT ָ������λ�����ͣ�32|64
# �ֱ��Ӧ 32 λ��64 λ
#
#####################################################################################################

# ����ϵͳʹ�õı���汾����
# ���δָ�� TRAINBUILDTYPE ����������ȱʡ�� debug ����
BUILDTYPE = $$(TRAINBUILDTYPE)
isEmpty(BUILDTYPE) {	
	message('TRAINBUILDTYPE'��������δ���ã�ʹ��ȱʡֵdebug.)
	BUILDTYPE = debug
}
# ��TRAINBUILDTYPE���ý��м򵥵Ĵ�����
# BUILDTYPE��ֵ����Ϊ��ֵ
!count(BUILDTYPE,1){
	error(���ܶ���ʹ��һ����Ч�ı���汾���ͣ�����TRAINBUILDTYPE������������.)
}
!equals(BUILDTYPE,all){
!equals(BUILDTYPE,debug){
!equals(BUILDTYPE,release){
	error(δ��֧�ֵĵı���汾���ͣ�����TRAINBUILDTYPE������������.)
		}
	}
}

# ��ͬ����汾��ص�����
equals(BUILDTYPE,debug){
	CONFIG += debug
	CONFIG -= release
}
equals(BUILDTYPE,release){
	CONFIG += release
	CONFIG -= debug
}
equals(BUILDTYPE,all){
	CONFIG += debug_and_release build_all
}
# ָ�������к궨��
debug_and_release {
	CONFIG(debug, debug|release) {
	    DEFINES += TRAIN_DEBUG
	}
	CONFIG(release, debug|release) {
	    DEFINES += TRAIN_RELEASE
	}
} else {
	debug:DEFINES += TRAIN_DEBUG
	release:DEFINES += TRAIN_RELEASE
}

# ����ϵͳʹ�õı���λ������
# ���δָ�� TRAINBUILDBIT ����������ȱʡ�� 32 λ����
BUILDBIT = $$(TRAINBUILDBIT)
isEmpty(BUILDBIT) {	
	message('TRAINBUILDBIT'��������δ���ã�ʹ��ȱʡֵ 32 λ.)
	BUILDBIT = 32
}

# ��TRAINBUILDBIT���ý��м򵥵Ĵ�����
# BUILDBIT��ֵ����Ϊ��ֵ
!count(BUILDBIT,1){
	error(���ܶ���ʹ��һ����Ч�ı���λ�����ͣ�����TRAINBUILDBIT������������.)
}
!equals(BUILDBIT,32){
	!equals(BUILDBIT,64){
		error(δ��֧�ֵĵı���λ�����ͣ�����TRAINBUILDBIT������������.)
	}
}

# ��ͬ����汾��ص�����
equals(BUILDBIT,32){
	# ��չ 32 λ������
	CONFIG *= x86

	DEFINES *= TRAIN_32
}
equals(BUILDBIT,64){
	# ��չ 64 λ������
	CONFIG *= x64

	DEFINES *= TRAIN_64
}


# ���ر���������
#########################################################################################
#
# ��ͬƽ̨�ı���������
#
#####################################################################################################

# ��ȡ���� Qt �ı���������
TRAIN_QMAKESPEC = $$(QMAKESPEC)

#UNIX + gcc������ʹ��Ԥ����ͷ�ļ�
#GCC 3.4 ���Ժ�汾֧��Ԥ����ͷ�ļ�
unix{
	contains( TRAIN_QMAKESPEC, g++ ) {
		CONFIG *= precompile_header
	}
}
#WIN32������ʹ��Ԥ����ͷ�ļ�
win32{
	CONFIG *= precompile_header
}

#UNIX�±�������
unix{
	DEFINES *= unix __unix

	contains( TRAIN_QMAKESPEC, hpux.* ) {
		# HPUX��ȫ��֧��C++
		QMAKE_CXXFLAGS *= -Aa
		LIBS += -lrt
	}
	contains( TRAIN_QMAKESPEC, aix-xlc.* ) {
		# AIX�¼��� rtti ����ѡ��
		# ʹ��ע���ļ�����ģ��ʵ����
		QMAKE_CXXFLAGS *= -qrtti=all -qtemplateregistry
		# AIX�±��붯̬���ӿ������ѡ��
		QMAKE_LFLAGS_SHLIB *= -G
		# AIX�±����ִ�г��������ѡ��Ժ� orbaucs ����ѡ��ƥ�䣬����������б�������
		QMAKE_LFLAGS_APP *= -bdynamic -brtl
		# AIX�±����ִ�г��������ѡ�����չÿ����������ʹ�õ��ڴ�������ȱʡֵ256M��Ŀǰ����1G����0x40000000��
		#QMAKE_LFLAGS_APP *= -bmaxdata:0x40000000
	}
}

#WIN32�±�������
win32{
	# 0x0500 -> 0x0501 ����ϵͳ��� Windows XP������֧�� Windows 2000
	DEFINES	*= WIN32 _WIN32_WINNT=0x0501

	# ui ���ɵ��ļ�ʹ�� utf-8 ���룬����ʱ���� 4819 ���棬ȥ��
	QMAKE_CXXFLAGS *= -wd4819

	# ȥ�� strcpy �ȱ��뾯��
	QMAKE_CXXFLAGS *= -wd4996
}


#���� STL��RTTI��EXCEPTIONS ֧��
CONFIG *= stl exceptions rtti
#������̡߳����뾯��
CONFIG *= thread warn_on



# ָ����ͬ����汾�м��ļ�Ŀ¼
debug_and_release {
	CONFIG(debug, debug|release) {
	    TRAIN_OBJ_PATH = $$TRAIN_OBJ_PATH/debug
	}
	CONFIG(release, debug|release) {
	    TRAIN_OBJ_PATH = $$TRAIN_OBJ_PATH/release
	}
} else {
	debug:TRAIN_OBJ_PATH = $$TRAIN_OBJ_PATH/debug
	release:TRAIN_OBJ_PATH = $$TRAIN_OBJ_PATH/release
}
DEFINES *= QT_NO_OPENGL