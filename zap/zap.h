#ifndef _ZAP_H_
#define _ZAP_H_

#include <stdbool.h>
#include <stdint.h>

// Platform-specific imports
#if defined(_WIN32) || defined(_WIN64)
  #define _ZAP_WINDOWS
  #include <Windows.h>
#endif

// User and built-in defines
#ifndef ZAP_API
  #define ZAP_API
#endif

#ifndef _ZAP_INTERNAL
  #if defined(__GNUC__) || defined(__clang__)
    #define _ZAP_INTERNAL __attribute__((unused)) static
  #else
    #define _ZAP_INTERNAL static
  #endif
#endif

#if defined(_ZAP_WINDOWS)
  #ifdef ZAP_WINDOWS_WNDCLASS_NAME
    #define _ZAP_WINDOWS_WNDCLASS ZAP_WINDOWS_WNDCLASS_NAME
  #else
    #define _ZAP_WINDOWS_WNDCLASS "zapWndClass"
  #endif
#endif

// Forward Declarations
typedef struct zap_options_t zap_options_t;
typedef struct zap_window_options_t zap_window_options_t;

// API - Typedefs and defines
typedef uint32_t zap_window_t;
typedef uint32_t zap_display_t;

typedef enum zap_window_display_mode_t {
  ZAP_DISPLAY_MODE_NORMAL,
  ZAP_DISPLAY_MODE_MAXIMIZED,
  ZAP_DISPLAY_MODE_FULLSCREEN,
  ZAP_DISPLAY_MODE_BORDERLESS_FULLSCREEN,
  ZAP_DISPLAY_MODE_COUNT,
} zap_window_display_mode_t;

typedef enum zap_event_type_t {
  ZAP_EVENT_KEY_INVALID = 0,
  ZAP_EVENT_KEY_DOWN,
  ZAP_EVENT_KEY_UP,
  ZAP_EVENT_MOUSE_ENTERED,
  ZAP_EVENT_MOUSE_LEFT,
  ZAP_EVENT_MOUSE_MOVED,
  ZAP_EVENT_MOUSE_BUTTON_CLICKED,
  ZAP_EVENT_MOUSE_BUTTON_UP,
  ZAP_EVENT_MOUSE_BUTTON_DOWN,
  ZAP_EVENT_WINDOW_RESIZED,
  ZAP_EVENT_WINDOW_MOVED,
  ZAP_EVENT_WINDOW_FOCUSED,
  ZAP_EVENT_WINDOW_UNFOCUSED,
  ZAP_EVENT_DISPLAY_MODE_CHANGED,
  ZAP_EVENT_FILE_DROP_STARTED,
  ZAP_EVENT_FILE_DROPPED,
  ZAP_EVENT_FILE_DROP_ENDED,
  ZAP_EVENT_TYPE_COUNT,
} zap_event_type_t;

