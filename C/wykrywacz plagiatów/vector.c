#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector.h"
int create(struct array_t *a, int N)
{
    if(a == NULL || N < 1) return 1;

    a->ptr = (float*)malloc(N * sizeof(float));
    if(a->ptr == NULL) return 2;

    a->size = 0;
    a->capacity = N;
    return 0;
}
int add(struct array_t *a, float value)
{
    if(a == NULL) return 1;
    if(a->capacity == a->size) return 2;

    *(a->ptr + a->size) = value;
    a->size++;
    return 0;
}
void destroy(struct array_t *a)
{
    if(a == NULL) return;
    free(a->ptr);
}
int create_array(struct array_t **a, int N)
{
    if(a == NULL || N < 1) return 1;

    *a = (struct array_t*)malloc(sizeof(struct array_t));
    if(*a == NULL) return 2;

    (*a)->ptr = (float*)malloc(N * sizeof(float));
    if((*a)->ptr == NULL)
    {
        free(*a);
        return 2;
    }

    (*a)->capacity = N;
    (*a)->size = 0;
    return 0;
}
void destroy_array(struct array_t **a)
{
    if(a == NULL || *a == NULL) return;
    if((*a)->ptr != NULL) free((*a)->ptr);
    free(*a);
}
float length(const struct array_t *a)
{
    int i;
    float len = 0;
    if(a == NULL || a->ptr == NULL || a->capacity <= 0 || a->size <= 0 || a->size > a->capacity)
        return -1;

    for(i = 0; i < a->size; i++)
        len += *(a->ptr + i) * (*(a->ptr + i));

    len = sqrt(len);
    return len;
}
float dot_product(const struct array_t *a, const struct array_t *b)
{
    int i;
    float res = 0;
    if(a == NULL || a->ptr == NULL || a->capacity <= 0 || a->size <= 0 || a->size > a->capacity)
        return -1;
    if(b == NULL || b->ptr == NULL || b->capacity <= 0 || b->size <= 0 || b->size > b->capacity)
        return -1;
    if(a->size != b->size) return -1;
    for(i = 0; i < a->size; i++)
        res += *(a->ptr + i) * (*(b->ptr + i));

    return res;
}
