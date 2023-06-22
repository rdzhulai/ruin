#include "game.h"
#include "world.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 10
#define INITIAL_ROOM "The Dilapidated Study"

bool is_solved(struct game *game)
{
    if (strcmp(game->current_room->name, "The Fort Haven") == 0)
    {
        if (get_item_from_room(game->current_room, "Canned Food"))
        {
            if (get_item_from_room(game->current_room, "Water Bottle"))
            {
                if (get_item_from_room(game->current_room, "First Aid Kit") ||
                    get_item_from_room(game->current_room, "Vial of Medicine"))
                    return true;
            }
        }
    }
    return false;
}

void play_game(struct game *game)
{
    if (!game || !game->parser || !game->world || !game->current_room)
        return;
    char input[INPUT_BUFFER_SIZE];
    struct command *command;
    while (game->state != GAMEOVER && game->state != SOLVED)
    {
        if (game->state == RESTART)
        {
            game = destroy_game(game);
            game = create_game();
            if (!game)
                return;
            game->state = PLAYING;
        }

        while (game->state == PLAYING)
        {
            if (is_solved(game))
            {
                printf("As you place the requested supplies outside the gate, you wait anxiously for a response. Moments later, the sentinel in the guard post notices your offering. They signal for you to step back and wait. After a few tense minutes, the gate creaks open, and a fellow survivor emerges to inspect the goods. The survivor eyes the supplies, examining them closely. After a brief evaluation, they nod in approval and gesture for you to enter. You step through the gate, feeling a mix of relief and anticipation. Inside Fort Haven, you find yourself in a secure compound bustling with activity. People are going about their daily tasks, some tending to crops in a makeshift garden, while others are gathered around a communal fire pit, sharing stories and camaraderie. The atmosphere is surprisingly warm and welcoming, a stark contrast to the harsh world outside. You take in the surroundings of Fort Haven. The compound is well-organized, with several buildings serving different purposes. There's a central building that appears to be a mess hall and communal area, where people gather for meals and socializing. Nearby, you see a medical tent and a workshop where repairs and maintenance are carried out. Further, into the compound, there are living quarters and storage facilities. It's clear that Fort Haven is a self-sustaining community, with its residents working together to survive and thrive. Feeling a sense of belonging, you approach a group of residents in the communal area and strike up a conversation. They warmly welcome you, curious about your journey and background. As you share your experiences and skills, they express gratitude for your willingness to contribute. During the conversation, you learn more about the daily life in Fort Haven. The community follows a structured schedule to ensure everyone's needs are met. They have designated times for meals, work shifts, rest, and recreational activities. Additionally, they emphasize cooperation, resource sharing, and mutual support. As the conversation continues, you express your need for shelter and inquire about available accommodations. One of the residents offers to show you to an empty living quarters building where you can settle in. You follow the resident through the bustling compound, passing by various structures and communal areas. Eventually, you arrive at a modest building with several individual rooms. The resident opens one of the doors, revealing a small but comfortable living space with a bed, a small desk, and a storage chest. You express your gratitude to the resident for their assistance and for providing you with a place to stay. They assure you that the community is built on mutual support and that they are happy to help fellow survivors. With a sense of relief, you settle into your new living quarters. It's a stark contrast to the harsh world outside, offering safety, shelter, and the opportunity to rebuild your life within the fortified walls of Fort Haven.\n");
                game->state = SOLVED;
                break;
            }

            fgets(input, INPUT_BUFFER_SIZE, stdin);
            command = parse_input(game->parser, input);
            if (!command)
            {
                printf("Command not found\n");
                continue;
            }

            execute_command(game, command);

            if (strcmp(command->name, "NAHRAJ") != 0 &&
                strcmp(command->name, "ULOZ") != 0)
            {
                if (!game->parser->history)
                    game->parser->history = create_container(NULL, COMMAND, command);
                else
                    create_container(game->parser->history, COMMAND, command);
            }
        }
    }
}

struct game *create_game()
{
    struct game *game = calloc(1, sizeof(struct game));
    if (!game)
        return NULL;
    game->backpack = create_backpack(CAPACITY);
    game->parser = create_parser();
    game->world = create_world();
    game->current_room = get_room(game->world, INITIAL_ROOM);
    game->state = PLAYING;

    if (!game->backpack || !game->parser ||
        !game->world || !game->current_room)
        game = destroy_game(game);

    return game;
}

struct game *destroy_game(struct game *game)
{
    if (!game)
        return NULL;
    game->backpack = destroy_backpack(game->backpack);
    game->parser = destroy_parser(game->parser);
    game->world = destroy_world(game->world);
    free(game);
    game = NULL;
    return NULL;
}

