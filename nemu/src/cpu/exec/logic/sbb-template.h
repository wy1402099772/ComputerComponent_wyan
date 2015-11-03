#include "cpu/exec/template-start.h"

#define instr sbb

static void do_execute() {
    DATA_TYPE src = op_src->val + cpu.CF;
	DATA_TYPE result = op_dest->val - src;
	OPERAND_W(op_dest, result);


    //OF, SF, ZF, AF, CF, and PF
    cpu.OF = (((int32_t)(op_dest->val) > 0) && ((int32_t)(src) < 0) && ((int32_t)result < 0)) || (((int32_t)(op_dest->val) < 0) && ((int32_t)(src) > 0) && ((int32_t)result > 0));

#if DATA_BYTE == 1
    cpu.SF = (result >> 7) & 0x1;
#endif // DATA_BYTE
#if DATA_BYTE == 2
    cpu.SF = (result >> 15) & 0x1;
#endif // DATA_BYTE
#if DATA_BYTE == 4
    cpu.SF = (result >> 31) & 0x1;
#endif // DATA_BYTE

    cpu.ZF = result ? 0 : 1;

    cpu.AF = ((uint32_t)(op_dest->val & 0x0f) < (uint32_t)(-(src & 0x0f)));

	cpu.CF = ((uint32_t)op_dest->val >= (uint32_t)(src));

	cpu.PF = (result ^ (result >> 1) ^ (result >> 2) ^ (result >> 3) ^ (result >> 4) ^ (result >> 5) ^ (result >> 6) ^ (result >> 7)) & 0x01;

	print_asm_template2();
}

make_instr_helper(i2a)
make_instr_helper(i2rm)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
#endif
make_instr_helper(r2rm)
make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
