/*
 * File: command.c
 * Description: holder for the logic of interpreting
                assembler instructions.
 * Created at: 2018-4-3
 */

#include "command.h"

#include <ctype.h>
#include <glib.h>
#include <stdio.h>

#define VALUE_LEN 25
#define VALUE_MASK 0x01ffffff

static FILE *f;
static int loc;
static int num_of_passes;
static GHashTable *hash = NULL;

static void initialize_label_record(struct label_record **record, char *label) {
    *record = malloc(sizeof(struct label_record));
    strcpy((*record)->label, label);
    (*record)->loc = loc;
}

static int get_label_loc(char *label) {
    struct label_record *label_record_ptr =
        (struct label_record *)g_hash_table_lookup(hash, label);
    printf("[interpreter]  label record location=%d\n", label_record_ptr->loc);
    if (label_record_ptr) {
        return label_record_ptr->loc;
    }
    printf("[interpreter]  label=%s, location couldn't be found\n", label);
    return -1;
}

void init(void) {
    f = fopen("out.bin", "we");
    loc = 0;
    num_of_passes = 0;
    hash = g_hash_table_new(g_str_hash, g_str_equal);
}

void destroy_command(void) { g_hash_table_destroy(hash); }

int pass_two(void) { return num_of_passes > 0; }

void increment_loc(void) { ++loc; }

static void iterator(gpointer key, gpointer value, gpointer user_data) {
    struct label_record *label_record_ptr = (struct label_record *)value;
    printf("[label]=%s, location=%d\n", label_record_ptr->label,
           label_record_ptr->loc);
}

void increment_pass(void) {
    puts("[interpreter]  printing all the labels.");
    g_hash_table_foreach(hash, (GHFunc)iterator, NULL);
    ++num_of_passes;
    loc = 0;
}

void add_label(char *label) {
    printf("[interpreter]  adding_label=%s\n", label);
    struct label_record *label_record_ptr = NULL;
    initialize_label_record(&label_record_ptr, label);
    g_hash_table_insert(hash, label, label_record_ptr);
}

static unsigned int encode_instruction_data(int value, int opcode) {
    int sign = value < 0 ? 1 : 0;
    value = abs(value);
    unsigned int instruction = VALUE_MASK & value;
    if (sign) {
        instruction = instruction | (1 << VALUE_LEN);
    }
    instruction = instruction | opcode;
    return instruction;
}

void encode_push(int value) {
    printf("[interpreter]  encoding push command with value=%d\n", value);
    int instruction = encode_instruction_data(value, PUSH);
    fprintf(f, "%u\n", instruction);
}

void encode_pop(void) {
    puts("[interpreter]  encoding pop");
    fprintf(f, "%u\n", POP);
}

void encode_goto(char *label) {
    for (int i = 0; label[i]; ++i) {
        label[i] = tolower(label[i]);
    }
    printf("[interpreter]  encoding goto with label=%s\n", label);
    int label_loc = get_label_loc(label);
    int disp = label_loc - loc;
    int instruction = encode_instruction_data(disp, GOTO);
    fprintf(f, "%u\n", instruction);
}

void encode_mul(void) {
    puts("[interpreter]  encoding multiply");
    fprintf(f, "%u\n", MUL);
}

void encode_add(void) {
    puts("[interpreter]  encoding add");
    fprintf(f, "%u\n", ADD);
}

void encode_label(void) {
    puts("[interpreter] encoding label");
    fprintf(f, "%u\n", LABEL);
}

void encode_div(void) {
    puts("[interpreter]  encoding division");
    fprintf(f, "%u\n", DIV);
}

void encode_sub(void) {
    puts("[interpreter]  encoding subtraction");
    fprintf(f, "%u\n", SUB);
}

void encode_halt(void) {
    puts("[interpreter]  encoding halt");
    fprintf(f, "%u\n", HALT);
}

void encode_lt(void) {
    puts("[interpreter]  encoding LT");
    fprintf(f, "%u\n", LT);
}

void encode_lte(void) {
    puts("[interpreter]  encoding LTE");
    fprintf(f, "%u\n", LTE);
}

void encode_gt(void) {
    puts("[interpreter]  encoding GT");
    fprintf(f, "%u\n", GT);
}

void encode_gte(void) {
    puts("[interpreter]  encoding GTE");
    fprintf(f, "%u\n", GTE);
}

void encode_eq(void) {
    puts("[interpreter]  encoding EQ");
    fprintf(f, "%u\n", EQ);
}
