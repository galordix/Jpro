#pragma once
#include "Structures.h"
item get_item(itemtype);
void get_map(FILE *, map *);
void initialize_chara(character *);
void get_enemy(enemy*, int);
int fight(enemy*, character *);
void initialize_inventory(int size_x, int size_y, inventory* new_inventory);
void enemy_init(enemy* instance);
void construct_item(item* A);
void check_item(item A, character hero);
void put_in_inventory(inventory *inv, item *new_item);
void stat_regen(character *hero);
void drop_item(inventory *inv, character hero);
void check_inventory(inventory *inv, character *hero);
void equip_item(inventory *inv, character *hero, item* equipped_item);
void check_stats(inventory *inv, character *hero);
void equipment_stats(character *hero);
void write_stats(character hero);
void level_up(character* hero);
void write_enemy_stats(enemy monster);