#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "human.h"
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class player : public human{
private:
	int id;
	string name;
	int age;
	string ability;
	int salary;
	int money_to_transfer;
	int scores;
	int service_year;
public:
	player(int Id, string Name, int Age, string Abi, int sal, int tran, int sco, int ser)
	{ // player 构造函数
		id = Id;
		name = Name; 
		age = Age; 
		ability = Abi;
		salary = sal;	
		money_to_transfer = tran;
		scores = sco;
		service_year = ser;
	}
	player(){};
//			Player[current_player_amount].init_player(name, age, ability, salary, money_to_transfer, scores, service_years);
	void init_player(int Id, string Name, int Age, string Abi, int sal, int tran, int sco, int ser){
		id = Id;// 从0开始 
		name = Name; 
		age = Age; 
		ability = Abi;
		salary = sal;	
		money_to_transfer = tran;
		scores = sco;
		service_year = ser;
	}
	void reset_age(int new_age) { age = new_age; }
	void reset_salary(int new_sa) { salary = new_sa; } 
	void reset_money_to_transfer(int new_tran) { money_to_transfer = new_tran; }
	void reset_scores(int new_sco) { scores = new_sco; }
	void reset_year(int new_year) { service_year = new_year; }
		
	string get_name() { return name; }
	int get_id() { return id; }
	int get_age() { return age; }
	int get_salary() { return salary; }
	int get_transfer() { return money_to_transfer; }
	int get_score() { return scores; }
	int get_year() { return service_year; }
	~player() { /*cout << " break player" << endl;*/ }
};


#endif
