#include "util.h"

#define THREADS_AMOUNT 7

int         dictionary_word_count;
int         password_count;
pthread_t   th_producent0, th_producent1, th_producent2;
pthread_t   th_producent3_2word, th_producent4_2word, th_producent5_2word;
pthread_t   th_konsument;
uint8_t     th_reset_list[THREADS_AMOUNT];

struct {
    pthread_mutex_t     mutex;
    pthread_cond_t      cond;
    char                **dictionary;
    uint8_t             password_list[PASSWORD_AMOUNT][16];
    uint8_t             identified[PASSWORD_AMOUNT];
    password_unhashed   identified_password_list[PASSWORD_AMOUNT];
    int                 num_identified;
    int                 num_ready;
} shared = {PTHREAD_MUTEX_INITIALIZER,PTHREAD_COND_INITIALIZER,0,0,0,0,0,0};

void* producent_0(void* id)
{
    MD5_CTX md5;
    uint8_t wynik[16];
    uint8_t with_number_flag = 0;
    char    temp_buffor[500];
    int     cur_number = 0;
    int     cur_dic_word = 0;

    while(1)
    {
        if(th_reset_list[(long)id] == 1)
        { 
            cur_dic_word = 0;
            cur_number = 0;
            with_number_flag = 0;
            th_reset_list[(long)id] = 0;
        }
        if(with_number_flag)
            sprintf(temp_buffor, "%d%s%d", cur_number, shared.dictionary[cur_dic_word], cur_number);
        else 
            strcpy(temp_buffor, shared.dictionary[cur_dic_word]);
        
        MD5_Init(&md5);
        MD5_Update(&md5, temp_buffor, strlen(temp_buffor));
        MD5_Final(wynik, &md5);
        
        for(int q = 0; q < password_count; q++)
        {
            if(th_reset_list[(long)id] == 1) break;
            if(shared.identified[q] == 1) continue;
            if(hashes_equal(wynik, shared.password_list[q]))
            {
                pthread_mutex_lock(&shared.mutex);
                shared.identified_password_list[shared.num_identified].password_hashed_id = q;
                shared.identified_password_list[shared.num_identified].producer_id = (long)id;
                strcpy(shared.identified_password_list[shared.num_identified].password_real, temp_buffor);
                shared.num_identified++;
                shared.num_ready++;
                pthread_cond_signal(&shared.cond);
                pthread_mutex_unlock(&shared.mutex);
            }
        }
        cur_dic_word++;
        if(cur_dic_word >= dictionary_word_count)
        {
            with_number_flag = 1;
            cur_dic_word = 0;
            cur_number++;
        }
    }
}

void* producent_1(void* id)
{
    MD5_CTX md5;
    uint8_t wynik[16];
    uint8_t with_number_flag = 0;
    char    temp_buffor[500];
    char    temp_buffor_small[50];
    int     cur_number = 0;
    int     cur_dic_word = 0;

    while(1)
    {
        if(th_reset_list[(long)id] == 1)
        { 
            cur_dic_word = 0;
            cur_number = 0;
            with_number_flag = 0;
            th_reset_list[(long)id] = 0;
        }
        strcpy(temp_buffor_small, shared.dictionary[cur_dic_word]);
        temp_buffor_small[0] = toupper(temp_buffor_small[0]);
        if(with_number_flag)
            sprintf(temp_buffor, "%d%s%d", cur_number, temp_buffor_small, cur_number);
        else 
            strcpy(temp_buffor, temp_buffor_small);
        
        MD5_Init(&md5);
        MD5_Update(&md5, temp_buffor, strlen(temp_buffor));
        MD5_Final(wynik, &md5);

        for(int q = 0; q < password_count; q++)
        {
            if(th_reset_list[(long)id] == 1) break;
            if(shared.identified[q] == 1) continue;
            if(hashes_equal(wynik, shared.password_list[q]))
            {
                pthread_mutex_lock(&shared.mutex);
                shared.identified_password_list[shared.num_identified].password_hashed_id = q;
                shared.identified_password_list[shared.num_identified].producer_id = (long)id;
                strcpy(shared.identified_password_list[shared.num_identified].password_real, temp_buffor);
                shared.num_identified++;
                shared.num_ready++;
                pthread_cond_signal(&shared.cond);
                pthread_mutex_unlock(&shared.mutex);
            }
        }
        cur_dic_word++;
        if(cur_dic_word >= dictionary_word_count)
        {
            with_number_flag = 1;
            cur_dic_word = 0;
            cur_number++;
        }
    }
}

