#define ZAP_IMPL
#include "../zap.h"
#undef ZAP_IMPL

#include <stdio.h>
#include <stdbool.h>

bool on_window_before_close(zap_window_t window) {
  char* user_data = (char*)zap_window_get_user_data(window);
  printf("Window %d is closing. It has user data: %s\n", window, user_data == NULL ? "<NULL>" : user_data);
  return true;
}

void on_event(zap_event_t event) {
  if (event.type == ZAP_EVENT_KEY_DOWN &&
      event.keycode == ZAP_KEYCODE_W &&
      event.keymod == ZAP_KEYMOD_CTRL
  ) {
    printf("Got Ctrl+W, closing window %d\n", event.window);
    zap_window_request_close(event.window);
  }
}

bool on_after_init(zap_options_t options) {
  (void)options; // stop the compiler from complaining about the unused variable
  return zap_window_create((zap_window_options_t) {
    .width = 1366,
    .height = 768,
    .position = ZAP_WINDOW_POSITION_CENTERED,
    .title = "zap example - hit Ctrl+W to close",
    .user_data = (void*)"my user data",
    .on_before_close = on_window_before_close,
  });
}

int main(int argc, const char** argv) {
  return zap_main(argc, argv, (zap_options_t) {
    .on_after_init = on_after_init,
    .on_event = on_event,
  });
}
