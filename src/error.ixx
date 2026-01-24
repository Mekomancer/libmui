module;
#include <errno.h>
export module mui.error;
import std;
import mui.types;
// normally i would use string_view but system_error() takes a string&
export [[noreturn]] void throw_errno(const string &what_arg);

module :private;

[[noreturn]] void throw_errno(const string &what) {
  throw std::system_error(errno, std::generic_category(), what);
};