typedef enum zap_keycode_t {
  ZAP_KEYCODE_INVALID          = 0,
  ZAP_KEYCODE_SPACE            = 32,
  ZAP_KEYCODE_APOSTROPHE       = 39,  /* ' */
  ZAP_KEYCODE_COMMA            = 44,  /* , */
  ZAP_KEYCODE_MINUS            = 45,  /* - */
  ZAP_KEYCODE_PERIOD           = 46,  /* . */
  ZAP_KEYCODE_SLASH            = 47,  /* / */
  ZAP_KEYCODE_0                = 48,
  ZAP_KEYCODE_1                = 49,
  ZAP_KEYCODE_2                = 50,
  ZAP_KEYCODE_3                = 51,
  ZAP_KEYCODE_4                = 52,
  ZAP_KEYCODE_5                = 53,
  ZAP_KEYCODE_6                = 54,
  ZAP_KEYCODE_7                = 55,
  ZAP_KEYCODE_8                = 56,
  ZAP_KEYCODE_9                = 57,
  ZAP_KEYCODE_SEMICOLON        = 59,  /* ; */
  ZAP_KEYCODE_EQUAL            = 61,  /* = */
  ZAP_KEYCODE_A                = 65,
  ZAP_KEYCODE_B                = 66,
  ZAP_KEYCODE_C                = 67,
  ZAP_KEYCODE_D                = 68,
  ZAP_KEYCODE_E                = 69,
  ZAP_KEYCODE_F                = 70,
  ZAP_KEYCODE_G                = 71,
  ZAP_KEYCODE_H                = 72,
  ZAP_KEYCODE_I                = 73,
  ZAP_KEYCODE_J                = 74,
  ZAP_KEYCODE_K                = 75,
  ZAP_KEYCODE_L                = 76,
  ZAP_KEYCODE_M                = 77,
  ZAP_KEYCODE_N                = 78,
  ZAP_KEYCODE_O                = 79,
  ZAP_KEYCODE_P                = 80,
  ZAP_KEYCODE_Q                = 81,
  ZAP_KEYCODE_R                = 82,
  ZAP_KEYCODE_S                = 83,
  ZAP_KEYCODE_T                = 84,
  ZAP_KEYCODE_U                = 85,
  ZAP_KEYCODE_V                = 86,
  ZAP_KEYCODE_W                = 87,
  ZAP_KEYCODE_X                = 88,
  ZAP_KEYCODE_Y                = 89,
  ZAP_KEYCODE_Z                = 90,
  ZAP_KEYCODE_LEFT_BRACKET     = 91,  /* [ */
  ZAP_KEYCODE_BACKSLASH        = 92,  /* \ */
  ZAP_KEYCODE_RIGHT_BRACKET    = 93,  /* ] */
  ZAP_KEYCODE_GRAVE_ACCENT     = 96,  /* ` */
  ZAP_KEYCODE_WORLD_1          = 161, /* non-US #1 */
  ZAP_KEYCODE_WORLD_2          = 162, /* non-US #2 */
  ZAP_KEYCODE_ESCAPE           = 256,
  ZAP_KEYCODE_ENTER            = 257,
  ZAP_KEYCODE_TAB              = 258,
  ZAP_KEYCODE_BACKSPACE        = 259,
  ZAP_KEYCODE_INSERT           = 260,
  ZAP_KEYCODE_DELETE           = 261,
  ZAP_KEYCODE_RIGHT            = 262,
  ZAP_KEYCODE_LEFT             = 263,
  ZAP_KEYCODE_DOWN             = 264,
  ZAP_KEYCODE_UP               = 265,
  ZAP_KEYCODE_PAGE_UP          = 266,
  ZAP_KEYCODE_PAGE_DOWN        = 267,
  ZAP_KEYCODE_HOME             = 268,
  ZAP_KEYCODE_END              = 269,
  ZAP_KEYCODE_CAPS_LOCK        = 280,
  ZAP_KEYCODE_SCROLL_LOCK      = 281,
  ZAP_KEYCODE_NUM_LOCK         = 282,
  ZAP_KEYCODE_PRINT_SCREEN     = 283,
  ZAP_KEYCODE_PAUSE            = 284,
  ZAP_KEYCODE_F1               = 290,
  ZAP_KEYCODE_F2               = 291,
  ZAP_KEYCODE_F3               = 292,
  ZAP_KEYCODE_F4               = 293,
  ZAP_KEYCODE_F5               = 294,
  ZAP_KEYCODE_F6               = 295,
  ZAP_KEYCODE_F7               = 296,
  ZAP_KEYCODE_F8               = 297,
  ZAP_KEYCODE_F9               = 298,
  ZAP_KEYCODE_F10              = 299,
  ZAP_KEYCODE_F11              = 300,
  ZAP_KEYCODE_F12              = 301,
  ZAP_KEYCODE_F13              = 302,
  ZAP_KEYCODE_F14              = 303,
  ZAP_KEYCODE_F15              = 304,
  ZAP_KEYCODE_F16              = 305,
  ZAP_KEYCODE_F17              = 306,
  ZAP_KEYCODE_F18              = 307,
  ZAP_KEYCODE_F19              = 308,
  ZAP_KEYCODE_F20              = 309,
  ZAP_KEYCODE_F21              = 310,
  ZAP_KEYCODE_F22              = 311,
  ZAP_KEYCODE_F23              = 312,
  ZAP_KEYCODE_F24              = 313,
  ZAP_KEYCODE_F25              = 314,
  ZAP_KEYCODE_KP_0             = 320,
  ZAP_KEYCODE_KP_1             = 321,
  ZAP_KEYCODE_KP_2             = 322,
  ZAP_KEYCODE_KP_3             = 323,
  ZAP_KEYCODE_KP_4             = 324,
  ZAP_KEYCODE_KP_5             = 325,
  ZAP_KEYCODE_KP_6             = 326,
  ZAP_KEYCODE_KP_7             = 327,
  ZAP_KEYCODE_KP_8             = 328,
  ZAP_KEYCODE_KP_9             = 329,
  ZAP_KEYCODE_KP_DECIMAL       = 330,
  ZAP_KEYCODE_KP_DIVIDE        = 331,
  ZAP_KEYCODE_KP_MULTIPLY      = 332,
  ZAP_KEYCODE_KP_SUBTRACT      = 333,
  ZAP_KEYCODE_KP_ADD           = 334,
  ZAP_KEYCODE_KP_ENTER         = 335,
  ZAP_KEYCODE_KP_EQUAL         = 336,
  ZAP_KEYCODE_LEFT_SHIFT       = 340,
  ZAP_KEYCODE_LEFT_CONTROL     = 341,
  ZAP_KEYCODE_LEFT_ALT         = 342,
  ZAP_KEYCODE_LEFT_SUPER       = 343,
  ZAP_KEYCODE_RIGHT_SHIFT      = 344,
  ZAP_KEYCODE_RIGHT_CONTROL    = 345,
  ZAP_KEYCODE_RIGHT_ALT        = 346,
  ZAP_KEYCODE_RIGHT_SUPER      = 347,
  ZAP_KEYCODE_MENU             = 348,
} zap_keycode_t;

typedef enum zap_keymod_t {
  ZAP_KEYMOD_SHIFT = (1 << 1),
  ZAP_KEYMOD_CTRL  = (1 << 2),
  ZAP_KEYMOD_ALT   = (1 << 3),
  ZAP_KEYMOD_META  = (1 << 4),
} zap_keymod_t;

typedef enum zap_mbutton_t {
  ZAP_MBUTTON_LEFT   = (1 << 1),
  ZAP_MBUTTON_RIGHT  = (1 << 2),
  ZAP_MBUTTON_MIDDLE = (1 << 3),
} zap_mbutton_t;

typedef struct zap_event_t {
  zap_event_type_t type;
  zap_window_t window;
  zap_keycode_t keycode;
  zap_keymod_t keymod;
  bool key_repeat;
  const char* filename;
} zap_event_t;

