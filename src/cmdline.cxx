module cmdline;

void print_help();
void print_version();

// Check for help and version options. also check argument syntax
int quick_parse_args(int argc, char *argv[]) {
  for (int i = 0; i < argc; ++i) {
    string arg = argv[i];
    if (arg == "--help" || arg == "-h") {
      print_help();
      return 1;
    } else if (arg == "--version" || arg == "-V") {
      print_version();
      return 1;
    }
  }
  return 0;
}

void print_help() {
  print_version();
  std::print("\nOPTIONS:\n");
  std::print("\t-h --help       Print this message\n");
  std::print("\t-V --version    Print version info\n");
}

void print_version() { std::print("{} {}\n", NAME, VERSION); };
