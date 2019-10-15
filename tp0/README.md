# TP0 - Familiarisation avec le noyau secos

Le but du TP est de se familiariser avec le noyau secos.

Le noyau est linké grâce au LD-script "utils/linker.lds" qui définit l'agencement mémoire du noyau lorsqu'il va être chargé par le bootloader GRUB.

```bash
(tp0)$ readelf -l kernel.elf

Elf file type is EXEC (Executable file)
Entry point 0x302010
There are 3 program headers, starting at offset 52

Program Headers:
  Type           Offset   VirtAddr   PhysAddr   FileSiz MemSiz  Flg Align
  LOAD           0x000094 0x00300000 0x00300000 0x0000c 0x0000c RWE 0x4
  LOAD           0x0000a0 0x00300010 0x00300010 0x00000 0x02000 RW  0x10
  LOAD           0x0000b0 0x00302010 0x00302010 0x013f8 0x01810 RWE 0x20
```

Le fichier ELF nous indique que le noyau est chargé à l'adresse physique `0x300000`.

Lors du démarrage, le noyau vous affiche sur le port série, la zone mémoire qu'il occupe:

```bash
(tp0)$ make qemu
secos-a241db6-59e4545 (c) Airbus
kernel mem [0x302010 - 0x303820]
```

Si vous regardez le code "start.c", vous découvrirez l'affichage de ces informations à l'aide des symbols `__kernel_start__` et `__kernel_end__`.

Vous pouvez modifier le fichier "tp0/tp.c" pour commencer le TP.

Par défaut, les fichiers de TP permettent d'accéder à un objet global pré-initialisé `info`. C'est un pointeur dont la structure est définie dans "include/info.h". Pour l'instant il ne contient que le champ `mbi` provenant de Grub. Ce champ donne accès à la structure `multiboot_info` (version 1) qui contient de nombreuses informations sur le système. Vous trouverez sa définition dans "include/mbi.h" et "include/grub_mbi.h".


## Questions

### Question 1

**Pourquoi le noyau indique `0x302010` et pas `0x300000` comme adresse de début ? Indice: essayer de comprendre linker.lds, regardez également le code de "entry.s"**

2000 => pour la pile noyau de base !
---

### Question 2

**A l'aide de la structure "multiboot_info", vous devez afficher la cartographie mémoire de la VM. Pour cela, utilisez les champs `mmap_addr` et `mmap_length`. Aidez-vous d'internet pour trouver des informations sur le standard multiboot. Le champ `mmap_addr` contient l'adresse du premier objet de type `multiboot_memory_map` qui vous permettra d'afficher des informations sur la mémoire.**

---

### Question 3

**Vous allez découvrir différentes zones de mémoire physique, certaines étant réservées, d'autres libres. Déclarez un pointeur d'entier par exemple et initialisez le avec une des adresses que vous avez trouvée. Essayez de lire/écrire la mémoire à cette adresse. Que se passe-t-il ? Avez-vous un "segmentation fault" ? Pourquoi ?**

---

### Question 4

**Essayez de lire/écrire en dehors de la RAM disponible (128MB). Que se passe-t-il ?**
=> segment flat on a le droit donc de taper dans les 4Giga, il se passe donc rien.


gdt_reg_t gdtr;
size-t 

get_gtdr(gdtr);
n = (gdtr.limit+1)/sizeof(seg_desc_t); //nombre d'entree de la gdt
for(i=0;i<n;i++){
	seg_desc_t *dec = &gdtr.desc[i];
	win32_t base = dec->base_J<<24 | dec->base_2 << 16 | dec->base_1;
}

gdt_flat_dac
c0_desc(_d)
d0_desc(_d)

GDT[0].raw = OULL => 0 sur long long 


GDT[3].base_1 = base
GTD[3].base_2 = base >>16;
GDT[3].base_3 = base >> 24
GDT[3].limit_1 = 32-1
GDT[3].type = SEC_DESC_DATA_RW;
set_es(gdt_krn_seg_sel(3))