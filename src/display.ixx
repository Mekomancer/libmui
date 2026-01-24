export module mui.graphics;
import std;
import mui.types;

export class display {
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
  virtual void set_pixel(Position pos, Pixel pix) = 0;
  void draw_line(Position p1, Position p2, Pixel color);
};
