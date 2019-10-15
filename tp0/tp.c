/* GPLv2 (c) Airbus */
#include <debug.h>
#include <info.h>

extern info_t   *info;
extern uint32_t __kernel_start__;
extern uint32_t __kernel_end__;

void tp() {
   debug("kernel mem [0x%x - 0x%x]\n", &__kernel_start__, &__kernel_end__);
   debug("MBI flags 0x%x\n", info->mbi->flags);

   multiboot_uint32_t start;
   multiboot_uint32_t end;

   start = info->mbi->mmap_addr;
   end = start + info->mbi->mmap_length;

   int * test = (int *) 0xFF5600;
   *test = 20;
   debug("TEST %p\n", test);
   while(start < end){
   		multiboot_memory_map_t *entry = (multiboot_memory_map_t*) start;
   		debug("0x%llx 0x%llx %d Ox%x\n", entry->addr, entry->addr + entry->len, entry->type, entry->len);
   		start += sizeof(multiboot_memory_map_t);
   }
}
