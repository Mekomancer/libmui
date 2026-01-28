export module mui.fs;
import mui.io;
import mui.types;

export struct FileMode {
  bool read = false;
  bool write = false;
  bool execute = false;
  bool create = false;
  bool mkdir = true;
  operator int();
};

export class File : public InOut {
public:
  FileMode file_mode;
  size_t read_bytes(uint8_t *buf, size_t count) override;
  size_t write_bytes(const uint8_t *buf, size_t count) override;
  static File open(fs::path path, FileMode mode);
  ~File();

private:
  int fd;
};
