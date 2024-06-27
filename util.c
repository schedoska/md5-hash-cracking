#include "util.h"

uint8_t hashes_equal(uint8_t *hash1, uint8_t *hash2)
{
    for(int q = 0; q < 16; q++)
    {
        if(hash1[q] != hash2[q]) return 0;
    }
    return 1;
}

void init_uint8_arrays(uint8_t *array, int size, uint8_t value)
{
    for(int q = 0; q < size; q++)
    {
        array[q] = value;
    }
}

void load_dictionary2(int *dictionary_word_count, char ***dictionary)
{
    FILE *file_dictionary;
    char buffor[BUFFOR_SIZE];
    file_dictionary = fopen("slownik","r");

    fscanf(file_dictionary, "%i\n", dictionary_word_count);
    printf("Słownik zawiera %d slów\n", *dictionary_word_count);

    *dictionary = malloc(*dictionary_word_count * sizeof(char*));
    for(int q = 0; q < *dictionary_word_count; q++)
    {
        fgets(buffor, BUFFOR_SIZE, file_dictionary);
        buffor[strcspn(buffor, "\n")] = 0;
        buffor[strcspn(buffor, " ")] = 0;
        (*dictionary)[q] = malloc(strlen(buffor) * sizeof(char));
        strcpy((*dictionary)[q], buffor);
    }

    fclose(file_dictionary);
}

void load_password_list2(char *file_name, int *password_count, uint8_t (*password_list)[][16])
{
    FILE *passwords_file;
    passwords_file = fopen(file_name, "r");
    *password_count = 0;
    uint8_t buf[35];
    uint8_t *pos;

    while(fgets(buf, 35, passwords_file) && *password_count < PASSWORD_AMOUNT)
    {
        pos = buf;
        for(int i = 0; i < 16; i++)
        {
            sscanf(pos, "%2hhx", &(*password_list)[*password_count][i]);
            pos += 2;
        }
        (*password_count)++;
    }
    printf("Zbiór zawiera %d zakodowanych haseł\n", *password_count);
}