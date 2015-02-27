// license:BSD-3-Clause
// copyright-holders:Aaron Giles
//============================================================
//
//  video.h - Win32 implementation of MAME video routines
//
//============================================================

#ifndef __WIN_VIDEO__
#define __WIN_VIDEO__

#include "render.h"
//#include "modules/osdwindow.h"

//============================================================
//  CONSTANTS
//============================================================

#define MAX_WINDOWS         4

enum {
	VIDEO_MODE_NONE,
	VIDEO_MODE_GDI,
	VIDEO_MODE_DDRAW,
	VIDEO_MODE_D3D,
	VIDEO_MODE_BGFX,
#if (USE_OPENGL)
	VIDEO_MODE_OPENGL,
#endif
};

#define GLSL_SHADER_MAX 10

//============================================================
//  TYPE DEFINITIONS
//============================================================

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

inline osd_rect RECT_to_osd_rect(const RECT &r)
{
	return osd_rect(r.left, r.top, r.right - r.left, r.bottom - r.top);
}

class win_monitor_info
{
public:
	win_monitor_info();
	virtual ~win_monitor_info();

	void refresh();

	const HMONITOR handle() { return m_handle; }
	// position_size is used only by draw_dd renderer
	const osd_rect position_size() { refresh(); return RECT_to_osd_rect(m_info.rcMonitor); }
	const osd_rect usuable_position_size() { refresh(); return RECT_to_osd_rect(m_info.rcWork); }
	bool is_primary() { return (m_info.dwFlags & MONITORINFOF_PRIMARY) != 0; }
	const char *devicename() { refresh(); return (m_name != NULL) ? m_name : "UNKNOWN"; }

	float aspect();

	void set_aspect(const float a) { m_aspect = a; }

	win_monitor_info  * m_next;                   // pointer to next monitor in list

	// static

	static BOOL CALLBACK monitor_enum_callback(HMONITOR handle, HDC dc, LPRECT rect, LPARAM data);

private:
	HMONITOR            m_handle;                 // handle to the monitor
	MONITORINFOEX       m_info;                   // most recently retrieved info

	float               m_aspect;               // computed/configured aspect ratio of the physical device
	char *              m_name;
};

struct win_video_config
{
	// global configuration
	int                 windowed;                   // start windowed?
	int                 prescale;                   // prescale factor
	int                 keepaspect;                 // keep aspect ratio
	int                 numscreens;                 // number of screens
	render_layer_config layerconfig;                // default configuration of layers

	// per-window configuration
	//osd_window_config   window[MAX_WINDOWS];        // configuration data per-window

	// hardware options
	int                 mode;                       // output mode
	int                 waitvsync;                  // spin until vsync
	int                 syncrefresh;                // sync only to refresh rate
	int                 triplebuf;                  // triple buffer
	int                 switchres;                  // switch resolutions

	// ddraw options
	int                 hwstretch;                  // stretch using the hardware

	// d3d options
	int                 filter;                     // enable filtering

	// OpenGL options
	//int                 filter;         // enable filtering, disabled if glsl_filter>0
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
};



//============================================================
//  GLOBAL VARIABLES
//============================================================

extern win_video_config video_config;


//============================================================
//  PROTOTYPES
//============================================================

win_monitor_info *winvideo_monitor_from_handle(HMONITOR monitor);

#endif
