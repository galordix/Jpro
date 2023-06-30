#pragma once
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
struct wektor
{
	int x, y;
};
struct item
{
	float attack, defense, HPbonus, weight, lvl;
	int size_x, size_y, type;
	wektor position;
	char *name;
};
struct character
{
	wektor position;
	item itemstats;
	int HP, HPregen, attack, defense, lvl, equipment_slots, currentHP, currentSP, exp, exp_next;
	item** equipment;
};
struct map
{
	int size_x=10, size_y=10, maplvl=1, maxEnemies=5;
	int** tile;
};
struct enemy
{
	wektor position;
	int HP, SP, attack, defense, lvl, currentHP, currentSP, exp;
};
struct inventory
{
	int size_y, size_x;
	item*** item_arr;
};
enum itemtype { sword = 0, helmet, leggings, chestplate, boots };