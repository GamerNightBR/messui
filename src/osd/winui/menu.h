//============================================================
//
//  menu.h - NEWUI
//
//============================================================

#ifndef MENU_H
#define MENU_H

///// NOT-NEEDED INCLUDES /////

//#include <commctrl.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <assert.h>
//#include <winuser.h>
//#include <ctype.h>
//#include "png.h"
//#include "opresolv.h"
//#include "osdcore.h"
//#include "windows/video.h"
//#include "windows/input.h"
//#include "pool.h"
//#include "winutil.h"

///// INCLUDES /////

#include <windows.h>
#include <commdlg.h>
#include <tchar.h>
#include "emu.h"
#include "emuopts.h"
#include "ui/ui.h"
#include "messres.h"
#include "strconv.h"
#include "debug/debugcpu.h"
#include "imagedev/cassette.h"
#include "windows/window.h"
#include "winutf8.h"



// These are called from src/osd/windows/windows.c and
//   provide the linkage between newui and the core. 

LRESULT CALLBACK winwindow_video_window_proc_ui(HWND wnd, UINT message, WPARAM wparam, LPARAM lparam);

int win_create_menu(running_machine &machine, HMENU *menus);

#endif /* MENU_H */
