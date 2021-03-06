#include "hashtable.h"

#define SEED 0x1234567

/**
 * FNV hashes are designed to be fast while maintaining a low collision rate.
 * The high dispersion of the FNV hashes makes them well suited for hashing nearly
 * identical strings such as URLs, hostnames, filenames, text, IP addresses, etc.
 * @param key (const void*), key to get hash value from.
 * @param len (size_t), length of the key.
 * @return hash value of the Key (uint32_t)
 */
static uint32_t FNV_hash(const void *key, size_t len) {
    uint32_t h = SEED;
    // Source: https://github.com/aappleby/smhasher/blob/master/src/Hashes.cpp
    h ^= 2166136261UL;
    const uint8_t *data = (const uint8_t *) key;
    for (int i = 0; i < len; i++) {
        h ^= data[i];
        h *= 16777619;
    }
    return h;
}

/**
 * Frees the HashElement and its chain.
 * @param el (HashElement *), HashElement to free
 */
static void free_element(HashElement *el) {
    HashElement *tmp = el;
    HashElement *next = NULL;
    while (tmp != NULL) {
        next = tmp->next;
        memset(tmp->string, 0, strlen(tmp->string));
        free(tmp->string);
        free(tmp);
        tmp = next;
    }
}

/**
 * Creates hashtable with number of buckets specified.
 * @param size (uint), number of buckets to create.
 * @return NULL if error occurred otherwise pointer to HashTable
 */
HashTable *create_table(uint size) {
    HashTable *table = NULL;
    table = calloc(1, sizeof(HashTable));
    if (table == NULL) {
        goto cleanup;
    }

    table->count = 0;
    table->size = size;

    table->buckets = (HashElement **) calloc(size, sizeof(HashElement));
    if (table->buckets == NULL) {
        free(table);
        table = NULL;
        goto cleanup;
    }

    for (int i = 0; i < table->size; i++)
        table->buckets[i] = NULL;

    cleanup:
    return table;
}

/**
 * Frees the entire HashTable and sets to NULL.
 * @param table (HashTable **), hashtable to free
 */
void destroy_table(HashTable **table) {
    // free elements from the buckets and respective chains
    for (int i = 0; i < (*table)->size; i++) {
        HashElement *el = (*table)->buckets[i];
        if (el != NULL) {
            free_element(el);
            el = NULL;
        }
    }
    // free the buckets and Hashtable
    memset((*table)->buckets, 0, (*table)->size * sizeof(HashElement));
    free((*table)->buckets);

    memset(*table, 0, sizeof(HashTable));
    free(*table);
    *table = NULL;
}

/**
 * Handle collision that occurs at HashElement (bucket) using chaining.
 * @param element (HashElement *), bucket to potentially add new element to its chain.
 * @param string (const char *), string of potential item to add.
 * @param hash (uint32_t), hash of the string of the potential item to add.
 * @return 1 on success else 0.
 */
static int handle_collision(HashElement *element, const char *string, uint32_t hash) {
    int ret = 0;
    HashElement *tmp = element;

    if (tmp->hash == hash)
        goto cleanup;

    while (tmp->next != NULL) {
        // look for hash
        if (tmp->next->hash == hash) {
            // hash exists in the chain already
            goto cleanup;
        }
        tmp = tmp->next;
    }

    HashElement *new = NULL;
    // assume it wasnt found, chain it.
    new = calloc(1, sizeof(HashElement));
    if (new == NULL) {
        goto cleanup;
    }

    size_t str_sz = strlen(string);
    new->string = calloc(1, str_sz + 1);
    if (new->string == NULL) {
        free(new);
        goto cleanup;
    }

    memcpy(new->string, string, str_sz);
    new->hash = hash;

    new->next = NULL;
    tmp->next = new;

    ret = 1;

    cleanup:
    return ret;
}

/**
 * Adds an item to the HashTable.
 * @param table (HashTable *), table to add item to.
 * @param string (const char *), item to add to table.
 * @return 1 on success else 0.
 */
int add_item(HashTable *table, const char *string) {
    int ret = 1;
    HashElement *element = NULL;
    size_t str_sz = strlen(string);
    uint32_t hash = FNV_hash(string, str_sz);

    uint index = (hash) % (table->size);

    // check if index exists
    if (table->buckets[index] != NULL) {
        ret = handle_collision(table->buckets[index], string, hash);
        goto cleanup;
    }

    // adding new element to index
    element = calloc(1, sizeof(HashElement));
    if (element == NULL) {
        ret = 0;
        goto cleanup;
    }

    element->string = calloc(1, str_sz + 1);
    if (element->string == NULL) {
        free(element);
        ret = 0;
        goto cleanup;
    }

    memcpy(element->string, string, str_sz);
    element->hash = FNV_hash(string, str_sz);

    element->next = NULL;

    table->buckets[index] = element;

    cleanup:
    return ret;
}