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
  ZAP_DISPLAY_MODE_NORMAL = 0,
  ZAP_DISPLAY_MODE_MAXIMIZED,
  ZAP_DISPLAY_MODE_FULLSCREEN,
  ZAP_DISPLAY_MODE_BORDERLESS_FULLSCREEN
} zap_window_display_mode_t;

typedef bool (*ZapInitCallback)(zap_options_t options);
typedef bool (*ZapDestroyCallback)(void);

typedef void (*ZapWindowCreateCallback)(zap_window_t window, zap_window_options_t options);
typedef void (*ZapWindowRenderCallback)(zap_window_t window, float delta);
typedef bool (*ZapWindowCloseCallback)(zap_window_t window);
typedef void (*ZapWindowDestroyCallback)(zap_window_t window);

typedef struct zap_options_t {
  void* user_data;
  ZapInitCallback on_after_init;
  ZapDestroyCallback on_before_destroy;
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

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

// Internal implementation
#if defined(ZAP_IMPL)
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

  bool inited;
  bool init_displays_loaded;
  ZapDestroyCallback on_before_destroy;
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

  printf("New window rect: (x=%d, y=%d, w=%d, h=%d)\n", rect->x, rect->y, rect->width, rect->height);
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

  printf("Found monitor %d -> x=%d, y=%d, w=%d, h=%d\n", ZAP.next_display_id - 1, entry->rect.x, entry->rect.y, entry->rect.width, entry->rect.height);

  return true;
}
#endif

#endif

#endif // _ZAP_H_
