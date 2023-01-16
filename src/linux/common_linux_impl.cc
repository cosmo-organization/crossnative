#include <iostream>
#include <common_cross.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <unistd.h>
#include <stdlib.h>

CROSS_NATIVE void something(){
	std::cout<<"Hello World"<<std::endl;
}


namespace helper{
	Window *list(Display* disp,unsigned long *len){
		Atom prop=XInternAtom(disp,"_NET_ACTIVE_WINDOW",False);
		Atom type;
		int form;
		unsigned long remain;
		unsigned char *list;
		XGetWindowProperty(disp,XDefaultRootWindow(disp),prop,0,1025,False,XA_WINDOW,&type,&form,len,&remain,&list);
		
		return (Window*)list;
	}
	
	Window *winlist (Display *disp, unsigned long *len) {
		Atom prop = XInternAtom(disp,"_NET_CLIENT_LIST",False), type;
		int form;
		unsigned long remain;
		unsigned char *list;

		errno = 0;
		if (XGetWindowProperty(disp,XDefaultRootWindow(disp),prop,0,1024,False,XA_WINDOW,
					&type,&form,len,&remain,&list) != Success) {
			perror("winlist() -- GetWinProp");
			return 0;
		}
		
		return (Window*)list;
	}


	char *name(Display* disp,Window window){
		Atom prop=XInternAtom(disp,"WM_NAME",False),type;
		int form;
		unsigned long len;
		unsigned long remain;
		unsigned char* list;
		XGetWindowProperty(disp,window,prop,0,1024,False,AnyPropertyType,&type,&form,&len,&remain,&list);
		
		return (char*)list;
	}
	
	Window* getWindowByTitle(Display* disp,std::string title){
		unsigned long len;
		Window* listOfWindow=winlist(disp,&len);
		for (int i=0;i<len;i++){
			if (title==std::string(name(disp,listOfWindow[i]))){
				return &listOfWindow[i];
			}
		}
		return NULL;
	}
	

	int catcher(Display* disp,XErrorEvent *xe){
		return 0;
	}
}

struct CrossWindowLinuxImpl:public CrossWindow{
	Window window;
};

CROSS_NATIVE std::string get_active_window_title(){
	Display* display=NULL;
	display=XOpenDisplay(NULL);
	XSetErrorHandler(helper::catcher);
	Window *wlist;
	unsigned long len;
	char* wname;
	wlist=(Window*)helper::list(display,&len);
	wname=helper::name(display,wlist[0]);
	free(wlist);
	XCloseDisplay(display);
	return std::string(wname);
}

CROSS_NATIVE CrossWindow* get_window_by_title(std::string title){
	Display* display=NULL;
	display=XOpenDisplay(NULL);
	XSetErrorHandler(helper::catcher);
	Window* window=helper::getWindowByTitle(display,title);
	XCloseDisplay(display);
	if (window==NULL)return NULL;
	CrossWindowLinuxImpl* impl=new CrossWindowLinuxImpl;
	impl->window=window[0];
	return impl;
}