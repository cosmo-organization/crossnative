#include <iostream>
#include <common_cross.h>
#include <windows.h>
CROSS_NATIVE void something(){
	std::cout<<"Hello World"<<std::endl;
}

CROSS_NATIVE std::string get_active_window_title(){
	char buff[1024];
	HWND handle=GetForegroundWindow();
	GetWindowText(handle,(LPSTR)&buff,1024);
	return std::string(buff);
}


struct CrossWindowWin32Impl:public CrossWindow{
	HWND window;
};


CROSS_NATIVE CrossWindow* get_window_by_title(std::string title){
	HWND hwnd=NULL;
	hwnd=FindWindow(NULL,title.c_str());
	if (hwnd==NULL)return NULL;
	
	CrossWindowWin32Impl* impl=new CrossWindowWin32Impl;
	impl->window=hwnd;
	return impl;
}