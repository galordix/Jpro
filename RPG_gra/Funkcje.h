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
void check_item(item A);
void put_in_inventory(inventory inv, item new_item);
void stat_regen(character *hero);
void drop_item(inventory inv);
void check_inventory(inventory inv);