typedef bool (*ZapInitCallback)(zap_options_t options);
typedef bool (*ZapDestroyCallback)(void);
typedef void (*ZapEventCallback)(zap_event_t event);

typedef void (*ZapWindowCreateCallback)(zap_window_t window, zap_window_options_t options);
typedef void (*ZapWindowRenderCallback)(zap_window_t window, float delta);
typedef bool (*ZapWindowCloseCallback)(zap_window_t window);
typedef void (*ZapWindowDestroyCallback)(zap_window_t window);

typedef struct zap_options_t {
  void* user_data;
  ZapInitCallback on_after_init;
  ZapDestroyCallback on_before_destroy;
  ZapEventCallback on_event;
} zap_options_t;

typedef struct zap_window_options_t {
  int x;
  int y;
  int width;
  int height;
  bool centered;
  zap_window_display_mode_t display_mode;
  char* title;
  void* user_data;
  ZapWindowCreateCallback on_after_create;
  ZapWindowRenderCallback on_render;
  ZapWindowCloseCallback on_before_close;
  ZapWindowDestroyCallback on_before_destroy;
} zap_window_options_t;

// API - Functions
ZAP_API char* zap_get_last_error(void);

ZAP_API int zap_main(int argc, const char** argv, zap_options_t options);
ZAP_API uint64_t zap_get_ticks(void);

ZAP_API bool zap_init(zap_options_t options);
ZAP_API void zap_destroy(void);
ZAP_API void zap_run_loop(void);

ZAP_API void zap_request_exit(void);
ZAP_API void zap_set_user_data(void* user_data);
ZAP_API void* zap_get_user_data(void);

ZAP_API zap_display_t zap_get_primary_display(void);

ZAP_API zap_window_t zap_window_create(zap_window_options_t options);
ZAP_API void zap_window_set_display_mode(zap_window_t window, zap_window_display_mode_t display_mode);
ZAP_API void zap_window_center_on_screen(zap_window_t window);
ZAP_API void zap_window_request_close(zap_window_t window);
ZAP_API zap_display_t zap_window_get_display(zap_window_t window);
ZAP_API void zap_window_get_position(zap_window_t window, int* x, int* y);
ZAP_API void zap_window_get_size(zap_window_t window, int* width, int* height);

ZAP_API void zap_window_set_user_data(zap_window_t window, void* user_data);
ZAP_API void* zap_window_get_user_data(zap_window_t window);

// TODO REMOVE THIS
#define ZAP_IMPL

// Internal implementation
#if defined(ZAP_IMPL)
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#define _ZAP_WINDOWS_FOREACH(x) \
  do { \
    assert(ZAP.inited); \
    for (size_t i = 0; i < ZAP.window_count; ++i) { \
      _zap_window_entry_t* it = &ZAP.windows[i]; \
      x \
    } \
  } while (0)

typedef struct {
  int x;
  int y;
  int width;
  int height;
} zap_recti_t;

typedef struct {
  zap_window_t id;
  zap_recti_t rect;
  zap_recti_t previous_rect;
  bool close_requested;
#if defined(_ZAP_WINDOWS)
  HWND hwnd;
#endif
  ZapWindowCreateCallback on_after_create;
  ZapWindowRenderCallback on_render;
  ZapWindowCloseCallback on_before_close;
  ZapWindowDestroyCallback on_before_destroy;
  void* user_data;
} _zap_window_entry_t;

typedef struct _zap_display_entry_t {
  zap_display_t id;
  zap_recti_t rect;
#if defined(_ZAP_WINDOWS)
  HMONITOR hmonitor;
#endif
} _zap_display_entry_t;

static struct ZAP {
  zap_window_t next_window_id;
  _zap_window_entry_t* windows;
  size_t window_count;

  zap_window_t next_display_id;
  _zap_display_entry_t* displays;
  size_t display_count;

  _zap_display_entry_t* primary_display;

#if defined(_ZAP_WINDOWS)
  HINSTANCE hinstance;
  WNDCLASSEX wndclass;
#endif

  zap_keycode_t keycodes[512];
  bool inited;
  bool init_displays_loaded;
  ZapDestroyCallback on_before_destroy;
  ZapEventCallback on_event;
  void* user_data;
} ZAP;

static char* _zap_last_error;
_ZAP_INTERNAL void _zap_window_destroy(_zap_window_entry_t* window);
_ZAP_INTERNAL void _zap_window_move_to(_zap_window_entry_t* window, int x, int y, int w, int h);
_ZAP_INTERNAL void _zap_window_set_display_mode(_zap_window_entry_t* window, zap_window_display_mode_t display_mode);
_ZAP_INTERNAL void _zap_window_center_on_screen(_zap_window_entry_t* window);
_ZAP_INTERNAL inline _zap_window_entry_t* _zap_findow_find(zap_window_t id);
_ZAP_INTERNAL inline void _zap_window_refresh_size(_zap_window_entry_t* window);
_ZAP_INTERNAL bool _zap_refresh_displays(void);
_ZAP_INTERNAL _zap_display_entry_t* _zap_window_get_display(_zap_window_entry_t* window);

#if defined(_ZAP_WINDOWS)
_ZAP_INTERNAL void _zap_windows_init(void);
LRESULT CALLBACK ZapWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
BOOL CALLBACK ZapMonitorEnumProc(HMONITOR hmonitor, HDC hdcmonitor, LPRECT lprect, LPARAM dwdata);
#endif