void* producent_2(void* id)
{
    MD5_CTX md5;
    uint8_t wynik[16];
    uint8_t with_number_flag = 0;
    char    temp_buffor[500];
    char    temp_buffor_small[50];
    int     cur_number = 0;
    int     cur_dic_word = 0;

    while(1)
    {
        if(th_reset_list[(long)id] == 1)
        { 
            cur_dic_word = 0;
            cur_number = 0;
            with_number_flag = 0;
            th_reset_list[(long)id] = 0;
        }

        strcpy(temp_buffor_small, shared.dictionary[cur_dic_word]);
        for(int a = 0; a < strlen(temp_buffor_small); a++)
        {
            temp_buffor_small[a] = toupper(temp_buffor_small[a]);
        }
        if(with_number_flag)
            sprintf(temp_buffor, "%d%s%d", cur_number, temp_buffor_small, cur_number);
        else 
            strcpy(temp_buffor, temp_buffor_small);
        
        MD5_Init(&md5);
        MD5_Update(&md5, temp_buffor, strlen(temp_buffor));
        MD5_Final(wynik, &md5);

        for(int q = 0; q < password_count; q++)
        {
            if(th_reset_list[(long)id] == 1) break;
            if(shared.identified[q] == 1) continue;
            if(hashes_equal(wynik, shared.password_list[q]))
            {
                pthread_mutex_lock(&shared.mutex);
                shared.identified_password_list[shared.num_identified].password_hashed_id = q;
                shared.identified_password_list[shared.num_identified].producer_id = (long)id;
                strcpy(shared.identified_password_list[shared.num_identified].password_real, temp_buffor);
                shared.num_identified++;
                shared.num_ready++;
                pthread_cond_signal(&shared.cond);
                pthread_mutex_unlock(&shared.mutex);
            }
        }
        cur_dic_word++;
        if(cur_dic_word >= dictionary_word_count)
        {
            with_number_flag = 1;
            cur_dic_word = 0;
            cur_number++;
        }
    }
}

void* producent_3(void* id)
{
    MD5_CTX md5;
    uint8_t wynik[16];
    uint8_t with_number_flag = 0;
    char    temp_buffor[500];
    char    temp_buffor_small[100];
    int     cur_number = 0;
    int     cur_dic_word1 = 0;
    int     cur_dic_word2 = 0;

    while(1)
    {
        if(th_reset_list[(long)id] == 1)
        { 
            cur_dic_word1 = 0;
            cur_dic_word2 = 0;
            cur_number = 0;
            with_number_flag = 0;
            th_reset_list[(long)id] = 0;
        }

        temp_buffor_small[0] = '\0';
        strcat(temp_buffor_small, shared.dictionary[cur_dic_word1]);
        strcat(temp_buffor_small, shared.dictionary[cur_dic_word2]);
        if(with_number_flag)
            sprintf(temp_buffor, "%d%s%d", cur_number, temp_buffor_small, cur_number);
        else 
            strcpy(temp_buffor, temp_buffor_small);
        
        MD5_Init(&md5);
        MD5_Update(&md5, temp_buffor, strlen(temp_buffor));
        MD5_Final(wynik, &md5);

        for(int q = 0; q < password_count; q++)
        {
            if(th_reset_list[(long)id] == 1) break;
            if(shared.identified[q] == 1) continue;
            if(hashes_equal(wynik, shared.password_list[q]))
            {
                pthread_mutex_lock(&shared.mutex);
                shared.identified_password_list[shared.num_identified].password_hashed_id = q;
                shared.identified_password_list[shared.num_identified].producer_id = (long)id;
                strcpy(shared.identified_password_list[shared.num_identified].password_real, temp_buffor);
                shared.num_identified++;
                shared.num_ready++;
                pthread_cond_signal(&shared.cond);
                pthread_mutex_unlock(&shared.mutex);
            }
        }
        cur_dic_word1++;
        if(cur_dic_word1 >= dictionary_word_count)
        {
            cur_dic_word1 = 0;
            cur_dic_word2++;
        }
        if(cur_dic_word2 >= dictionary_word_count)
        {
            with_number_flag = 1;
            cur_dic_word1 = 0;
            cur_dic_word2 = 0;
            cur_number++;
        }
    }
}

