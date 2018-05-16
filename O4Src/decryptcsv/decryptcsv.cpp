#include "decryptcsv.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>

char src1[] = {"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 &"};
char src2[] = {"cA1aBb2d Ce3fD4E5&Flm6nopGq7rHsjkt8uIv9wJxKyLzMNOPQgh0iRSTUVWXYZ"};
char files[][64] = {"hg_cunitstock.csv","hg_cunitstockenable.csv","hg_choldingdetail.csv","hg_centrusttabletype.csv","uft_cunitstock.csv","uft_choldingdetail.csv","uft_cinstancestock.csv",
          "uft_cfutureentrust.csv","uft_cfuturedeal.csv","uft_cunitstockex.csv","uft_cinstancestockex.csv","uft_cunitstockfactor.csv","uft_cinstncstckfctr.csv"};

#define MAX_PATH 255
#define GET_ARRAY_LEN(array,len) {len = (sizeof(array) / sizeof(array[0]));}

char g_srcdir[MAX_PATH];
char g_dstdir[MAX_PATH];

int main(int argc,char* argv[])
{
  //1-校验参数
  int type = check_param(argc,argv);
  switch (type)
  {
  case -1:
    std::cout<<"dcsv:Wrong arguments!"<<std::endl<<"Try `dcsv --help' for more information."<<std::endl;
    return -1;
  case 1:
    print_help();
    return 0;
  case 2:
    if (decrypt() == -1)
		return -1;
	else
		return 0;
  case 3:
  	if (encrypt() == -1)
		return -1;
	else
		return 0;
  default:
    std::cout<<"Inner error,please send email to jidl07639@hundsun.com."<<std::endl;
    break;
  };
  return 0;
  
}

int decrypt()
{
	int i = 0;
	int len = 0;
	int ret = 0;
	GET_ARRAY_LEN(files,len);
	for(;i < len;i++)
	{
		char src_file[MAX_PATH];
		char dst_file[MAX_PATH];
		sprintf(src_file,"%s/%s",g_srcdir,files[i]);
		sprintf(dst_file,"%s/%s",g_dstdir,files[i]);
		ret = decrypt_file(src_file,dst_file);
		if (ret == -1)
			return -1;
		else if (ret == -2)
			continue;
	}
	return 0;
}

int encrypt()
{
	int i = 0;
	int len = 0;
	GET_ARRAY_LEN(files,len);
	for(;i < len;i++)
	{
		char src_file[MAX_PATH];
		char dst_file[MAX_PATH];
		sprintf(src_file,"%s/%s",g_srcdir,files[i]);
		sprintf(dst_file,"%s/%s",g_dstdir,files[i]);
		if (encrypt_file(src_file,dst_file) == -1)
			return -1;
	}
	return 0;
}

int decrypt_file(char* src_file,char* dst_file)
{
  FILE *fp_src = NULL;
  FILE *fp_dst = NULL;
  int row_count = 0;
  char bufs[100][1024];
  char linebuf[102400];
  int report_code_index = -1;
  int inter_code_index = -1;
  fp_src = fopen(src_file,"r");
  fp_dst = fopen(dst_file,"w");
  if(!fp_src) 
  {
    printf("[WARNING] open file %s failed.Skip this file\n", src_file);
    return -2;
  }
  if(!fp_dst)
  {
    printf("[ERROR] open file %s failed\n", dst_file);
    return -1;
  }

  while(1)
  {
    int readed = fscanf(fp_src,"%[^\n]\n",linebuf);
    if(readed < 0) 
    {
      break;
    }
    row_count++;
    if (row_count == 1)
    {
      int col_count = dosplit(linebuf,bufs);
      for (int i = 0;i < col_count;i++)
      {
        if (strcmp(bufs[i],"report_code") == 0 || strcmp(bufs[i],"REPORT_CODE") == 0)
        {
          report_code_index = i;
        }
        if (strcmp(bufs[i],"inter_code") == 0 || strcmp(bufs[i],"INTER_CODE") == 0)
        {
          inter_code_index = i;
        }
      }
      fprintf(fp_dst,"%s\n",linebuf);
    }
    else
    {
		int col_count = dosplit(linebuf,bufs);
		if (inter_code_index >= 0)
		{
      int real_inter_code = hsInterCodeDecrypt(atoi(bufs[inter_code_index]));
			sprintf(bufs[inter_code_index],"%d",real_inter_code);
		}
		else
		{
		}

		if (report_code_index >= 0)
		{
			char real_report_code[1024];
			memset(real_report_code,0,1024);
			hsReportCodeDecrypt(bufs[report_code_index],real_report_code);
			strcpy(bufs[report_code_index],real_report_code);
		}
		else
		{
		}

		for (int i = 0;i < col_count;i++)
		{
			if (i != col_count-1)
			  fprintf(fp_dst,"%s,",bufs[i]);
			else
			  fprintf(fp_dst,"%s\n",bufs[i]);
		}
    }
  }
  fclose(fp_src);
  fclose(fp_dst);
  return 0;
}