ZAP_API int zap_main(int argc, const char** argv, zap_options_t options) {
  (void)argc;
  (void)argv;
  if (!zap_init(options)) {
    return 1;
  }
  zap_run_loop();
  zap_destroy();
  return 0;
}

ZAP_API inline uint64_t zap_get_ticks(void) {
#if defined(_ZAP_WINDOWS)
  return GetTickCount64();
#endif
  return 0;
}

ZAP_API bool zap_init(zap_options_t options) {
  if (ZAP.inited) {
    return false;
  }

  ZAP.next_window_id = 1;
  ZAP.on_before_destroy = options.on_before_destroy;
  ZAP.on_event = options.on_event;
  ZAP.windows = malloc(sizeof(_zap_window_entry_t) * 16);
  memset(ZAP.windows, 0, sizeof(_zap_window_entry_t) * 16);

  ZAP.next_display_id = 1;
  ZAP.displays = malloc(sizeof(_zap_display_entry_t) * 16);
  memset(ZAP.displays, 0, sizeof(_zap_display_entry_t) * 16);

#if defined(_ZAP_WINDOWS)
  HINSTANCE hinstance = GetModuleHandle(NULL);
  if (hinstance == NULL) {
    return false;
  }

  WNDCLASSEX wndclass = {
    .cbSize = sizeof(WNDCLASSEX),
    .lpfnWndProc = ZapWndProc,
    .hInstance = hinstance,
    .lpszClassName = _ZAP_WINDOWS_WNDCLASS,
    .style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC
    // .hIcon = LoadIcon(NULL, IDI_APPLICATION),
    // .hIconSm = LoadIcon(NULL, IDI_APPLICATION),
    // .hCursor = LoadCursor(NULL, IDC_ARROW),
  };

  if (!RegisterClassEx(&wndclass)) {
    return false;
  }

  ZAP.hinstance = hinstance;
  ZAP.wndclass = wndclass;

  _zap_windows_init();
#endif
  ZAP.inited = true;
  if (!_zap_refresh_displays()) {
    return false;
  }

  if (options.on_after_init && !options.on_after_init(options)) {
    ZAP.inited = false;
    return false;
  }

  return true;
}

ZAP_API void zap_destroy(void) {
  if (ZAP.on_before_destroy) {
    ZAP.on_before_destroy();
  }

  if (ZAP.windows != NULL) {
    _ZAP_WINDOWS_FOREACH({
      _zap_window_destroy(it);
    });
    free(ZAP.windows);
    ZAP.window_count = 0;
    ZAP.windows = NULL;
  }

  if (ZAP.windows != NULL) {
    _ZAP_WINDOWS_FOREACH({
      _zap_window_destroy(it);
    });
    free(ZAP.windows);
    ZAP.window_count = 0;
    ZAP.windows = NULL;
  }
}

ZAP_API void zap_run_loop(void) {
  assert(ZAP.inited);

#if defined(_ZAP_WINDOWS)
  MSG msg;
#endif

  while (ZAP.window_count > 0) {
    _zap_window_entry_t* windows_to_close[16];
    size_t num_pending_close = 0;

    _ZAP_WINDOWS_FOREACH({
      if (it->close_requested) {
        windows_to_close[num_pending_close++] = it;
      }
    });

#if defined(_ZAP_LINUX)
    while (XPending(ZAP.xdisplay)) {
      XNextEvent(ZAP.xdisplay, &xevent);

      switch(xevent.type) {
        case ClientMessage: {
          if (xevent.xclient.data.l[0] == ZAP.xwm_delete_window) {
            for (size_t i = 0; i < ZAP.window_count; ++i) {
              ZAPWindow* window = &ZAP.windows[i];
              if (window->xwindow == xevent.xclient.window) {
                ids_to_close[num_pending_close++] = window->id;
              }
            }
          }
        } break;
      }
    }
#elif defined(_ZAP_WINDOWS)
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
#endif

    for (size_t i = 0; i < num_pending_close; ++i) {
      _zap_window_destroy(windows_to_close[i]);
      ZAP.window_count -= 1;
    }
  }
}

ZAP_API void zap_request_exit(void) {
  _ZAP_WINDOWS_FOREACH(it->close_requested = true;);
}

ZAP_API void zap_set_user_data(void* user_data) {
  assert(ZAP.inited);
  ZAP.user_data = user_data;
}

ZAP_API void* zap_get_user_data(void) {
  assert(ZAP.user_data);
  return ZAP.user_data;
}

