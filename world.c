#include "world.h"
#include "item.h"
#include <stdlib.h>
struct container *create_world()
{
    struct item *broken_table = create_item(
        "Broken Table", "You meticulously inspect the broken table, taking note of its sorry state. The ravages of time and neglect have left their marks, evident in the splintered wood and signs of rot. Unfortunately, there doesn't appear to be anything valuable or useful on or around the table. However, just as you were about to move on, something peculiar caught your eye—an ominous trail of blood leading under the table. Curiosity piqued, your attention shifted towards a small, half-open door situated to the north. The sight of the blood instilled a sense of caution within you.", EXAMINABLE);
    struct item *cash = create_item(
        "Cash", "Despite being stained with blood, the bills appear to be mostly intact. You estimate there is a stack of around $500 in various denominations. The money could prove useful in the post-apocalyptic world, where traditional currency might still hold some value.", MOVABLE | USABLE | EXAMINABLE);
    struct item *dusty_bookshelf = create_item(
        "Book Shelf", "You approach the dusty bookshelf and examine its contents. Most of the books have deteriorated over time, their pages yellowed and brittle. However, one book catches your eye. It's titled \"Surviving the Apocalypse: A Guide to Outsmarting Walkers.\"",
        EXAMINABLE);
    struct item *book = create_item(
        "Book", "You pick up the book titled \"Surviving the Apocalypse: A Guide to Outsmarting Walkers\" and flip through its pages. The text is faded, but you manage to find a few useful survival tips. It mentions that walkers can be distracted by loud noises and are attracted to movement. It also emphasizes the importance of stealth and resourcefulness in avoiding confrontations.", MOVABLE | EXAMINABLE);
    struct item *tattared_journal = create_item(
        "Tattared Journal", "You pick up the tattered journal from the floor and carefully open its pages. The writing is faded, but you can still make out some entries. It seems to have belonged to a previous survivor, documenting their struggles and experiences in this world.",
        MOVABLE | EXAMINABLE);
    struct item *drawer = create_item(
        "Drawer", "You approach the coffee table and examine the partially open drawer. Inside, you find a small, rusted key. It's unclear what it unlocks, but it could potentially be useful in your journey.", EXAMINABLE);
    struct item *rusted_key = create_item(
        "Rusted Key", "You pick up the rusted key and hold it in your hand, observing its worn appearance. The metal is covered in patches of rust, indicating that it has been neglected for a long time. Despite its dilapidated state, the key feels sturdy and substantial in your grasp. Its teeth are slightly jagged, suggesting that it may have been used on various locks before. As you turn the key in your hand, you wonder what it might unlock in this old, abandoned house. There could be hidden compartments, locked doors, or even a safe waiting to be opened. The mystery of the key adds to the intrigue of your exploration, filling you with a sense of anticipation.",
        MOVABLE | USABLE | EXAMINABLE);
    struct item *couch = create_item(
        "Couch", "You approach the worn-out couch and examine it more closely. The cushions are threadbare and sagging, showing signs of age and wear. It doesn't look like a comfortable place to rest, but perhaps there might be something hidden beneath the cushions. You remove the cushions from the worn-out couch, hoping to find something hidden underneath. As you lift the cushions, you discover a small pocket concealed within the lining. Inside the pocket, you find a small vial of medicine.", EXAMINABLE);
    struct item *vial_of_medicine = create_item(
        "Vial of Medicine", "The label on the vial indicates that it contains painkillers, which could be useful for managing any discomfort or pain you may be experiencing. There is also the instruction provided.",
        MOVABLE | USABLE | EXAMINABLE);
    struct item *canned_food1 = create_item(
        "Canned Food", "A few cans of preserved food that could provide nourishment during your journey.", MOVABLE | USABLE | EXAMINABLE);
    struct item *canned_food2 = create_item(
        "Canned Food", "A few cans of preserved food that could provide nourishment during your journey.", MOVABLE | USABLE | EXAMINABLE);
    struct item *flashlight = create_item(
        "Flashlight", "A reliable source of light, essential for exploring dark places or during nighttime.", MOVABLE | USABLE | EXAMINABLE);
    struct item *first_aid_kit = create_item(
        "First Aid Kit", "A well-stocked kit containing bandages, antiseptics, and other medical supplies to tend to injuries and illnesses.",
        MOVABLE | USABLE | EXAMINABLE);
    struct item *crate = create_item(
        "Crate", "You carefully open the wooden crate labeled \"Supplies\" and find a collection of useful items inside. Among them is a glass bottle filled with clean drinking water, a beautifully crafted, single-action revolver with a polished wooden handle and intricate engravings, boxes of bullets specifically designed for a revolver.", EXAMINABLE);
    struct item *water_bottle1 = create_item(
        "Water Bottle", "Several glass bottles filled with clean drinking water. Staying hydrated is crucial in the harsh post-apocalyptic world.", MOVABLE | USABLE | EXAMINABLE);
    struct item *water_bottle2 = create_item(
        "Water Bottle", "Several glass bottles filled with clean drinking water. Staying hydrated is crucial in the harsh post-apocalyptic world.", MOVABLE | USABLE | EXAMINABLE);
    struct item *revolver = create_item(
        "Revolver", "A beautifully crafted, single-action revolver with a polished wooden handle and intricate engravings. It's a classic firearm from the cowboy era, capable of providing both protection and intimidation.", MOVABLE | USABLE | EXAMINABLE);
    struct item *counter = create_item(
        "Counter", "You approach the counter and find an old cash register, its drawers already emptied. However, you notice a copper key lying next to it.", EXAMINABLE);
    struct item *copper_key = create_item(
        "Copper Key", "As you examine the key, you notice its unique characteristics. The key is relatively small and made of tarnished brass, giving it an aged appearance. The metal has acquired a subtle patina over time, adding to its weathered charm. Its teeth are not perfectly aligned, showing signs of wear and use. The key has a few nicks and scratches on its surface, evidence of its long journey through different locks and doors. Despite its age and imperfections, it still retains a sense of durability and functionality. Its rustic appearance hints at forgotten secrets and hidden paths waiting to be discovered.", MOVABLE | USABLE | EXAMINABLE);
    struct item *notice_board = create_item(
        "Notice Board", "You approach the notice board and read through the rules and regulations. It states that in order to gain entry to Fort Haven, you must present valuable resources: food, water, and medical supplies, in exchange for shelter and protection. The board also mentions that anyone attempting to force their way in will be met with forceful resistance. It's clear that Fort Haven takes its security seriously.", EXAMINABLE);
    struct room *dilapidated_study = create_room(
        "The Dilapidated Study", "You take a closer look at the room you're in. The walls are crumbling, and the floorboards creak beneath your feet. The furniture is in disarray, and there are signs of previous occupancy. The windows are boarded up, providing some sense of security from the outside world. You notice a doorway on the east leading to a narrow hallway, and another doorway on the west opens into what appears to be a living room. There is a broken table in the corner and a dusty bookshelf against the wall. A tattered journal lies on the floor.");
    struct room *bloody_gallery = create_room(
        "The Bloody Gallery", "The terrible stink is overwhelming, and it's hard to breathe. The room is small and cramped, and you can only crawl on your hands and knees. The walls are covered in scary paintings, depicting scenes of death and torture. The blood stains on the walls and floor add to the feeling of horror. As you look closer, you notice a dead, rotten body lying in the corner. It's unclear how long the body has been there, but it's clear that no one has touched it in a long time. You cautiously approach the body and notice that its pockets are filled with cash stained in blood. You can't believe your luck, but the thought of touching the rotting corpse makes you shudder.");
    struct room *living_room = create_room(
        "The Living Room", "You step through the doorway to the west and enter the living room. The air feels heavy with dust, and the furniture is covered in a thick layer of grime. You take a moment to observe your surroundings. The living room is dimly lit, with the sunlight filtering through the dusty windows.  There is a worn-out couch against one wall and a coffee table in the center of the room. The worn-out couch looks uncomfortable, but it could provide a temporary place to rest if needed. As you look around, you notice a small drawer in the coffee table. It appears to be partially open. The doorway to the east leads back to the previous room.");
    struct room *narrow_hallway = create_room(
        "The Narrow Hallway", "The air feels colder as you enter a narrow hallway. The floorboards creak beneath your weight, echoing through the empty space. You take a closer look at your surroundings in the narrow hallway. The walls are covered in peeling wallpaper, revealing layers of faded patterns. The flickering light emanates from underneath the closed door at the end of the hallway, as if someone inside the room is using a flashlight or lantern. Curiosity piques your interest, wondering what or who could be on the other side of the door. As you approach, you notice that the door is locked and there is a small keyhole, maybe you could find the key somewhere in the house. You notice that there are two other doorways in the hallway— one to the north and another to the south. As you approach the north door, you notice that it's slightly ajar, allowing a faint beam of light to escape from the room beyond. The door on the south seems to be locked from the outside.");
    struct room *stockroom = create_room(
        "The Stockroom", "You enter the room cautiously, finding yourself in a small storage area. The shelves are filled with various supplies and items, including canned food, a flashlight, and a first aid kit, giving you a glimpse of hope in this grim world. The room itself is small but well-organized, with labeled boxes and neatly arranged shelves. The faint scent of mustiness hangs in the air, a testament to the room's isolation from the outside world. The doorway to the south leads back to the previous room.");
    struct room *armory_hideout = create_room(
        "The Armory Hideout", "As you push open the door, you step into a small room illuminated by a single flickering lantern. The room appears to be a makeshift shelter, filled with supplies and personal belongings. There are a few makeshift beds against the walls, indicating that multiple people might have sought refuge here. In the corner of the room, you see a wooden crate labeled \"Ammunition.\" It seems to contain weapons and other useful items.");
    struct room *forgotten_street = create_room(
        "The Forgotten Street", "The sun beats down on you, and you shield your eyes, adjusting to the brightness. You find yourself standing in the middle of a small street, surrounded by abandoned houses and overgrown vegetation. The silence is eerie, broken only by the distant groans of walkers. You scan your surroundings, taking in the desolate street. The houses on either side of you are in varying states of disrepair, their windows shattered and doors hanging precariously on their hinges. The road stretches out ahead, cracked and overgrown with weeds. To the east, you notice a dilapidated convenience store, its windows boarded up. To the south, there's an intersection leading to a wider street. In the west direction, there is a broken car. Its once shiny exterior now covered in a layer of dirt and grime. The vehicle appears to have been abandoned for quite some time, as nature has started to reclaim its territory around it. Vines and weeds entwine the tires, making it evident that this car has become a part of the decaying landscape.");
    struct room *broken_car = create_room(
        "The Broken Car", "As you cautiously approach the car, your heart pounds in your chest, overwhelmed by the eerie sight before you. The decaying body inside the vehicle sends shivers down your spine, its grisly appearance suggesting a violent end. The head bears a haunting hole, seemingly inflicted by a sharp object, leaving a grim impression of the brutality that unfolded.\nInside the car, you discover a desolate scene devoid of any remnants or clues. The windows, shattered and fragmented, only reinforce the sense of abandonment and destruction that has befallen the vehicle. It becomes evident that no amount of repair could salvage this car from its current state of disrepair.\nJust as you begin to grapple with the gravity of the situation, a faint sound pierces the silence. A crackling radio springs to life, its scratchy voice cutting through the airwaves with a desperate message. The voice trembles with a plea for survival: “If you're hearing this... if anyone is out there... I beg you, find a way to endure. Cherish every breath, every heartbeat, because in this world, life is a cruel joke. The infection has spread, and it's chaos out there. The dead are everywhere, relentless, and hungering for flesh. Society has crumbled, and chaos reigns supreme. People have turned on each other, driven by fear and desperation. It's survival of the fittest now, and we must—[Transmission cuts off abruptly] ”\nYou were listening to the voice in a chilling silence. Your mind races, grappling with the enormity of the situation and the uncertain fate that lies ahead.");
    struct room *storefront = create_room(
        "The Storefront", "As you walk near the store, your peripheral vision catches a glimpse of movement. Swiftly turning to confront the source, your gaze meets a haunting sight—a small cluster of walkers, their lifeless bodies inching closer towards you, fixated on your presence. Their once-human forms have been ravaged by time and decay, their flesh rotting and mottled with shades of sickly gray. Tattered clothes cling to their emaciated frames, barely holding together. Sunken eyes, devoid of any spark of life, lock onto you with an unnerving intensity. With each step, their movements are stiff and uncoordinated, their feet dragging along the cracked pavement, creating a disconcerting scraping sound. The scent of death and decay permeates the air, causing your stomach to churn and your heart to race. Their groans and low, guttural moans fill the silence, echoing through the desolate streets, a chilling reminder of the world that once was. As they shuffle closer, their outstretched arms and gnarled fingers seem to reach for you, a grim testament to their insatiable hunger. Your instinct compels you to consider bolting in the opposite direction, seeking a safer path.");
    struct room *looted_convenience = create_room(
        "The Looted Convenience", "The air is musty, and the shelves are mostly empty, their contents long looted. However, there might still be something of use left. You survey the interior of the convenience store. The shelves are mostly bare, with a few dusty, half-empty cans scattered around. A counter stands at the far end of the store, behind which lies a locked door leading to what seems to be a storage area. To the west, you can see the broken window through which you entered");
    struct room *supplies_warehouse = create_room(
        "The Supplies Warehouse", "You cautiously step into the storage area, feeling the coolness of the air. As your eyes adjust to the dim light, you notice rows of shelves filled with various supplies. This seems to be a treasure trove of useful items. You take a closer look at the shelves in the storage area. They are filled with a variety of supplies, including canned food and bottled water. It seems like this storage area was well-stocked before it was abandoned.");
    struct room *wider_street = create_room(
        "The Wider Street", "You cautiously make your way towards the wider street, stepping over debris and shattered glass. The eerie echoes of groans grow louder, reverberating through the once bustling intersection. The remnants of buildings, reduced to crumbling facades and twisted metal, tower over you, casting haunting silhouettes in the fading daylight. As you sweep your gaze across the desolate landscape, a glimmer of hope catches your eye—a faint flickering light in the distance, emanating from a long-abandoned campsite to the north. Intrigued and wary, you contemplate the potential dangers that lie ahead, yet the possibility of finding answers or even temporary respite beckons you to investigate further.");
    struct room *abandoned_campsite = create_room(
        "The Abandoned Campsite", "You still can see the road ahead, be the campfire drew your attention. You cautiously approach the eerie and desolate campsite, the flickering light casting eerie shadows that dance eerily around the few remaining tents. The once bustling haven for survivors now lies in ruins, with supplies haphazardly strewn across the muddy ground. As you carefully sift through the debris, a pungent odor assaults your nostrils, emanating from the rotten food that has long since expired. Suddenly, your heart skips a beat as you detect movement from the corner of your eye—a horde of relentless walkers emerges from the shadows, their hollow eyes fixed on you with a hunger that can only be satisfied by human flesh.");
    struct room *sorrowful_wilderness = create_room(
        "The Sorrowful Wilderness", "As you cautiously emerge from the thick underbrush, the chilling atmosphere of the forsaken place seeps into your bones. A woman, her face streaked with tears and dirt. Her voice quivers as she implores me for help, her words laced with anguish and desperation. \"Please... save us,\" she begs, her voice a mere whisper above the cacophony of moans. But then she realized that only she were still alive. Her eyes, once vibrant with life, now reflect a resignation born of the deepest despair. She knows her time is limited, and her final request cuts through me like a knife. Her trembling voice barely carries over the haunting whispers of the undead. \"End it,\" she pleads, her voice strained with grief and exhaustion. \"I want to join my family.\"");
    struct room *fort_haven = create_room(
        "The Fort Haven", "The streets become narrower, and the buildings more dilapidated as you move deeper into the abandoned city. As you walk, you notice a faint glow of light ahead. You cautiously approach the source of the faint glow, moving deeper into the abandoned city. As you continue your journey, you come across a tall, fortified structure standing amidst the ruins. The walls are reinforced with metal sheets and barbed wire, giving it an imposing appearance. A sturdy gate stands before you, secured with a heavy padlock. Above the gate, a sign reads \"Fort Haven: A Sanctuary in the Wasteland.\" You take a moment to assess the surroundings of Fort Haven. The area beyond the gate is well-lit, with floodlights illuminating the entrance. The walls are high and sturdy, offering protection from walkers and other threats. You notice a guard post to the right of the gate, where a sentinel keeps watch, armed with a rifle. To the left, you see a notice board displaying rules and regulations for entering the shelter. It seems that Fort Haven has strict entry protocols to maintain the safety and well-being of its residents.");

