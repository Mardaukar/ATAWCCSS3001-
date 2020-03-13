//T‰m‰ kirjasto sis‰lt‰‰ funktiot, jotka muuttavat pelin tilaa.

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

#include "Header.h"

//T‰m‰ funktio muuttaa tankin kokoa, riippuen kuinka monta targettia on ammuttu. Jos kaikki
//targetit on ammuttu, saa tankki kookseen MEGASIZE
void resize_tank(int *p_tank_size, int targets_left[], int targets_right[]) {
	int bonus = 0;

	for (int i = 0; i < 3; i++) {
		if (targets_left[i] < 3) {
			bonus += 1;
		}
		if (targets_right[i] < 3) {
			bonus += 1;
		}
	}

	if (bonus == 6) {
		*p_tank_size = MEGASIZE;
	}
	else {
		*p_tank_size = START_SIZE + 2 * bonus;
	}
}

//T‰m‰ funktio p‰ivitt‰‰ targetit. Targettien tila on v‰lilt‰ 3 (ehj‰) ja 0 (poistunut).
//Jos tila on 1 tai 2 (pieni ja iso r‰j‰hdys), tilaa v‰hennet‰‰n yhdell‰.
//Myˆs, tarkistetaan sisimmist‰ ehjist‰ targeteista, osuuko niihin ammus t‰ll‰ hetkell‰,
//mik‰ puolestaan tiputtaa ne tilaan 2, eli pieneen r‰j‰hdykseen.
void update_targets(int targets_left[], int targets_right[], int shots[STARTING_AMMO][2]) {
	for (int i = 0; i < 3; i++) {
		if (targets_left[i] == 1 || targets_left[i] == 2) {
			targets_left[i] -= 1;
		}
		if (targets_right[i] == 1 || targets_right[i] == 2) {
			targets_right[i] -= 1;
		}
	}

	if (targets_left[0] == 3) {
		if (check_collision(true, LIMIT - 6, shots)) {
			targets_left[0] = 2;
		}
	}
	else if (targets_left[1] == 3) {
		if (check_collision(true, LIMIT - 12, shots)) {
			targets_left[1] = 2;
		}
	}
	else if (targets_left[2] == 3) {
		if (check_collision(true, LIMIT - 18, shots)) {
			targets_left[2] = 2;
		}
	}

	if (targets_right[0] == 3) {
		if (check_collision(false, WIDTH - LIMIT + 6, shots)) {
			targets_right[0] = 2;
		}
	}
	else if (targets_right[1] == 3) {
		if (check_collision(false, WIDTH - LIMIT + 12, shots)) {
			targets_right[1] = 2;
		}
	}
	else if (targets_right[2] == 3) {
		if (check_collision(false, WIDTH - LIMIT + 18, shots)) {
			targets_right[2] = 2;
		}
	}
}

//T‰m‰ funktio testaa, osuuko annettuun targettiin mik‰‰n ammuksista.
bool check_collision(bool left, int place, int shots[STARTING_AMMO][2]) {
	bool collision = false;

	for (int i = 0; i < STARTING_AMMO; i++) {
		if (shots[i][0] != -100) {
			if (left == true) {
				if (shots[i][0] <= place) {
					collision = true;
					shots[i][0] = -100;
				}
			}
			else {
				if (shots[i][0] >= place) {
					collision = true;
					shots[i][0] = -100;
				}
			}
		}
	}

	return collision;
}

//T‰m‰ funktio liikuttaa ammuksia nopeutensa verran eteenp‰in.
void move_shots(int shots[STARTING_AMMO][2]) {
	for (int x = 0; x < STARTING_AMMO; x++) {
		if (shots[x][0] != -100) {
			shots[x][0] = shots[x][0] + shots[x][1];

			if (shots[x][0] < -20 || shots[x][0] > WIDTH + 20) {
				shots[x][0] = -100;
			}
		}
	}
}

//Antaa ammuksille alkusijainnin (kuvaruudun ulkopuolelle) ja nopeuden nolla.
void init_shots(int shots[STARTING_AMMO][2]) {
	for (int x = 0; x < STARTING_AMMO; x++) {
		shots[x][0] = -100;
		shots[x][1] = 0;
	}
}

//Antaa ammukselle sijainnin ammuttaessa tankin sijainnin ja suunnan mukaan.
int get_shot_location(int location, int tank_size, bool facing_right) {
	int shot_location;

	if (facing_right == true) {
		shot_location = location + 13;
	}
	else {
		shot_location = location + tank_size - 14;
	}

	return shot_location;
}

//Antaa ammukselle nopeuden tankin nopeuden mukaan.
int get_shot_speed(int speed, bool facing_right) {
	int shot_speed = SHOT_SPEED;

	if (facing_right == false) {
		shot_speed *= -1;
	}

	shot_speed += speed;

	return shot_speed;
}

//Siirt‰‰ tankkia nopeutensa verran, mutta pys‰ytt‰‰ esteeseen.
void move_tank(int *p_location, int *p_speed, int tank_size) {
	*p_location += *p_speed;

	if (*p_location < LIMIT) {
		*p_location = LIMIT;
		*p_speed = 0;
	}

	if (*p_location > WIDTH - tank_size - LIMIT) {
		*p_location = WIDTH - tank_size - LIMIT;
		*p_speed = 0;
	}
}