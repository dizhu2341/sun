# *********************************************************************
# Make�ļ�ע�⣺
# ���붨�����»���������
#   windows: 
#       ORACLE_HOME �����磺e:\oracle\ora10g��
#       VC_HOME �����磺c:\program files\devstudio\vc\include��
#   linux: 
#       GCC_VER �����磺export GCC_VER = 3.2.3�� ����ִ�У�g++ -v���ҵ�ǰ�汾 }
# 
# ����ʵ����
#   windows: 
#       ִ�а汾:     nmake -fs_XXXXflow.mvc -D _DEBUG=1 ORA_VER=10  
#   linux: 
#       ִ�а汾:       make -fs_XXXXflow.gcc ORA_VER=10  
# 
# *********************************************************************


#Ҫ����������,���������obj�ļ�����
FC1 = jc_finger

OBJS1 = $(FC1).o

ifneq (,$(findstring solaris,$(OSTYPE)))
OUTDIR = $(HOME)/appcom
else
OUTDIR = $(HOME)/appcom
endif

#PROCԤ������
PROC = $(ORACLE_HOME)/bin/proc
#CPP������
CC = g++

#Ԥ����ѡ��
CPP_PROFLAGS = ireclen=132 \
oreclen=132 \
char_map=string \
close_on_commit=yes \
code=cpp \
cpp_suffix=cpp \
def_sqlcode=yes \
define=USE_PRO_C \
hold_cursor=yes \
maxopencursors=60 \
mode=ansi \
parse=partial \
prefetch=200 \
select_error=yes \
sqlcheck=full \
threads=yes \
sys_include=/usr/include/c++/4.4.4/x86_64-redhat-linux \
sys_include=/usr/include/c++/4.4.4 \
userid=hsjc/hsjc@ora10g \
include=$(ORACLE_HOME)/precomp/public\
include=$(ORACLE_HOME)/oci/include\
include=$(ORACLE_HOME)/rdbms/public\
include=$(FBASE_HOME)\
include=$(HOME)/src\
include=$(GCC_LIB)


#(-Dxxx should be added to DEFS macro):
DEFS =-D OS_UNIX


#option ���룬����ѡ��
CFLAGS = -c -fPIC $(DEFS)
LDFLAGS = -shared
STDLIBS = -lc -lnsl -ldl -lm -lstdc++ -lpthread
LIBPATH=$(OUTDIR)
DBLIB = -L$(ORACLE_HOME)/lib -lclntsh -L$(ORACLE_HOME)/lib  -lsql$(ORA_VER)
HSLIB = -L$(OUTDIR) 

#ͷ�ļ�·��
INCLALL =  -I $(HOME)/src  -I $(ORACLE_HOME)/precomp/public  -I $(ORACLE_HOME)/oci/include -I $(ORACLE_HOME)/rdbms/public  -I $(FBASE_HOME)/ 

#debug�汾
all:$(FC1)

$(FC1):$(OBJS1)
	$(CC)  $(LDFLAGS) $(OBJS1) $(DBLIB) $(HSLIB) -o$(OUTDIR)/libs_as_$(FC1).$(ORA_VER).so $(LIBS) $(EXP)

$(FC1).o:$(FC1).pc
	$(PROC) $(CPP_PROFLAGS) iname=$(FC1).pc oname=$(FC1).cpp
	$(CC) $(CFLAGS) $(FC1).cpp $(INCLALL)

cleanobj:
	rm -fr *.o core *~ cxx_repository
	
clean: cleanobj
	rm -f tp*
	
doxygen:
	doxygen doxygen.cfg
	-del *.obj
