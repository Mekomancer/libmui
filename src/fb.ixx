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
  void set_pixel(Position pos, Pixel pix);
  Pixel get_pixel(Position pos);
  void print_info();

protected:
  virtual size_t to_byte_offset(Position pos);
  uint8_t *addr;
  fb_fix_screeninfo finfo;
  fb_var_screeninfo vinfo;
};
export template <int rotation> struct RotatedFramebuffer : public Framebuffer {
protected:
  size_t to_byte_offset(Position pos) override;
};
export Framebuffer *open_framebuffer(int rotation = 0);
