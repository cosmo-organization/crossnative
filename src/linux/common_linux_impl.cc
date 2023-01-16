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

	char *name(Display* disp,Window window){
		Atom prop=XInternAtom(disp,"WM_NAME",False),type;
		int form;
		unsigned long len;
		unsigned long remain;
		unsigned char* list;
		XGetWindowProperty(disp,window,prop,0,1024,False,AnyPropertyType,&type,&form,&len,&remain,&list);
		
		return (char*)list;
	}

	int catcher(Display* disp,XErrorEvent *xe){
		return 0;
	}
}


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