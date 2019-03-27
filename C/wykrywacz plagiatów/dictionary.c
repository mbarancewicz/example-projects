#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"
struct dictionary_t* create_dictionary(int N)
{
    struct dictionary_t* ptr;
    if(N < 1) return NULL;

    ptr = NULL;
    ptr = (struct dictionary_t*)malloc(sizeof(struct dictionary_t));
    if(ptr == NULL) return NULL;

    ptr->wc = NULL;
    ptr->wc = (struct word_count_t*)malloc(N * sizeof(struct word_count_t));
    if(ptr->wc == NULL)
    {
        free(ptr);
        return NULL;
    }

    ptr->capacity = N;
    ptr->size = 0;

    return ptr;
}
void destroy_dictionary(struct dictionary_t** d)
{
    int i;
    if(d == NULL) return;
    if((*d)->capacity < 1 || (*d)->size < 0 || (*d)->size > (*d)->capacity || (*d)->wc == NULL) return;

    for(i=0; i<(*d)->size; i++)
    {
        free(((*d)->wc+i)->word);
    }
    free((*d)->wc);
    free(*d);
}
struct word_count_t* dictionary_find_word(const struct dictionary_t *d, const char *word)
{
    int i;
    if(d == NULL || word == NULL) return NULL;
    if(d->capacity < 1 || d->size < 0 || d->size > d->capacity || d->wc == NULL) return NULL;

    for(i=0; i<d->size; i++)
    {
        if((d->wc+i)->word == NULL) return NULL;
        if((d->wc+i)->counter < 1) return NULL;

        if(strcmp((d->wc+i)->word, word) == 0) return (d->wc+i);
    }
    return NULL;
}
void dictionary_display(const struct dictionary_t *d)
{
    int i;
    if(d == NULL) return;
    if(d->capacity < 1 ||  d->size < 0 || d->size > d->capacity || d->wc == NULL) return;

    for(i=0; i<d->size; i++)
    {
        if((d->wc+i)->word == NULL) return;
        if((d->wc+i)->counter < 1) return;
    }

    for(i=0; i<d->size; i++)
    {
        printf("%s %d\n", (d->wc+i)->word, (d->wc+i)->counter);
    }
}
int dictionary_add_word(struct dictionary_t *d, const char *word)
{
    struct word_count_t* found_word;
    struct dictionary_t* new_ptr;

    if(d == NULL || word == NULL || strlen(word) == 0) return 1;
    if(d->capacity < 1 || d->size < 0 || d->size > d->capacity || d->wc == NULL) return 1;

    found_word = dictionary_find_word((const struct dictionary_t*)d , word);

    if(found_word == NULL)
    {
        if(d->size == d->capacity)
        {
            new_ptr = NULL;
            new_ptr = (struct dictionary_t*)malloc(sizeof(struct dictionary_t));
            if(new_ptr == NULL) return 2;

            new_ptr->wc = NULL;
            new_ptr->wc = (struct word_count_t*)realloc(d->wc, 2 * d->capacity * sizeof(struct word_count_t));
            if(new_ptr->wc == NULL)
            {
                free(new_ptr);
                return 2;
            }

            d->wc = new_ptr->wc;
            d->capacity *= 2;

            free(new_ptr);
        }

        (d->wc+d->size)->word = (char*)malloc(((int)strlen(word) + 1) * sizeof(char));
        if((d->wc+d->size)->word == NULL) return 2;

        strcpy((d->wc+d->size)->word, word);
        (d->wc+d->size)->counter = 1;

        d->size++;
    }
    else
    {
        found_word->counter++;
    }
    return 0;
}
