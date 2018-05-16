##########################################################################
##  makefile.gcc 通用包含文件
##  -------------------------------------------------
##  
##概    要:
##  Makefile for g++ 3.4.6~
##
##  文件名: makefile.gcc
##  模块名: libfsc_arbmgr.so
##  模块说明: 
##   
##  -------------------------------------------------
##  Copyright (C) 2008-2010 HUNDSUN TECHNOLOGIES INC.
##  Hangzhou, China, Fri July 29 11:05:51 GMT 2016
##  -------------------------------------------------
##作    者: 公司研发中心 chengjin
##创建时间: 2016-07-29
##备    注: 
##
##修改记录: 
##########################################################################

#(1)目标文件
FC1 = ArbMgrMain
FC2 = CArbManager
FC3 = CArbMgrIOC
FC4 = CStatusMonitorMgr
FC5 = thread
FC6 = CSendHeartThread
FC7 = CRecvHeartThread
FC8 = msg_queue
FC9 = CArbMsgRWThread
FC10 = s_liblogpublic

OUTDIR = $(HOME)/appcom
HSLIB = -L$(OUTDIR) -l$(FC10)
OBJS=$(FC1).$(TO) $(FC2).$(TO) $(FC3).$(TO) $(FC4).$(TO) $(FC5).$(TO) $(FC6).$(TO) $(FC7).$(TO) $(FC8).$(TO) $(FC9).$(TO)

#(2)编译依赖.cpp.o:,
#先清除目标文件
all : cleanobj  $(EXES)
$(FC1).$(TO): $(FC1).cpp 
	$(CC) $(CFLAGS) $(FC1).cpp $(INCDIR)
$(FC2).$(TO): $(FC2).cpp 
	$(CC) $(CFLAGS) $(FC2).cpp $(INCDIR)
$(FC3).$(TO): $(FC3).cpp 
	$(CC) $(CFLAGS) $(FC3).cpp $(INCDIR)
$(FC4).$(TO): $(FC4).cpp 
	$(CC) $(CFLAGS) $(FC4).cpp $(INCDIR)
$(FC5).$(TO): $(FC5).cpp 
	$(CC) $(CFLAGS) $(FC5).cpp $(INCDIR)
$(FC6).$(TO): $(FC6).cpp 
	$(CC) $(CFLAGS) $(FC6).cpp $(INCDIR)
$(FC7).$(TO): $(FC7).cpp 
	$(CC) $(CFLAGS) $(FC7).cpp $(INCDIR)
$(FC8).$(TO): $(FC8).cpp 
	$(CC) $(CFLAGS) $(FC8).cpp $(INCDIR)
$(FC9).$(TO): $(FC9).cpp 
	$(CC) $(CFLAGS) $(FC9).cpp $(INCDIR)

$(EXES): $(OBJS)
	$(LD) $(LFLAGS) -o$(OUTDIR)/$(LIB_PRE)$(EXES)$(LIB_EXT) $(OBJS) $(STDLIBS) $(DEFLIBS) $(EXPS) $(HSLIB)

#(3)清理命令
cleanobj:
	$(RM) *.$(TO)
clean:cleanobj
	@echo clean all