bool use_item(char *name, struct game *game)
{
    struct item *item = get_item_from_backpack(game->backpack, name);
    bool use_from_bp = (bool)item;
    if (!use_from_bp)
        item = get_item_from_room(game->current_room, name);
    if (!item)
        return false;

    if (strcmp(item->name, "Canned Food") == 0)
    {
        printf("You decide to open one of the cans of canned food from your inventory. It provides a convenient and easily consumable source of sustenance. As you open the can, the aroma of preserved food fills the air, making your stomach grumble with anticipation. You quickly eat the contents, feeling nourished and reenergized. After finishing your meal, you dispose of the empty can responsibly.\n");
        if (use_from_bp)
            delete_item_from_backpack(game->backpack, item);
        else
            delete_item_from_room(game->current_room, item);
        return true;
    }
    if (strcmp(item->name, "First Aid Kit") == 0)
    {
        printf("You take a moment to assess your small injury and decide to use the first aid kit to tend to it. Opening the kit, you locate the appropriate supplies. Carefully, you clean the wound with an antiseptic wipe, ensuring it's free from any potential bacteria. Next, you retrieve a sterile bandage from the kit and carefully apply it to the injury, providing protection and promoting healing. With the first aid kit's assistance, you effectively address your small injury, allowing it to heal properly and minimizing any discomfort or risk of infection.\n");
        if (use_from_bp)
            delete_item_from_backpack(game->backpack, item);
        else
            delete_item_from_room(game->current_room, item);
        return true;
    }
    if (strcmp(item->name, "Vial of Medicine") == 0)
    {
        printf("The label on the vial indicates that it contains painkillers, which could be useful for managing any discomfort or pain you may be experiencing. Following the instructions provided, you open the vial and consume the appropriate dosage of the medicine. You feel a sense of relief as the medicine takes effect, easing any pain and allowing you to continue your journey with greater comfort and mobility.\n");
        if (use_from_bp)
            delete_item_from_backpack(game->backpack, item);
        else
            delete_item_from_room(game->current_room, item);
        return true;
    }
    if (strcmp(item->name, "Water Bottle") == 0)
    {
        printf("Recognizing the importance of staying hydrated, you grab the bottle filled with clean drinking water. You unscrew the cap and take a refreshing sip of the water, quenching your thirst and replenishing your body. The coolness of the water revitalizes you, providing a much-needed boost of energy.\n");
        if (use_from_bp)
            delete_item_from_backpack(game->backpack, item);
        else
            delete_item_from_room(game->current_room, item);
        return true;
    }
    if (strcmp(item->name, "Flashlight") == 0)
    {
        printf("You grasp the flashlight firmly in your hand and press the power button. A bright beam of light illuminates the area ahead, cutting through the darkness and revealing the details of your surroundings. With the flashlight guiding your way, you feel more confident and prepared to navigate through any dimly lit areas or explore the depths of the unknown.\n");
        return true;
    }
    if (strcmp(item->name, "Rusted Key") == 0)
    {
        if (strcmp(game->current_room->name, "The Narrow Hallway") != 0)
            return false;
        printf("Since the door at the end of the hallway appears to be locked, you decide to use the rusted key from your inventory. You insert the key into the keyhole and give it a turn. Surprisingly, the key fits perfectly, and the lock clicks open.\n");
        if (use_from_bp)
            delete_item_from_backpack(game->backpack, item);
        else
            delete_item_from_room(game->current_room, item);
        return true;
    }
    if (strcmp(item->name, "Copper Key") == 0)
    {
        if (strcmp(game->current_room->name, "The Looted Convenience") != 0)
            return false;
        printf("You insert the key into the lock of the door behind the counter and turn it. The lock clicks, and the door swings open, revealing a dimly lit storage area.\n");
        if (use_from_bp)
            delete_item_from_backpack(game->backpack, item);
        else
            delete_item_from_room(game->current_room, item);
        return true;
    }
    if (strcmp(item->name, "Revolver") == 0)
    {
        if (strcmp(game->current_room->name, "The Narrow Hallway") == 0)
        {
            printf("With precision, you deftly aim the revolver at the lock securing the south door, expertly pulling the trigger. The resounding shot shatters the lock, causing the door to swing open effortlessly, granting you access to the other side.\n");
        }
        else if (strcmp(game->current_room->name, "The Storefront") == 0)
        {
            printf("You raise your revolver and take aim at the nearest walker. With a steady hand, you squeeze the trigger, and a loud gunshot reverberates through the street. The walker's head explodes, showering the ground with blood and brain matter. The other walkers pause momentarily, momentarily disoriented by the sudden noise. Taking advantage of the distraction, you quickly move past the remaining walkers.\n");
            // game->current_room->west->east = game->current_room->east;
            // game->current_room->east->west = game->current_room->west;
            // game->current_room = game->current_room->east;
        }
        else if (strcmp(game->current_room->name,
                        "The Abandoned Campsite") == 0)
        {
            printf("You swiftly draw your trusty revolver, its worn grip fitting perfectly in your hand. With a hardened gaze, you lock onto a walker's decaying face, its lifeless eyes fixated on your warm flesh. Steadying your breath, you squeeze the trigger, the sharp crack of the gunshot slicing through the air. The walker crumples to the ground, its threat eliminated in a single precise shot. The other walkers, alerted by the disturbance, twist their twisted bodies toward you, their moans of hunger growing louder. Adrenaline surges through your veins as you prepare to defend yourself against this relentless horde. Each subsequent shot finds its mark, as you methodically take down the remaining walkers, their twisted forms falling to the ground like marionettes with severed strings. The echoes of your gunshots reverberate through the campsite, shattering the stillness of the night and serving as a stark reminder of the post-apocalyptic world in which you now exist. Suddenly, you hear a cry from the bushes on the west.\n");
        }
        else if (strcmp(game->current_room->name,
                        "The Sorrowful Wilderness") == 0)
        {
            printf("Guilt and sorrow consume you as you gaze into her eyes, witnessing the devastation that surrounds her. The weight of her cursed existence, the agony of her past, bears down upon us both. With a mix of sorrow and resolve, as you raise my weapon, memories of her whispered story flash through my mind. Her family, desperate for safety, had sought refuge in a nearby shelter, only to be turned away. The survivors inside, consumed by fear and scarcity, had denied them entry, leaving them to fend for themselves in the face of the undead.\nIn one swift, heart-wrenching motion, you bring an end to her torment. Her body crumples to the ground, and a chilling stillness settles upon the desolate landscape. The moans of the undead continue, an unrelenting reminder of the tragedy that unfolds in this nightmarish realm.\nYou stand amidst the carnage, haunted by the faces of those lost, the shelter that denied them, and the cruelty that permeates this forsaken world. The heaviness of their stories lingers in the air, a testament to the depths of human desperation and the horrors it begets.\nAs I retreat from the chilling scene, the weight of their lives lost settles upon me. Their story, etched in my memory, serves as a grim reminder of the fragility of humanity and the fragility of hope. Each step I take is burdened by the knowledge that even in the face of unimaginable horror, there are those who would forsake compassion for self-preservation.\n");
        }
        else if (strcmp(game->current_room->name, "The Fort Haven") == 0)
        {
            printf("As the tense silence hung in the air, you took a deep breath and gripped your trusty revolver tightly, determination etched onto your face. Your finger curled around the trigger, a bead of sweat trickling down your temple. The echoes of your heartbeat reverberated in your ears as time seemed to slow. With a resounding blast, the revolver erupted, its thunderous report shattering the stillness. The bullet found its mark, piercing the sentinel's armor, and with a bone-rattling crash, it plummeted from its lofty perch, a lifeless hulk crashing to the ground below. The chilling sound of the gunshot reverberated through the desolate landscape, reaching the ears of the walking dead that lurked nearby. They had once been human, now reduced to mindless predators driven by insatiable hunger. Sensing the commotion, their decaying limbs began to shuffle in your direction, an unholy army thirsting for flesh. But that was not the only threat unleashed by the gunshot.\nThe sound of your gunshot had also carried across the wind, reaching the ears of the survivors dwelling within Fort Haven. The walls of Fort Haven bristled with armed defenders, their weapons erupting in a symphony of fire and fury. Streams of deadly projectiles arced through the air, seeking to silence the perceived threat that stood beyond their gates.\nThe sky erupted in a storm of bullets, raining down upon you with deadly intent. Each bullet became a harbinger of death, tearing into your body with savage precision. Pain erupted within you, fierce and unrelenting, as your leg and shoulder became a canvas painted in crimson agony. Each searing impact threatened to shatter your resolve, but you refused to yield.\nDesperation clawed at your every thought as the walkers drew closer, their moans of hunger growing louder with every step. Blood stained the ground beneath you, your strength waning with each passing moment. Your vision blurred, the world tilting and spinning as the weight of the situation bore down upon you. Every fiber of your being screamed for escape, for a chance at survival. But your crippled body betrayed you, rendering you immobile, trapped within the jaws of fate. The ravenous undead descended upon you, their fetid breath and gnashing teeth filling the air. You fought valiantly, but it was a battle you could not win. The darkness swallowed you whole, consuming your final moments in a tragic symphony of pain and despair. The game had reached its inevitable conclusion, and in this cruel world, you had succumbed to its unforgiving nature. Game over. You had lost the game, forever joining the ranks of the fallen.\n");
            game->state = GAMEOVER;
        }
        else
            return false;

        return true;
    }

    return false;
}

