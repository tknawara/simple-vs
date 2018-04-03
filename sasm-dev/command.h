/*
 * File: command.h
 * Description: responsible for assembler translation
 * Created at: 2018-4-3
 */

/* initialize the output file. */
void init(void);

/* encode the multiplication instruction. */
void encode_push(const int value);

/* encode the addition instruction. */
void encode_mul(void);

/* encode the subtraction instruction. */
void encode_add(void);

/* encode the division instruction. */
void encode_div(void);

/* encode the subtraction instruction. */
void encode_sub(void);
