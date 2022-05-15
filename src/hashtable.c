#include "hashtable.h"

#define SEED 0x1234567

static uint32_t FNV_hash(const void* key, int len)
{
    uint32_t h = SEED;
    // Source: https://github.com/aappleby/smhasher/blob/master/src/Hashes.cpp
    h ^= 2166136261UL;
    const uint8_t* data = (const uint8_t*)key;
    for(int i = 0; i < len; i++)
    {
        h ^= data[i];
        h *= 16777619;
    }
    return h;
}

static void free_element(HashElement * el)
{
  memset(el->string, 0, strlen(el->string));
  free(el->string);
  free(el);
}

HashTable* create_table(uint size)
{
  HashTable *table = NULL;
  table = calloc(1, sizeof(HashTable));
  if (table == NULL)
  {
    goto cleanup;
  }
  
  table->count = 0;
  table->size = size;
  
  table->table = (HashElement **)calloc(size, sizeof(HashElement));
  if (table->table == NULL)
  {
    free(table);
    table = NULL;
    goto cleanup;
  }

  for (int i=0; i<table->size; i++)
        table->table[i] = NULL;
  
cleanup:
  return table;
}

void destroy_table(HashTable **table)
{
  for (int i=0; i < (*table)->size; i++)
  {
      HashElement* el = (*table)->table[i];
      if (el != NULL)
          free_element(el);   
  }

  memset((*table)->table, 0, (*table)->size * sizeof(HashElement));
  free((*table)->table);

  memset(*table, 0, sizeof(HashTable));
  free(*table);
  *table = NULL;
}

int add_item(HashTable *table, const char * string)
{
  int ret = 1;
  HashElement *element = NULL;
  size_t str_sz = strlen(string);
  uint32_t hash = FNV_hash(string, str_sz);

  uint index = (hash) % (table->size);

  // check if index exists
  if (table->table[index] != NULL)
  {
    ret = 0;
    goto cleanup;
  }
  
  element = calloc(1, sizeof(HashElement));
  if (element == NULL)
  {
    ret = 0;
    goto cleanup;
  }
  
  element->string = calloc(1, str_sz + 1);
  if (element->string == NULL)
  {
    ret = 0;
    goto cleanup;
  }
  
  memcpy(element->string, string, str_sz);
  element->hash = FNV_hash(string, str_sz);

  printf("String %s\nHash = %u\n", string, hash);
  table->table[index] = element;
  
cleanup:
  return ret;
}