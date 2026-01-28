export module mui.display;
import std;
import mui.types;

export class Display {
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
  void draw_rect(Position p1, Position p2, Pixel color);
  virtual ~Display() = default;
};
