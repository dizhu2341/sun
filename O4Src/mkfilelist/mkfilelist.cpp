#include "mkfilelist.h"

int main(int argc,char* argv[])
{
	vector<string> vDirList;
	string xmlString;
	int retCode;
	string updateDir;
	string fileListXml;
	
	if (argc == 1)
	{
		cout<<"Without argument DEST_DIR"<<endl
		<<"Try mkfilelist --help for more information"<<endl;
		return -1;
	}
	
	if (strcmp(argv[1],"--help") == 0)
	{
		cout<<"Usage: mkfilelist DEST_DIR"<<endl
		<<"Make XML file about the auto update file list"<<endl;
		return 0;
	}
	else
	{
		updateDir = argv[1];
		int lastPos = updateDir.size()-1;
		if (updateDir[lastPos] == '/')
		{
			updateDir.erase(lastPos);
		}
		fileListXml.append(updateDir).append("/filelist.xml");
	}
    
	vDirList = scanDir(updateDir.c_str());
	vDirList.push_back(updateDir.c_str());
	
	xmlString = genXmlFile(vDirList, updateDir.c_str());
	cout<<xmlString<<endl;
    
	retCode = writeXml(fileListXml.c_str(), xmlString.data());
	if (retCode >= 0)
	{
		cout<<"write xml success: "<<fileListXml<<endl;
	}
	else
	{
		cout<<"write xml error: errorCode="<<retCode<<endl;
	}
    return 0;
}

vector<string> scanDir(const char* dir)
{
	vector <string> vDirList;
	vector <string> vChildDirList;
	DIR* dp;
	struct dirent* entry;
	struct stat statbuf;
	char childDir[500] = {0};
	
	if ((dp = opendir(dir)) == NULL)
	{
		printf("can not open directory: %s\n", dir);
	}
	else
	{
		while ((entry = readdir(dp)) != NULL)
		{
			sprintf(childDir, "%s/%s", dir, entry->d_name);
			stat(childDir, &statbuf);
			if (S_ISDIR(statbuf.st_mode))
			{
				if (strcmp(entry->d_name, ".") == 0 ||
					strcmp(entry->d_name, "..") == 0)
					continue;
				
				vDirList.push_back((string)childDir);
				vChildDirList = scanDir(childDir);
				
				vector<string>::iterator iterChild;
				for (iterChild = vChildDirList.begin(); iterChild != vChildDirList.end(); iterChild++)
				{
					vDirList.push_back(*iterChild);
				}
			}
		}
	}
	
	closedir(dp);
	return vDirList;
}

string genXmlFile(vector<string> vDirList, const char* updateDir)
{
	string xmlString("<?xml  version=\"1.0\" encoding=\"GBK\"?>\n");
	char sysconfigXml[256] = {0};
	char upgradefilesXml[256] = {0};
	char targetStr[512] = {0};
	char targetStr2[512] = {0};
	int i = 1;
	
	xmlString.append("<UPGRADE>\n");
	xmlString.append("<sysconfig>\n");
	vector<string>::iterator iter;
	for (iter = vDirList.begin(), i = 1; iter != vDirList.end(); iter++,i++)
	{
		if (replace((*iter).data(), targetStr, UPDATE_DIR, "./updatedir") == 0)
		{
			sprintf(sysconfigXml, "    <localfilepath dir_id=\"%d\" local_path=\"%s\"/>\n", i, targetStr);
		}
		else
		{
			sprintf(sysconfigXml, "    <localfilepath dir_id=\"%d\" local_path=\"%s\"/>\n", i, (*iter).data());
		}
		
		xmlString.append((string)sysconfigXml);
	}
	xmlString.append("</sysconfig>\n");
	xmlString.append("<upgradefiles>\n");
	for (iter = vDirList.begin(), i = 1; iter != vDirList.end(); iter++,i++)
	{
		if ((replace((*iter).data(), targetStr, updateDir, ".") == 0) && (replace(targetStr, targetStr2, "/", "\\") == 0))		/*lint !e1023*/

		{
			sprintf(upgradefilesXml, "    <fileinfo file_name=\"*\" file_path=\"%s\\\" file_flag=\"\" dir_id=\"%d\"/>\n", targetStr2, i);
		}
		else
		{
			sprintf(upgradefilesXml, "    <fileinfo file_name=\"*\" file_path=\"%s\\\" file_flag=\"\" dir_id=\"%d\"/>\n", (*iter).data(), i);
		}
		xmlString.append((string)upgradefilesXml);
	}
	xmlString.append("</upgradefiles>\n");
	xmlString.append("<deletefiles>\n");
	xmlString.append("</deletefiles>\n");
	xmlString.append("<removedirs>\n");
	xmlString.append("</removedirs>\n");
	xmlString.append("</UPGRADE>\n");
	
	return xmlString;
}

int replace(const char *src, char *dest, const char *old_str, const char *new_str)
{
	const char *s_tmp = NULL;
    char s_str[8192]={0};
    
    if (src == NULL || src[0] == '\0')
	{
		cout<<"src is null"<<endl;
        return -1;
	}
	else
	{
	}
    
    if (dest == NULL)
	{
		cout<<"dest is null"<<endl;
        return -1;
	}
	else
	{
	}

    dest[0] = '\0';
    s_str[0] = '\0';
	while((s_tmp = strstr(src,old_str)) != NULL)
    {
        strncpy(s_str,src,s_tmp-src);
        s_str[s_tmp-src]='\0';
        strcat(dest,s_str);
        strcat(dest,new_str);
        src = s_tmp + strlen(old_str);
    }
    
	strcat(dest, src);
	
    return 0;
}

int writeXml(const char *xmlFile, const char *xmlString)
{
	FILE* fp;
	int retCode = 0;
	fp = fopen(xmlFile, "w+");
    if (fp == NULL)
    {
        printf("can not open file: %s\n", xmlFile);
        retCode = -1;
    }
	else
	{
		retCode = fprintf(fp, "%s", xmlString);
		fclose(fp);
	}
	return retCode;
}