ZAP_API zap_window_t zap_window_create(zap_window_options_t options) {
  _zap_window_entry_t window = {
    .id = ZAP.next_window_id,
    .rect = {
      .width = options.width,
      .height = options.height,
    },
    .on_after_create = options.on_after_create,
    .on_before_close = options.on_before_close,
    .on_before_destroy = options.on_before_destroy,
    .on_render = options.on_render,
    .user_data = options.user_data,
  };

  char* title = options.title == NULL ? "zap" : options.title;

#if defined(_ZAP_LINUX)
  assert(ZAP.xdisplay != NULL);

  int attr_mask = CWBackPixel | CWEventMask;
  XSetWindowAttributes attrs = {0};
  attrs.background_pixel = 0x00000000;
  attrs.event_mask =
    StructureNotifyMask |
    KeyPressMask |
    KeyReleaseMask |
    ExposureMask;

  Window xwindow = XCreateWindow(
    ZAP.xdisplay,
    ZAP.xroot_window,
    0, 0,
    width, height,
    0, CopyFromParent, CopyFromParent, CopyFromParent,
    attr_mask, &attrs
  );

  XMapWindow(ZAP.xdisplay, xwindow);
  window.xwindow = xwindow;

  XStoreName(ZAP.xdisplay, xwindow, title);
  XSetWMProtocols(ZAP.xdisplay, xwindow, &ZAP.xwm_delete_window, 1);

  XWindowAttributes out_attr = {0};
  XGetWindowAttributes(ZAP.xdisplay, xwindow, &out_attr);

  window.w = out_attr.width;
  window.h = out_attr.height;
  window.x = out_attr.x;
  window.y = out_attr.y;
#elif defined(_ZAP_WINDOWS)
  assert(ZAP.hinstance != NULL);

  HWND hwnd = CreateWindowEx(
    WS_EX_CLIENTEDGE,
    _ZAP_WINDOWS_WNDCLASS,
    title,
    WS_OVERLAPPEDWINDOW,
    0,
    0,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    NULL,
    NULL,
    ZAP.hinstance,
    NULL
  );

  if (hwnd == NULL) {
    return 0;
  }

  SetWindowLongPtrW(hwnd, GWLP_USERDATA, window.id);
  window.hwnd = hwnd;
#endif

  ZAP.windows[ZAP.window_count] = window;
  ZAP.next_window_id += 1;
  ZAP.window_count += 1;

  switch (options.display_mode) {
    case ZAP_DISPLAY_MODE_NORMAL: {
      if (options.centered) {
        _zap_window_center_on_screen(&window);
      } else {
        _zap_window_move_to(&window, options.x, options.y, options.width, options.height);
      }
    } break;

    default: {
      _zap_window_set_display_mode(&window, options.display_mode);
    } break;
  }

#if defined(_ZAP_WINDOWS)
  ShowWindow(hwnd, SW_SHOW);
#endif

  return window.id;
}

ZAP_API void zap_window_set_display_mode(zap_window_t window, zap_window_display_mode_t display_mode) {
  _zap_window_entry_t* win = _zap_findow_find(window);
  if (win != NULL) {
    _zap_window_set_display_mode(win, display_mode);
  }
}


ZAP_API void zap_window_center_on_screen(zap_window_t window) {
  _zap_window_entry_t* win = _zap_findow_find(window);
  if (win != NULL) {
    _zap_window_center_on_screen(win);
  }
}

ZAP_API void zap_window_request_close(zap_window_t window) {
  assert(window != 0);
  _zap_window_entry_t* win = _zap_findow_find(window);

  if (win == NULL || win->close_requested) {
    return;
  }

  if (win->on_before_close && !win->on_before_close(window)) {
    return;
  }

  win->close_requested = true;
}

ZAP_API void zap_window_set_user_data(zap_window_t window, void* user_data) {
  _zap_window_entry_t* win = _zap_findow_find(window);
  if (win != NULL) {
    win->user_data = user_data;
  }
}

ZAP_API void* zap_window_get_user_data(zap_window_t window) {
  _zap_window_entry_t* win = _zap_findow_find(window);
  if (win == NULL) {
    return NULL;
  }
  return win->user_data;
}

// Internal implementation
_ZAP_INTERNAL void _zap_window_move_to(_zap_window_entry_t* window, int x, int y, int w, int h) {
  assert(window != NULL);
#if defined(_ZAP_WINDOWS)
  if (window->hwnd != NULL) {
    MoveWindow(window->hwnd, x, y, w, h, true);

    RECT new_rect = {0};
    if (GetWindowRect(window->hwnd, &new_rect)) {
      window->previous_rect = window->rect;

      zap_recti_t* rect = &window->rect;
      rect->x = new_rect.left;
      rect->y = new_rect.top;
      rect->width = new_rect.right - new_rect.left;
      rect->height = new_rect.bottom - new_rect.top;
    }
  }
#endif
}

_ZAP_INTERNAL void _zap_window_set_display_mode(_zap_window_entry_t* window, zap_window_display_mode_t display_mode) {
  assert(window != NULL);

  _zap_display_entry_t* display = _zap_window_get_display(window);
  assert(display != NULL);

  switch (display_mode) {
    case ZAP_DISPLAY_MODE_FULLSCREEN: {

    } break;

    case ZAP_DISPLAY_MODE_BORDERLESS_FULLSCREEN: {
      window->previous_rect = window->rect;
#if defined(_ZAP_WINDOWS)
      if (window->hwnd != NULL) {
        SetWindowLong(window->hwnd, GWL_STYLE, 0);
        SetWindowPos(window->hwnd, HWND_TOP, display->rect.x, display->rect.y, display->rect.width, display->rect.height, SWP_FRAMECHANGED);
      }
#endif
    } break;

    case ZAP_DISPLAY_MODE_MAXIMIZED: {
      // TODO implement this
    } break;

    case ZAP_DISPLAY_MODE_NORMAL: {
      // TODO implement this
    } break;
  }
}

_ZAP_INTERNAL void _zap_window_destroy(_zap_window_entry_t* window) {
  if (window == NULL) {
    return;
  }

  if (window->on_before_destroy) {
    window->on_before_destroy(window->id);
  }

#if defined(_ZAP_WINDOWS)
  if (window->hwnd != NULL) {
    DestroyWindow(window->hwnd);
  }
#endif
}

