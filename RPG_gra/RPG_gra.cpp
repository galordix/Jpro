// RPG_gra.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#include "Funkcje.h"

int main()
{
	//inicjalizowanie stałych
	int game = 1;
	char map_name[100];
	character hero;
	inventory backpack;
	initialize_inventory(10, 5, &backpack);
	srand(time(NULL));
	FILE** maps = (FILE**)malloc(sizeof(FILE*) * 8);
	for (int i = 0; i < 8; i++)
	{
		sprintf_s(map_name, "maps/Map%d.txt", i + 1);
		fopen_s(&maps[i], map_name, "r");
		if (maps[i] == NULL)
		{
			perror("plik sie nie otworzyl");
		}
	}
	initialize_chara(&hero);
	map current_map;
	get_map(maps[0], &current_map);
	enemy** enemies = (enemy**)malloc(sizeof(enemy*) * current_map.maxEnemies);
	for (int i = 0; i < current_map.maxEnemies; i++)
	{
		enemies[i] = (enemy*)malloc(sizeof(enemy));
	}
	int current_enemies = 0;
	int infight = 0;
	int fighted_enemy;
	char button;
	//petla gry
	while (game == true)
	{

		//rysowanie mapy
		for (int i = 0; i < current_map.size_y; i++)
		{
			for (int j = 0; j < current_map.size_x; j++)
			{
				if (hero.position.x == j && hero.position.y == i)
				{
					std::cout << 'X';
				}
				else
				{
					switch (current_map.tile[i][j])
					{
					case 1:
						std::cout << '-';
						break;
					case 2:
						std::cout << '*';
						break;
					case 3:
						std::cout << '*';
						break;
					case 4:
						std::cout << 'o';
						break;
					case 5:
						std::cout << ' ';
						break;

					}
				}
			}
			printf("\n");
		}
		write_stats(hero);
		std::cout << "Press [WASD] to move, [C] to open backpack, [Spacebar] to attack enemy, [X] to close game." << std::endl;
		//kontrole
		infight = 0;
		switch (_getch())
		{
		case 'a':
			if (hero.position.x == 0) break;
			if (current_map.tile[hero.position.y][hero.position.x - 1] == 1 && hero.position.x - 1 >= 0 && current_map.tile[hero.position.x - 1][hero.position.x] != 0)
				hero.position.x--;
			break;
		case 'd':
			if (hero.position.x == current_map.size_x - 1) break;
			if (current_map.tile[hero.position.y][hero.position.x + 1] == 1 && hero.position.x + 1 < current_map.size_x && current_map.tile[hero.position.x + 1][hero.position.x] != 0)
				hero.position.x++;
			break;
		case 'w':
			if (hero.position.y <= 0) break;
			if (current_map.tile[hero.position.y - 1][hero.position.x] == 1 && hero.position.y - 1 >= 0 && current_map.tile[hero.position.y - 1][hero.position.x] != 0)
				hero.position.y--;
			break;
		case 's':
			if (hero.position.y == current_map.size_y - 1) break;
			if (current_map.tile[hero.position.y + 1][hero.position.x] == 1 && hero.position.y + 1 < current_map.size_x && current_map.tile[hero.position.y + 1][hero.position.x] != 0)
				hero.position.y++;
			break;
		case 'x':
			game = 0;
			break;
		case 'c':
			check_inventory(&backpack, &hero);
			break;
		case 32:
			for (int i = 0; i < current_map.maxEnemies; i++)
			{
				if ((enemies[i]->position.x == hero.position.x + 1 && enemies[i]->position.y == hero.position.y) ||
					(enemies[i]->position.x == hero.position.x - 1 && enemies[i]->position.y == hero.position.y) ||
					(enemies[i]->position.x == hero.position.x && enemies[i]->position.y == hero.position.y + 1) ||
					(enemies[i]->position.x == hero.position.x && enemies[i]->position.y == hero.position.y - 1))
				{
					int outcome = fight(enemies[i], &hero);
					infight = 1;
					fighted_enemy = i;
					switch (outcome)
					{
					case 1:
						//if (rand() % 4 == 0)
						{
							drop_item(&backpack, hero);
							
						}
						hero.exp += enemies[i]->lvl * 20;
						if (hero.exp >= hero.exp_next)
						{
							level_up(&hero);
						}
						current_map.tile[enemies[i]->position.y][enemies[i]->position.x] = 1;
						for (int j = i; j < current_enemies-1; j++)
						{
							*enemies[j] = *enemies[j + 1];
						}
						free(enemies[current_enemies-1]);
						enemies[current_enemies-1]= (enemy*)malloc(sizeof(enemy));
						current_enemies--;
						
						break;
					case 0:
						enemies[i]->currentHP = enemies[i]->HP;
						break;
					case -1:
						if (hero.exp - 20 >= 0)hero.exp -= 20;
						enemies[i]->currentHP = enemies[i]->HP;
						break;
					}
					
				}

			}
		}

		stat_regen(&hero);
		//tworzenie losowych wrogow

		if (rand() % 5 == 0 && current_enemies < current_map.maxEnemies)
		{

			get_enemy(enemies[current_enemies], current_map.maplvl);
			if (current_map.tile[enemies[current_enemies]->position.y][enemies[current_enemies]->position.x] != 1)
			{
				free(enemies[current_enemies]);
				//enemies[current_enemies] = NULL;
				enemies[current_enemies] = (enemy*)malloc(sizeof(enemy));
				enemy_init(enemies[current_enemies]);
			}
			else
			{
				current_map.tile[enemies[current_enemies]->position.y][enemies[current_enemies]->position.x] = 4;
				current_enemies++;
			}

		}
		system("cls");

	}


	//Zwolnienie miejsca
	for (int i = 0; i < 8; i++)
	{
		fclose(maps[i]);
	}
	for (int i = 0; i < current_map.maxEnemies; i++)
	{
		free(enemies[i]);
	}
	for (int i = 0; i < current_map.size_y - 1; i++)
	{
		free(current_map.tile[i]);
	}
	free(current_map.tile);
	free(hero.equipment);
	for (int i = 0; i < backpack.size_y; i++)
	{
		free(backpack.item_arr[i]);

	}
	free(backpack.item_arr);
	free(maps);
}

void enemy_init(enemy* instance)
{
	instance->attack = 0;
	instance->currentHP = 0;

}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
