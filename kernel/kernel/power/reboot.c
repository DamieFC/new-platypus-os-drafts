#include <kernel/ports.h>
#include <kernel/power.h>
#include <stddef.h>
#include <system/vtconsole.h>

extern *vtc;

void reboot() {
  vtconsole_delete(vtc);
  uint8_t t = 0x02;
  while (t & 0x02) {
    t = inp(0x64);
  }
  outp(0x64, 0xFE);
  __asm__ volatile("hlt");
}