_ZAP_INTERNAL void _zap_window_center_on_screen(_zap_window_entry_t *window) {
  assert(window != NULL);
  
  _zap_display_entry_t* display = _zap_window_get_display(window);
  if (display != NULL) {
    int x = (display->rect.width - window->rect.width) / 2;
    int y = (display->rect.height - window->rect.height) / 2;
    _zap_window_move_to(window, x, y, window->rect.width, window->rect.height);
  }
}

_ZAP_INTERNAL inline _zap_window_entry_t* _zap_findow_find(zap_window_t window) {
  _ZAP_WINDOWS_FOREACH({
    if (it->id == window) {
      return it;
    }
  });
  return NULL;
}

_ZAP_INTERNAL inline void _zap_window_refresh_size(_zap_window_entry_t* window) {
  assert(window != NULL);
  zap_recti_t* rect = &window->rect;
#if defined(_ZAP_WINDOWS)
  RECT winrect = {0};
  if (window->hwnd != NULL && GetWindowRect(window->hwnd, &winrect)) {
    rect->x = winrect.left;
    rect->y = winrect.top;
    rect->width = winrect.right - winrect.left;
    rect->height = winrect.bottom - winrect.top;
  }
#endif
}

_ZAP_INTERNAL bool _zap_refresh_displays(void) {
  assert(ZAP.inited);
  assert(ZAP.displays != NULL);

#if defined(_ZAP_WINDOWS)
  if (!EnumDisplayMonitors(NULL, NULL, ZapMonitorEnumProc, 0)) {
    return false;
  }
#endif

  // TODO: find a better way to select the primary display
  if (ZAP.display_count > 0) {
    ZAP.primary_display = &ZAP.displays[0];
  }

  return true;
}

_ZAP_INTERNAL _zap_display_entry_t* _zap_window_get_display(_zap_window_entry_t* window) {
  assert(ZAP.inited);
  assert(window != NULL);

#if defined(_ZAP_WINDOWS)
  assert(window->hwnd);
  HMONITOR hmonitor = MonitorFromWindow(window->hwnd, MONITOR_DEFAULTTOPRIMARY);
  if (hmonitor == NULL) {
    return NULL;
  }

  for (size_t i = 0; i < ZAP.display_count; ++i) {
    _zap_display_entry_t* it = &ZAP.displays[i];
    if (it->hmonitor == hmonitor) {
      return it;
    }
  }
#endif

  return NULL;
}

