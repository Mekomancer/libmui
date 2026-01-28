export module mui.io;
import mui.types;
export class Input {
public:
  virtual size_t read_bytes(uint8_t *buf, size_t count) = 0;
};
export class Output {
public:
  virtual size_t write_bytes(const uint8_t *buf, size_t count) = 0;
};
export class InOut : public Input, public Output {};
