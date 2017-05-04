/*
 * FileUtils.h
 *
 *  Created on: 2017年3月31日
 *      Author: heping
 */

#ifndef FILEUTILS_FILEUTILS_H_
#define FILEUTILS_FILEUTILS_H_
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include <dirent.h>
#include <algorithm>
using namespace std;

class FileUtils
{
public:
	FileUtils();
private:

public:
	/*
	 * 获取指定目录下,带有指定前缀的文件夹名称列表
	 */
	vector<string> get_sub_dirs(const string path, const string prefix = "");
	/*
	 * 获取指定目录下指定后缀名的所有文件列表
	 */
	vector<string> get_need_files(const string path, const string suffix = "");
	/*
	 * 获取程序当前工作目录
	 */
	string get_cur_path();
};
#endif /* FILEUTILS_FILEUTILS_H_ */
