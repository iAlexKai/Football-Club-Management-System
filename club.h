#ifndef _CLUB_H_
#define _CLUB_H_
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include "player.h"
#define Max_Player_Amount 100
using namespace std;

class club {
private:
	string name;
	int total_cash;
	int player_amount;
	vector <player> players;
public:
	club(string Name, int total, int amount) {
		name = Name;
		total_cash = total;
		player_amount = amount;
		players.reserve(amount);
	}
	club(){};
	void init_club(string Name, int total){
		name = Name;
		total_cash = total;
		player_amount = 0;
		players.reserve(Max_Player_Amount);	
	}
	void add_player(player adder);
	void delete_player(player deleter);
	void update_player(player updater);
	void get_players_number(string command);
	void get_players_number_with_nak(string command);
	void output_current_players();
	void advanced_search_player_withnak(struct command_for_compare[], char op1, char op2, char op);
	bool search_all_players_in_club();
	int advanced_player_search();
	int output_all_players_in_the_group(club Club[]);
	bool compare_to_search(struct command_for_compare compare[], int player_id, int order_amount);
	bool advanced_search_player(struct command_for_compare[], int op1, int op2, char op);
	bool advanced_compare_to_search(struct command_for_compare compare[], int player_id, int command_number);
	bool club_empty();
	string get_club_name() { return name; }
	string get_player_name(int id) { return players.at(id).get_name(); }
	player get_player(int id) { return players.at(id);} 
	int search_player(struct command_for_compare compare[]);
	int get_player_amount() { return player_amount; }
	int get_cash() { return total_cash; }
	void set_cash(string command, int amount) { 
		if (command == "add") total_cash += amount; 
		else if (command == "minus") total_cash -= amount; 
		else cout << "bad command" << endl;
	}
	
	~club() { /*std::cout << " break club" << endl; */}
};




#endif
