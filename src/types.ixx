export module types;
import std;
export {
  using std::array;
  using std::span;
  using std::string;
  using std::string_view;
  using std::vector;

  using namespace std::placeholders;
  using namespace std::literals;
  namespace std {
  namespace fs = filesystem;
  };

  using std::int16_t;
  using std::int32_t;
  using std::int64_t;
  using std::int8_t;

  using std::uint16_t;
  using std::uint32_t;
  using std::uint64_t;
  using std::uint8_t;

  using std::size_t;
  using ssize_t = std::ptrdiff_t;

  template <typename T = void, typename E = int>
  using Result = std::expected<T, E>;
  template <typename E = int> using Err = std::unexpected<E>;
};
