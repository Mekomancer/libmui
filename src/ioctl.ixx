module;
#include <linux/fb.h>
export module mui.ioctl;
import mui.types;
export {
  /// fd to /dev/fb0
  muiResult<fb_fix_screeninfo> fbioget_fscreeninfo(int fd);
  muiResult<fb_var_screeninfo> fbioget_vscreeninfo(int fd);
};
