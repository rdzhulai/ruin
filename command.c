#include "command.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct command *create_command(char *name, char *description, char *pattern, size_t nmatch)
{
    if (!name || !description || strlen(name) == 0 || strlen(description) == 0)
        return NULL;

    struct command *new_command = calloc(1, sizeof(struct command));
    if (!new_command)
    {
        return NULL;
    }
    new_command->nmatch = nmatch;
    size_t name_length = strlen(name) + 1;
    new_command->name = calloc(1, name_length);
    new_command->name = memcpy(new_command->name, name, name_length);
    size_t description_length = strlen(description) + 1;
    new_command->description = calloc(1, description_length);
    memcpy(new_command->description, description, description_length);
    if (pattern)
    {
        new_command->groups = calloc(nmatch, sizeof(char *));
        int res = regcomp(&new_command->preg, pattern, REG_EXTENDED | REG_ICASE);
        if (!new_command->groups || res != 0)
        {
            new_command = destroy_command(new_command);
            return NULL;
        }
    }
    if (!new_command->name || !new_command->description)
    {
        new_command = destroy_command(new_command);
        return NULL;
    }

    return new_command;
}

struct command *destroy_command(struct command *command)
{
    if (!command)
        return NULL;

    free(command->name);
    command->name = NULL;
    free(command->description);
    command->description = NULL;
    regfree(&command->preg);

    if (command->groups)
    {
        for (size_t i = 0; i < command->nmatch; ++i)
        {
            free(command->groups[i]);
            command->groups[i] = NULL;
        }
        free(command->groups);
        command->groups = NULL;
    }

    free(command);
    command = NULL;
    return NULL;
}
