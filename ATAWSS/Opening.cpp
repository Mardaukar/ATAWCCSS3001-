//T‰h‰n alifunktiokirjastoon on ker‰tty kaikki alkudemoon liittyv‰t funktiot

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

//T‰m‰ t‰ytt‰‰ alkukuvan samoilla funktioilla, joita k‰ytet‰‰n oikeissa pelitilanteissa
//Alkukuvaa ei ole siis tarvinnut erikseen laatia
void fill_start(char table[HEIGHT][WIDTH]) {
	add_tank(table, 100, 20, 3, 3, false, true);

	int opening_left[] = { 1,3,3 };
	int opening_right[] = { 1,3,2 };
	add_targets(table, opening_left, opening_right);

	table[HEIGHT - 3][70] = '<';
	table[HEIGHT - 3][80] = '<';
	table[HEIGHT - 3][150] = '>';
}

//T‰m‰ funktio suorittaa pelin "lataamisen"
void run_intro(char table[HEIGHT][WIDTH]) {
	fill_start(table);
	print_title();
	print_screen(table);
	cout << "\n\t\tResize your window to full screen, Commander.\n";
	cout << "\t\tWhen you are ready, press any key to continue...";
	_getch(); _getch();

	int i = 0;
	while (true) {
		system("cls");
		print_title();
		cout << "\n";

		cout << "\t\tInitializing game state...\t\t";
		if (i < 100) {
			cout << i;
		}
		else {
			cout << "100";
		}
		cout << "% \n";

		if (i >= 100) {
			cout << "\t\tLoading high level physics engine...\t";
		}
		if (i > 100 && i < 200) {
			cout << i - 100;
		}
		else if (i >= 200) {
			cout << "100";
		}
		if (i >= 100) {
			cout << "% \n";
		}

		if (i >= 200) {
			cout << "\t\tLaunching dynamic weather simulation...\t";
		}
		if (i > 200 && i < 300) {
			cout << i - 200;
		}
		else if (i >= 300) {
			cout << "100";
		}
		if (i >= 200) {
			cout << "% \n";
		}

		if (i >= 300 && i < 400) {
			cout << "\t\tMaximizing gore and violence...\t\t";
		}
		if (i > 300 && i < 350) {
			cout << i - 300 << " %";
		}
		else if (i >= 350 && i < 400) {
			cout << "ERROR";
		}

		if (i >= 400) {
			cout << "\t\tRemoving parental locks...\t\t";
		}
		if (i > 400 && i < 500) {
			cout << i - 400;
		}
		else if (i >= 500) {
			cout << "100";
		}
		if (i >= 400) {
			cout << "% \n";
		}

		if (i >= 500) {
			cout << "\t\tMaximizing gore and violence...\t\t";
		}
		if (i > 500 && i < 600) {
			cout << (i - 500)*10;
		}
		else if (i >= 600) {
			cout << "1000";
		}
		if (i >= 500) {
			cout << "% \n";
		}

		if (i >= 600) {
			cout << "\t\tFueling the tank...\t\t\t";
		}
		if (i > 600 && i < 700) {
			cout << i - 600;
		}
		else if (i >= 700) {
			cout << "100";
		}
		if (i >= 600) {
			cout << "% \n";
		}

		if (i >= 610) {
			cout << "\t\tLoading ammunition...\t\t\t";
		}
		if (i > 610 && i < 710) {
			cout << i - 610;
		}
		else if (i >= 710) {
			cout << "100";
		}
		if (i >= 610) {
			cout << "% \n";
		}

		if (i >= 620) {
			cout << "\t\tCranking, boosting, adrenalizing...\t";
		}
		if (i > 620 && i < 720) {
			cout << i - 620;
		}
		else if (i >= 720) {
			cout << "100";
		}
		if (i >= 620) {
			cout << "% \n";
		}

		if (i >= 720) {
			cout << "\n\t\tSHOW ME YOUR WAR FACE!!!";
			Sleep(3000);
			break;
		}

		Sleep(2);
		i += 3;
	}
}