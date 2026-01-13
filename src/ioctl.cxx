module;
#include <linux/fb.h>
#include <sys/ioctl.h>
module ioctl;

fb_fix_screeninfo fbioget_fscreeninfo(int fd) {
  fb_fix_screeninfo ret;
  ioctl(fd, FBIOGET_FSCREENINFO, &ret);
  return ret;
}
fb_var_screeninfo fbioget_vscreeninfo(int fd) {
  fb_var_screeninfo ret;
  ioctl(fd, FBIOGET_VSCREENINFO, &ret);
  return ret;
} 
