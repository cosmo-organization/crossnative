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
