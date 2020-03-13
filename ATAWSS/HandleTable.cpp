//T‰m‰n kirjaston alifunktiot liittyv‰t p‰‰taulukon sis‰lt‰mien ascii-merkkien p‰ivitt‰miseen.

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>

#define HEIGHT 15
#define WIDTH 180
#define START_SIZE 14
#define MEGASIZE 32
#define LIMIT 24
#define MAX_SPEED 5
#define SHOT_SPEED 10
#define LOAD_TIME 3
#define STARTING_AMMO 10
#define EXPLOSION_HEIGHT 3
#define EXPLOSION_WIDTH 5

//T‰m‰ funktio lis‰‰ taulukkoon kaikki ammukset, ottaen huomioon niiden suunnan ja sijainnin.
void add_shots(char table[HEIGHT][WIDTH], int shots[STARTING_AMMO][2]) {
	for (int x = 0; x < STARTING_AMMO; x++) {
		if (shots[x][0] >= 0) {
			if (shots[x][1] > 0) {
				table[HEIGHT - 3][shots[x][0]] = '>';
				table[HEIGHT - 3][shots[x][0] - 1] = '>';
			}
			else {
				table[HEIGHT - 3][shots[x][0]] = '<';
				table[HEIGHT - 3][shots[x][0] + 1] = '<';
			}
		}
	}
}

//Tyhjent‰‰ taulukon, lukuunottamatta reunoja.
void clear_screen(char table[HEIGHT][WIDTH]) {
	for (int y = 1; y < HEIGHT - 1; y++) {
		for (int x = 1; x < WIDTH - 1; x++) {
			table[y][x] = ' ';
		}
	}
}

//Lis‰‰ taulukkoon reunat.
void add_borders(char table[HEIGHT][WIDTH]) {
	for (int x = 0; x < WIDTH; x++) {
		table[0][x] = '*';
		table[HEIGHT - 1][x] = '*';
	}
	for (int y = 1; y < HEIGHT - 1; y++) {
		table[y][0] = '*';
		table[y][WIDTH - 1] = '*';
	}
	for (int x = 1; x < WIDTH - 1; x++) {
		table[HEIGHT - 2][x] = '_';
	}
	table[HEIGHT - 2][LIMIT - 1] = 'A';
	table[HEIGHT - 2][WIDTH - LIMIT] = 'A';
	for (int x = 1; x < 4; x++) {
		table[HEIGHT - 2][LIMIT - 6 * x] = 'T';
		table[HEIGHT - 2][WIDTH - LIMIT + 6 * x] = 'T';
	}
}

//Tekee r‰j‰hdyksen annettuun kohtaan. Size on 1 tai 2.
//Suuremmassa r‰j‰hdyksess‰ tehd‰‰n kaksinkertainen pieneen verrattuna.
//R‰j‰hdys on k‰yt‰nnˆss‰ satunnaisesti arvottuja * merkkej‰ r‰j‰hdysalueella.
void add_explosion(char table[HEIGHT][WIDTH], int location, int size) {
	for (int i = 0; i < EXPLOSION_HEIGHT * size; i++) {
		for (int j = 0; j < EXPLOSION_WIDTH * size; j++) {
			if (rand() % 2 == 0) {
				table[HEIGHT - 3 - i][location - EXPLOSION_WIDTH / 2 - (size - 1) * 2 + j] = '*';
			}
		}
	}
}

//Lis‰‰ targetit taulukkoon niiden tilan mukaan
//(ehj‰, pieni r‰j‰hdys, suuri r‰j‰hdys ja poistunut)
void add_targets(char table[HEIGHT][WIDTH], int targets_left[], int targets_right[]) {
	for (int x = 0; x < 3; x++) {
		if (targets_left[x] == 3) {
			table[HEIGHT - 3][LIMIT - 6 * (x + 1) - 1] = '(';
			table[HEIGHT - 3][LIMIT - 6 * (x + 1)] = 'o';
			table[HEIGHT - 3][LIMIT - 6 * (x + 1) + 1] = ')';
		}
		else if (targets_left[x] == 2) {
			add_explosion(table, LIMIT - 6 * (x + 1), 1);

			table[HEIGHT - 3][LIMIT - 6 * (x + 1) - 2] = '(';
			table[HEIGHT - 3][LIMIT - 6 * (x + 1) + 2] = ')';
		}
		else if (targets_left[x] == 1) {
			add_explosion(table, LIMIT - 6 * (x + 1), 2);
		}

		if (targets_right[x] == 3) {
			table[HEIGHT - 3][WIDTH - LIMIT + 6 * (x + 1) - 1] = '(';
			table[HEIGHT - 3][WIDTH - LIMIT + 6 * (x + 1)] = 'o';
			table[HEIGHT - 3][WIDTH - LIMIT + 6 * (x + 1) + 1] = ')';
		}
		else if (targets_right[x] == 2) {
			add_explosion(table, WIDTH - LIMIT + 6 * (x + 1), 1);

			table[HEIGHT - 3][WIDTH - LIMIT + 6 * (x + 1) - 2] = '(';
			table[HEIGHT - 3][WIDTH - LIMIT + 6 * (x + 1) + 2] = ')';
		}
		else if (targets_right[x] == 1) {
			add_explosion(table, WIDTH - LIMIT + 6 * (x + 1), 2);
		}
	}
}

//Lis‰‰ tankin taulukkoon
//Muuttuja "start" on k‰tev‰ apuv‰line tankkia piirrett‰ess‰ eri suuntiin
void add_tank(char table[HEIGHT][WIDTH], int location, int tank_size, int speed, int firing_status, bool facing_right, bool turn_out) {

	//Initialize variables
	int x, y, start, direction;
	char front_panel, blast_fire; //N‰m‰ joudutaan alustamaan erikseen, koska eiv‰t ole suunnan suhteen symmetriset

	if (facing_right == true) {
		start = location + 1;
		direction = 1;
		front_panel = '\\';
		blast_fire = '(';
	}
	else {
		start = location + tank_size - 2;
		direction = -1;
		front_panel = '/';
		blast_fire = ')';
	}

	//Draw bottom & speed lines
	y = HEIGHT - 2;

	table[y][location] = '(';
	table[y][location + tank_size - 1] = ')';

	for (x = location + 1; x < location + tank_size - 1; x++) {
		table[y][x] = 'o';
	}

	if (speed > 0) {
		for (x = 1; x <= speed; x++) {
			table[y][location - (x)] = '-';
		}
	}
	else if (speed < 0) {
		for (x = -1; x >= speed; x--) {
			table[y][location + tank_size - 1 - (x)] = '-';
		}
	}

	// Draw middle, gun & blast
	y = HEIGHT - 3;

	for (int x = 0; x < 3; x++) {
		table[y][start + x * direction] = '_';
	}

	table[y][start + 3 * direction] = '|';
	table[y][start + 8 * direction] = front_panel;

	for (int x = 9; x < 14; x++) {
		table[y][start + x * direction] = '=';
	}

	if (firing_status == LOAD_TIME) {
		table[y][start + 14 * direction] = blast_fire;
	}

	//Draw top & commander
	y = HEIGHT - 4;

	for (x = 4; x < 8; x++) {
		table[y][start + x * direction] = '_';
	}

	if (turn_out == true) {
		table[y][start + 6 * direction] = 'W';
	}
}