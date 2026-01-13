import mui;
import std;

using std::print;
using std::string;

bool test_help_opt();

int main(int argc, char *argv[]) {
  print("Starting tests\n");
  test_help_opt();
  print("Finished tests\n");
  return 0;
}

bool test_help_opt() {
  string name = "libmui";
  string bogus_opt = "--do-a-flip";
  string help_opt = "--help";
  string ver_opt = "-V";
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
