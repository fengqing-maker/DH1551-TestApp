#include <sys_config.h>
#include <sys_parameters.h>
#include <api/libc/printf.h>
#include <api/libchunk/chunk.h>

#ifdef SUPPORT_MULTI_SECTION

#define SECTION_INFO_ADDR 0xbfc10080
#define BUFFER_AREA     0x80180000

#define SECNAMESIZE 12
struct INFO_OVERLAY
{
    unsigned long index;
    unsigned char secname[SECNAMESIZE];
    unsigned long vma;
    unsigned long lma;
    unsigned long ori_size;
    unsigned long size;
}__attribute__ ((packed));

struct INFO_INIT
{
    unsigned long index;
    unsigned char secname[SECNAMESIZE];
    unsigned long vma;
    unsigned long lma;
    unsigned long ori_size;
    unsigned long size;

}__attribute__ ((packed));

struct INFO_FLASH
{
    unsigned long index;
    unsigned char secname[SECNAMESIZE];
    unsigned long vma;
    unsigned long lma;
    unsigned long size;

}__attribute__ ((packed));

unsigned char *expand(unsigned char *maincode, int unzip( \
      unsigned char *, unsigned char *, unsigned char *))
{
    unsigned char *entry = NULL;
    unsigned char *codestart = NULL;
    unsigned long overlay_sec_num = 0;
    unsigned long flash_sec_num = 0;
    unsigned long init_sec_num = 0;
    unsigned long i = 0;
    unsigned long offset = 0;
    unsigned long maincode_offset = 0;
    unsigned int ret = 0;

    if (NULL == maincode)
    {
        return 0;
    }

    codestart = (unsigned char *)sto_fetch_long(maincode + \
          CHUNK_CODESTART);
    entry = (unsigned char *)sto_fetch_long(maincode + CHUNK_ENTRY);
    if (codestart == 0 || codestart == (unsigned char *)0xFFFFFFFF)
        codestart = (unsigned char *)0x80000200;
    if (entry == 0 || entry == (unsigned char *)0xFFFFFFFF)
        entry = codestart;

    init_sec_num = *(unsigned long *)(SYS_FLASH_BASE_ADDR+maincode + CHUNK_HEADER_SIZE);
    overlay_sec_num = *(unsigned long *)(SYS_FLASH_BASE_ADDR+maincode + CHUNK_HEADER_SIZE + 4);
    flash_sec_num = *(unsigned long *)(SYS_FLASH_BASE_ADDR+maincode + CHUNK_HEADER_SIZE + 8);

    maincode_offset =  12 + init_sec_num*sizeof(struct INFO_INIT) + \
                      overlay_sec_num*sizeof(struct INFO_OVERLAY) + \
                      flash_sec_num*sizeof(struct INFO_FLASH);

    for(i = 0, offset = CHUNK_HEADER_SIZE + 12; i < init_sec_num; i++, offset +=  sizeof(struct INFO_INIT))
    {

        ret = unzip((unsigned char *)((struct INFO_INIT *)(SYS_FLASH_BASE_ADDR+maincode + offset))->lma, \
                 (unsigned char *)((struct INFO_INIT *)(SYS_FLASH_BASE_ADDR+maincode + offset))->vma, \
                     (unsigned char *)BUFFER_AREA) ;
        if (ret != 0)
        {
            return 0;
        }
    };

   // soc_printf("init_sec_num = %x overlay_sec_num = %x flash_sec_num = %x maincode_offset = %x\n",
    // init_sec_num,overlay_sec_num,flash_sec_num,maincode_offset);
   // soc_printf("maincode_offset = %x\n",maincode + CHUNK_HEADER_SIZE + maincode_offset);

    if (un7zip(SYS_FLASH_BASE_ADDR+maincode + CHUNK_HEADER_SIZE + maincode_offset, codestart, \
          (unsigned char *)BUFFER_AREA) != 0)
    {
        ERRMSG("Boot loader: Decompress error! Enter shell.\n");
        entry = 0;
    }

    return entry;
}



static unsigned char *expand_overlay_section(int index)
{
    unsigned char *section_info_addr = (unsigned char *)SECTION_INFO_ADDR;
    unsigned long overlay_sec_num = 0;
    unsigned long flash_sec_num = 0;
    unsigned long init_sec_num = 0;
    unsigned long i = 0;
    unsigned long overlay_offset = 0;
    unsigned int ret = 0s;

    init_sec_num = *(unsigned long *)(section_info_addr);
    overlay_sec_num = *(unsigned long *)(section_info_addr + 4);
    flash_sec_num = *(unsigned long *)(section_info_addr + 8);

    overlay_offset = 12 + init_sec_num*sizeof(struct INFO_INIT) + index*sizeof(struct INFO_OVERLAY);
//    for(i = 0, offset = overlay_offset; i < overlay_sec_num; i++, offset +=  sizeof(struct INFO_OVERLAY))
//    {
    ret = un7zip((0xa0000000|((struct INFO_OVERLAY *)(section_info_addr + overlay_offset))->lma), \
                  ((struct INFO_OVERLAY *)(section_info_addr + overlay_offset))->vma, \
                       (unsigned char *)BUFFER_AREA);
    if (ret != 0)
    {
        // asm(".half 0xe801;");
        return 0;
    }
    //};
    // asm(".half 0xe801;");
    return ((struct INFO_OVERLAY *)(section_info_addr + overlay_offset));
}

#endif
