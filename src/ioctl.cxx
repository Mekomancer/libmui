module;
#include <linux/fb.h>
#include <sys/ioctl.h>
module mui.ioctl;
import mui.types;
Result<fb_fix_screeninfo> fbioget_fscreeninfo(int fd) {
  fb_fix_screeninfo ret;
  int err = ioctl(fd, FBIOGET_FSCREENINFO, &ret);
  if (err == -1) return Err(err);
  return ret;
}
Result<fb_var_screeninfo> fbioget_vscreeninfo(int fd) {
  fb_var_screeninfo ret;
  int err = ioctl(fd, FBIOGET_VSCREENINFO, &ret);
  if (err == -1) return Err(err);
  return ret;
}
