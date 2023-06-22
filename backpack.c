#include "backpack.h"
#include <stdlib.h>
struct backpack *create_backpack(const int capacity)
{
    if (capacity < 0)
        return NULL;

    struct backpack *backpack = calloc(1, sizeof(struct backpack));
    if (!backpack)
        return NULL;
    backpack->capacity = capacity;
    backpack->size = 0;
    backpack->items = NULL;

    return backpack;
}

struct backpack *destroy_backpack(struct backpack *backpack)
{
    if (!backpack)
        return NULL;
    backpack->items = destroy_containers(backpack->items);
    free(backpack);
    backpack = NULL;

    return NULL;
}

bool add_item_to_backpack(struct backpack *backpack, struct item *item)
{
    if (!backpack || backpack->size + 1 > backpack->capacity)
        return false;
    if (!backpack->items)
    {
        backpack->items = create_container(NULL, ITEM, item);
        if (!backpack->items)
            return false;
    }
    else if (!create_container(backpack->items, ITEM, item))
        return false;
    ++backpack->size;
    return true;
}

void delete_item_from_backpack(struct backpack *backpack, struct item *item)
{
    if (!backpack || !item || !backpack->items || backpack->size == 0)
        return;

    struct container *current = backpack->items;
    if (current->item == item)
    {
        backpack->items = current->next;
        free(current);
        --backpack->size;

        return;
    }
    while (current->next)
    {
        if (current->next->item == item)
        {
            struct container *temp = current->next->next;
            free(current->next);
            --backpack->size;
            current->next = temp;
            break;
        }
        current = current->next;
    }
}

struct item *get_item_from_backpack(const struct backpack *backpack,
                                    char *name)
{
    if (backpack)
        return (struct item *)get_from_container_by_name(
            backpack->items, name);
    return NULL;
}