#if defined(_ZAP_WINDOWS)
_ZAP_INTERNAL void _zap_windows_init(void) {
  ZAP.keycodes[0x00B] = ZAP_KEYCODE_0;
  ZAP.keycodes[0x002] = ZAP_KEYCODE_1;
  ZAP.keycodes[0x003] = ZAP_KEYCODE_2;
  ZAP.keycodes[0x004] = ZAP_KEYCODE_3;
  ZAP.keycodes[0x005] = ZAP_KEYCODE_4;
  ZAP.keycodes[0x006] = ZAP_KEYCODE_5;
  ZAP.keycodes[0x007] = ZAP_KEYCODE_6;
  ZAP.keycodes[0x008] = ZAP_KEYCODE_7;
  ZAP.keycodes[0x009] = ZAP_KEYCODE_8;
  ZAP.keycodes[0x00A] = ZAP_KEYCODE_9;
  ZAP.keycodes[0x01E] = ZAP_KEYCODE_A;
  ZAP.keycodes[0x030] = ZAP_KEYCODE_B;
  ZAP.keycodes[0x02E] = ZAP_KEYCODE_C;
  ZAP.keycodes[0x020] = ZAP_KEYCODE_D;
  ZAP.keycodes[0x012] = ZAP_KEYCODE_E;
  ZAP.keycodes[0x021] = ZAP_KEYCODE_F;
  ZAP.keycodes[0x022] = ZAP_KEYCODE_G;
  ZAP.keycodes[0x023] = ZAP_KEYCODE_H;
  ZAP.keycodes[0x017] = ZAP_KEYCODE_I;
  ZAP.keycodes[0x024] = ZAP_KEYCODE_J;
  ZAP.keycodes[0x025] = ZAP_KEYCODE_K;
  ZAP.keycodes[0x026] = ZAP_KEYCODE_L;
  ZAP.keycodes[0x032] = ZAP_KEYCODE_M;
  ZAP.keycodes[0x031] = ZAP_KEYCODE_N;
  ZAP.keycodes[0x018] = ZAP_KEYCODE_O;
  ZAP.keycodes[0x019] = ZAP_KEYCODE_P;
  ZAP.keycodes[0x010] = ZAP_KEYCODE_Q;
  ZAP.keycodes[0x013] = ZAP_KEYCODE_R;
  ZAP.keycodes[0x01F] = ZAP_KEYCODE_S;
  ZAP.keycodes[0x014] = ZAP_KEYCODE_T;
  ZAP.keycodes[0x016] = ZAP_KEYCODE_U;
  ZAP.keycodes[0x02F] = ZAP_KEYCODE_V;
  ZAP.keycodes[0x011] = ZAP_KEYCODE_W;
  ZAP.keycodes[0x02D] = ZAP_KEYCODE_X;
  ZAP.keycodes[0x015] = ZAP_KEYCODE_Y;
  ZAP.keycodes[0x02C] = ZAP_KEYCODE_Z;
  ZAP.keycodes[0x028] = ZAP_KEYCODE_APOSTROPHE;
  ZAP.keycodes[0x02B] = ZAP_KEYCODE_BACKSLASH;
  ZAP.keycodes[0x033] = ZAP_KEYCODE_COMMA;
  ZAP.keycodes[0x00D] = ZAP_KEYCODE_EQUAL;
  ZAP.keycodes[0x029] = ZAP_KEYCODE_GRAVE_ACCENT;
  ZAP.keycodes[0x01A] = ZAP_KEYCODE_LEFT_BRACKET;
  ZAP.keycodes[0x00C] = ZAP_KEYCODE_MINUS;
  ZAP.keycodes[0x034] = ZAP_KEYCODE_PERIOD;
  ZAP.keycodes[0x01B] = ZAP_KEYCODE_RIGHT_BRACKET;
  ZAP.keycodes[0x027] = ZAP_KEYCODE_SEMICOLON;
  ZAP.keycodes[0x035] = ZAP_KEYCODE_SLASH;
  ZAP.keycodes[0x056] = ZAP_KEYCODE_WORLD_2;
  ZAP.keycodes[0x00E] = ZAP_KEYCODE_BACKSPACE;
  ZAP.keycodes[0x153] = ZAP_KEYCODE_DELETE;
  ZAP.keycodes[0x14F] = ZAP_KEYCODE_END;
  ZAP.keycodes[0x01C] = ZAP_KEYCODE_ENTER;
  ZAP.keycodes[0x001] = ZAP_KEYCODE_ESCAPE;
  ZAP.keycodes[0x147] = ZAP_KEYCODE_HOME;
  ZAP.keycodes[0x152] = ZAP_KEYCODE_INSERT;
  ZAP.keycodes[0x15D] = ZAP_KEYCODE_MENU;
  ZAP.keycodes[0x151] = ZAP_KEYCODE_PAGE_DOWN;
  ZAP.keycodes[0x149] = ZAP_KEYCODE_PAGE_UP;
  ZAP.keycodes[0x045] = ZAP_KEYCODE_PAUSE;
  ZAP.keycodes[0x146] = ZAP_KEYCODE_PAUSE;
  ZAP.keycodes[0x039] = ZAP_KEYCODE_SPACE;
  ZAP.keycodes[0x00F] = ZAP_KEYCODE_TAB;
  ZAP.keycodes[0x03A] = ZAP_KEYCODE_CAPS_LOCK;
  ZAP.keycodes[0x145] = ZAP_KEYCODE_NUM_LOCK;
  ZAP.keycodes[0x046] = ZAP_KEYCODE_SCROLL_LOCK;
  ZAP.keycodes[0x03B] = ZAP_KEYCODE_F1;
  ZAP.keycodes[0x03C] = ZAP_KEYCODE_F2;
  ZAP.keycodes[0x03D] = ZAP_KEYCODE_F3;
  ZAP.keycodes[0x03E] = ZAP_KEYCODE_F4;
  ZAP.keycodes[0x03F] = ZAP_KEYCODE_F5;
  ZAP.keycodes[0x040] = ZAP_KEYCODE_F6;
  ZAP.keycodes[0x041] = ZAP_KEYCODE_F7;
  ZAP.keycodes[0x042] = ZAP_KEYCODE_F8;
  ZAP.keycodes[0x043] = ZAP_KEYCODE_F9;
  ZAP.keycodes[0x044] = ZAP_KEYCODE_F10;
  ZAP.keycodes[0x057] = ZAP_KEYCODE_F11;
  ZAP.keycodes[0x058] = ZAP_KEYCODE_F12;
  ZAP.keycodes[0x064] = ZAP_KEYCODE_F13;
  ZAP.keycodes[0x065] = ZAP_KEYCODE_F14;
  ZAP.keycodes[0x066] = ZAP_KEYCODE_F15;
  ZAP.keycodes[0x067] = ZAP_KEYCODE_F16;
  ZAP.keycodes[0x068] = ZAP_KEYCODE_F17;
  ZAP.keycodes[0x069] = ZAP_KEYCODE_F18;
  ZAP.keycodes[0x06A] = ZAP_KEYCODE_F19;
  ZAP.keycodes[0x06B] = ZAP_KEYCODE_F20;
  ZAP.keycodes[0x06C] = ZAP_KEYCODE_F21;
  ZAP.keycodes[0x06D] = ZAP_KEYCODE_F22;
  ZAP.keycodes[0x06E] = ZAP_KEYCODE_F23;
  ZAP.keycodes[0x076] = ZAP_KEYCODE_F24;
  ZAP.keycodes[0x038] = ZAP_KEYCODE_LEFT_ALT;
  ZAP.keycodes[0x01D] = ZAP_KEYCODE_LEFT_CONTROL;
  ZAP.keycodes[0x02A] = ZAP_KEYCODE_LEFT_SHIFT;
  ZAP.keycodes[0x15B] = ZAP_KEYCODE_LEFT_SUPER;
  ZAP.keycodes[0x137] = ZAP_KEYCODE_PRINT_SCREEN;
  ZAP.keycodes[0x138] = ZAP_KEYCODE_RIGHT_ALT;
  ZAP.keycodes[0x11D] = ZAP_KEYCODE_RIGHT_CONTROL;
  ZAP.keycodes[0x036] = ZAP_KEYCODE_RIGHT_SHIFT;
  ZAP.keycodes[0x136] = ZAP_KEYCODE_RIGHT_SHIFT;
  ZAP.keycodes[0x15C] = ZAP_KEYCODE_RIGHT_SUPER;
  ZAP.keycodes[0x150] = ZAP_KEYCODE_DOWN;
  ZAP.keycodes[0x14B] = ZAP_KEYCODE_LEFT;
  ZAP.keycodes[0x14D] = ZAP_KEYCODE_RIGHT;
  ZAP.keycodes[0x148] = ZAP_KEYCODE_UP;
  ZAP.keycodes[0x052] = ZAP_KEYCODE_KP_0;
  ZAP.keycodes[0x04F] = ZAP_KEYCODE_KP_1;
  ZAP.keycodes[0x050] = ZAP_KEYCODE_KP_2;
  ZAP.keycodes[0x051] = ZAP_KEYCODE_KP_3;
  ZAP.keycodes[0x04B] = ZAP_KEYCODE_KP_4;
  ZAP.keycodes[0x04C] = ZAP_KEYCODE_KP_5;
  ZAP.keycodes[0x04D] = ZAP_KEYCODE_KP_6;
  ZAP.keycodes[0x047] = ZAP_KEYCODE_KP_7;
  ZAP.keycodes[0x048] = ZAP_KEYCODE_KP_8;
  ZAP.keycodes[0x049] = ZAP_KEYCODE_KP_9;
  ZAP.keycodes[0x04E] = ZAP_KEYCODE_KP_ADD;
  ZAP.keycodes[0x053] = ZAP_KEYCODE_KP_DECIMAL;
  ZAP.keycodes[0x135] = ZAP_KEYCODE_KP_DIVIDE;
  ZAP.keycodes[0x11C] = ZAP_KEYCODE_KP_ENTER;
  ZAP.keycodes[0x037] = ZAP_KEYCODE_KP_MULTIPLY;
  ZAP.keycodes[0x04A] = ZAP_KEYCODE_KP_SUBTRACT;
}

