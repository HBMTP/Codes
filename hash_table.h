#ifndef HT_H
#define HT_H
typedef struct hash_table hash_table;
typedef struct element element;
hash_table* create_hash_table();
int create_index(unsigned char key);
void put(hash_table *ht, unsigned char key, unsigned char value);
int get(hash_table *ht, unsigned char key);
void remove_ht(hash_table *ht, unsigned char key);

#endif