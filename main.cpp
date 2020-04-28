#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xutil.h>
#include <iostream>

int main() {

    Display *d;
    // Window w;
    XEvent e;
    int s;

    d = XOpenDisplay(NULL);
    if (d == NULL) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    s = DefaultScreen(d);
    // w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 100, 100, 1,
    //                         BlackPixel(d, s), WhitePixel(d, s));

    // Window w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 100, 100, 1,
    //                         BlackPixel(d, s), WhitePixel(d, s));

    XVisualInfo vinfo;
    XMatchVisualInfo(d, DefaultScreen(d), 32, TrueColor, &vinfo); // 

    XSetWindowAttributes attr;
    attr.colormap = XCreateColormap(d, DefaultRootWindow(d), vinfo.visual, AllocNone);
    attr.border_pixel = 0;
    attr.background_pixel = 0;// 0x80808080;

    auto scr = ScreenOfDisplay(d, 0);
    auto wdt = WidthOfScreen(scr);
    auto hgh = HeightOfScreen(scr);


    auto w_ = wdt/4;
    auto h_ = hgh/4;

    Window w = XCreateWindow(d, DefaultRootWindow(d),
                             (wdt-w_)/2, (hgh-h_)/2,
                             w_, h_,
                             5, vinfo.depth, InputOutput, vinfo.visual, CWColormap | CWBorderPixel | CWBackPixel, &attr);

    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapWindow(d, w);

    XClassHint ch
        = { "screenshotifinator", "screenshotifinator"};

    
    XSetClassHint(d, w, &ch);

    int code = 0;
    while (1) {
        XNextEvent(d, &e);
        // if (e.type == Expose) {
        // }
        if (e.type == KeyPress) {
            // printf("'%d'\n", e.xkey.keycode);
            if (e.xkey.keycode == 0x41 || e.xkey.keycode == 0x24) {//space and enter
                break;
            } else if (e.xkey.keycode == 9 || e.xkey.keycode == 24) {//escape and q
                code = 1;
                break;
            }
        }
    }

    XCloseDisplay(d);
    return code;
}

