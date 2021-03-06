###########################################################################
#
#   winui.mak
#
#   winui (MESSUI) makefile
#
#   Copyright (c) 1996-2007, Nicola Salmoria and the MAME Team.
#   Visit http://mamedev.org for licensing and usage restrictions.
#
###########################################################################


###########################################################################
#################   BEGIN USER-CONFIGURABLE OPTIONS   #####################
###########################################################################


#-------------------------------------------------
# specify build options; see each option below
# for details
#-------------------------------------------------

# uncomment next line to enable a build using Microsoft tools
# MSVC_BUILD = 1

# uncomment next line to use ICL with MSVC
# USE_ICL = 1

# uncomment next line to enable code analysis using Microsoft tools
# MSVC_ANALYSIS = 1

# uncomment next line to use cygwin compiler
# CYGWIN_BUILD = 1

# set this to the minimum DirectInput version to support (7 or 8)
# DIRECTINPUT = 8

# uncomment next line to use SDL library for sound and video output
# USE_SDL = 1

# uncomment next line to compile OpenGL video renderer
# uncomment next line to compile OpenGL video renderer
USE_OPENGL = 1

# uncomment the next line to build a binary using GL-dispatching.
USE_DISPATCH_GL = 1

# uncomment next line to use QT debugger
# USE_QTDEBUG = 1

# uncomment next line to enable multi-monitor stubs on Windows 95/NT
# you will need to find multimon.h and put it into your include
# path in order to make this work
# WIN95_MULTIMON = 1

# uncomment next line to enable a Unicode build
UNICODE = 1


###########################################################################
##################   END USER-CONFIGURABLE OPTIONS   ######################
###########################################################################

# add a define identifying the target osd
DEFS += -DOSD_WINDOWS


#-------------------------------------------------
# append "ui" to the emulator name
#-------------------------------------------------

EMULATOR = $(PREFIX)$(NAME)ui$(SUFFIX)$(SUFFIX64)$(SUFFIXDEBUG)$(EXE)

#-------------------------------------------------
# object and source roots
#-------------------------------------------------

WINSRC = $(SRC)/osd/windows
WINOBJ = $(OBJ)/osd/windows

OSDSRC = $(SRC)/osd
OSDOBJ = $(OBJ)/osd

OBJDIRS += $(WINOBJ) \
	$(OSDOBJ)/modules/sync \
	$(OSDOBJ)/modules/lib \
	$(OSDOBJ)/modules/midi \
	$(OSDOBJ)/modules/font \
	$(OSDOBJ)/modules/netdev \
	$(OSDOBJ)/modules/render \
	$(OSDOBJ)/modules/render/d3d \
	$(OSDOBJ)/modules/debugger/win

# add ui specific src/objs
UISRC = $(SRC)/osd/$(OSD)
UIOBJ = $(OBJ)/osd/$(OSD)

OBJDIRS += $(UIOBJ)

DEFS += -DWINUI

ifdef USE_QTDEBUG
OBJDIRS += $(OSDOBJ)/modules/debugger/qt
DEFS += -DUSE_QTDEBUG=1
else
DEFS += -DUSE_QTDEBUG=0
endif

ifdef USE_SDL
DEFS += -DSDLMAME_SDL2=0
DEFS += -DUSE_XINPUT=0
DEFS += -DUSE_OPENGL=0
DEFS += -DUSE_SDL=1
else
DEFS += -DUSE_SDL=0
endif

#-------------------------------------------------
# configure the resource compiler
#-------------------------------------------------

RC = @windres --use-temp-file

RCDEFS = -DNDEBUG -D_WIN32_IE=0x0501

# include UISRC directory
RCFLAGS = -O coff -I $(UISRC) -I $(UIOBJ)



#-------------------------------------------------
# overrides for the CYGWIN compiler
#-------------------------------------------------

ifdef CYGWIN_BUILD
CFLAGS	+= -mno-cygwin
LDFLAGS	+= -mno-cygwin
endif



#-------------------------------------------------
# overrides for the MSVC compiler
#-------------------------------------------------

ifdef MSVC_BUILD

VCONV = $(WINOBJ)/vconv$(EXE)

# append a 'v' prefix if nothing specified
ifndef PREFIX
PREFIX = v
endif

# replace the various compilers with vconv.exe prefixes
CC = @$(VCONV) gcc -I.
LD = @$(VCONV) ld /profile
AR = @$(VCONV) ar
RC = @$(VCONV) windres

