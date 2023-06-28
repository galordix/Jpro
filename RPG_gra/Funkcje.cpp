#include "Funkcje.h"
item get_item(itemtype type)
{
	item returned_item;
	construct_item(&returned_item);
	switch (type)
	{
	case sword:
		returned_item.attack = rand() % 10;
		returned_item.SPbonus = rand() % 100;
		returned_item.size_y = rand() % 2 + 1;
		break;
	case helmet:
		returned_item.defense = rand() % 10;
		returned_item.HPbonus = rand() % 100;
		returned_item.size_y = rand() % 2 + 1;
		returned_item.size_x = rand() % 2 + 1;
		break;
	case leggings:
		returned_item.defense = rand() % 15;
		returned_item.HPbonus = rand() % 150;
		returned_item.SPbonus = rand() % 200;
		returned_item.size_y = rand() % 3 + 1;
		break;
	case chestplate:
		returned_item.defense = rand() % 40;
		returned_item.HPbonus = rand() % 300;
		returned_item.size_y = rand() % 3 + 1;
		returned_item.size_x = rand() % 2 + 2;
		break;
	case boots:
		returned_item.defense = rand() % 10;
		returned_item.SPbonus = rand() % 100;
		returned_item.size_y = rand() % 2 + 1;
		returned_item.size_x = rand() % 2 + 1;
		break;
	}
	return returned_item;
	
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
	new_inventory->size_x = size_x;
	new_inventory->size_y = size_y;
	new_inventory->item_arr = (item***)malloc(size_y * sizeof(item**));
	for (int i = 0; i < size_y; i++)
	{
		new_inventory->item_arr[i] = (item**)malloc(size_x * sizeof(item*));
	}
	for (int i = 0; i < size_y; i++)
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
	A->lvl = 1;
	A->SPbonus = 0;
	A->weight = 0;
	A->position.x = 0;
	A->position.y = 0;
	A->size_x = 1;
	A->size_y = 1;
}
void check_item(item A)
{
	system("cls");
	if (A.attack > 0) std::cout <<"attack" << A.attack << std::endl;
	if (A.defense > 0)std::cout <<"defense: " << A.defense << std::endl;
	if (A.HPbonus > 0)std::cout <<"bonus HP: " << A.HPbonus << std::endl;
	if (A.SPbonus > 0)std::cout <<"bonus SP: " << A.SPbonus << std::endl;
	if (A.weight > 0)std::cout <<"weight: " << A.weight << std::endl;
	if (A.lvl > 0) std::cout <<"lvl: " << A.lvl << std::endl;
}
void check_inventory(inventory inv)
{
	system("cls");
	for (int i = -1; i < inv.size_y; i++)
	{
		for (int j = -1; j < inv.size_x; j++)
		{
			if (i == -1)
			{
				std::cout << j+1 << "		";
			}
			else if (j == -1)
			{
				std::cout << i+1 << " ";
			}
			else
			{
				std::cout << inv.item_arr[i][j] << " ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << "press any key to continue";
	_getch();
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
int inventory_space(inventory inv, item* new_item)
{
	int starting_x, starting_y;
	int temp = 0;
	for (starting_y = 0; starting_y < inv.size_y; starting_y++)
	{
		
		for (starting_x = 0; starting_x < inv.size_x; starting_x++)
		{
			temp = 0;
			for (int i = 0; i < new_item->size_y + starting_y; i++)
			{
				for (int j = 0; j < new_item->size_x + starting_x; j++)
				{
					if (j + new_item->size_x < inv.size_x && i + new_item->size_y < inv.size_y)
					{
						if (inv.item_arr[i][j] == NULL)
						{
							temp++;
						}
					}
				}

			}
			if (temp == new_item->size_x * new_item->size_y)
			{
				new_item->position.x = starting_x;
				new_item->position.y = starting_y;
				return 0;
			}
		}
	}
}
void put_in_inventory(inventory inv, item *new_item)
{
	inventory_space(inv, new_item);
	for (int i = new_item->position.y; i < new_item->position.y + new_item->size_y; i++)
	{
		for (int j = new_item->position.x; j < new_item->position.x + new_item->size_x; j++)
		{
			inv.item_arr[i][j] = new_item;
		}
	}
};
void drop_item(inventory inv)
{
	item* tempitem = (item*)malloc(sizeof(item));
	char button;
	*tempitem = get_item((itemtype)(rand() % 5));
	check_item(*tempitem);
	std::cout << "press 1 to accept item or 0 to trash item";
	do
	{
		button = _getch();
		switch (button)
		{
		case '1':
			put_in_inventory(inv, tempitem);
			break;
		}
	} while (button != '1' && button != '0');
}