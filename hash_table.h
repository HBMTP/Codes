#ifndef HT_H
#define HT_H
typedef struct hash_table hash_table;
typedef struct element element;
hash_table* create_hash_table();
int create_index(unsigned char key);
void put(hash_table *ht, unsigned char key);
int get(hash_table *ht, unsigned char key);
void remove_ht(hash_table *ht, unsigned char key);
void print_hs(hash_table *ht);

#endif
