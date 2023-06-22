#include "room.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct room *create_room(char *name, char *description)
{
    if (!name || !description || strlen(name) == 0 || strlen(description) == 0)
        return NULL;

    struct room *new_room = calloc(1, sizeof(struct room));
    if (!new_room)
        return NULL;

    size_t name_size = strlen(name) + 1;
    new_room->name = malloc(name_size);
    if (!new_room->name)
    {
        free(new_room);
        new_room = NULL;
        return NULL;
    }
    new_room->name = memcpy(new_room->name, name, name_size);

    size_t description_size = strlen(description) + 1;
    new_room->description = malloc(description_size);
    if (!new_room->description)
    {
        free(new_room->name);
        new_room->name = NULL;
        free(new_room);
        new_room = NULL;
        return NULL;
    }
    new_room->description = memcpy(new_room->description, description, description_size);

    new_room->north = NULL;
    new_room->south = NULL;
    new_room->west = NULL;
    new_room->east = NULL;

    return new_room;
}

struct room *destroy_room(struct room *room)
{
    if (room)
    {
        room->items = destroy_containers(room->items);
        free(room->name);
        room->name = NULL;
        free(room->description);
        room->description = NULL;
        free(room);
        room = NULL;
    }
    return NULL;
}

void set_exits_from_room(struct room *room, struct room *north, struct room *south, struct room *east, struct room *west)
{
    if (room)
    {
        room->north = north;
        room->south = south;
        room->west = west;
        room->east = east;
    }
}

void show_room(const struct room *room)
{
    if (!room)
        return;

    printf("# %s\n", room->name);
    printf("%s\n", room->description);
}

void delete_item_from_room(struct room *room, struct item *item)
{
    if (!room || !item || !room->items)
        return;

    struct container *current = room->items;
    if (current->item == item)
    {
        room->items = current->next;
        return;
    }
    while (current->next)
    {
        if (current->next->item == item)
        {
            struct container *temp = current->next->next;
            free(current->next);
            current->next = temp;
            break;
        }
        current = current->next;
    }
}

void add_item_to_room(struct room *room, struct item *item)
{
    if (!room || !item)
        return;
    if (!room->items)
        room->items = create_container(NULL, ITEM, item);
    else
        create_container(room->items, ITEM, item);
}

struct item *get_item_from_room(const struct room *room, const char *name)
{
    if (!room || !name || !room->items)
        return NULL;
    return (struct item *)get_from_container_by_name(room->items, name);
}