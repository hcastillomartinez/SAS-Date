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

void test_hash (char * str)
{
  printf("test hash = %u\n", FNV_hash(str, strlen(str)));
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

static int handle_collision(HashElement *element, const char * string, uint32_t hash)
{
  int ret = 0;
  HashElement *tmp = element;

  if (tmp->hash == hash)
    goto cleanup;

  while(tmp->next != NULL)
  {
    // look for hash
    if (tmp->hash == hash)
    {
      printf("exists in the chain\n");
      goto cleanup;
    }
    printf("hash = %u\nsearch hash %u\nstring = %s\nsearch string = %s\n", tmp->hash, hash, tmp->string, string);
    tmp = tmp->next;
  }

  
  printf("adding to %u %s chain\n", hash, string);
  // assume it wasnt found, chain it.
  tmp->next = calloc(1, sizeof(HashElement));
  if (tmp->next == NULL)
  {
    goto cleanup;
  }

  size_t str_sz = strlen(string);
  tmp->next->string = calloc(1, str_sz + 1);
  if (tmp->next->string == NULL)
  {
    goto cleanup;
  }
  
  memcpy(tmp->next->string, string, str_sz);
  tmp->next->hash = hash;

  tmp->next->next = NULL;

  ret = 1;

cleanup:
  return ret;
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
    HashElement* el = table->table[index];
    if (el->hash == hash)
      ret = 0;
    else
    {
      printf("\nindex = %d\n", index);
      ret = handle_collision(table->table[index], string, hash);
      if (ret)
        printf("succesful collision\n");
    }
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

  element->next = NULL;

  // printf("String %s\nHash = %u\n", string, hash);
  table->table[index] = element;
  
cleanup:
  return ret;
}