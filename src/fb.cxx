module;
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <unistd.h>
module mui.fb;
import mui.ioctl;
import mui.error;

constexpr auto bitscale(auto val, int cur, int target) -> decltype(val) {
  return (((2 * val * ((1 << target) - 1)) / ((1 << cur) - 1)) + 1) / 2;
}
void Framebuffer::set_pixel(Framebuffer::Position pos, Framebuffer::Pixel pix) {
  *reinterpret_cast<uint16_t *>(addr + to_byte_offset(pos)) =
      bitscale<uint16_t>(pix.red, 8, vinfo.red.length) << vinfo.red.offset |
      bitscale<uint16_t>(pix.grn, 8, vinfo.green.length) << vinfo.green.offset |
      bitscale<uint16_t>(pix.blu, 8, vinfo.blue.length) << vinfo.blue.offset;
};

Framebuffer::Framebuffer() {
  // Opens fbdev and mmaps it
  int fd = open("/dev/fb0", O_RDWR);
  if (fd < 0) throw_errno("Failed to open framebuffer device");
  Result<fb_fix_screeninfo> finfo_res = fbioget_fscreeninfo(fd);
  if (!finfo_res) throw_errno("Failed to get framebuffer's fixed screen info");
  else finfo = *finfo_res;
  Result<fb_var_screeninfo> vinfo_res = fbioget_vscreeninfo(fd);
  if (!vinfo_res) throw_errno("Failed to get framebuffer's var screen info");
  else vinfo = *vinfo_res;
  void *addr_ret =
      mmap(0, finfo.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (addr_ret == MAP_FAILED) throw_errno("Failed to mmap framebuffer");
  addr = reinterpret_cast<uint8_t *>(addr_ret);
  if (close(fd) < 0) throw_errno("Failed to close framebuffer device");
}
Framebuffer::~Framebuffer() {
  if (munmap(addr, finfo.smem_len)) throw_errno("Failed to munmap framebuffer");
}
size_t Framebuffer::to_byte_offset(Framebuffer::Position pos) {
  return (pos.col + pos.row * vinfo.xres) * vinfo.bits_per_pixel / 8;
}
template <>
size_t RotatedFramebuffer<0>::to_byte_offset(RotatedFramebuffer::Position pos) {
  return (pos.col + pos.row * vinfo.xres) * vinfo.bits_per_pixel / 8;
}
template <>
size_t
RotatedFramebuffer<90>::to_byte_offset(RotatedFramebuffer::Position pos) {
  return ((vinfo.xres - 1 - pos.row) + pos.col * vinfo.xres) *
         vinfo.bits_per_pixel / 8;
}
template <>
size_t
RotatedFramebuffer<180>::to_byte_offset(RotatedFramebuffer::Position pos) {
  return ((vinfo.xres - 1 - pos.col) +
          (vinfo.yres - 1 - pos.row) * vinfo.xres) *
         vinfo.bits_per_pixel / 8;
}
template <>
size_t
RotatedFramebuffer<270>::to_byte_offset(RotatedFramebuffer::Position pos) {
  return ((vinfo.yres - 1 - pos.col) * vinfo.xres + (pos.row)) *
         vinfo.bits_per_pixel / 8;
}

void Framebuffer::print_info() {
  using std::print;
  print("{:-^42}\n", "Fixed Info");
  print("id: {:16}\n", finfo.id);
  print("smem_start: {:}\tsmem_len: {:}\n", finfo.smem_start, finfo.smem_len);
  print("type: {:}\ttype_aux: {:}\n", finfo.type, finfo.type_aux);
  print("visual: {:}\n", finfo.visual);
  print("xpanstep: {:}\nypanstep: {:}\tywrapstep: {:}\n", finfo.xpanstep,
        finfo.ypanstep, finfo.ywrapstep);
  print("line_length: {:}\n", finfo.line_length);
  print("mmio_start: {:}\tmmio_len: {:}\n", finfo.mmio_start, finfo.mmio_len);
  print("accel: {:}\n", finfo.accel);
  print("capabilities: {:}\n", finfo.capabilities);
  print("{:-^42}\n", "Variable Info");
  print("xres        : {:}\tyres        : {:}\n", vinfo.xres, vinfo.yres);
  print("xres_virtual: {:}\tyres_virtual: {:}\n", vinfo.xres_virtual,
        vinfo.yres_virtual);
  print("xoffset     : {:}\tyoffset     : {:}\n", vinfo.xoffset, vinfo.yoffset);
  print("bits_per_pixel: {:}\tgrayscale: {:}\n", vinfo.bits_per_pixel,
        vinfo.grayscale);
  print("red::   offset: {:}\tlength: {:}\tmsb_right: {:}\n", vinfo.red.offset,
        vinfo.red.length, vinfo.red.msb_right);
  print("green:: offset: {:}\tlength: {:}\tmsb_right: {:}\n",
        vinfo.green.offset, vinfo.green.length, vinfo.green.msb_right);
  print("blue::  offset: {:}\tlength: {:}\tmsb_right: {:}\n", vinfo.blue.offset,
        vinfo.blue.length, vinfo.blue.msb_right);
  print("nonstd: {:}\tactivate: {:}\n", vinfo.nonstd, vinfo.activate);
  print("height: {:} mm\twidth: {:} mm\n", vinfo.height, vinfo.width);
  print("pixclock: {:} ps\n", vinfo.pixclock);
  print("rotate: {:}\n", vinfo.rotate);
  return;
}

Framebuffer *open_framebuffer(int rotation) {
  if (rotation == 90) return new RotatedFramebuffer<90>;
  else if (rotation == 180) return new RotatedFramebuffer<180>;
  else if (rotation == 270) return new RotatedFramebuffer<270>;
  else return new Framebuffer;
}
