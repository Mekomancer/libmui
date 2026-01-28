module;
#include <linux/fb.h>
export module mui.fb;
import mui.types;
import std;
import mui.display;

export class Framebuffer : public Display {
public:
  Framebuffer();
  ~Framebuffer();
  void set_pixel(Position pos, Pixel pix) override;
  void print_info();

protected:
  virtual size_t to_byte_offset(Position pos);
  uint8_t *addr;
  fb_fix_screeninfo finfo;
  fb_var_screeninfo vinfo;
};
export template <int rotation> class RotatedFramebuffer : public Framebuffer {
protected:
  size_t to_byte_offset(Position pos) override;
};
export Framebuffer *open_framebuffer(int rotation = 0);
