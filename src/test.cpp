import mui;
import std;

using std::print;
using std::size_t;
using std::string;
using std::uint8_t;

bool test_help_opt();
bool test_framebuffer();

int main(int argc, char *argv[]) {
  print("Starting tests\n");
  test_help_opt();
  test_framebuffer();
  print("Finished tests\n");
  return 0;
}
bool test_framebuffer() {
  print("Testing framebuffer\n");
  Display *fb = open_framebuffer(270);
  for (uint8_t row = 0; row < 255; ++row) {
    for (uint8_t col = 0; col < 255; ++col) {
      fb->set_pixel({row, col}, {0, row, col});
    }
  }
  fb->draw_rect({0, 0}, {319, 479}, {0, 0, 0});
  fb->draw_rect({319, 479}, {0, 0}, {255, 255, 255});
  delete fb;
  print("Finished testing framebuffer\n");
  return true;
};
bool test_help_opt() {
  string name = "libmui";
  string bogus_opt = "--do-a-flip";
  string help_opt = "--help";
  string ver_opt = "--version";
  print("Testing help and version options\n");
  char *opts1[] = {name.data(), bogus_opt.data(), ver_opt.data(),
                   help_opt.data()};
  print("args = {} {} {} {}\n", name, bogus_opt, ver_opt, help_opt);
  quick_parse_args(4, opts1);
  char *opts2[] = {name.data(), bogus_opt.data(), help_opt.data()};
  print("args = {} {} {}\n", name, bogus_opt, help_opt);
  quick_parse_args(3, opts2);
  return true;
}
