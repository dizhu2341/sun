#ifndef SQLCA
#  include <sqlca.h>
#endif
#ifndef ORACA
#  include <oraca.h>
#endif
#ifndef SQLPRO
#  define SQLPRO
#define SQL_SUCCESS (sword)0
#define SQL_ERROR (sword)-1
#define SQL_SINGLE_RCTX (dvoid *)0
#define SQLErrorGetText(arg1, arg2, arg3, arg4) sqlglmt(arg1, arg2, arg3, arg4)
#define SQLStmtGetText(arg1, arg2, arg3, arg4) sqlglst(arg1, arg2, arg3, arg4)
#define SQLColumnNullCheck(arg1, arg2, arg3, arg4) sqlnult(arg1, arg2, arg3, arg4)
#define SQLNumberPrecV6(arg1, arg2, arg3, arg4) sqlprct(arg1, arg2, arg3, arg4)
#define SQLNUmberPrecv7(arg1, arg2, arg3, arg4) sqlpr2t(arg1, arg2, arg3, arg4)
#define SQLVarcharGetLength(arg1, arg2, arg3) sqlvcpt(arg1, arg2, arg3)
#define SQLGetStride(arg1, arg2, arg3, arg4) sqlstrdt(arg1, arg2, arg3, arg4)
#if defined (__STDC__) || defined (__cplusplus)
#ifdef  __cplusplus
extern "C" {  
#endif
extern void sqlglm( char*, size_t*, size_t* );  
extern void sqlgls( char*, size_t*, size_t* );  
extern void sqliem( char*, int* );  
extern void sqlnul(  short*,  short*, int* );  
extern void sqlprc(  int*,  int*,  int* );  
extern void sqlpr2( unsigned int*, int*, int*);  
extern void sqlvcp( unsigned int*, unsigned int* );  
extern void sqlglmt( void*, char*, size_t*, size_t* );  
extern void sqlglst( void*, char*, size_t*, size_t* );  
extern void sqliemt( void*, char*, int*);  
extern void sqlnult( void*, unsigned short*, unsigned short*, int*);  
extern void sqlpr2t( void*, unsigned int*, int*, int*);  
extern void sqlprct( void*, unsigned int*, int*, int*);  
extern void sqlvcpt( void*, unsigned int*, unsigned int*);  
extern void SQLExtProcError( void*, char*, size_t );  
extern int iapprs( char* );  
extern int iappfo( char*, char*, unsigned int );  
extern int exiterr( char* );  
extern struct SQLDA *sqlald( int, size_t, size_t );  
extern void sqlclu( struct SQLDA*);  
extern struct SQLDA *sqlaldt( void*, int, size_t, size_t );  
extern void sqlclut( void*, struct SQLDA*);  
#ifdef  __cplusplus
}  
#endif
#else
extern void sqlglm(  );  
extern void sqlgls( );  
extern void sqliem(  );  
extern void sqlnul(  );  
extern void sqlprc(  );  
extern void sqlpr2( );  
extern void sqlvcp( );  
extern void sqlstrd();  
extern void sqlglmt( );  
extern void sqlglst();  
extern void sqliemt( );  
extern void sqlnult( );  
extern void sqlprct( );  
extern void sqlpr2t();  
extern void sqlvcpt();  
extern void sqlstrdt();  
extern void SQLExtProcError();  
extern void SQLRowidGet();  
extern int iapprs(  );  
extern int iappfo(  );  
extern int exiterr(  );  
extern struct SQLDA *sqlald(  );  
extern void sqlclu( );  
extern struct SQLDA *sqlaldt( );  
extern void sqlclut();  
#endif
#endif
