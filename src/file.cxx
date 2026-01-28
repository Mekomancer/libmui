module;
#include <fcntl.h>
#include <unistd.h>
module mui.fs;
import mui.types;
import mui.error;
import std;
import mui.types;
FileMode::operator int() {
  int ret = 0;
  if (write) {
    ret = 01;
    if (read) {
      ret = 02;
    }
  }
  if (create) ret |= 0100;
  return ret;
};

File File::open(fs::path path, FileMode mode) {
  File ret;
  ret.file_mode = mode;
  ret.fd = ::open(path.c_str(), ret.file_mode);
  if (ret.fd < 0) throw_errno("Failed to open "s + path.c_str());
  return ret;
}
File::~File() { ::close(fd); };
size_t File::read_bytes(uint8_t *buf, size_t cnt) { return read(fd, buf, cnt); }
size_t File::write_bytes(const uint8_t *buf, size_t cnt) {
  return write(fd, buf, cnt);
}
