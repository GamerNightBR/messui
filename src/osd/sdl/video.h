//============================================================
//
//  video.h - SDL implementation of MAME video routines
//
//  Copyright (c) 1996-2014, Nicola Salmoria and the MAME Team.
//  Visit http://mamedev.org for licensing and usage restrictions.
//
//  SDLMAME by Olivier Galibert and R. Belmont
//
//============================================================

#ifndef __SDLVIDEO__
#define __SDLVIDEO__

#include "osdsdl.h"

//============================================================
//  CONSTANTS
//============================================================

#define MAX_VIDEO_WINDOWS           (4)

enum {
	VIDEO_MODE_SOFT = 0,
	VIDEO_MODE_OPENGL,
	VIDEO_MODE_SDL2ACCEL,
	VIDEO_MODE_BGFX
};

#define VIDEO_SCALE_MODE_NONE       (0)

// texture formats
// This used to be an enum, but these are now defines so we can use them as
// preprocessor conditionals
#define SDL_TEXFORMAT_ARGB32            (0) // non-16-bit textures or specials
#define SDL_TEXFORMAT_RGB32             (1)
#define SDL_TEXFORMAT_RGB32_PALETTED    (2)
#define SDL_TEXFORMAT_YUY16             (3)
#define SDL_TEXFORMAT_YUY16_PALETTED    (4)
#define SDL_TEXFORMAT_PALETTE16         (5)
#define SDL_TEXFORMAT_RGB15             (6)
#define SDL_TEXFORMAT_RGB15_PALETTED    (7)
#define SDL_TEXFORMAT_PALETTE16A        (8)
// special texture formats for 16bpp texture destination support, do not use
// to address the tex properties / tex functions arrays!
#define SDL_TEXFORMAT_PALETTE16_ARGB1555    (16)
#define SDL_TEXFORMAT_RGB15_ARGB1555        (17)
#define SDL_TEXFORMAT_RGB15_PALETTED_ARGB1555   (18)

#define GLSL_SHADER_MAX 10

//============================================================
//  TYPE DEFINITIONS
//============================================================

struct sdl_mode
{
	int                 width;
	int                 height;
};

class osd_dim
{
public:
	osd_dim(const int &w, const int &h)
	: m_w(w), m_h(h)
	{
	}
	int width() const { return m_w; }
	int height() const { return m_h; }

	bool operator!=(const osd_dim &other) { return (m_w != other.width()) || (m_h != other.height()); }
	bool operator==(const osd_dim &other) { return (m_w == other.width()) && (m_h == other.height()); }
private:
	int m_w;
	int m_h;
};

class osd_rect
{
public:
	osd_rect(const int x, const int y, const int &w, const int &h)
	: m_x(x), m_y(y), m_d(w,h)
	{
	}
	osd_rect(const int x, const int y, const osd_dim &d)
	: m_x(x), m_y(y), m_d(d)
	{
	}
	int top() const { return m_y; }
	int left() const { return m_x; }
	int width() const { return m_d.width(); }
	int height() const { return m_d.height(); }

	osd_dim dim() const { return m_d; }

	int bottom() const { return m_y + m_d.height(); }
	int right() const { return m_x + m_d.width(); }

	osd_rect move_by(int dx, int dy) const { return osd_rect(m_x + dx, m_y + dy, m_d); }
	osd_rect resize(int w, int h) const { return osd_rect(m_x, m_y, w, h); }

private:
	int m_x;
	int m_y;
	osd_dim m_d;
};

inline osd_rect SDL_Rect_to_osd_rect(const SDL_Rect &r)
{
	return osd_rect(r.x, r.y, r.w, r.h);
}

// FIXME: This is sort of ugly ... and should be a real interface only
class sdl_monitor_info
{
public:

	sdl_monitor_info()
	: m_next(NULL), m_handle(0), m_aspect(0.0f)
		{}
	sdl_monitor_info(const UINT64 handle, const char *monitor_device, float aspect)
	: m_next(NULL), m_handle(handle), m_aspect(aspect)
	{
		strncpy(m_name, monitor_device, ARRAY_LENGTH(m_name) - 1);
		refresh();
	}

	const UINT64 handle() { return m_handle; }
	const osd_rect position_size() { refresh(); return SDL_Rect_to_osd_rect(m_dimensions); }
	const osd_rect usuable_position_size() { refresh(); return SDL_Rect_to_osd_rect(m_dimensions); }

	const char *devicename() { refresh(); return m_name[0] ? m_name : "UNKNOWN"; }

	float aspect();

	void set_aspect(const float a) { m_aspect = a; }

	// STATIC
	static void init();
	static void exit();
	static sdl_monitor_info *pick_monitor(sdl_options &options, int index);
#if !defined(SDLMAME_WIN32) && !(SDLMAME_SDL2)
	static void add_primary_monitor(void *data);
#endif

	sdl_monitor_info    * next() { return m_next; }   // pointer to next monitor in list

	// STATIC
	static sdl_monitor_info *primary_monitor;
	static sdl_monitor_info *list;

	sdl_monitor_info    * m_next;                   // pointer to next monitor in list
private:
	void refresh();

	UINT64              m_handle;                 // handle to the monitor
	SDL_Rect            m_dimensions;
	char                m_name[64];
	float               m_aspect;                 // computed/configured aspect ratio of the physical device
};

struct sdl_video_config
{
	// performance options
	int                 novideo;                // don't draw, for pure CPU benchmarking

	// global configuration
	int                 windowed;               // start windowed?
	int                 prescale;                   // prescale factor
	int                 keepaspect;                 // keep aspect ratio
	int                 numscreens;             // number of screens
	int                 centerh;
	int                 centerv;

	// hardware options
	int                 mode;           // output mode
	int                 waitvsync;      // spin until vsync
	int                 syncrefresh;    // sync only to refresh rate
	int                 switchres;      // switch resolutions

	int                 fullstretch;

	// vector options
	float               beamwidth;      // beam width

	// OpenGL options
	int                 filter;         // enable filtering, disabled if glsl_filter>0
	int                 glsl;
	int                 glsl_filter;        // glsl filtering, >0 disables filter
	char *              glsl_shader_mamebm[GLSL_SHADER_MAX]; // custom glsl shader set, mame bitmap
	int                 glsl_shader_mamebm_num; // custom glsl shader set number, mame bitmap
	char *              glsl_shader_scrn[GLSL_SHADER_MAX]; // custom glsl shader set, screen bitmap
	int                 glsl_shader_scrn_num; // custom glsl shader number, screen bitmap
	int                 pbo;
	int                 vbo;
	int                 allowtexturerect;   // allow GL_ARB_texture_rectangle, default: no
	int                 forcepow2texture;   // force power of two textures, default: no

	// perftest
	int                 perftest;       // print out real video fps

	// X11 options
	int                 restrictonemonitor; // in fullscreen, confine to Xinerama monitor 0

	// YUV options
	int                 scale_mode;
};

//============================================================
//  GLOBAL VARIABLES
//============================================================

extern sdl_video_config video_config;

#endif
