module;
#include <linux/fb.h>
#include <sys/ioctl.h>
module mui.ioctl;
import mui.types;
muiResult<fb_fix_screeninfo> fbioget_fscreeninfo(int fd) {
  fb_fix_screeninfo ret;
  int err = ioctl(fd, FBIOGET_FSCREENINFO, &ret);
  if (err == -1) return muiErr(err);
  return ret;
}
muiResult<fb_var_screeninfo> fbioget_vscreeninfo(int fd) {
  fb_var_screeninfo ret;
  int err = ioctl(fd, FBIOGET_VSCREENINFO, &ret);
  if (err == -1) return muiErr(err);
  return ret;
}