# make sure we use the multithreaded runtime
ifdef DEBUG
CC += /MTd
else
CC += /MT
endif

# turn on link-time codegen if the MAXOPT flag is also set
ifdef MAXOPT
CC += /GL
LD += /LTCG
endif

ifdef PTR64
CC += /wd4267
endif

# explicitly set the entry point for UNICODE builds
ifdef UNICODE
LD += /ENTRY:wmainCRTStartup
endif

# add some VC++-specific defines
DEFS += -D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE -DXML_STATIC -D__inline__=__inline -Dsnprintf=_snprintf

# make msvcprep into a pre-build step
# OSPREBUILD = $(VCONV)

# add VCONV to the build tools
BUILD += $(VCONV)

$(VCONV): $(WINOBJ)/vconv.o
	@echo Linking $@...
	@link.exe /nologo $^ version.lib /out:$@

$(WINOBJ)/vconv.o: $(WINSRC)/vconv.c
	@echo Compiling $<...
	@cl.exe /nologo /O1 -D_CRT_SECURE_NO_DEPRECATE -c $< /Fo$@

endif



#-------------------------------------------------
# due to quirks of using /bin/sh, we need to
# explicitly specify the current path
#-------------------------------------------------

CURPATH = ./



#-------------------------------------------------
# Windows-specific debug objects and flags
#-------------------------------------------------

# define the x64 ABI to be Windows
DEFS += -DX64_WINDOWS_ABI

# debug build: enable guard pages on all memory allocations
ifdef DEBUG
#DEFS += -DMALLOC_DEBUG
LDFLAGS += -Wl,--allow-multiple-definition
endif

ifdef UNICODE
DEFS += -DUNICODE -D_UNICODE
endif

# ensure we statically link the gcc runtime lib
LDFLAGS += -static-libgcc
TEST_GCC = $(shell gcc --version)
ifeq ($(findstring 4.4,$(TEST_GCC)),)
	#if we use new tools
	LDFLAGS += -static-libstdc++
endif
ifeq ($(findstring 4.7.,$(TEST_GCC)),4.7.)
	CCOMFLAGS += -Wno-narrowing -Wno-attributes
endif

# add unicode flag to emulator linking only
LDFLAGSEMULATOR += -municode

#-------------------------------------------------
# Windows-specific flags and libraries
#-------------------------------------------------

# add our prefix files to the mix, include WINSRC in UI build
CFLAGS += -include $(WINSRC)/winprefix.h

INCPATH += -I$(WINSRC)

ifdef WIN95_MULTIMON
CFLAGS += -DWIN95_MULTIMON
endif


# add the windows libaries, 3 additional libs at the end for UI
BASELIBS += -luser32 -lgdi32 -ldsound -ldxguid -lwinmm -ladvapi32 -lcomctl32 -lshlwapi -lwsock32
LIBS += -luser32 -lgdi32 -ldsound -ldxguid -lwinmm -ladvapi32 -lcomctl32 -lshlwapi -lwsock32 \
	-lddraw -lcomdlg32

ifeq ($(DIRECTINPUT),8)
LIBS += -ldinput8
CFLAGS += -DDIRECTINPUT_VERSION=0x0800
else
LIBS += -ldinput
CFLAGS += -DDIRECTINPUT_VERSION=0x0700
endif

# add -mwindows for UI
LDFLAGSEMULATOR += \
	-mwindows \
	-lkernel32 \
	-lshell32 \
	-lcomdlg32 \


#-------------------------------------------------
# OSD core library
#-------------------------------------------------
# still not sure what to do about main.

OSDCOREOBJS = \
	$(WINOBJ)/strconv.o \
	$(WINOBJ)/windir.o  \
	$(WINOBJ)/winfile.o \
	$(WINOBJ)/winclip.o \
	$(WINOBJ)/winutf8.o \
	$(WINOBJ)/winutil.o \
	$(WINOBJ)/winptty.o \
	$(WINOBJ)/winsocket.o \
	$(OSDOBJ)/modules/lib/osdlib_win32.o \
	$(OSDOBJ)/modules/sync/sync_windows.o \
	$(OSDOBJ)/modules/sync/work_osd.o \
	$(OSDOBJ)/modules/osdmodule.o \

# if malloc debugging is enabled, include the necessary code
ifneq ($(findstring MALLOC_DEBUG,$(DEFS)),)
OSDCOREOBJS += \
	$(WINOBJ)/winalloc.o
endif

$(LIBOCORE): $(OSDCOREOBJS)



