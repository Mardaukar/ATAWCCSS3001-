#pragma once

void add_borders(char[HEIGHT][WIDTH]);
void fill_start(char[HEIGHT][WIDTH]);
void print_screen(char[HEIGHT][WIDTH]);
void clear_screen(char[HEIGHT][WIDTH]);
void add_tank(char[HEIGHT][WIDTH], int, int, int, int, bool, bool);
void add_targets(char[HEIGHT][WIDTH], int[], int[]);
void move_tank(int*, int*, int);
void resize_tank(int*, int[], int[]);
void move_shots(int[STARTING_AMMO][2]);
void update_targets(int[], int[], int[STARTING_AMMO][2]);
void init_shots(int[STARTING_AMMO][2]);
void add_shots(char[HEIGHT][WIDTH], int[STARTING_AMMO][2]);
void print_status(int, int, int, bool, bool, int);
int get_shot_location(int, int, bool);
int get_shot_speed(int, bool);
bool check_collision(bool, int, int[STARTING_AMMO][2]);
void add_explosion(char[HEIGHT][WIDTH], int, int);
void print_title();
void run_intro(char[HEIGHT][WIDTH]);