_ZAP_INTERNAL zap_keymod_t _zap_windows_get_keymod(void) {
  uint32_t mod = 0;
  static int mask = 1 << 15;
  if (GetKeyState(VK_SHIFT) & mask) {
    mod |= ZAP_KEYMOD_SHIFT;
  }
  if (GetKeyState(VK_CONTROL) & mask) {
    mod |= ZAP_KEYMOD_CTRL;
  }
  if (GetKeyState(VK_MENU) & mask) {
    mod |= ZAP_KEYMOD_ALT;
  }
  if ((GetKeyState(VK_LWIN) | GetKeyState(VK_RWIN)) & mask) {
    mod |= ZAP_KEYMOD_META;
  }
  return (zap_keymod_t)mod;
}

LRESULT CALLBACK ZapWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
  zap_window_t window_id = GetWindowLongPtrW(hwnd, GWLP_USERDATA);

  switch (msg) {
    case WM_CLOSE: {
      zap_window_request_close(window_id);
      return 0;
    } break;

    case WM_SIZE:
    case WM_MOVE: {
      // TODO(performance) - run a timer to run this refresh method
      _zap_window_entry_t* window = _zap_findow_find(window_id);
      if (window != NULL) {
        _zap_window_refresh_size(window);

        ZAP.on_event((zap_event_t) {
          .type = msg == WM_SIZE ? ZAP_EVENT_WINDOW_RESIZED : ZAP_EVENT_WINDOW_MOVED,
          .window = window_id,
        });
      }
    } break;

    case WM_MOUSEMOVE: {

    } break;

    case WM_KEYUP:
    case WM_KEYDOWN: {
      if (ZAP.on_event != NULL) {
        zap_keycode_t keycode = ZAP.keycodes[HIWORD(lparam) & 0x1FF];
        if (keycode) {
          bool is_repeat = msg == WM_KEYDOWN ? (lparam & 0xFF) > 0 : false;

          ZAP.on_event((zap_event_t) {
            .type = msg == WM_KEYUP ? ZAP_EVENT_KEY_UP : ZAP_EVENT_KEY_DOWN,
            .window = window_id,
            .keycode = keycode,
            .keymod = _zap_windows_get_keymod(),
            .key_repeat = is_repeat,
          });
        }
      }
    } break;
  }

  return DefWindowProc(hwnd, msg, wparam, lparam);
}

BOOL CALLBACK ZapMonitorEnumProc(HMONITOR hmonitor, HDC hdcmonitor, LPRECT lprect, LPARAM dwdata) {
  (void)hdcmonitor;
  (void)dwdata;

  _zap_display_entry_t* entry = NULL;

  for (size_t i = 0; i < ZAP.display_count; ++i) {
    _zap_display_entry_t* it = &ZAP.displays[i];
    if (it->hmonitor == hmonitor) {
      entry = it;
      break;
    }
  }

  if (entry == NULL) {
    ZAP.display_count += 1;
    ZAP.displays[ZAP.display_count] = (_zap_display_entry_t) {
      .id = ZAP.next_display_id,
      .hmonitor = hmonitor,
    };
    entry = &ZAP.displays[ZAP.display_count];
    ZAP.display_count += 1;
  }

  if (lprect != NULL) {
    zap_recti_t* rect = &entry->rect;
    rect->x = lprect->left;
    rect->y = lprect->top;
    rect->width = lprect->right - lprect->left;
    rect->height = lprect->bottom - lprect->top;
  }

  return true;
}
#endif

#endif

#endif // _ZAP_H_