#-------------------------------------------------
# OSD Windows library
#-------------------------------------------------

OSDOBJS = \
	$(OSDOBJ)/modules/render/drawd3d.o \
	$(OSDOBJ)/modules/render/d3d/d3d9intf.o \
	$(OSDOBJ)/modules/render/d3d/d3dhlsl.o \
	$(OSDOBJ)/modules/render/drawdd.o \
	$(OSDOBJ)/modules/render/drawgdi.o \
	$(OSDOBJ)/modules/render/drawbgfx.o \
	$(OSDOBJ)/modules/render/drawnone.o \
	$(WINOBJ)/input.o \
	$(WINOBJ)/output.o \
	$(WINOBJ)/video.o \
	$(WINOBJ)/window.o \
	$(OSDOBJ)/modules/midi/portmidi.o \
	$(OSDOBJ)/modules/lib/osdobj_common.o \
	$(OSDOBJ)/modules/midi/portmidi.o \
	$(OSDOBJ)/modules/midi/none.o \
	$(OSDOBJ)/modules/lib/osdobj_common.o \
	$(OSDOBJ)/modules/sound/js_sound.o  \
	$(OSDOBJ)/modules/sound/direct_sound.o  \
	$(OSDOBJ)/modules/sound/sdl_sound.o  \
	$(OSDOBJ)/modules/sound/none.o  \
	$(OSDOBJ)/modules/font/font_sdl.o \
	$(OSDOBJ)/modules/font/font_windows.o \
	$(OSDOBJ)/modules/font/font_osx.o \
	$(OSDOBJ)/modules/font/font_none.o \
	$(OSDOBJ)/modules/debugger/debugwin.o \
	$(OSDOBJ)/modules/debugger/debugint.o \
	$(OSDOBJ)/modules/debugger/debugqt.o \
	$(OSDOBJ)/modules/debugger/none.o \
	$(OSDOBJ)/modules/debugger/win/consolewininfo.o \
	$(OSDOBJ)/modules/debugger/win/debugbaseinfo.o \
	$(OSDOBJ)/modules/debugger/win/debugviewinfo.o \
	$(OSDOBJ)/modules/debugger/win/debugwininfo.o \
	$(OSDOBJ)/modules/debugger/win/disasmbasewininfo.o \
	$(OSDOBJ)/modules/debugger/win/disasmviewinfo.o \
	$(OSDOBJ)/modules/debugger/win/disasmwininfo.o \
	$(OSDOBJ)/modules/debugger/win/editwininfo.o \
	$(OSDOBJ)/modules/debugger/win/logwininfo.o \
	$(OSDOBJ)/modules/debugger/win/memoryviewinfo.o \
	$(OSDOBJ)/modules/debugger/win/memorywininfo.o \
	$(OSDOBJ)/modules/debugger/win/pointswininfo.o \
	$(OSDOBJ)/modules/debugger/win/uimetrics.o \
	$(OSDOBJ)/modules/netdev/pcap.o \
	$(OSDOBJ)/modules/netdev/taptun.o \
	$(OSDOBJ)/modules/netdev/none.o \
	$(UIOBJ)/newui.o \

ifdef USE_OPENGL
OSDOBJS += \
	$(OSDOBJ)/modules/render/drawogl.o \
	$(OSDOBJ)/modules/opengl/gl_shader_tool.o \
	$(OSDOBJ)/modules/opengl/gl_shader_mgr.o

OBJDIRS += \
	$(OSDOBJ)/modules/opengl

DEFS += -DUSE_OPENGL=1

ifdef USE_DISPATCH_GL
DEFS += -DUSE_DISPATCH_GL=1
else
LIBS += -lopengl32
endif

else
DEFS += -DUSE_OPENGL=0
endif

ifdef USE_SDL
DEFS += -DUSE_SDL_SOUND
endif

ifndef DONT_USE_NETWORK
DEFS +=	-DSDLMAME_NET_PCAP
endif

CFLAGS += -DDIRECT3D_VERSION=0x0900

