
#include <iostream>
#include <common_cross.h>

int main(const int argc,const char** argv){
	something();
	std::cout<<get_active_window_title()<<std::endl;
	CrossWindow* window=get_window_by_title("hacker - fuzzytest");
	
	std::cout<<(window==NULL)<<std::endl;
	return 0;
}