int encrypt_file(char* src_file,char* dst_file)
{
  FILE *fp_src = NULL;
  FILE *fp_dst = NULL;
  int row_count = 0;
  char bufs[100][1024];
  char linebuf[102400];
  int report_code_index = -1;
  int inter_code_index = -1;
  fp_src = fopen(src_file,"r");
  fp_dst = fopen(dst_file,"w");
  if(!fp_src) 
  {
    printf("[ERROR] open file %s failed\n", src_file);
    return -1;
  }
  if(!fp_dst)
  {
    printf("[ERROR] open file %s failed\n", dst_file);
    return -1;
  }

  while(1)
  {
    int readed = fscanf(fp_src,"%[^\n]\n",linebuf);
    if(readed < 0) 
    {
      break;
    }
    row_count++;
    if (row_count == 1)
    {
      int col_count = dosplit(linebuf,bufs);
      for (int i = 0;i < col_count;i++)
      {
        if (strcmp(bufs[i],"report_code") == 0)
        {
          report_code_index = i;
        }
        if (strcmp(bufs[i],"inter_code") == 0)
        {
          inter_code_index = i;
        }
      }
      fprintf(fp_dst,"%s\n",linebuf);
    }
    else
    {
		int col_count = dosplit(linebuf,bufs);
		if (inter_code_index >= 0)
		{
			int real_inter_code = hsInterCodeEncrypt(atoi(bufs[inter_code_index]));
			sprintf(bufs[inter_code_index],"%d",real_inter_code);
		}
		else
		{
		}

		if (report_code_index >= 0)
		{
			char real_report_code[1024];
			hsReportCodeEncrypt(bufs[report_code_index],real_report_code);
			strcpy(bufs[report_code_index],real_report_code);
		}
		else
		{
		}

		for (int i = 0;i < col_count;i++)
		{
			if (i != col_count-1)
				fprintf(fp_dst,"%s,",bufs[i]);
			else
				fprintf(fp_dst,"%s\n",bufs[i]);
		}
    }
  }
  fclose(fp_src);
  fclose(fp_dst);
  return 0;
}

int dosplit(char *linebuf,char buf[][1024]) 
{
  int i = 0;
  int j = 0;
  int count = -1;
  while(1) 
  {
    count ++;
    if(linebuf[count] == ',') 
    {
      buf[i][j] = 0;
      i ++;
      j = 0;

    } 
    else if(linebuf[count] == '\n' || linebuf[count] == '\r'  || linebuf[count] == 0) 
    {
      buf[i][j] = 0;
      break;
    } 
    else 
    {
      buf[i][j] = linebuf[count];
      j ++;
    }
  }
  return i + 1;
}

void print_help()
{
  std::cout<<"Usage: dcsv [OPTION] SOURCE_DIR DEST_DIR"<<std::endl
    <<"  -d        decrypt csv files"<<std::endl
    <<"  -e        encrypt csv files"<<std::endl<<std::endl
    <<"This command is used decrypt or encrypt csv files of Ultra Fast Trade System.The default option is [-d]."<<std::endl<<std::endl
    <<"The command will check the [SOURCE_DIR] directory and deal the csv files which are in the contents.After treatment,new csv files will be stored in the [DEST_DIR] directory."<<std::endl;
}

int check_param(int argc,char* argv[])
{
	if (argc == 2)
	{
		if (strcmp(argv[1],"--help")==0)
			return 1;
		else
		{
			std::cout<<"dcsv:unrecognized option `"<<argv[1]<<"'"<<std::endl;	
			return -1;
		}
	}
	else if (argc == 3)
	{
		strcpy(g_srcdir,argv[1]);
		strcpy(g_dstdir,argv[2]);
		return 2;
	}
	else if (argc == 4)
	{
		strcpy(g_srcdir,argv[2]);
		strcpy(g_dstdir,argv[3]);
		if (strcmp(argv[1],"-d") == 0)
		{
			return 2;
		}
		else if (strcmp(argv[1],"-e") == 0)
		{
			return 3;
		}
		else
		{
			std::cout<<"dcsv:unrecognized option `"<<argv[1]<<"'"<<std::endl;	
			return -1;
		}
	}
	else
	{
		std::cout<<"dcsv:unrecognized option。"<<std::endl;	
		return -1;
	}
}