    set_exits_from_room(dilapidated_study, bloody_gallery,
                        NULL, narrow_hallway, living_room);
    set_exits_from_room(bloody_gallery, NULL, dilapidated_study, NULL, NULL);
    set_exits_from_room(living_room, NULL, NULL, dilapidated_study, NULL);
    set_exits_from_room(narrow_hallway, stockroom,
                        forgotten_street, armory_hideout, dilapidated_study);
    set_exits_from_room(stockroom, NULL, narrow_hallway, NULL, NULL);
    set_exits_from_room(armory_hideout, NULL, NULL, NULL, narrow_hallway);
    set_exits_from_room(forgotten_street, narrow_hallway,
                        wider_street, storefront, broken_car);
    set_exits_from_room(broken_car, NULL, NULL, forgotten_street, NULL);
    set_exits_from_room(storefront, NULL, NULL,
                        looted_convenience, forgotten_street);
    set_exits_from_room(looted_convenience, NULL, NULL,
                        supplies_warehouse, storefront);
    set_exits_from_room(supplies_warehouse, NULL, NULL,
                        NULL, looted_convenience);
    set_exits_from_room(wider_street, forgotten_street,
                        abandoned_campsite, NULL, NULL);
    set_exits_from_room(abandoned_campsite, wider_street, fort_haven,
                        NULL, sorrowful_wilderness);
    set_exits_from_room(sorrowful_wilderness, NULL, NULL,
                        abandoned_campsite, NULL);
    set_exits_from_room(fort_haven, abandoned_campsite, NULL, NULL, NULL);

