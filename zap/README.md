# zap
`zap` is a standalone library that allows you to create and maintain a main loop, while creating as many windows as you wish.

Supported Platforms:
- Windows
- (WIP) Linux (X11)
- (Planned) MacOS
- (Planned) FreeBSD

## Getting Started
To use `zap`, add `zap.h` to your include path and specify `#define ZAP_IMPL` somewhere in your project (typically the main entrypoint) to compile it. Make sure to define this in one single file per target to avoid compilation errors.

Depending on your target platform, you will need to include and link additional libraries.

### Windows
Open up a Visual Studio terminal, navigate to the project folder, and compile the source code by specifying the path to zap.h and linking to `user32.lib`

```batch
cl.exe main.c -I"path\to\zap" /link user32.lib
```

### MacOS
On MacOS zap needs to compile Objective-C code, and will rely on Cocoa and OpenGL for interacting with the operating system.

For this you'll have to enable the Objective-C language in your compiler, and link to the `Cocoa` framework.

Here's an example command using `clang`

```bash
$ clang src/main.c -I/path/to/zap -lX11 -framework Cocoa -xobjc -o bin/main
```

### Linux
zap uses X11 so you will need `libX11` to be installed on the machine, and then you'll have to link it.

Here's an example command using `cc`

```bash
$ cc src/main.c -I/path/to/zap -lX11 -o bin/main
```

## User Defines
| Name | Description | Example |
|------|-------------|---------|
| `ZAP_IMPL` | (Required) Allows zap's internal implementation to be compiled. Specify this in **only one** of your source files (typically the main entrypoint) to load the implementation, otherwise you'll get linkage errors. |
| `ZAP_WINDOWS_WNDCLASS_NAME` | (Optional - Windows) The name of the WNDCLASS to create in Windows. Defaults to `zapWndClass` |

## Example
Here's a very simple example that opens a new window at the center of the screen, and associates some user data with it.

> **Note:** See [./example](./example/) for an example with compilation scripts

`main.c`
```c
#define ZAP_IMPL
#include "zap.h"
#undef ZAP_IMPL

#include <stdio.h>

bool on_window_before_close(zap_window_t window) {
  char* user_data = (char*)zap_window_get_user_data(window);
  printf("Window %d is closing. It has user data: %s\n", window, user_data == NULL ? "<NULL>" : user_data);
  return true;
}

bool on_after_init(zap_options_t options) {
  (void)options; // stop the compiler from complaining about the unused variable
  return zap_window_create((zap_window_options_t) {
    .width = 1366,
    .height = 768,
    .centered = true,
    .title = "zap test",
    .user_data = (void*)"my user data",
    .on_before_close = on_window_before_close,
  });
}

int main(int argc, const char** argv) {
  return zap_main(argc, argv, (zap_options_t) {
    .on_after_init = on_after_init,
  });
}
```

## Thanks
This project was inspired by other similar projects such as
- [Sokol](https://github.com/floooh/sokol)
- [SDL](https://github.com/libsdl-org/SDL/)
- [GLFW](https://github.com/glfw/glfw)
