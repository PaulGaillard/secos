/* GPLv2 (c) Airbus */
#include <debug.h>
#include <info.h>
#include <segmem.h>
  #include <string.h>

extern info_t *info;
seg_desc_t GDT[4];

void displayGDT(gdt_reg_t gdtr){
	debug("GDT addr : %p\n",gdtr.addr);
	debug("GDT limite : %p\n",gdtr.addr + gdtr.limit);
	int n = (gdtr.limit+1)/sizeof(seg_desc_t); //nombre d'entree de la gdt
	int i;
	for(i=0;i<n;i++){
		seg_desc_t * dec = &gdtr.desc[i];
		int index = (int) dec - (int) gdtr.addr;
		uint32_t base = dec->base_3 << 24 | dec->base_2 << 16 | dec->base_1;
		uint32_t limit = dec->limit_2 << 16 | dec->limit_1;
		debug("Segment descriptor index : %d\n",index/sizeof(seg_desc_t));
		debug("@ de base SD : %p\n",base);
		debug("Limit SD : %p\n",limit);
		debug("Ring SD : %d\n", dec->dpl);
		debug("Type SD : %x\n\n", dec->type);
	}

}

void tp()
{
	//Affichage GDT de Grub
	gdt_reg_t gdtr;
	get_gdtr(gdtr);
	displayGDT(gdtr);

	//Creation GDT perso
	long long int zero64 = 0; 
	GDT[0].raw = zero64; //=> 0 sur long long 

	GDT[1].limit_1 = 0xFFFF;
	GDT[1].limit_2 = 0xF;
	GDT[1].base_1 = 0x0000;
	GDT[1].base_2 = 0x00;
	GDT[1].base_3 = 0x00;
	GDT[1].dpl = 0;
	GDT[1].type = SEG_DESC_CODE_XR;
	GDT[1].d = 1;
	GDT[1].g = 1;
	GDT[1].avl = 1;
	GDT[1].s = 1;
	GDT[1].p = 1;

	GDT[2].limit_1 = 0xFFFF;
	GDT[2].limit_2 = 0xF;
	GDT[2].base_1 = 0x0000;
	GDT[2].base_2 = 0x00;
	GDT[2].base_3 = 0x00;
	GDT[2].dpl = 0;
	GDT[2].type = SEG_DESC_DATA_RW;
	GDT[2].g = 1;
	GDT[2].d = 1;
	GDT[2].avl = 0;
	GDT[2].s = 1;
	GDT[2].p = 1;

	GDT[3].limit_1 = 32-1;
	GDT[3].base_1 = 0x00;
	GDT[3].base_2 = 0x600000>>16;
	GDT[3].base_3 = 0x600000>>24;
	GDT[3].dpl = 0;
	GDT[3].type = SEG_DESC_DATA_RW;
	GDT[3].g = 0; //Granularité à 0 sinon on fait limit*4 et on a une limite à 128 au lieu de 32
	GDT[3].d = 1;
	GDT[3].avl = 0;
	GDT[3].s = 1;
	GDT[3].p = 1;

	gdtr.desc = &GDT[0];
	gdtr.limit = sizeof(GDT) - 1;
	set_gdtr(gdtr);
	displayGDT(gdtr);


	set_cs(gdt_krn_seg_sel(1));
	set_ss(gdt_krn_seg_sel(2));
 	set_ds(gdt_krn_seg_sel(2));
 	set_es(gdt_krn_seg_sel(2));
 	set_fs(gdt_krn_seg_sel(2));
 	set_gs(gdt_krn_seg_sel(2));

  	char  src[64];
  	char *dst = 0;
  	memset(src, 0xff, 64); 	
  	set_es(gdt_krn_seg_sel(3));
  	_memcpy8(dst, src, 32);
}
