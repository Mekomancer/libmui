module;
#include <linux/fb.h>
export module fb;
import types;
import std;
export struct Framebuffer {
public:
  struct Pixel {
    uint8_t red;
    uint8_t grn;
    uint8_t blu;
  };
  struct Position {
    size_t row;
    size_t col;
  };
  Framebuffer();
  ~Framebuffer();
template <int rotation = 0>
  requires(rotation % 90 == 0)
  void set_pixel(Position, Pixel);
template <int rotation = 0>
  requires(rotation % 90 == 0)
  Pixel get_pixel(Position);

private:
  void *addr;
  template <int rotation>
    requires(rotation % 90 == 0)
  size_t to_byte_offset(Position pos);
  fb_fix_screeninfo finfo;
  fb_var_screeninfo vinfo;
};
