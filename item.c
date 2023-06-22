#include "item.h"
#include <stdlib.h>
#include <string.h>

struct item *create_item(char *name, char *description, unsigned int properties)
{
    if (!name || !description || strlen(name) == 0 || strlen(description) == 0)
        return NULL;

    struct item *new_item = malloc(sizeof(struct item));
    if (!new_item)
        return NULL;

    size_t name_size = strlen(name) + 1;
    new_item->name = malloc(name_size);
    if (!new_item->name)
    {
        free(new_item);
        new_item = NULL;
        return NULL;
    }
    new_item->name = memcpy(new_item->name, name, name_size);

    size_t description_size = strlen(description) + 1;
    new_item->description = malloc(description_size);
    if (!new_item->description)
    {
        free(new_item->name);
        new_item->name = NULL;
        free(new_item);
        new_item = NULL;
        return NULL;
    }
    new_item->description = memcpy(new_item->description, description, description_size);

    new_item->properties = properties;

    return new_item;
}

struct item *destroy_item(struct item *item)
{
    free(item->name);
    item->name = NULL;
    free(item->description);
    item->description = NULL;
    free(item);
    item = NULL;

    return NULL;
}