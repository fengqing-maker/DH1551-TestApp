/* The following TEXT start address leaves space for the monitor
   workspace. i.e. the NEC VR4300 (IDT) first free address is actually
   0xa001af20. */

ENTRY(_start)
OUTPUT_FORMAT("elf32-tradlittlemips")
SEARCH_DIR(.)
__DYNAMIC  =  0;

/*
 * Allocate the stack to be at the top of memory, since the stack
 * grows down
 */
PROVIDE (__stack = 0);
/* PROVIDE (__global = 0); */

/*
 * Initalize some symbols to be zero so we can reference them in the
 * crt0 without core dumping. These functions are all optional, but
 * we do this so we can have our crt0 always use them if they exist.
 * This is so BSPs work better when using the crt0 installed with gcc.
 * We have to initalize them twice, so we multiple object file
 * formats, as some prepend an underscore.
 */


__RAM_BASE = 0x80880000;
__LOAD_BASE =  __RAM_BASE;
__ROM_BASE = __LOAD_BASE;

__RAM_BASE2 = 0x80000200;

MEMORY
{
  ram (rwx) : ORIGIN = 0x80000000, LENGTH = 32M
  sram (rwx): ORIGIN = 0x80000200, LENGTH = (8K+0x200)
  rom (rx)  : ORIGIN = 0xAFC00000, LENGTH = 512K
}

SECTIONS
{
  __BOOT_ROM_ADDR = (__BOOT_LOADER ? 0xAFC00000 - 512K : __ROM_BASE);
  .boot __LOAD_BASE : AT(__BOOT_ROM_ADDR) {
	   boot.o(.text)
	   __SEE_ROM_START = .;
	   see_bloader3.o
	   __SEE_ROM_END = .;
  }
  
  __STANDBY_RAM_ADDR = __BOOT_LOADER ? (__RAM_BASE + SIZEOF(.boot)) : __RAM_BASE2;
  __STANDBY_ROM_ADDR = __BOOT_ROM_ADDR + SIZEOF(.boot);
  .standby __STANDBY_RAM_ADDR : AT(__STANDBY_ROM_ADDR) {
     libslot.a(.text)      
     libstandby.a(.text)      		
		 __STANDBY_DATA_START = .;
		 libslot.a(.rodata)
     libstandby.a(.rodata)
	 	 *(.bootdata)
	 	 __STANDBY_DATA_END = .;
  }>sram


  __TEXT_RAM_ADDR = __RAM_BASE + SIZEOF(.boot)+SIZEOF(.standby);
  __TEXT_ROM_ADDR = __STANDBY_ROM_ADDR + SIZEOF(.standby);
  .text __TEXT_RAM_ADDR : AT(__TEXT_ROM_ADDR) {
    *(.reuse)
    *(.init)
    *(.text)
    *(.text.*)
    *(.gnu.linkonce.t*)
    *(.mips16.fn.*)
    *(.mips16.call.*)
    PROVIDE (__runtime_reloc_start = .);
    *(.rel.sdata)
    PROVIDE (__runtime_reloc_stop = .);
    *(.fini)
    . = ALIGN(16);
  } >ram

  __RODATA_RAM_ADDR = __TEXT_RAM_ADDR + SIZEOF(.text);
  __RODATA_ROM_ADDR = __TEXT_ROM_ADDR + SIZEOF(.text);
  .rodata __RODATA_RAM_ADDR : AT(__RODATA_ROM_ADDR) {
    *(.rdata)
    *(.rodata)
    *(.rodata.*)
    *(.gnu.linkonce.r*)
    . = ALIGN(4);
  } >ram

  __DATA_RAM_ADDR = __RODATA_RAM_ADDR + SIZEOF(.rodata);
  __DATA_ROM_ADDR = __RODATA_ROM_ADDR + SIZEOF(.rodata);
  .data __DATA_RAM_ADDR : AT(__DATA_ROM_ADDR) {
    *(.eh_frame)
    *(.data)
    *(.data.*)
    *(.gnu.linkonce.d*)
    *(.rel.dyn)
    . = ALIGN(4);
  } >ram

  _gp = . + 0x8000;
  __global = _gp;
  .lit8 : {
    *(.lit8)
  }
  .lit4 : {
    *(.lit4)
  }
  __SDATA_RAM_ADDR = __DATA_RAM_ADDR + SIZEOF(.data);
  __SDATA_ROM_ADDR = __DATA_ROM_ADDR + SIZEOF(.data);
  .sdata __SDATA_RAM_ADDR : AT(__SDATA_ROM_ADDR) {
    *(.sdata)
    *(.sdata.*)
    *(.gnu.linkonce.s*)
    . = ALIGN(4);
  } >ram

  _edata = __SDATA_ROM_ADDR + SIZEOF(.sdata);

  __SBSS_RAM_ADDR = __SDATA_RAM_ADDR + SIZEOF(.sdata);
  .sbss __SBSS_RAM_ADDR : AT(__SBSS_RAM_ADDR) {
    *(.sbss)
    *(.scommon)
  } >ram

  __BSS_RAM_ADDR = __SBSS_RAM_ADDR + SIZEOF(.sbss);
  .bss __BSS_RAM_ADDR : AT(__BSS_RAM_ADDR) {
    *(.bss)
    *(COMMON)
  } >ram

  _end = .;

  .reginfo 0 : { *(.reginfo) }
  .mdebug 0 : { *(.mdebug) }
}
