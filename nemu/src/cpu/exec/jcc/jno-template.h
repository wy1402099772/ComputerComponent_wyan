#include "cpu/exec/template-start.h"

#define instr jno

static void do_execute ()
{
    printf("OF:%d", cpu.OF);
    if (!cpu.OF)
    {
    printf("1111\n");
        int32_t tsrc = (DATA_TYPE_S)op_src->val;
        cpu.eip += tsrc;
#if DATA_BYTE == 2
        cpu.eip &= 0x0000ffff;
#endif // DATA_BYTE
    }
    print_asm_template1();
}

make_instr_helper(i)


#include "cpu/exec/template-end.h"
