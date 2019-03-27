#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"
#include "vector.h"
struct dictionary_t* read_txt(FILE* fp, char* line, int line_size, struct dictionary_t* dic)
{
    char* word;
    char* delim = ". \n";

    dic = create_dictionary(1);
    if(dic == NULL)
    {
        free(line);
        fclose(fp);
        return NULL;
    }

    while(fgets(line, line_size, fp))
    {
        word = strtok(line, delim);
        if(word == NULL) continue;
        if(dictionary_add_word(dic, word) == 2)
        {
            free(line);
            fclose(fp);
            return NULL;
        }

        while(word != NULL)
        {
            word = strtok(NULL, delim);
            if(word == NULL) break;
            if(dictionary_add_word(dic, word) == 2)
            {
                free(line);
                fclose(fp);
                return NULL;
            }
        }
    }
    return dic;
}
int main()
{
    int i;
    float x;
    char* line = NULL;
    char* buffer = NULL;
    struct array_t *v1, *v2;
    struct dictionary_t *d1, *d2, *dcommon;
    FILE *fp;

    buffer = (char*)malloc(50 * sizeof(char));
    if(buffer == NULL)
    {
        printf("Failed to allocate memory");
        return 4;
    }

    line = (char*)malloc(700 * sizeof(char));
    if(line == NULL)
    {
        printf("Failed to allocate memory");
        free(buffer);
        return 2;
    }

    printf("Podaj nazweee pierwszego pliku: ");
    scanf("%s", buffer);
    if((fp = fopen(buffer, "r")) == NULL)
    {
        free(buffer);
        free(line);
        printf("File not found");
        return 2;
    }
    if((d1 = read_txt(fp, line, 700, d1)) == NULL)
    {
        free(buffer);
        printf("Failed to allocate memory");
        return 4;
    }
    fclose(fp);

    printf("Podaj nazweee drugiegoo pliku: ");
    scanf("%s", buffer);
    if((fp = fopen(buffer, "r")) == NULL)
    {
        free(buffer);
        free(line);
        destroy_dictionary(&d1);
        printf("File not found");
        return 2;
    }
    if((d2 = read_txt(fp, line, 700, d2)) == NULL)
    {
        free(buffer);
        destroy_dictionary(&d1);
        printf("Failed to allocate memory");
        return 4;
    }
    fclose(fp);

    dcommon = create_dictionary(1);
    if(dcommon == NULL)
    {
        destroy_dictionary(&d1);
        destroy_dictionary(&d2);
        free(buffer);
        free(line);
        return 4;
    }

    for(i = 0; i < d1->size; i++)
        dictionary_add_word(dcommon, (d1->wc+i)->word);
    for(i = 0; i < d2->size; i++)
        dictionary_add_word(dcommon, (d2->wc+i)->word);

    if(create_array(&v1, dcommon->size) != 0 || create_array(&v2, dcommon->size) != 0)
    {
        destroy_dictionary(&d1);
        destroy_dictionary(&d2);
        destroy_dictionary(&dcommon);
        free(buffer);
        free(line);
        return 4;
    }

    for(i = 0; i < dcommon->size; i++)
    {
        if(dictionary_find_word(d1, (dcommon->wc+i)->word) == NULL) x = 0;
        else x = (float)dictionary_find_word(d1, (dcommon->wc+i)->word)->counter / (float)d1->size;
        add(v1, x);
    }

    for(i = 0; i < dcommon->size; i++)
    {
        if(dictionary_find_word(d2, (dcommon->wc+i)->word) == NULL) x = 0;
        else x = (float)dictionary_find_word(d2, (dcommon->wc+i)->word)->counter / (float)d2->size;
        add(v2, x);
    }

    x = dot_product(v1, v2) / (length(v1) * length(v2));
    printf("Podobienstwo: %.5f", x);

    destroy_dictionary(&d1);
    destroy_dictionary(&d2);
    destroy_dictionary(&dcommon);
    destroy_array(&v1);
    destroy_array(&v2);
    free(buffer);
    free(line);
    return 0;
}
