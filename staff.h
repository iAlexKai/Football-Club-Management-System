#include "human.h"
#ifndef _STAFF_H_
#define _STAFF_H_

class staff : public human{
	
private:	
	string name;
	int age;
	string ability;
	int salary;
public:
	staff(string Name, int Age, string Abi, int sal)
	{ // player ¹¹Ôìº¯Êý
		name = Name;
		age = Age;
		ability = Abi;
		salary = sal;
	}
	~staff() { cout << " break staff" << endl; }

};


#endif
