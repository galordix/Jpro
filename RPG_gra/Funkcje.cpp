#include "Funkcje.h"
item get_item(itemtype type)
{
	item returned_item;
	construct_item(&returned_item);
	switch (type)
	{
	case sword:
		returned_item.attack = rand() % 10;
		returned_item.size_y = rand() % 2 + 1;
		returned_item.name = (char*)"Sword";
		returned_item.type = sword;
		break;
	case helmet:
		returned_item.defense = rand() % 10;
		returned_item.HPbonus = rand() % 100;
		returned_item.size_y = rand() % 2 + 1;
		returned_item.size_x = rand() % 2 + 1;
		returned_item.name = (char*)"Helmet";
		returned_item.type = helmet;
		break;
	case leggings:
		returned_item.defense = rand() % 15;
		returned_item.HPbonus = rand() % 150;
		returned_item.size_y = rand() % 3 + 1;
		returned_item.name = (char*)"Leggings";
		returned_item.type = leggings;
		break;
	case chestplate:
		returned_item.defense = rand() % 40;
		returned_item.HPbonus = rand() % 300;
		returned_item.size_y = rand() % 3 + 1;
		returned_item.size_x = rand() % 2 + 2;
		returned_item.name = (char*)"Chestplate";
		returned_item.type = chestplate;
		break;
	case boots:
		returned_item.defense = rand() % 10;
		returned_item.size_y = rand() % 2 + 1;
		returned_item.size_x = rand() % 2 + 1;
		returned_item.name = (char*)"Boots";
		returned_item.type = boots;
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
	A->exp_next = 100 + 100*A->lvl * log(A->lvl)/log(A->lvl+1);
	A->attack = 12;
	A->defense = 12;
	A->equipment_slots = 5;
	A->HP = 120;
	A->currentHP = 120;
	A->currentSP = 120;
	A->equipment = (item**)malloc(sizeof(item*) * A->equipment_slots);
	for (int i = 0; i < A->equipment_slots; i++)
	{
		A->equipment[i]=NULL;
	}
	A->position.x = 4;
	A->position.y = 4;
	A->HPregen = 10;
	construct_item(&A->itemstats);
}
void get_enemy(enemy* new_enemy, int lvl)
{
	new_enemy->lvl = lvl;
	new_enemy->attack = (rand() % 10 + 10) * lvl;
	new_enemy->defense = (rand() % 10 + 10) * lvl;
	new_enemy->SP = (rand() % 100 + 100) * lvl;
	new_enemy->HP = (rand() % 100 + 100) * lvl;
	new_enemy->currentHP = new_enemy->HP;
	new_enemy->currentSP=new_enemy->SP;
	new_enemy->position.x = (rand() % 10);
	new_enemy->position.y = (rand() % 10);
	new_enemy->exp = (rand() % 20 + 20) * lvl;
}
int fight(enemy* monster, character *hero)
{
	int attack_ratio = 1, defense_ratio = 1, escape = 0;
	char button;
	
	while (monster->currentHP > 0 && hero->currentHP > 0 && !escape)
	{
		system("cls");
		std::cout << "Press A to attack, D to defend and S to escape battle" << std::endl;
		write_stats(*hero);
		std::cout << std::endl;
		write_enemy_stats(*monster);
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

		monster->currentHP -= (((hero->attack + hero->itemstats.attack) * attack_ratio) * monster->defense/(10+monster->defense));
		hero->currentHP -= ((monster->attack * (hero->defense + hero->itemstats.defense) * defense_ratio) / ((hero->defense + hero->itemstats.defense * defense_ratio)+ 10));
		
	}
	if (monster->currentHP <= 0)
	{
		return 1;
	}
	else if(hero->currentHP <= 0)
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
		for (int j = 0; j < size_x; j++)
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
	A->weight = 0;
	A->position.x = 0;
	A->position.y = 0;
	A->size_x = 1;
	A->size_y = 1;
	A->type = 0;
	A->name = (char*)malloc(sizeof(char) * 15);
	A->name = (char*)"";
}
void check_item(item A, character hero)
{
	system("cls");
	std::cout << A.name << std::endl;
	if (A.attack > 0) std::cout <<"attack: " << A.attack << std::endl;
	if (A.defense > 0)std::cout <<"defense: " << A.defense << std::endl;
	if (A.HPbonus > 0)std::cout <<"bonus HP: " << A.HPbonus << std::endl;
	if (A.weight > 0)std::cout <<"weight: " << A.weight << std::endl;
	if (A.lvl > 0) std::cout <<"lvl: " << A.lvl << std::endl;
	std::cout << "sizeX: " << A.size_x << std::endl;
	std::cout << "sizeY: " << A.size_y << std::endl;
	if (hero.equipment[A.type] != NULL)
	{
		std::cout <<std::endl <<"Currently equipped:" << std::endl;
		if (A.attack > 0) std::cout << "attack: " << hero.equipment[A.type]->attack << std::endl;
		if (A.defense > 0)std::cout << "defense: " << hero.equipment[A.type]->defense << std::endl;
		if (A.HPbonus > 0)std::cout << "bonus HP: " << hero.equipment[A.type]->HPbonus << std::endl;
		if (A.weight > 0)std::cout << "weight: " << hero.equipment[A.type]->weight << std::endl;
		if (A.lvl > 0) std::cout << "lvl: " << hero.equipment[A.type]->lvl << std::endl;
		std::cout << "sizeX: " << hero.equipment[A.type]->size_x << std::endl;
		std::cout << "sizeY: " << hero.equipment[A.type]->size_y << std::endl;
	}

}
void check_inventory(inventory *inv, character *hero)
{
	system("cls");
	bool is_open = true;
	bool has_items = false;
	for (int i = -1; i < inv->size_y; i++)
	{
		for (int j = -1; j < inv->size_x; j++)
		{
			if (i==-1 && j==-1)
			{
				std::cout << "        ";
			}
			else if (i == -1)
			{
				std::cout << j+1 << "                ";
			}
			else if (j == -1)
			{
				std::cout << i+1 << " ";
			}
			else
			{
				std::cout << inv->item_arr[i][j] << " ";
				if (inv->item_arr[i][j] != NULL && !has_items)
				{
					has_items = true;
				}
			}
			
		}
		std::cout << std::endl;
	}
	std::cout << "press [S] to check stats, press [X] to close backpack"<< std::endl;
	while (is_open)
	{
		switch (_getch())
		{
		case 'x':
			is_open = false;
			break;
		case 's':
			if (has_items) 
			{
				check_stats(inv, hero);
				is_open = false;
			}
			else
			{
				std::cout << "You have no items" << std::endl;
			}
			break;
		}
	}
}
void stat_regen(character *hero)
{
	if (hero->currentHP + hero->HPregen < hero->HP + hero->itemstats.HPbonus)
	{
		hero->currentHP += hero->HPregen;
	}
	else
	{
		hero->currentHP = hero->HP + hero->itemstats.HPbonus;
	}
}
void write_stats(character hero)
{
	std::cout << "Your stats" << std::endl;
	std::cout << "Lvl: " << hero.lvl << std::endl;
	std::cout << "Exp: " << hero.exp << "/" << hero.exp_next << std::endl;
	std::cout << "HP: " << hero.currentHP << "/" << hero.HP + hero.itemstats.HPbonus << std::endl;
	std::cout << "Attack: " << hero.attack + hero.itemstats.attack << std::endl;
	std::cout << "Defense: " << hero.defense + hero.itemstats.defense << std::endl;
	std::cout << "HPregen: " << hero.HPregen << std::endl;
}
void write_enemy_stats(enemy monster)
{
	std::cout << "Enemy stats" << std::endl;
	std::cout << "Lvl: " << monster.lvl << std::endl;
	std::cout << "HP: " << monster.currentHP << "/" << monster.HP<< std::endl;
	std::cout << "Attack: " << monster.attack<< std::endl;
	std::cout << "Defense: " << monster.defense << std::endl;
}
int inventory_space(inventory *inv, item* new_item)
{
	int starting_x, starting_y;
	int temp = 0;
	for (starting_y = 0; starting_y < inv->size_y; starting_y++)
	{
		
		for (starting_x = 0; starting_x < inv->size_x; starting_x++)
		{
			temp = 0;
			for (int i = starting_y; i < new_item->size_y + starting_y; i++)
			{
				for (int j = starting_x; j < new_item->size_x + starting_x; j++)
				{
					if (starting_x + new_item->size_x < inv->size_x && starting_y + new_item->size_y < inv->size_y)
					{
						if (inv->item_arr[i][j] == NULL)
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
	return -1;
}
void put_in_inventory(inventory *inv, item *new_item)
{
	int is_space=inventory_space(inv, new_item);
	if (is_space == 0)
	{
		for (int i = new_item->position.y; i < new_item->position.y + new_item->size_y; i++)
		{
			for (int j = new_item->position.x; j < new_item->position.x + new_item->size_x; j++)
			{
				inv->item_arr[i][j] = new_item;
			}
		}
	}
	else if (is_space == -1)
	{
		std::cout << "not enough inventory space";
	}
};
void drop_item(inventory *inv, character hero)
{
	item* tempitem = (item*)malloc(sizeof(item));
	char button;
	*tempitem = get_item((itemtype)(rand() % 5));
	check_item(*tempitem, hero);
	std::cout << "press 1 to accept item or 0 to trash item";
	do
	{
		button = _getch();
		switch (button)
		{
		case '1':
			put_in_inventory(inv, tempitem);
			break;
		case '0':
			free(tempitem);
			break;
		}

	} while (button != '1' && button != '0');
}
void check_stats(inventory *inv, character *hero)
{
	item** queue = (item**)malloc(sizeof(item*)*inv->size_x*inv->size_y);
	bool open_stats = true, is_new=true;
	int queue_elements=0, current_element=0;
	for (int i = 0; i < inv->size_y; i++)
	{
		for (int j = 0; j < inv->size_x; j++)
		{
			is_new = true;
			for (int k = 0; k < queue_elements; k++)
			{
				if (inv->item_arr[i][j] == queue[k])
				{
					is_new = false;
				}
			}
			if (inv->item_arr[i][j] != NULL && is_new == true)
			{
				queue[queue_elements] = inv->item_arr[i][j];
				queue_elements++;
			}
				
		}
	}
	while (open_stats)
	{
		
		system("cls");
		check_item(*queue[current_element], *hero);
		std::cout << "press [A] or [D] to change items, [E] to equip current item, [X] to return to backpack";
		switch (_getch())
		{
		case 'e':
			if (hero->equipment[queue[current_element]->type] != NULL)
			{
				if (hero->lvl >= queue[current_element]->lvl && inventory_space(inv, hero->equipment[queue[current_element]->type]) == 0)
				{
					equip_item(inv, hero, queue[current_element]);
					open_stats = false;
				}
				else if (hero->lvl < queue[current_element]->lvl) {
					std::cout << "Your level is too small" << std::endl;
				}
				else {
					std::cout << "Not enough inventory space for currently equipped item" << std::endl;
				}
			}
			else {
				if (hero->lvl >= queue[current_element]->lvl)
				{
					equip_item(inv, hero, queue[current_element]);
					open_stats = false;
				}
				else{
					std::cout << "Your level is too small" << std::endl;
				}
			}
			break;
		case 'x':
			open_stats = false;
			break;
		case 'a':
			if (current_element > 0) current_element--;
			break;
		case 'd':
			if (current_element < queue_elements-1) current_element++;
			break;
		}
		
	}
	free(queue);
}
void equip_item(inventory *inv, character *hero, item *equipped_item)
{
	if(hero->equipment[equipped_item->type]!=NULL)put_in_inventory(inv, hero->equipment[equipped_item->type]);
	hero->equipment[equipped_item->type] = equipped_item;
	for (int i = 0; i < inv->size_y; i++)
	{
		for (int j = 0; j < inv->size_x; j++)
		{
			if (inv->item_arr[i][j] == equipped_item)
			{
				inv->item_arr[i][j] = NULL;
			}
		}
	}
	equipment_stats(hero);
}
void equipment_stats(character *hero)
{
	construct_item(&hero->itemstats);
	for (int i = 0; i < hero->equipment_slots; i++)
	{
		if (hero->equipment[i] != NULL)
		{
			hero->itemstats.attack += hero->equipment[i]->attack;
			hero->itemstats.defense += hero->equipment[i]->defense;
			hero->itemstats.HPbonus += hero->equipment[i]->HPbonus;
		}
	}
}
void level_up(character* hero)
{
	hero->exp = hero->exp % hero->exp_next;
	hero->lvl++;
	hero->attack += 5;
	hero->defense += 5;
	hero->HP += 50;
	if (hero->currentHP + 50 <= hero->HP)hero->currentHP += 50;
	hero->HPregen += 5;
	hero->exp_next=100 + 100 * hero->lvl * log(hero->lvl) / log(hero->lvl + 1);
}