    add_item_to_room(dilapidated_study, broken_table);
    add_item_to_room(dilapidated_study, dusty_bookshelf);
    add_item_to_room(dilapidated_study, book);
    add_item_to_room(dilapidated_study, tattared_journal);
    add_item_to_room(living_room, couch);
    add_item_to_room(living_room, drawer);
    add_item_to_room(living_room, vial_of_medicine);
    add_item_to_room(living_room, rusted_key);
    add_item_to_room(bloody_gallery, cash);
    add_item_to_room(stockroom, canned_food1);
    add_item_to_room(stockroom, flashlight);
    add_item_to_room(stockroom, first_aid_kit);
    add_item_to_room(armory_hideout, water_bottle1);
    add_item_to_room(armory_hideout, revolver);
    add_item_to_room(armory_hideout, crate);
    add_item_to_room(looted_convenience, counter);
    add_item_to_room(looted_convenience, copper_key);
    add_item_to_room(supplies_warehouse, water_bottle2);
    add_item_to_room(supplies_warehouse, canned_food2);
    add_item_to_room(fort_haven, notice_board);

    struct container *world = add_room_to_world(NULL, dilapidated_study);
    add_room_to_world(world, bloody_gallery);
    add_room_to_world(world, living_room);
    add_room_to_world(world, narrow_hallway);
    add_room_to_world(world, stockroom);
    add_room_to_world(world, armory_hideout);
    add_room_to_world(world, forgotten_street);
    add_room_to_world(world, broken_car);
    add_room_to_world(world, storefront);
    add_room_to_world(world, looted_convenience);
    add_room_to_world(world, supplies_warehouse);
    add_room_to_world(world, wider_street);
    add_room_to_world(world, abandoned_campsite);
    add_room_to_world(world, sorrowful_wilderness);
    add_room_to_world(world, fort_haven);

    return world;
}

struct container *destroy_world(struct container *world)
{
    world = destroy_containers(world);
    return NULL;
}

struct room *get_room(struct container *world, char *name)
{
    return (struct room *)get_from_container_by_name(world, name);
}

struct container *add_room_to_world(struct container *world, struct room *room)
{
    if (room == NULL || get_from_container_by_name(world, room->name) != NULL)
        return NULL;
    return create_container(world, ROOM, room);
}