# add UI objs
OSDOBJS += \
	$(WINOBJ)/winmainui.o \
	$(UIOBJ)/mui_util.o \
	$(UIOBJ)/directinput.o \
	$(UIOBJ)/dijoystick.o \
	$(UIOBJ)/directdraw.o \
	$(UIOBJ)/directories.o \
	$(UIOBJ)/mui_audit.o \
	$(UIOBJ)/columnedit.o \
	$(UIOBJ)/screenshot.o \
	$(UIOBJ)/treeview.o \
	$(UIOBJ)/splitters.o \
	$(UIOBJ)/bitmask.o \
	$(UIOBJ)/datamap.o \
	$(UIOBJ)/dxdecode.o \
	$(UIOBJ)/picker.o \
	$(UIOBJ)/properties.o \
	$(UIOBJ)/tabview.o \
	$(UIOBJ)/help.o \
	$(UIOBJ)/history.o \
	$(UIOBJ)/dialogs.o \
	$(UIOBJ)/mui_opts.o \
	$(UIOBJ)/datafile.o \
	$(UIOBJ)/dirwatch.o \
	$(UIOBJ)/winui.o \
	$(UIOBJ)/helpids.o \
	$(UIOBJ)/messui.o \
	$(UIOBJ)/optionsms.o \
	$(UIOBJ)/msuiutil.o \
	$(UIOBJ)/propertiesms.o \
	$(UIOBJ)/swconfig.o \
	$(UIOBJ)/softwarepicker.o \
	$(UIOBJ)/softwarelist.o \
	$(UIOBJ)/devview.o \
	$(UIOBJ)/layoutms.o

# extra dependencies
$(WINOBJ)/drawdd.o :	$(SRC)/emu/rendersw.inc
$(WINOBJ)/drawgdi.o :	$(SRC)/emu/rendersw.inc
BGFX_LIB = $(OBJ)/libbgfx.a
INCPATH += -I$(3RDPARTY)/bgfx/include -I$(3RDPARTY)/bx/include

$(WINOBJ)/winmainui.o : $(WINSRC)/winmain.c
	@echo Compiling $<...
	$(CC) $(CDEFS) -Dmain=utf8_main $(CFLAGS) -c $< -o $@

# add our UI resources
RESFILE += $(UIOBJ)/mameui.res

$(LIBOSD): $(OSDOBJS)

# The : is important! It prevents the dependency above from including mui_main.o in its target!
LIBOSD := $(UIOBJ)/mui_main.o $(LIBOSD)



#-------------------------------------------------
# rule for making the ledutil sample
#
# Don't build for an MSVC_BUILD
#-------------------------------------------------

ledutil$(EXE): $(WINOBJ)/ledutil.o $(LIBOCORE)
	@echo Linking $@...
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@

TOOLS += ledutil$(EXE)



#-------------------------------------------------
# rules for creating helpids.c
#-------------------------------------------------

$(UISRC)/helpids.c : $(UIOBJ)/mkhelp$(EXE) $(UISRC)/resource.h $(UISRC)/resource.hm $(UISRC)/mameui.rc
	@"$(UIOBJ)/mkhelp$(EXE)" $(UISRC)/mameui.rc >$@

# rule to build the generator
$(UIOBJ)/mkhelp$(EXE): $(UIOBJ)/mkhelp.o $(LIBOCORE)
	@echo Linking $@...
	$(LD) $(LDFLAGS) $(OSDBGLDFLAGS) $^ $(LIBS) -o $@



#-------------------------------------------------
# rule for making the verinfo tool
#-------------------------------------------------

#VERINFO = $(UIOBJ)/verinfo$(EXE)

#$(VERINFO): $(UIOBJ)/verinfo.o $(LIBOCORE)
#	@echo Linking $@...
#	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@

#BUILD += $(VERINFO)



#-------------------------------------------------
# Specific rele to compile verinfo util.
#-------------------------------------------------

#$(BUILDOBJ)/verinfo.o : $(BUILDSRC)/verinfo.c
#	@echo Compiling $<...
#	@echo $(CC) -DWINUI $(CDEFS) $(CFLAGS) -c $< -o $@
#	$(CC) -DWINUI $(CDEFS) $(CFLAGS) -c $< -o $@



#-------------------------------------------------
# generic rule for the resource compiler for UI
#-------------------------------------------------

$(RESFILE): $(UISRC)/mameui.rc $(UIOBJ)/mamevers.rc
	@echo Compiling mameui resources $<...
	$(RC) $(RCDEFS) $(RCFLAGS) -o $@ -i $<



#-------------------------------------------------
# rules for resource file
#-------------------------------------------------
ifeq ($(TARGET),mame)
$(UIOBJ)/mamevers.rc: $(SRC)/build/verinfo.py $(SRC)/version.c
	@echo Emitting $@...
	$(PYTHON) $(SRC)/build/verinfo.py -b mame -o $@ $(SRC)/version.c
endif



#####  End winui.mak ##############################################

