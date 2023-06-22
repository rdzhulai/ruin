#include "parser.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

struct command_info
{
    char *name;
    char *description;
    char *pattern;
    int nmatch;
};

struct parser *create_parser()
{
    static struct command_info command_list[] = {
        {"KONIEC", "Príkaz ukončí rozohratú hru. Nastaví príslušný stav hry.",
         "^[[:space:]]*(KONIEC|QUIT|EXIT)[[:space:]]*$", 1},
        {"SEVER", "Presun do miestnosti nachádzajúcej sa na sever od aktuálnej. Zmení referenciu aktuálnej miestnosti.",
         "^[[:space:]]*(SEVER|S|NORTH)[[:space:]]*$", 1},
        {"JUH",
         "Presun do miestnosti nachádzajúcej sa na juh od aktuálnej. Zmení referenciu aktuálnej miestnosti.",
         "^[[:space:]]*(JUH|J|SOUTH)[[:space:]]*$", 1},
        {"VYCHOD",
         "Presun do miestnosti nachádzajúcej sa na východ od aktuálnej. Zmení referenciu aktuálnej miestnosti.",
         "^[[:space:]]*(VYCHOD|V|EAST)[[:space:]]*$", 1},
        {"ZAPAD",
         "Presun do miestnosti nachádzajúcej sa na západ od aktuálnej. Zmení referenciu aktuálnej miestnosti.",
         "^[[:space:]]*(ZAPAD|Z|WEST)[[:space:]]*$", 1},
        {"ROZHLIADNI SA",
         "Príkaz vypíše aktuálne informácie o miestnosti, v ktorej sa hráč práve nachádza.",
         "^[[:space:]]*(ROZHLIADNI SA|LOOK)[[:space:]]*$", 1},
        {"PRIKAZY",
         "Príkaz vypíše na obrazovku zoznam všetkých príkazov, ktoré hra poskytuje.",
         "^[[:space:]]*(PRIKAZY|HELP|POMOC)[[:space:]]*$", 1},
        {"VERZIA",
         "Príkaz zobrazí číslo verzie hry, ľubovoľný sprievodný text a meno a priezvisko autora s kontaktom (e-mailová adresa, webová stránka).",
         "^[[:space:]]*(VERZIA)[[:space:]]*$", 1},
        {"RESTART",
         "Znovu spustí hru od začiatku. Zmení stav hry na požadovaný.",
         "^[[:space:]]*(RESTART)[[:space:]]*$", 1},
        {"O HRE",
         "Príkaz zobrazí krátky text, ktorý poslúži ako úvod do príbehu",
         "^[[:space:]]*(O HRE|ABOUT)[[:space:]]*$", 1},
        {"VEZMI",
         "Vloží predmet z miestnosti do batohu. Príkaz má jeden povinný parameter, ktorým je názov predmetu.",
         "^[[:space:]]*(VEZMI|TAKE)[[:space:]]+(([[:space:]]*[A-Z])+)?[[:space:]]*$", 2},
        {"POLOZ",
         "Položí predmet z batohu do miestnosti. Príkaz má jeden povinný parameter, ktorým je názov predmetu.",
         "^[[:space:]]*(POLOZ|PLACE)[[:space:]]+(([[:space:]]*[A-Z])+)?[[:space:]]*$", 2},
        {"INVENTAR",
         "Zobrazí obsah hráčovho batohu.",
         "^[[:space:]]*(INVENTAR|I)[[:space:]]*$", 1},
        {"POUZI",
         "Použije predmet z batohu alebo miestnosti. Príkaz má jeden povinný parameter, ktorým je názov predmetu.",
         "^[[:space:]]*(POUZI|USE)[[:space:]]+(([[:space:]]*[A-Z])+)?[[:space:]]*$", 2},
        {"PRESKUMAJ",
         "Vypíše opis predmetu, ktorý sa musí nachádzať v miestnosti alebo batohu. Príkaz má jeden povinný parameter, ktorým je názov predmetu.",
         "^[[:space:]]*(PRESKUMAJ|EXAMINE)[[:space:]]+(([[:space:]]*[A-Z])+)?[[:space:]]*$", 2},
        {"NAHRAJ",
         "Príkaz zabezpečí nahratie uloženej pozície hry z disku. Voliteľným parametrom je cesta k súboru.",
         "^[[:space:]]*(NAHRAJ|LOAD)[[:space:]]+([^[:space:]]+)?[[:space:]]*$", 2},
        {"ULOZ",
         "Príkaz uloží stav rozohratej hry na disk. Voliteľným parametrom je cesta k súboru.",
         "^[[:space:]]*(ULOZ|SAVE)[[:space:]]+([^[:space:]]+)?[[:space:]]*$", 2}

    };

    struct parser *parser = calloc(1, sizeof(struct parser));
    if (!parser)
        return NULL;

    int num_commands = sizeof(command_list) / sizeof(struct command_info);

    parser->commands = create_container(NULL, COMMAND,
                                        create_command(command_list[0].name,
                                                       command_list[0].description,
                                                       command_list[0].pattern,
                                                       (size_t)command_list[0].nmatch));
    if (!parser->commands)
    {
        free(parser);
        return NULL;
    }

    for (int i = 1; i < num_commands; i++)
    {

        if (!create_container(parser->commands, COMMAND,
                              create_command(command_list[i].name,
                                             command_list[i].description,
                                             command_list[i].pattern,
                                             (size_t)command_list[i].nmatch)))
        {
            destroy_containers(parser->commands);
            free(parser);
            return NULL;
        }
    }

    parser->history = NULL;

    return parser;
}

struct parser *destroy_parser(struct parser *parser)
{
    if (parser)
    {
        destroy_containers(parser->commands);
        destroy_containers(parser->history);
        free(parser);
    }
    return NULL;
}

struct command *parse_input(struct parser *parser, char *input)
{
    if (!parser || !input)
        return NULL;

    struct container *current = parser->commands;
    while (current)
    {
        regmatch_t *matches = calloc(current->command->nmatch + 1,
                                     sizeof(regmatch_t));
        if (!matches)
            return NULL;

        if (regexec(&current->command->preg, input, current->command->nmatch + 1, matches, 0) == 0)
        {
            current->command->groups = calloc(current->command->nmatch,
                                              sizeof(char *));
            if (!current->command->groups)
            {
                free(matches);
                return NULL;
            }

            for (size_t i = 0; i < current->command->nmatch; ++i)
            {
                int start = matches[i + 1].rm_so;
                if (start == -1)
                {
                    current->command->groups[i] = NULL;
                    continue;
                }
                int end = matches[i + 1].rm_eo;
                int group_size = end - start + 1;

                current->command->groups[i] = calloc((size_t)group_size, sizeof(char));
                if (!current->command->groups[i])
                {
                    for (size_t j = 0; j <= i; ++j)
                        free(current->command->groups[j]);
                    free(current->command->groups);
                    free(matches);
                    return NULL;
                }
                snprintf(current->command->groups[i], (size_t)group_size,
                         "%s", input + start);
            }

            free(matches);
            return current->command;
        }

        free(matches);
        current = current->next;
    }

    return NULL;
}