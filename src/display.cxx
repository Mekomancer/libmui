module mui.display;

void Display::draw_line(Position p1, Position p2, Display::Pixel color) {}
void Display::draw_rect(Position p1, Position p2, Display::Pixel color) {
  for (size_t r = p1.row; r <= p2.row; ++r) {
    for (size_t c = p1.col; c <= p2.col; ++c) {
      set_pixel({r, c}, color);
    }
  }
}
