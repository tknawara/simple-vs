/*
 * File: command.h
 * Description: responsible for assembler translation
 * Created at: 2018-4-3
 */

struct label_record {
  char label[100];
  int loc;
};

/* initialize the output file. */
void init(void);

/* clean up all the allocated memory. */
void destroy_command(void);
/* return 1 if running in pass two. */
int pass_two(void);

/* increment the location of the program. */
void increment_loc(void);

/* increment number of passes. */
void increment_pass(void);

/* add the label to the list of defined labels. */
void add_label(char *label);

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
