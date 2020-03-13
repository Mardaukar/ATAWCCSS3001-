//Tämä kirjasto sisältää funktiot, jotka liittyvät näytölle tulostamiseen.

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

using namespace std;

//Tämä funktio tulostaa pelin päätaulukon.
void print_screen(char table[HEIGHT][WIDTH]) {
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			cout << table[y][x];
		}
		cout << "\n";
	}
}

//Tulostaa pelin nimen.
void print_title() {
	cout << "\nADVANCED TACTICAL ARMOR WARFARE COMBAT CONTROL SIMULATION SYSTEM 3001++\n";
}

//Tämä funktio tulostaa pelikentän alla sijaitsevat ohjeet ja statistiikat. Jokainen rivi valmistellaan
//erikseen, ja lopuksi kaikki printataan.
void print_status(int tank_size, int speed, int firing_status, bool facing_right, bool turn_out, int ammo) {
	string inst0 = "";
	string inst1 = "\t\tUP\t\t";
	string inst2 = "\t\tDOWN\t\t";
	string inst3 = "\t\tLEFT/RIGHT\tAccelerate";
	string inst4 = "\t\tSPACE\t\t";
	string inst5 = "\t\tC\t\t";
	string inst6 = "\t\tESC\t\tQuit";

	string speed_text = "SPEED\t";
	string bearing_text = "BEARING\t";
	string ammo_text = "";
	string ammo_text2 = "";

	//Prepare 0. Line
	if (tank_size == MEGASIZE) {
		inst0 = "\t\t\t\t\t\t\t\tM\tE\tG\tA\tT\tA\tN\tK";
	}

	//Prepare 1. Line
	if (turn_out == false) {
		inst1 += "Turn Out\t";
	}
	else {
		inst1 += "\t\t";
	}

	if (speed != 0) {
		speed *= 10;
		speed += rand() % 10 - 4;
		if (facing_right == false) {
			speed = speed * -1;
		}
	}

	speed_text += to_string(speed) + " km/h";

	inst1 += "\t\t\t" + speed_text;

	//Prepare 2. Line
	if (turn_out == true) {
		inst2 += "Turn In\t";
	}
	else {
		inst2 += "\t";
	}

	int bearing;

	if (facing_right == true) {
		bearing = 0;
	}
	else {
		bearing = 180;
	}

	int spd;

	if (speed == 0) {
		spd = 5;
	}
	else {
		spd = speed;
	}

	bearing += (rand() % 351 - 175) / spd;

	bearing_text += to_string(bearing) + " degrees";

	inst2 += "\t\t\t\t" + bearing_text;

	//Prepare 4. Line
	if (firing_status == 0 && ammo != 0) {
		inst4 += "Fire";
	}

	if (ammo == 0) {
		ammo_text = "OUT OF AMMO";
	}
	else {
		ammo_text = "AMMO\t" + to_string(ammo);
	}

	inst4 += "\t\t\t\t\t" + ammo_text;

	//Prepare 5. Line
	if (speed == 0) {
		inst5 += "Hold";
	}
	else {
		inst5 += "Roll On";
	}

	if (ammo != 0) {
		if (firing_status == 0) {
			ammo_text2 = "READY TO FIRE";
		}
		else if (firing_status == LOAD_TIME) {
			int x = rand() % 5;

			if (x == 0) {
				ammo_text2 = "KA-POW!";
			}
			else if (x == 1) {
				ammo_text2 = "BOOM!";
			}
			else if (x == 2) {
				ammo_text2 = "KA-BLAM!";
			}
			else if (x == 3) {
				ammo_text2 = "BANGGG!";
			}
			else if (x == 4) {
				ammo_text2 = "POWWW!";
			}
		}
		else {
			ammo_text2 = "RELOADING...";
		}
	}

	inst5 += "\t\t\t\t\t" + ammo_text2;

	//Print Instructions
	cout << inst0 << "\n";
	cout << inst1 << "\n";
	cout << inst2 << "\n";
	cout << inst3 << "\n";
	cout << inst4 << "\n";
	cout << inst5 << "\n";
	cout << "\n" << inst6 << "\n";
}