/*
 * File: command.h
 * Description: responsible for assembler translation
 * Created at: 2018-4-3
 */

/* initialize the output file. */
void init(void);

/* encode the push instruction. */
void encode_push(const int value);

/* encode pop instruction */
void encode_pop(void);

/* encode goto instruction */
void encode_goto(char *label);

/* encode halt instruction. */
void encode_halt(void);

/* encode the addition instruction. */
void encode_mul(void);

/* encode the subtraction instruction. */
void encode_add(void);

/* encode the division instruction. */
void encode_div(void);

/* encode the subtraction instruction. */
void encode_sub(void);

/* encode less than instruction. */
void encode_lt(void);

/* encode less than or equal. */
void encode_lte(void);

/* encode greater than instruction. */
void encode_gt(void);

/* encode less than or equal. */
void encode_gte(void);

/* encode equal instruction. */
void encode_eq(void);
