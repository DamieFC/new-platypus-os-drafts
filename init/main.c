#include <cpu/gdt.h>
#include <cpu/idt.h>
#include <cpu/irq.h>
#include <cpu/isr.h>
#include <kernel/log.h>
#include <kernel/nmi.h>
#include <keyboard/keyboard.h>
#include <pit/pit.h>
#include <system/terminal.h>
#include <system/vtconsole.h>
#include <vga/vga.h>
#include <printm/printm.h>

extern *vtc;
extern void paint_callback(vtconsole_t *vtc, vtcell_t *cell, int x, int y);
extern void cursor_move_callback(vtconsole_t *vtc, vtcursor_t *cur);

void kernel_main() {

  /* Load GDT, IDT, ISR, IRQ and PIT */
  init_gdt();
  printm(0, "[OK] Load GDT\n");
  init_idt();
  printm(0, "[OK] Load IDT\n");
  init_isr();
  printm(0, "[OK] Load ISR\n");
  init_irq();
  printm(0, "[OK] Load IRQ\n");
  nmi_enable();
  printm(0, "[OK] Enable NMI\n");
  init_timer(50);
  printm(0, "[OK] Load PIT\n");

  /* Load Drivers */
  init_keyboard();
  printm(0, "[OK] Load Drivers\n");

  __asm__ volatile("sti");

  info_log("System Loaded\n");

  vtc = vtconsole(VGA_SCREEN_WIDTH, VGA_SCREEN_HEIGHT, paint_callback,
                  cursor_move_callback);

  /* neofetch like result */
  print("\033[1;34mOS: \033[1;37mPlatypusOS x86_32 x86_64 \n");
  print("\033[1;34mKernel: \033[1;37mPlatypus\n");
  print("\033[1;34mVersion: \033[1;37m0.08-dev\n");
  putstr("\n", COLOR_WHT, COLOR_BLK);
  init_terminal();
}
