#include <nuttx/elf.h>
#include <nuttx/config.h>
#include <debug.h>
#include <arch/arm/include/elf.h>
#include <errno.h>


/* TODO:  Fill in implementation. */

#ifdef CONFIG_LIBC_ARCH_ELF

bool up_checkarch(FAR const Elf32_Ehdr *ehdr)
{
	  /* Make sure it's an ARM executable */

	  if (ehdr->e_machine != EM_ARM)
	    {
	      berr("ERROR: Not for ARM: e_machine=%04x\n", ehdr->e_machine);
	      return false;
	    }

	  /* Make sure that 32-bit objects are supported */

	  if (ehdr->e_ident[EI_CLASS] != ELFCLASS32)
	    {
	      berr("ERROR: Need 32-bit objects: e_ident[EI_CLASS]=%02x\n", ehdr->e_ident[EI_CLASS]);
	      return false;
	    }

	  /* Verify endian-ness */

	#ifdef CONFIG_ENDIAN_BIG
	  if (ehdr->e_ident[EI_DATA] != ELFDATA2MSB)
	#else
	  if (ehdr->e_ident[EI_DATA] != ELFDATA2LSB)
	#endif
	    {
	      berr("ERROR: Wrong endian-ness: e_ident[EI_DATA]=%02x\n", ehdr->e_ident[EI_DATA]);
	      return false;
	    }

	  /* Make sure the entry point address is properly aligned */

	  if ((ehdr->e_entry & 3) != 0)
	    {
	      berr("ERROR: Entry point is not properly aligned: %08x\n", ehdr->e_entry);
	      return false;
	    }

	  /* TODO:  Check ABI here. */
	  return true;
}



int up_relocate(FAR const Elf32_Rel *rel, FAR const Elf32_Sym *sym,
                uintptr_t addr)
{
	  int32_t offset;
	  unsigned int relotype;

	  /* All relocations except R_ARM_V4BX depend upon having valid symbol
	   * information.
	   */

	  relotype = ELF32_R_TYPE(rel->r_info);
	  if (sym == NULL && relotype != R_ARM_NONE && relotype != R_ARM_V4BX)
	    {
	      return -EINVAL;
	    }

	  /* Handle the relocation by relocation type */

	  switch (relotype)
	    {
	    case R_ARM_NONE:
	      {
	        /* No relocation */
	      }
	      break;

	    case R_ARM_PC24:
	    case R_ARM_CALL:
	    case R_ARM_JUMP24:
	      {
	        binfo("Performing PC24 [%d] link at addr %08lx [%08lx] to sym '%p' st_value=%08lx\n",
	              ELF32_R_TYPE(rel->r_info), (long)addr, (long)(*(uint32_t *)addr),
	              sym, (long)sym->st_value);

	        offset = (*(uint32_t *)addr & 0x00ffffff) << 2;
	        if (offset & 0x02000000)
	          {
	            offset -= 0x04000000;
	          }

	        offset += sym->st_value - addr;
	        if (offset & 3 || offset < (int32_t) 0xfe000000 || offset >= (int32_t) 0x02000000)
	          {
	            berr("ERROR:   ERROR: PC24 [%d] relocation out of range, offset=%08lx\n",
	                  ELF32_R_TYPE(rel->r_info), offset);

	            return -EINVAL;
	          }

	        offset >>= 2;

	        *(uint32_t *)addr &= 0xff000000;
	        *(uint32_t *)addr |= offset & 0x00ffffff;
	      }
	      break;

	    case R_ARM_ABS32:
	    case R_ARM_TARGET1:  /* New ABI:  TARGET1 always treated as ABS32 */
	      {
	        binfo("Performing ABS32 link at addr=%08lx [%08lx] to sym=%p st_value=%08lx\n",
	              (long)addr, (long)(*(uint32_t *)addr), sym, (long)sym->st_value);

	        *(uint32_t *)addr += sym->st_value;
	      }
	      break;

	    case R_ARM_V4BX:
	      {
	        binfo("Performing V4BX link at addr=%08lx [%08lx]\n",
	              (long)addr, (long)(*(uint32_t *)addr));

	         /* Preserve only Rm and the condition code */

	        *(uint32_t *)addr &= 0xf000000f;

	        /* Change instruction to 'mov pc, Rm' */

	        *(uint32_t *)addr |= 0x01a0f000;
	      }
	      break;

	    case R_ARM_PREL31:
	      {
	        binfo("Performing PREL31 link at addr=%08lx [%08lx] to sym=%p st_value=%08lx\n",
	              (long)addr, (long)(*(uint32_t *)addr), sym, (long)sym->st_value);

	        offset            = *(uint32_t *)addr + sym->st_value - addr;
	        *(uint32_t *)addr = offset & 0x7fffffff;
	      }
	      break;

	    case R_ARM_MOVW_ABS_NC:
	    case R_ARM_MOVT_ABS:
	      {
	        binfo("Performing MOVx_ABS [%d] link at addr=%08lx [%08lx] to sym=%p st_value=%08lx\n",
	              ELF32_R_TYPE(rel->r_info), (long)addr, (long)(*(uint32_t *)addr),
	              sym, (long)sym->st_value);

	        offset = *(uint32_t *)addr;
	        offset = ((offset & 0xf0000) >> 4) | (offset & 0xfff);

	        offset += sym->st_value;
	        if (ELF32_R_TYPE(rel->r_info) == R_ARM_MOVT_ABS)
	          {
	            offset >>= 16;
	          }

	        *(uint32_t *)addr &= 0xfff0f000;
	        *(uint32_t *)addr |= ((offset & 0xf000) << 4) | (offset & 0x0fff);
	      }
	      break;

	    default:
	      berr("ERROR: Unsupported relocation: %d\n", ELF32_R_TYPE(rel->r_info));
	      return -EINVAL;
	    }

	  return OK;
}



int up_relocateadd(FAR const Elf32_Rela *rel,
                   FAR const Elf32_Sym *sym, uintptr_t addr)
{
	  berr("ERROR: RELA relocation not supported\n");
	  return -ENOSYS;
}

#endif



#ifdef CONFIG_CXX_EXCEPTION
int up_init_exidx(Elf32_Addr address, Elf32_Word size)
{
	return 0;
}
#endif





