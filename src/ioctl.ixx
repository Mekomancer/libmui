module;
#include <linux/fb.h>
export module ioctl;
import types;
export {
  /// fd to /dev/fb0
  Result<fb_fix_screeninfo> fbioget_fscreeninfo(int fd);
  Result<fb_var_screeninfo> fbioget_vscreeninfo(int fd);
};
