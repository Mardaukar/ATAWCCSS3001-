
//Advanced Tactical Armor Warfare Combat Command Simulation System 3001++

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>

//Määrittelen tässä vakiot, joita ohjelmassa käytetään

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

#include "header.h"

using namespace std;

int main() {
	//Alustetaan päätaulukko, tyhjennetään se ja laitetaan siihen peliruudun reunat
	char table[HEIGHT][WIDTH];
	clear_screen(table);
	add_borders(table);

	//Suoritetaan alkudemo
	run_intro(table);

	//Alustetaan kaikki muuttujat ja taulukot
	bool turn_out = false, facing_right = true, quit_game = false;
	int location = WIDTH / 2 - START_SIZE / 2, ammo = STARTING_AMMO, speed = 0, firing_status = 0, tank_size = START_SIZE;
	int targets_left[] = { 3, 3, 3 }, targets_right[] = { 3, 3, 3 }; //3 on ehjän targetin tila
	int shots[STARTING_AMMO][2]; //Tämä taulukko pitää kirjaa ammuksista
	init_shots(shots);

	//Peli alkaa...
	while (true) {

		//Lisätään taulukkoon kaikki ascii-merkit oikeille paikoilleen alifunktioilla
		system("cls");
		clear_screen(table);
		add_borders(table);
		add_targets(table, targets_left, targets_right);
		add_tank(table, location, tank_size, speed, firing_status, facing_right, turn_out);
		add_shots(table, shots);

		//Printataan kaikki
		print_title();
		print_screen(table);
		print_status(tank_size, speed, firing_status, facing_right, turn_out, ammo);

		//Vastaanotetaan pelaajan antama käsky
		while (true) {
			int command1, command2;

			command1 = _getch();
			command2 = _getch();

			if (command1 == 224) { //Kiihdytys vasemmalle
				if (command2 == 75) {
					if (speed > -MAX_SPEED) {
						speed -= 1;
					}
					facing_right = false;
					break;
				}

				if (command2 == 77) { //Kiihdytys oikealle
					if (speed < MAX_SPEED) {
						speed += 1;
					}
					facing_right = true;
					break;
				}

				if (command2 == 72) { //Komentaja näkyviin
					if (turn_out == false) {
						turn_out = true;
						break;
					}
				}

				if (command2 == 80) { //Komentaja pois näkyvistä
					if (turn_out == true) {
						turn_out = false;
						break;
					}
				}
			}
			
			if (command1 == 32) { //Ampuminen
				if (firing_status == 0 && ammo > 0) {
					firing_status = LOAD_TIME + 1;
					shots[STARTING_AMMO - ammo][0] = get_shot_location(location, tank_size, facing_right);
					shots[STARTING_AMMO - ammo][1] = get_shot_speed(speed, facing_right);
					ammo--;
					break;
				}
			}

			if (command1 == 99) { //Jatkaa peliä tekemättä mitään (roll on / hold)
				break;
			}

			if (command1 == 27) { //Lopetus ESC
				quit_game = true;
				break;
			}
		}

		if (quit_game == true) { //Lopettaa pelin
			break;
		}

		//Pelitilan päivitys alifunktioilla
		move_tank(&location, &speed, tank_size);
		move_shots(shots);
		update_targets(targets_left, targets_right, shots);
		resize_tank(&tank_size, targets_left, targets_right);

		if (firing_status > 0) { //Lataa ammusta tankissa
			firing_status -= 1;
		}
	}

	//Pelin lopetus
	cout << "\n\nESCAPING THE BATTLE FIELD...";

	Sleep(2000);

	return EXIT_SUCCESS;
}