void* producent_4(void* id)
{
    MD5_CTX md5;
    uint8_t wynik[16];
    uint8_t with_number_flag = 0;
    char    temp_buffor[500];
    char    temp_buffor_small[100];
    char    temp_buffor_small_1[50];
    char    temp_buffor_small_2[50];
    int     cur_number = 0;
    int     cur_dic_word1 = 0;
    int     cur_dic_word2 = 0;

    while(1)
    {
        if(th_reset_list[(long)id] == 1)
        { 
            cur_dic_word1 = 0;
            cur_dic_word2 = 0;
            cur_number = 0;
            with_number_flag = 0;
            th_reset_list[(long)id] = 0;
        }

        strcpy(temp_buffor_small_1, shared.dictionary[cur_dic_word1]);
        strcpy(temp_buffor_small_2, shared.dictionary[cur_dic_word2]);
        temp_buffor_small_1[0] = toupper(temp_buffor_small_1[0]);
        temp_buffor_small_2[0] = toupper(temp_buffor_small_2[0]);
        temp_buffor_small[0] = '\0';
        strcat(temp_buffor_small, temp_buffor_small_1);
        strcat(temp_buffor_small, temp_buffor_small_2);
        if(with_number_flag)
            sprintf(temp_buffor, "%d%s%d", cur_number, temp_buffor_small, cur_number);
        else 
            strcpy(temp_buffor, temp_buffor_small);
        
        MD5_Init(&md5);
        MD5_Update(&md5, temp_buffor, strlen(temp_buffor));
        MD5_Final(wynik, &md5);

        for(int q = 0; q < password_count; q++)
        {
            if(th_reset_list[(long)id] == 1) break;
            if(shared.identified[q] == 1) continue;
            if(hashes_equal(wynik, shared.password_list[q]))
            {
                pthread_mutex_lock(&shared.mutex);
                shared.identified_password_list[shared.num_identified].password_hashed_id = q;
                shared.identified_password_list[shared.num_identified].producer_id = (long)id;
                strcpy(shared.identified_password_list[shared.num_identified].password_real, temp_buffor);
                shared.num_identified++;
                shared.num_ready++;
                pthread_cond_signal(&shared.cond);
                pthread_mutex_unlock(&shared.mutex);
            }
        }
        cur_dic_word1++;
        if(cur_dic_word1 >= dictionary_word_count)
        {
            cur_dic_word1 = 0;
            cur_dic_word2++;
        }
        if(cur_dic_word2 >= dictionary_word_count)
        {
            with_number_flag = 1;
            cur_dic_word1 = 0;
            cur_dic_word2 = 0;
            cur_number++;
        }
    }
}

void* producent_5(void* id)
{
    MD5_CTX md5;
    uint8_t wynik[16];
    uint8_t with_number_flag = 0;
    char    temp_buffor[500];
    char    temp_buffor_small[100];
    char    temp_buffor_small_1[50];
    char    temp_buffor_small_2[50];
    int     cur_number = 0;
    int     cur_dic_word1 = 0;
    int     cur_dic_word2 = 0;

    while(1)
    {
        if(th_reset_list[(long)id] == 1)
        { 
            cur_dic_word1 = 0;
            cur_dic_word2 = 0;
            cur_number = 0;
            with_number_flag = 0;
            th_reset_list[(long)id] = 0;
        }

        strcpy(temp_buffor_small_1, shared.dictionary[cur_dic_word1]);
        strcpy(temp_buffor_small_2, shared.dictionary[cur_dic_word2]);
        for(int a = 0; a < strlen(temp_buffor_small_1); a++)
            temp_buffor_small_1[a] = toupper(temp_buffor_small_1[a]);
        for(int b = 0; b < strlen(temp_buffor_small_2); b++)   
            temp_buffor_small_2[b] = toupper(temp_buffor_small_2[b]);
        temp_buffor_small[0] = '\0';
        strcat(temp_buffor_small, temp_buffor_small_1);
        strcat(temp_buffor_small, temp_buffor_small_2);
        if(with_number_flag)
            sprintf(temp_buffor, "%d%s%d", cur_number, temp_buffor_small, cur_number);
        else 
            strcpy(temp_buffor, temp_buffor_small);
        
        MD5_Init(&md5);
        MD5_Update(&md5, temp_buffor, strlen(temp_buffor));
        MD5_Final(wynik, &md5);

        for(int q = 0; q < password_count; q++)
        {
            if(th_reset_list[(long)id] == 1) break;
            if(shared.identified[q] == 1) continue;
            if(hashes_equal(wynik, shared.password_list[q]))
            {
                pthread_mutex_lock(&shared.mutex);
                shared.identified_password_list[shared.num_identified].password_hashed_id = q;
                shared.identified_password_list[shared.num_identified].producer_id = (long)id;
                strcpy(shared.identified_password_list[shared.num_identified].password_real, temp_buffor);
                shared.num_identified++;
                shared.num_ready++;
                pthread_cond_signal(&shared.cond);
                pthread_mutex_unlock(&shared.mutex);
            }
        }
        cur_dic_word1++;
        if(cur_dic_word1 >= dictionary_word_count)
        {
            cur_dic_word1 = 0;
            cur_dic_word2++;
        }
        if(cur_dic_word2 >= dictionary_word_count)
        {
            with_number_flag = 1;
            cur_dic_word1 = 0;
            cur_dic_word2 = 0;
            cur_number++;
        }
    }
}

