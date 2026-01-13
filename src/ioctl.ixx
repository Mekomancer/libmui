module;
#include <linux/fb.h>
export module ioctl;

/// fd to /dev/fb0
fb_fix_screeninfo fbioget_fscreeninfo(int fd);
fb_var_screeninfo fbioget_vscreeninfo(int fd);