void execute_command(struct game *game, struct command *command)
{
    if (!game || !command)
        return;
    struct container *current;
    struct item *item;
    // FILE *fp;

    if (strcmp(command->name, "KONIEC") == 0)
    {
        game->state = GAMEOVER;
    }
    else if (strcmp(command->name, "SEVER") == 0)
    {
        if (game->current_room->north)
            game->current_room = game->current_room->north;
    }
    else if (strcmp(command->name, "JUH") == 0)
    {
        if (game->current_room->south)
            game->current_room = game->current_room->south;
    }
    else if (strcmp(command->name, "VYCHOD") == 0)
    {
        if (game->current_room->east)
            game->current_room = game->current_room->east;
    }
    else if (strcmp(command->name, "ZAPAD") == 0)
    {
        if (game->current_room->west)
            game->current_room = game->current_room->west;
    }
    else if (strcmp(command->name, "ROZHLIADNI SA") == 0)
    {
        show_room(game->current_room);
    }
    else if (strcmp(command->name, "PRIKAZY") == 0)
    {
        current = game->parser->commands;
        while (current)
        {
            printf("# %s\n", current->command->name);
            printf("%s\n", current->command->description);
            current = current->next;
        }
    }
    else if (strcmp(command->name, "VERZIA") == 0)
    {
        printf("0.1v\n");
        printf("Created by Roman Dzhulai\n");
        printf("Hit me up via email if you've got any questions: rdzhulai@gmail.com\n");
    }
    else if (strcmp(command->name, "RESTART") == 0)
    {
        game->state = RESTART;
    }
    else if (strcmp(command->name, "O HRE") == 0)
    {
        printf("You find yourself in a post-apocalyptic world, overrun by walkers. As a survivor, you must navigate through dangerous territories, scavenge for supplies, and make crucial decisions to ensure your survival. Your journey begins in a small abandoned house.\n");
        printf("To uncover the list of commands at your disposal, go ahead and type \"PRIKAZY\".\n");
    }
    else if (strcmp(command->name, "VEZMI") == 0)
    {
        item = get_item_from_room(game->current_room, command->groups[1]);
        if (!item)
            printf("Neviem, čo chceš vziať.\n");
        else
        {
            if (add_item_to_backpack(game->backpack, item))
                delete_item_from_room(game->current_room, item);
            else
                printf("Backpack je plný.\n");
        }
    }
    else if (strcmp(command->name, "INVENTAR") == 0)
    {

        current = game->backpack->items;
        if (!current)
        {
            printf("You check your inventory. So far, you have no items in it.\n");
        }
        else
        {
            printf("You check your inventory. So far, you have the following items:\n");
            int count = 1;
            while (current)
            {
                printf("\t%d. %s\n", count++, current->item->name);
                current = current->next;
            }
        }
    }
    else if (strcmp(command->name, "POLOZ") == 0)
    {
        item = get_item_from_backpack(game->backpack, command->groups[1]);
        if (!item)
            printf("Neviem, čo chceš položiť.\n");
        else
        {
            add_item_to_room(game->current_room, item);
            delete_item_from_backpack(game->backpack, item);
        }
    }
    else if (strcmp(command->name, "POUZI") == 0)
    {
        if (!use_item(command->groups[1], game))
            printf("Neviem, čo chceš položiť.\n");
    }
    else if (strcmp(command->name, "PRESKUMAJ") == 0)
    {
        item = get_item_from_backpack(game->backpack, command->groups[1]);
        if (!item)
            item = get_item_from_room(game->current_room, command->groups[1]);
        if (!item)
            printf("Neviem, čo chceš preskúmať.\n");
        else
            printf("%s\n", item->description);
    }
    // else if (strcmp(command->name, "ULOZ") == 0)
    // {
    //     fp = fopen((bool)command->groups[1] ? command->groups[1] : "game_backup", "w");
    //     if (!fp)
    //         printf("No such file or directory./n");
    //     fwrite(&game, sizeof(game), 1, fp) != 1 else if ()
    //                                               printf("Could not write to the file.\n");
    //     else printf("Game was saved to the file.\n");
    //     fclose(fp);
    // }
    // else if (strcmp(command->name, "NAHRAJ") == 0)
    // {
    //     fp = fopen((bool)command->groups[1] ? command->groups[1] : "game_backup", "r");
    //     if (!fp)
    //         printf("No such file or directory./n");
    //     else if (fread(&game, sizeof(game), 1, fp) != 1)
    //         printf("Could not read from the file.\n");
    //     else
    //         printf("Game was loaded from the file.\n");
    //     fclose(fp);
    // }
}