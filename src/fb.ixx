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
  Framebuffer();
  ~Framebuffer();;
private:
};
