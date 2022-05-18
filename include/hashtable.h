#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef struct HashElement_ {
    char *string;
    uint32_t hash;
    struct HashElement_ *next;
} HashElement;

typedef struct HashTable_ {
    HashElement **buckets;
    uint size;
    uint count;
} HashTable;


void test_hash(char *string);

HashTable *create_table(uint size);

void destroy_table(HashTable **table);

int add_item(HashTable *table, const char *string);

int remove_item(HashTable *table, const char *string);