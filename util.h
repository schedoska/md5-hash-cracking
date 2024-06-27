#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <openssl/md5.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>
#include <signal.h>

#define BUFFOR_SIZE 40
#define PASSWORD_AMOUNT 1000

struct password_unhashed
{
    int producer_id;
    int password_hashed_id;
    char password_real[500];
};
typedef struct password_unhashed password_unhashed;

void load_dictionary2(int *dictionary_word_count, char ***dictionary);
void load_password_list2(char *file_name, int *password_count, uint8_t (*password_list)[][16]);

uint8_t hashes_equal(uint8_t *hash1, uint8_t *hash2);
void init_uint8_arrays(uint8_t *array, int size, uint8_t value);

#endif