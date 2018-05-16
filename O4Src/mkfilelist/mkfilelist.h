#ifndef MAKE_FILELIST_H_
#define MAKE_FILELIST_H_

#define UPDATE_DIR "../../workspace/updatedir"
#define FILELIST_XML "../../workspace/updatedir/filelist.xml"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <vector>
#include <iostream>
using namespace std;

vector<string> scanDir(const char* dir);
string genXmlFile(vector<string> vDirList, const char* updateDir);
int replace(const char *src, char *dest, const char *old_str, const char *new_str);
int writeXml(const char *xmlFile, const char *xmlString);

#endif