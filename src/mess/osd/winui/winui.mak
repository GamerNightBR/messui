###########################################################################
#
#   winui.mak
#
#   MESS Windows-specific makefile
#
###########################################################################

# build the executable names
RCFLAGS += -DMESS

EMU_EXE = $(PREFIX)$(NAME)$(SUFFIX)$(SUFFIX64)$(SUFFIXDEBUG)$(EXE)
BUILD += $(EMU_EXE)

MESS_WINUISRC = $(SRC)/mess/osd/winui
MESS_WINUIOBJ = $(OBJ)/mess/osd/winui
WINUISRC = $(SRC)/osd/winui
WINUIOBJ = $(OBJ)/osd/winui

RESFILE = $(MESS_WINUIOBJ)/messui.res

INCPATH += \
	-I$(MESSSRC)/osd/winui

OBJDIRS += \
	$(MESSOBJ)/osd \
	$(MESSOBJ)/osd/winui


$(MESS_WINUIOBJ)/messui.res:	$(WINUISRC)/mameui.rc $(MESS_WINUISRC)/messui.rc $(WINUISRC)/resource.h $(WINUISRC)/resourcems.h $(WINUIOBJ)/mamevers.rc
	@echo Compiling resources $<...
	$(RC) $(RCDEFS) $(RCFLAGS) --include-dir $(WINUISRC) --include-dir $(MESS_WINUISRC) --include-dir $(WINUIOBJ) -o $@ -i $(MESS_WINUISRC)/messui.rc

$(WINUIOBJ)/mamevers.rc: $(OBJ)/build/verinfo$(EXE) $(SRC)/version.c
	@echo Emitting $@...
	@"$(VERINFO)" -b mess $(SRC)/version.c  > $@

$(LIBOSD): $(OSDOBJS)

$(LIBOCORE): $(OSDCOREOBJS)

$(LIBOCORE_NOMAIN): $(OSDCOREOBJS:$(WINOBJ)/main.o=)

#-------------------------------------------------
# OSD Windows library
#-------------------------------------------------

WINOSDOBJS = \
	$(WINOBJ)/d3d9intf.o \
	$(WINOBJ)/drawd3d.o \
	$(WINOBJ)/drawdd.o \
	$(WINOBJ)/d3dhlsl.o \
	$(WINOBJ)/drawgdi.o \
	$(WINOBJ)/drawnone.o \
	$(WINOBJ)/input.o \
	$(WINOBJ)/output.o \
	$(WINOBJ)/../modules/sound/direct_sound.o \
	$(WINOBJ)/video.o \
	$(WINOBJ)/window.o \
	$(WINOBJ)/../modules/debugger/debugwin.o \
	$(WINOBJ)/winmain.o \
	$(UIOBJ)/menu.o	\

ifndef DONT_USE_NETWORK
WINOSDOBJS += \
	$(WINOBJ)/netdev.o \
	$(WINOBJ)/netdev_pcap.o
endif

$(EMU_EXE): $(VERSIONOBJ) $(EMUINFOOBJ) $(DRIVLISTOBJ) $(DRVLIBS) $(WINOSDOBJS) $(LIBBUS) $(LIBOPTIONAL) $(LIBEMU) $(LIBDASM) $(LIBUTIL) $(EXPAT) $(SOFTFLOAT) $(JPEG_LIB) $(FLAC_LIB) $(7Z_LIB) $(FORMATS_LIB) $(LUA_LIB) $(SQLITE3_LIB) $(WEB_LIB) $(ZLIB) $(LIBOCORE) $(MIDI_LIB) $(RESFILE)
	@echo Linking $@...
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
#ifeq ($(TARGETOS),win32)
#ifdef SYMBOLS
#ifndef MSVC_BUILD
#	$(OBJDUMP) --section=.text --line-numbers --syms --demangle $@ >$(FULLNAME).sym
#endif
#endif
#endif
