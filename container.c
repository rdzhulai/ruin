#include "container.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int strcasecmp(const char *s1, const char *s2)
{
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);

    if (len1 != len2)
        return 1; // Strings are not equal if lengths differ

    for (size_t i = 0; i < len1; i++)
    {
        if (tolower(s1[i]) != tolower(s2[i]))
            return 1; // Strings are not equal
    }

    return 0; // Strings are equal
}

struct container *create_container(struct container *first,
                                   enum container_type type, void *entry)
{
    // Validate input arguments.
    if (!entry)
    {
        fputs("No entry data was given.\n", stderr);
        return NULL;
    }

    if (first && first->type != type)
    {
        fputs("The given type is not the same as the type of the given list items.\n", stderr);
        return NULL;
    }

    // Allocate a new container.
    struct container *new = malloc(sizeof(struct container));
    if (!new)
    {
        fputs("Memory for a container wasn't allocated.\n", stderr);
        return NULL;
    }

    // Initialize the container with given arguments.
    new->type = type;
    new->next = NULL;

    switch (type)
    {
    case ROOM:
        new->room = (struct room *)entry;
        break;
    case ITEM:
        new->item = (struct item *)entry;
        break;
    case COMMAND:
        new->command = (struct command *)entry;
        break;

    case TEXT:
    {
        size_t text_size = strlen((char *)entry) + 1;
        new->text = calloc(text_size, sizeof(char));
        if (!new->text)
        {
            free(new);
            new = NULL;
            fputs("Memory for a container text wasn't allocated.\n", stderr);
            return NULL;
        }
        new->text = strncpy(new->text, (char *)entry, text_size);
        break;
    }
    }
    // Append the container to the end of the list.
    if (first)
    {
        struct container *p = first;
        while (p->next != NULL)
            p = p->next;
        p->next = new;
    }

    // Return the newly created container.
    return new;
}

struct container *destroy_containers(struct container *first)
{
    if (first)
    {
        first->next = destroy_containers(first->next);
        switch (first->type)
        {
        case ROOM:
            first->room = destroy_room(first->room);
            break;
        case ITEM:
            first->item = destroy_item(first->item);
            break;
        case COMMAND:
            first->command = destroy_command(first->command);
            break;
        case TEXT:
            free(first->text);
            first->text = NULL;
            break;
        }
        free(first);
        first = NULL;
    }
    return NULL;
}

void *get_from_container_by_name(struct container *first, const char *name)
{
    if (!name || !first)
        return NULL;

    struct container *p = first;

    while (p)
    {
        switch (p->type)
        {
        case ROOM:
            if (p->room && !strcasecmp(p->room->name, name))
                return p->room;
            break;
        case ITEM:
            if (p->item && !strcasecmp(p->item->name, name))
                return p->item;
            break;
        case COMMAND:
            if (p->command && !strcasecmp(p->command->name, name))
                return p->command;
            break;
        case TEXT:
            if (p->text && !strcasecmp(p->text, name))
                return p->text;
            break;
        }

        p = p->next;
    }

    return NULL;
}

struct container *remove_container(struct container *first, void *entry)
{
    if (!first || !entry)
        return first;

    struct container *prev = NULL;
    struct container *current = first;
    bool found = false;

    while (current)
    {
        switch (current->type)
        {
        case ROOM:
            found = current->room == entry;
            break;
        case ITEM:
            found = current->item == entry;
            break;
        case COMMAND:
            found = current->command == entry;
            break;
        case TEXT:
            found = current->text == entry;
            break;
        }

        if (found)
        {
            if (prev)
                prev->next = current->next;
            else
                first = current->next;

            free(current);
            current = NULL;
            break;
        }

        prev = current;
        current = current->next;
    }

    return first;
}
