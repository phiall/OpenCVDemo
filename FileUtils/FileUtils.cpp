/*
 * FileUtils.cpp
 *
 *  Created on: 2017年3月31日
 *      Author: heping
 */
#include "FileUtils.h"

FileUtils::FileUtils()
{

}
/*
 * 获取指定目录下,带有指定前缀的文件夹名称列表
  */
vector<string> FileUtils::get_sub_dirs(const string path, const string prefix)
{
		vector<string> ret;
		DIR *dir;
		struct dirent *ptr;
		if( (dir = opendir(path.c_str())) == NULL ) {
			cerr << "get_sub_dirs open dir fail" << endl;
			exit(-1);
		}
		while((ptr = readdir(dir)) != NULL) {
			if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0) {
				continue;
			}
			if(DT_DIR == ptr->d_type) {
				string tmp(ptr->d_name);
				if(tmp.find(prefix) == 0) {
					ret.push_back(path + "/" + ptr->d_name);
					//cout <<  ptr->d_name << endl;
				}
			}
		}
		closedir(dir);
		sort(ret.begin(), ret.end());
		return ret;
}
/*
 * 获取指定目录下指定后缀名的所有文件列表
 */
vector<string> FileUtils::get_need_files(const string path, const string suffix)
{
	vector<string>  ret;
	DIR *dir;
	struct dirent *ptr;
	if( (dir = opendir(path.c_str())) == NULL ) {
		cerr << "get_need_files open dir fail" << endl;
		exit(-1);
	}
	while((ptr = readdir(dir)) != NULL) {
		if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0) {
			continue;
		}
		if(DT_REG == ptr->d_type) {
			string tmp = ptr->d_name;
			int pos = (tmp).find_last_of('.');
			if(pos ==  -1) {
				continue;
			}
			string suffix = tmp.substr(pos + 1);
			//cout << suffix << endl;
			if(suffix == suffix) {
				ret.push_back(ptr->d_name);
				//cout <<  ptr->d_name << endl;
			}
		}
	}
	closedir(dir);
	return ret;
}
/*
 * 获取程序当前工作目录
 */
string FileUtils::get_cur_path()
{
		char pwd_path[256];
		if( !getcwd(pwd_path, 256) )
		{
			cerr << "get cureent path fail" << endl;
			return NULL;
		}
		return pwd_path;
}



