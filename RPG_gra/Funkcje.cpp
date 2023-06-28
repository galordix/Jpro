#include "Funkcje.h"
item get_item(itemtype type)
{
	switch (type)
	{
	case sword:
		item sword;
		sword.attack = rand() % 10;
		sword.SPbonus = rand() % 100;
		return sword;
		break;
	case helmet:
		item helmet;
		helmet.defense = rand() % 10;
		sword.HPbonus = rand() % 100;
		return helmet;
	case leggings:
		item leggings;
		leggings.defense = rand() % 15;
		leggings.HPbonus = rand() % 150;
		leggings.SPbonus = rand() % 200;
		return leggings;
	case chestplate:
		item chestplate;
		chestplate.defense = rand() % 40;
		chestplate.HPbonus = rand() % 300;
		return chestplate;
	case boots:
		item boots;
		boots.defense = rand() % 10;
		boots.SPbonus = rand() % 100;
	}
	
	
}

void get_map(FILE* map_file, map* new_map)
{
	int temp;
	new_map->tile = (int**)malloc(new_map->size_y * sizeof(int*));
	for (int i = 0; i < new_map->size_y; i++)
	{
		new_map->tile[i] = (int*)malloc(sizeof(int) * new_map->size_x);
	}
	for (int i = 0; i < new_map->size_y; i++)
	{
		for (int j = 0; j < new_map->size_x+1; j++)
		{
			temp = fgetc(map_file);
			if(temp != '\n') new_map->tile[i][j] = temp - 48;
		}
	}
}
void initialize_chara(character* A)
{
	A->lvl = 1;
	A->exp = 0;
	A->exp_next = A->lvl * A->lvl / log(A->lvl);
	A->attack = 10;
	A->defense = 10;
	A->equipment_slots = 5;
	A->HP = 100;
	A->currentHP = 100;
	A->SP = 100;
	A->currentSP = 100;
	A->equipment = (item*)malloc(sizeof(item) * A->equipment_slots);
	A->position.x = 0;
	A->position.y = 0;
	A->HPregen = 10;
	A->SPregen = 10;
}
void get_enemy(enemy* new_enemy, int lvl)
{
	new_enemy->attack = rand()%6 + 1;
	new_enemy->defense = rand()%6 + 1;
	new_enemy->SP = rand() % 100 + 10;
	new_enemy->HP = rand() % 100 + 10;
	new_enemy->currentHP = new_enemy->HP;
	new_enemy->currentSP=new_enemy->SP;
	new_enemy->position.x = rand() % 10;
	new_enemy->position.y = rand() % 10;
}
int fight(enemy* monster, character *hero)
{
	int attack_ratio = 1, defense_ratio = 1, escape = 0;
	char button;
	
	while (monster->currentHP > 0 && hero->currentHP > 0 && !escape)
	{
		system("cls");
		std::cout << "Press A to attack, D to defend and S to escape battle" << std::endl;
		std::cout << "Your HP: " << hero->currentHP << "/" << hero->HP << std::endl;
		std::cout << "enemy HP: " << monster->currentHP << "/" << monster->HP << std::endl;
		do
		{
			button = _getch();
			switch (button)
			{
			case 'a':
				attack_ratio = 2;
				defense_ratio = 1;
				break;
			case 'd':
				attack_ratio = 1;
				defense_ratio = 2;
				break;
			case 's':
				escape = 1;
				break;
			}
		} while (button != 'a' && button != 'd' && button != 's');
		if (hero->currentSP >= 10)
		{
			monster->currentHP -= (hero->attack * attack_ratio - monster->defense);
			hero->currentSP -= 10;
		}
		if (monster->currentSP >= 10)
		{
			hero->currentHP -= (monster->attack - hero->defense * defense_ratio);
			monster->currentSP -= 10;
		}
		stat_regen(hero);
	}
	if (monster->currentHP < 0)
	{
		return 1;
	}
	else if(hero->currentHP < 0)
	{
		return -1;
	}
	else
	{
		return 0;
	}
	
}
void initialize_inventory(int size_x, int size_y, inventory* new_inventory)
{
	new_inventory->item_arr = (item***)malloc(size_y * sizeof(item**));
	for (size_t i = 0; i < size_y; i++)
	{
		new_inventory->item_arr[i] = (item**)malloc(size_x * sizeof(item*));
	}
	for (size_t i = 0; i < size_y; i++)
	{
		for (size_t j = 0; j < size_x; j++)
		{
			new_inventory->item_arr[i][j] = NULL;
		}
	}
}
void construct_item(item* A)
{
	A->attack = 0;
	A->defense = 0;
	A->HPbonus = 0;
	A->lvl = 0;
	A->SPbonus = 0;
	A->weight = 0;
}
void check_item(item A)
{
	system("cls");
	std::cout << A.attack << std::endl;
	std::cout << A.defense << std::endl ;
	std::cout << A.HPbonus << std::endl;
	std::cout << A.SPbonus << std::endl;
	std::cout << A.weight << std::endl;
	std::cout << A.lvl << std::endl;
}
void stat_regen(character *hero)
{
	if (hero->currentHP + hero->HPregen < hero->HP)
	{
		hero->currentHP += hero->HPregen;
	}
	else
	{
		hero->currentHP = hero->HP;
	}
	if (hero->currentSP + hero->SPregen < hero->SP)
	{
		hero->currentSP += hero->SPregen;
	}
	else
	{
		hero->currentSP = hero->SP;
	}
}
void put_in_inventory(inventory inv, item new_item)
{

};