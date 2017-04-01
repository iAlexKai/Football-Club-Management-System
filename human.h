#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;

#ifndef _HUMAN_H_
#define _HUMAN_H_

class human{
	private:
		string name;
		int age;
	public:
		human(){};
		int get_age(){	return age;}
		string get_name(){return name;}
		~human(){};
		
};

#endif
