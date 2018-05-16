include ../../Makefile.hs
include ./SubMakefile

INCDIR=$(COMMONINC)
LIBDIR=$(COMMONLIB) 

PREINCL=$(ORACLE_HOME)/precomp/public

PROGS = $(TMP_PROGS)

OBJ = $(PROGS:.cpp=.o)
OBJ0 = $(OBJ:.c=.o)
OBJ1 = $(OBJ0:.pc=.o)
OBJS = $(OBJ1)

.SUFFIXES:
.SUFFIXES: .pc .cpp .c .o

.pc.o:
	@echo "}>>>>>>>>>>>>>>>>>>>>>>proc pc to cpp"
	proc iname=$*.pc oname=$*.cpp $(ORCOPT_CPP) \
	include=../public include=$(ORACLE_HOME)/rdbms/demo include=$(FBASE_HOME) include=$(FBASE_HOME)/Include \
	include=$(ORACLE_HOME)/rdbms/public include=$(TUXINC) include=/usr/include
	$(CC) $(CFLAGS) -fpermissive $(INCDIR) -I$(FBASE_HOME) -c $*.cpp -o $@
	
.cpp.o:
	@echo "---------------CPP to .o "
	$(CC) $(CFLAGS) -fpermissive  $(INCDIR) -I$(FBASE_HOME) -I$(FBASE_HOME)/Include -c  $< -o $@
.c.o:
	@echo "{>>>>>>>>>>>>>make c to o"
	cc $(CFLAGS) $(INCDIR) -I$(FBASE_HOME) -I$(FBASE_HOME)/Include -c  $< -o $@


#user app
all: $(ANAME)

$(ANAME): $(OBJS)
	CFLAGS="$(CFLAGS) $(INCDIR) $(LIBDIR)" \
	CC=$(CC) \
	buildserver -o $(COMMONBIN)/$(ANAME) -s $(SNAME) -f "$(OBJS) $(LIBDIR)"

clean:
	$(RM) $(OBJS) $(ANAME)
	$(RM) *.o 
	$(RM) tp* 
	$(RM) -r SunWS_cache
	$(RM) ir.out

list:
	@echo $(PROGS) | \
	sed -e 's/^/$(CNAME)\/$(ANAME)\//' \
	-e 's/ / $(CNAME)\/$(ANAME)\//g'|tr ' ' '