int hsInterCodeEncrypt(int srcInterCode)
{
    int dstInterCode = 0;
  if (srcInterCode <= 0)
  {
    return srcInterCode;
  }

  int  one = srcInterCode % 10; srcInterCode /= 10;  one = (one+2)%10;
  int two = srcInterCode % 10; srcInterCode /= 10;  two = (two+2)%10;
  int three = srcInterCode %10; srcInterCode /= 10; three = (three+2)%10;
  int four = srcInterCode %10; srcInterCode /= 10;  four = (four+2)%10;
  int five = srcInterCode %10; srcInterCode /= 10;  five = (five+2)%10;
  int six = srcInterCode %10; srcInterCode /= 10;   six = (six+2)%10;
  int seven = srcInterCode %10; srcInterCode /= 10; seven = (seven+2)%10;
  int eight = srcInterCode %10; srcInterCode /= 10; eight = (eight+2)%10;

  dstInterCode = srcInterCode*100000000 +
      four*10000000 +
      three*1000000 +
      two*100000 + 
      one*10000 + 
      eight*1000 + 
      seven*100 + 
      six*10 + 
      five; 
  return dstInterCode;
}

int hsInterCodeDecrypt(int srcInterCode)
{
    int dstInterCode = 0;
  if (srcInterCode <= 0)
  {
    return srcInterCode;
  }

  int  one = srcInterCode % 10; srcInterCode /= 10;  one = (one+8)%10;
  int two = srcInterCode % 10; srcInterCode /= 10;  two = (two+8)%10;
  int three = srcInterCode %10; srcInterCode /= 10; three = (three+8)%10;
  int four = srcInterCode %10; srcInterCode /= 10;  four = (four+8)%10;
  int five = srcInterCode %10; srcInterCode /= 10;  five = (five+8)%10;
  int six = srcInterCode %10; srcInterCode /= 10;   six = (six+8)%10;
  int seven = srcInterCode %10; srcInterCode /= 10; seven = (seven+8)%10;
  int eight = srcInterCode %10; srcInterCode /= 10; eight = (eight+8)%10;

    dstInterCode = srcInterCode*100000000 +
        four*10000000 +
        three*1000000 +
        two*100000 + 
        one*10000 + 
        eight*1000 + 
        seven*100 + 
        six*10 + 
        five; 
  return dstInterCode;
}

char* hsReportCodeEncrypt(const char* srcReportCode, char* dstReportCode)
{
  if (NULL == srcReportCode || NULL == dstReportCode)
    return NULL;
  
  char m_asciiTranA[128];
  char m_asciiTranB[128];
  memset(m_asciiTranA, 0, sizeof(m_asciiTranA));
  memset(m_asciiTranB, 0, sizeof(m_asciiTranB));
  int i = 0;
  int len = strlen(src1);
  for (i=0; i<len; ++i)
  {
    m_asciiTranA[(int)src1[i]] = src2[i];
    m_asciiTranB[(int)src2[i]] = src1[i];
  }
  
  i = 0;
  len = strlen(srcReportCode);
  memset(dstReportCode, 0, sizeof(dstReportCode));
  for (i=0; i<len; ++i)
  {
    dstReportCode[i] = m_asciiTranA[(int)srcReportCode[i]];
  }
  return dstReportCode;
}

char* hsReportCodeDecrypt(const char* srcReportCode, char* dstReportCode)
{
  if (NULL == srcReportCode || NULL == dstReportCode)
    return NULL;
  
  char m_asciiTranA[128];
  char m_asciiTranB[128];
  memset(m_asciiTranA, 0, sizeof(m_asciiTranA));
  memset(m_asciiTranB, 0, sizeof(m_asciiTranB));
  int i = 0;
  int len = strlen(src1);
  for (i=0; i<len; ++i)
  {
    m_asciiTranA[(int)src1[i]] = src2[i];
    m_asciiTranB[(int)src2[i]] = src1[i];
  }
  
  i = 0;
  len  = strlen(srcReportCode);
  memset(dstReportCode, 0, sizeof(dstReportCode));
  for (i=0; i<len; ++i)
  {
    dstReportCode[i] = m_asciiTranB[(int)srcReportCode[i]];
  }
  return dstReportCode;
}
