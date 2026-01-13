module;
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <unistd.h>
module fb;
import ioctl;
import error;

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
  addr = mmap(0, finfo.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (addr == MAP_FAILED) throw_errno("Failed to mmap framebuffer");
  if (close(fd) < 0) throw_errno("Failed to close framebuffer device");
}
Framebuffer::~Framebuffer() {
  if (munmap(addr, finfo.smem_len)) throw_errno("Failed to munmap framebuffer");
}
//TODO Its not stored as rgb888 but rgb565
template <int rotation>
  requires(rotation % 90 == 0)
void Framebuffer::set_pixel(Framebuffer::Position pos, Framebuffer::Pixel pix) {
  
  reinterpret_cast<Pixel*>(addr+to_byte_offset<rotation>(pos)) = pix;
}

template <int rotation>
  requires(rotation % 90 == 0)
Framebuffer::Pixel Framebuffer::get_pixel(Framebuffer::Position pos) {
  return addr[to_byte_offset<rotation>(pos)];
}
template <int rotation>
  requires(rotation % 90 == 0)
size_t Framebuffer::to_byte_offset(Framebuffer::Position pos) {
  if (rotation < 0) {
    return to_byte_offset<(-rotation) % 360>(pos);
  } else {
    return to_byte_offset<(rotation) % 360>(pos);
  }
}
template <> size_t Framebuffer::to_byte_offset<0>(Framebuffer::Position pos) {
  return (pos.col + pos.row * vinfo.xres) * vinfo.bits_per_pixel/8;
}
template <> size_t Framebuffer::to_byte_offset<90>(Framebuffer::Position pos) {
  return ((vinfo.xres  - 1 - pos.row) + pos.col * vinfo.xres) * vinfo.bits_per_pixel/8;
}
template <> size_t Framebuffer::to_byte_offset<180>(Framebuffer::Position pos) {
  return ((vinfo.xres - 1 - pos.col) + (vinfo.yres - 1 - pos.row) * vinfo.xres) * vinfo.bits_per_pixel/8;
}
template <> size_t Framebuffer::to_byte_offset<270>(Framebuffer::Position pos) {
  return ((vinfo.yres - 1 - pos.col) * vinfo.xres + (pos.row))*vinfo.bits_per_pixel /8;
}
