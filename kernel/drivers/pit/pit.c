#include "pit.h"
#include <cpu/irq.h>
#include <kernel/ports.h>

int kernel_timer_ticks = 0;

void handler_timer() {
  kernel_timer_ticks++;
}

void init_timer(int frequency) {

  install_irq_handler(0, handler_timer);
  int divisor = 1193180 / frequency;

  outp(0x43, 0x36);
  outp(0x40, frequency & 0xFF);
  outp(0x40, frequency >> 8);
}