void* konsument(void* id)
{
    int q = 0;
    while(1)
    {
        pthread_mutex_lock(&shared.mutex);
        while(shared.num_ready == 0)
            pthread_cond_wait(&shared.cond, &shared.mutex);
        if(th_reset_list[(long)id] == 1)
        {
            q = 0; 
            th_reset_list[(long)id] = 0;
            pthread_mutex_unlock(&shared.mutex);
            continue;
        }
        shared.num_ready--;
        shared.identified[shared.identified_password_list[q].password_hashed_id] = 1;
        pthread_mutex_unlock(&shared.mutex);

        printf("Znaleziono! [producent %d]: ", shared.identified_password_list[q].producer_id - 1);
        for(int i = 0; i < 16; i++)
        {
            printf("%02hhx", shared.password_list[shared.identified_password_list[q].password_hashed_id][i]);
        }
        printf(" = %s\n", shared.identified_password_list[q].password_real);
        q++;
    }
}

void sighup_handler(int sig)
{
    printf("Podsumowanie: Na %d wczytanych haseł, odkodowano %d haseł [ %f%% ]\n", password_count, shared.num_identified,
          ((float) shared.num_identified / password_count)*100.);
}

int main()
{
    signal(SIGHUP, sighup_handler);

    pthread_mutex_init(&shared.mutex, NULL);
    pthread_cond_init(&shared.cond, NULL);

    init_uint8_arrays(shared.identified, PASSWORD_AMOUNT, 0);
    init_uint8_arrays(th_reset_list, THREADS_AMOUNT, 0);

    load_dictionary2(&dictionary_word_count, &shared.dictionary);
    load_password_list2("passwords", &password_count, &shared.password_list);

    pthread_create(&th_producent5_2word, NULL, producent_5, (void*) 6);
    pthread_create(&th_producent4_2word, NULL, producent_4, (void*) 5);
    pthread_create(&th_producent3_2word, NULL, producent_3, (void*) 4);
    pthread_create(&th_producent2,  NULL, producent_2, (void*) 3);
    pthread_create(&th_producent1, NULL, producent_1, (void*) 2);
    pthread_create(&th_producent0, NULL, producent_0, (void*) 1);
    pthread_create(&th_konsument, NULL, konsument, (void*) 0);

    char password_file_name[50];
    while(1)
    {
        scanf("%s", password_file_name);
        load_password_list2(password_file_name, &password_count, &shared.password_list);
        pthread_mutex_lock(&shared.mutex);
        shared.num_identified = 0;
        shared.num_ready = 0;
        init_uint8_arrays(shared.identified, PASSWORD_AMOUNT, 0);
        init_uint8_arrays(th_reset_list, THREADS_AMOUNT, 1);
        pthread_mutex_unlock(&shared.mutex);
    }
    
    for(int q = 0; q < dictionary_word_count; q++)
    {
        free(shared.dictionary[q]);
    }
    free(shared.dictionary);
}