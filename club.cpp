//string ��ȡһ�е�ʱ�����Ļس���������NULL 
//switch() ������ֻ�������αȷ�˵ int��char֮���,������string 
/*
	���������ν��ջ��ֻͳ�Ƶ�ǰ��������������������+1������������-1�� ���� @��ȡ������������� �����֮ǰ�����
	@@ ||ȷ������������Ա�����飬������������ && || ֻ�Ǹı䵱ǰָ������ܣ�����������Ϊ����ȷֹͣ������Ϊ
	����������� 
	new ��֮��һ���ǵ��ͷ� delete ��صģ�����ֱ��Խ�籨�� 
	string *ptr = new string[amount]
	delete []ptr;
	
*/ 
/*
	ǿ�ˣ��� 
	��ɣ�������һ���������
	����������򵥵�  @club=A 
*/

#include "stdafx.h"
#include <memory.h>
#define MaxOrderAmount 50
#define MaxPlayerAmount 100
void init_player_group();
void init_compare();
bool valid_compare(string com);
string in_to_Post_order(string order);
int *ini_group(int group[], int amount);
bool in_player_group(int op, int j);

player Player[Max_Player_Amount];
club Club[Max_Club_Amount];	
int *current_players; // ����߼������е�ǰ������������Ա�����, ��ʼ��Ϊȫ����Ա 
int *club_to_search;
int current_club_amount_to_search;
int current_players_amount;// ��ʼ��Ϊ0 
int current_order_amount;
int temp_order_amount;// �����ڽ���ջ����ʱ��ǰָ������ 
int input_order_amount; // �û������ָ������ 
int player_group[MaxOrderAmount][MaxPlayerAmount];// ���浱ǰ�������������Ӧ����Ա���� 
int nak_amount;
int club_allPlayer_search_amount;
int club_num[Max_Club_Amount];

struct command_for_compare{
	string content;   // �Ƚ϶������磺 age 
	bool no; // ��ʾǰ���Ǹ�! 
	char symbol; // �Ǵ���С �� ���� > 
	int number; // �Ͷ��ٱȣ� ���� 12
	int result[Max_Player_Amount];// �洢���ϴ���������Ա��������� 
};
struct command_for_compare compare[10]; // �����û���������������ĸ�����󲻳���10 


void init_compare(){
	for(int i = 0; i < 10; i++){  // string ����Ĭ��Ϊ�մ��� 
		compare[i].no = false;
		compare[i].number = -1;
	}
}

bool valid_compare(string com){
	string valid[COMPARE_AMOUNT] = {"age", "year", "kick", "salary", "transfer"};
	for(int i = 0; i < COMPARE_AMOUNT; i++){
		if(com == valid[i])
			return true;
	} 
	return false;
}


void output_order(int amount){
	cout << endl;
	for(int i = 0; i < amount; i++)
		cout << compare[i].content << compare[i].symbol << compare[i].number << endl;
}

char* pass_space(char *control){
	while(1){
		if(*control == ' '){
			control++;
//			cout << "������һ���ո�"; 	
		}
		else 
			return control;
	}
		
}


bool club::compare_to_search(struct command_for_compare compare[], int player_id, int order_amount){
//	cout << "blablabalbalbal �˶�Ա" << player_id << "�ŵ�����Ϊ" <<players.at(player_id).get_age() << endl; 
	int com[order_amount]; 
	for(int i = 0; i < order_amount; i++){
		if(compare[i].content == "age") com[i] = 1;
		if(compare[i].content == "salary") com[i] = 2;
		if(compare[i].content == "transfer") com[i] = 3;
		if(compare[i].content == "kick") com[i] = 4;
		if(compare[i].content == "year") com[i] = 5;		
	} 
		
//		for(int j = 0; j < order_amount; j++)
//			cout << compare[j].no << endl;
//		cout << "\n\nblablabla\n";	
//			cout << com[j] << endl;
	for(int i = 0; i < order_amount; i++){
		switch (com[i]){	
			case 1:
				if( (compare[i].symbol == '>' && compare[i].no == false 
				&& players.at(player_id).get_age() < compare[i].number ) ||
				(compare[i].symbol == '<' && compare[i].no == false 
				&& players.at(player_id).get_age() > compare[i].number ) )
					return false;
				else if( (compare[i].symbol == '>' && compare[i].no == true 
				&& players.at(player_id).get_age() > compare[i].number ) ||
				(compare[i].symbol == '<' && compare[i].no == true 
				&& players.at(player_id).get_age() < compare[i].number ) )
					return false;
				break;	
			case 2:
				if( (compare[i].symbol == '>' && compare[i].no == false 
				&& players.at(player_id).get_salary() < compare[i].number ) ||
				(compare[i].symbol == '<' && compare[i].no == false 
				&& players.at(player_id).get_salary() > compare[i].number ) )
					return false;
				else if( (compare[i].symbol == '>' && compare[i].no == true 
				&& players.at(player_id).get_salary() > compare[i].number ) ||
				(compare[i].symbol == '<' && compare[i].no == true 
				&& players.at(player_id).get_salary() < compare[i].number ) )
					return false;
				break;
			case 3:
				if( (compare[i].symbol == '>' && compare[i].no == false 
				&& players.at(player_id).get_transfer() < compare[i].number ) ||
				(compare[i].symbol == '<' && compare[i].no == false 
				&& players.at(player_id).get_transfer() > compare[i].number) )
					return false;
				else if( (compare[i].symbol == '>' && compare[i].no == true 
				&& players.at(player_id).get_transfer() > compare[i].number ) ||
				(compare[i].symbol == '<' && compare[i].no == true 
				&& players.at(player_id).get_transfer() < compare[i].number ) )
					return false;
				break;
			case 4:
				if( (compare[i].symbol == '>' && compare[i].no == false 
				&& players.at(player_id).get_score() < compare[i].number ) ||
				(compare[i].symbol == '<' && compare[i].no == false 
				&& players.at(player_id).get_score() > compare[i].number ) )
					return false;
				else if( (compare[i].symbol == '>' && compare[i].no == true 
				&& players.at(player_id).get_score() > compare[i].number ) ||
				(compare[i].symbol == '<' && compare[i].no == true 
				&& players.at(player_id).get_score() < compare[i].number ) )
					return false;
				break;
			case 5:
				if( (compare[i].symbol == '>' && compare[i].no == false 
				&& players.at(player_id).get_year() < compare[i].number ) ||
				(compare[i].symbol == '<' && compare[i].no == false 
				&& players.at(player_id).get_year() > compare[i].number ) )
					return false;
				else if( (compare[i].symbol == '>' && compare[i].no == true 
				&& players.at(player_id).get_year() > compare[i].number ) ||
				(compare[i].symbol == '<' && compare[i].no == true 
				&& players.at(player_id).get_year() < compare[i].number ) )
					return false;
				break;
			default:
				cout << "compare �������� ���޷��Ƚϡ�" << endl;
				break;
		}// end of switch
		
	}// end of for,����Ƚ����� �����true 
	return true;
}//end of compare




void club::update_player(player updater) {
	int new_age, new_salary, new_transfer, new_score, new_year;
	char command[20];
	for (int i = 0; i < 20; i++)
		command[i] = 0;
	cout << "������Ҫ���ĵĸ���Ա����Ϣ����eg����Ҫ�޸���������������ǰ�ı��1������֮���ÿո������" << endl
		<< "1�����䣻2����н��3��ת��ѣ�4������������5�� ��������" << endl;
	cin.getline(command, 20);
	for (int i = 0; i < 20 && command[i] != '\0'; i++) {
		if (command[i] == ' ')
			continue;
		else
			switch (command[i]) {
			case ' ':
				break;
			case '1':
				cout << "�������Ϊ���٣�" << endl;
				cin >> new_age;
				updater.reset_age(new_age);
				break;
			case '2':
				cout << "��н����Ϊ���٣�" << endl;
				cin >> new_salary;
				updater.reset_salary(new_salary);
				break;
			case '3':
				cout << "ת��Ѹ���Ϊ���٣�" << endl;
				cin >> new_transfer;
				updater.reset_money_to_transfer(new_transfer);
				break; 
			case '4':
				cout << "������������Ϊ���٣�" << endl;
				cin >> new_score;
				updater.reset_scores(new_score);
				break;		
			case '5':
				cout << "�������޸���Ϊ���٣�" << endl;
				cin >> new_year;
				updater.reset_year(new_year);
				break;
			default:
				cout << "��������";
				break;
			} // end of switch
	}// end of for}
}

void club::add_player(player adder) {
	player_amount++;
	cout << "The team " << name << " has add a new player: " << adder.get_name() << " and its corrent asset is " << get_cash() << endl;
	players.push_back(adder);
}

void club::delete_player(player deleter) {
	for (vector<player>::iterator iter = players.begin();	
		iter != players.end(); ++iter) {
		if(iter->get_id() == deleter.get_id()){
			players.erase(iter);
			cout << "The team " << name << " has deleted a  player: " << deleter.get_name() << " and its corrent asset is " << get_cash() << endl;		
			
		}
			
	}
}

void player_purchase(club buyer, club seller, player goods) {
	if (buyer.get_cash() < goods.get_transfer()){
		cout << "���ʽ��㣬�޷��������Ա������ʧ��" << endl;
		return;
	}

	//���׳ɹ�ʱ
	seller.set_cash("add", goods.get_transfer());
	seller.delete_player(goods);
	buyer.set_cash("minus", goods.get_transfer());
	buyer.add_player(goods);
}

bool club::club_empty(){
	if(club::get_player_amount() == 0)
		return true;
	else 
		return false;	
}

int my_precedence(char op1, char op2){
	if (op1 == '(')
        return -1;
    else if (op1 == '!'){
    	if(op2 == '|' || op2 == '&')
    		return 1;
    	else{
    		cout << "��������ȼ��Ƚ�ʱ����" << endl; 	
			return -2;
		}	
	}
	
    else if (op1 == '|'){
		if(op2 == '&' || op2 == '!')
    		return -1;
		else if(op2 == '|')
			return 0;
		else {
			cout << "��������ȼ��Ƚ�ʱ����" << endl; 	
			return -2;
		}
	} 

    else if (op1 == '&'){
		if(op2 == '|')
    		return 1;
		else if(op2 == '&')
			return 0;
		else if(op2 ==  '!')
			return -1;
		else {
			cout << "��������ȼ��Ƚ�ʱ����" << endl; 	
			return -2;
		}	
	}   
	
	else{
		cout << "something is wrong in the precedence comparation" << endl;
		return -2;
	}
}
void init_player_group(){
	for(int i = 0; i < MaxOrderAmount; i++)
		for(int j = 0; j < MaxPlayerAmount; j++)
			player_group[i][j] = -1;
}
string in_to_Post_order(string order){
/*
		����@��һ��compare[]����ջcompare������±꣬����ߵ�����֮���һ���ַ�	
*/
	int i = 0, j = 0, bracket_amount = 0;
	current_order_amount = 0; // ��ʾcompare������±� 
	string result;
	char temp_order[20][20] = {0};
	char *temp = (char *) malloc (sizeof(char));
	stack<char> st;	
	
		
	for(;order[i] != NULL;){// string�����һ���ַ���NULL	
		while(order[i] == ' ') { 
//		cout << "�����ո�\n"; 
		    i++;
		}	// �����ո�
		if(order[i] == '('){
			bracket_amount++;
			st.push(order[i]);
//			cout << order[i] << "��ջ" << endl;
			i++;
			while(order[i] == ' ') { 
			//cout << "�����ո�\n"; 
			    i++;
			}	// �����ո�
		}
		//��д����룡 
		
		
		
	 	else if(order[i] == ')'){
//	 		cout << "������ǽ�����" << endl;
			bracket_amount--;
			if(bracket_amount < 0){
				cout << "����ָ�����������������������ţ��������" << endl;
				return "wrong";
			}
				 
//	 		cout << st.top() << endl;
			while(st.top() != '('){
//				cout << "here\n\n\n\n\n" << endl;
				result += st.top();// �ַ��Ļ����ǿ���ֱ�Ӽӵ�string����� 
//				cout << " The result is " << result[j] << endl << endl;
				st.pop();
			}
			
			st.pop();// ���������� 
//			cout << "����һ��������\n" ; 
			i++; 
		}
		
		else if (order[i] == '@'){//�����һ���ж�����compare 
			i++;
			while(order[i] == ' '){ 
//			cout << "�����ո�\n"; 
			    i++;}	// �����ո�
			//�����һ���ַ��ǲ��������ַ� 
			if(!(order[i] >= 'a' && order[i] <= 'z')){
				cout << "�������" << endl;
				return "wrong";
			}
			
			for(j = 0; order[i] >= 'a' && order[i] <= 'z'; j++){/*��@����ĵ�һ���ǿո��ַ���ʼ*/
				temp_order[current_order_amount][j] = order[i];
				i++;
			}
			
			compare[current_order_amount].content = temp_order[current_order_amount];
			if(!valid_compare(compare[current_order_amount].content)){
				cout << "�������!" << endl; 
				return "wrong";
			} 
			
			
			while(order[i] == ' ') { 
//			cout << "�����ո�\n"; 
			    i++;
			}	// �����ո�
			
			//��ʱorderָ�� > < �� 
			if(order[i] == '>')
				compare[current_order_amount].symbol = '>';
			else if(order[i] == '<')
				compare[current_order_amount].symbol = '<';
			else{
				cout << "������������" << endl; 
				return "wrong";
			}
			i++;
			
		    while(order[i] == ' ') { 
//			cout << "�����ո�\n"; 
			    i++;
			}	// �����ո�
			
			if(!(order[i] >= '0' && order[i] <= '9')){
				cout << "������������" << endl; 
				return "wrong";		
			} 
				
			compare[current_order_amount].number = 0;	
			for(j = 0/*��@����ĵ�һ���ַ���ʼ*/; order[i] >= '0' && order[i] <= '9'; j++){
				compare[current_order_amount].number = (order[i] - '0') + compare[current_order_amount].number * 10;
				i++;
			}
			//���һ��compare�����룬 ���±������ ע�� compare�����±겢����ջ 
//			cout << compare[current_order_amount].content << compare[current_order_amount].symbol << compare[current_order_amount].number << endl;
			
			itoa(current_order_amount, temp, 10); // ��int�� ��k ת��Ϊchar* 
//			cout << "����" << current_order_amount << endl; 
			result += temp;  // �� k �嵽string�ͺ��� 
			
//			cout << "current_order_amount �� " << current_order_amount << endl;
			//ע�� ��result[j]ǿ��ת��Ϊint�ͼ��ɣ������� 
			 //����һ��ѭ��ʱ����ʵiָ��������ֺ���ĵ�һ���ַ����������ǧ��Ҫ�ټ�һ��i++�� 
			current_order_amount++; // ���һ��ָ������룬������һ�� 
		}//end of if(order[i] == '@')
			/* elseջ�ǿ��ҽ����ķ��ţ�&& ���� ||�ȣ����ȼ�С�ڻ����ջ��
			 ���ջ������ջ����󽫽����ķ�����ջ*/			
		else if((order[i] == '!') || (order[i] == '&' && order[i+1] == '&') || (order[i] == '|' && order[i+1] == '|')){
			if(order[i] == '!') nak_amount++;
			else if(order[i] != '!') i++;// ���ߵ��ڶ���&��λ�ã�������ַ���Ϊ��ǰ�ַ��������ȼ��Ƚ� 
			while(st.empty() == false && my_precedence(st.top(), order[i]) >= 0){
				if(my_precedence(st.top(), order[i]) == -2)
					return 0; 
				result += st.top();
//				cout << "����" << st.top() << endl; 
//				cout << "result is " << result[j] << endl << endl;
				st.pop();	
			}
			st.push(order[i]);
//			cout << order[i] << "��ջ" << endl;
			i++;
		} 
			
		else{ // �������ַ����� @ �� | �� &�� ���� 
			cout << "Bad input!!�����ַ�Ϊ" << order[i] << endl;
			return "wrong";
			i++;	
		}// end of else 				
		while(order[i] == ' ') { 
//		cout << "�����ո�\n"; 
			i++;
		}	// �����ո�
//		cout << "������ȡ���ַ���" << order[i] << "����һ����" << order[i+1] << endl;
//		if(order[i] == ')')  
//			cout << i << endl;
	}// end of for
	
	while(st.empty() == false){// �ַ�����ȡ��ϣ���ջ��ʣ������������result������
		result += st.top();		
		st.pop();
	}	
	if(bracket_amount != 0){
		cout << "���������ŵ��������������ţ������������������룡" << endl;
		return "wrong"; 
	}
//	if(nak_amount != 0)
//		cout << "���ʽ������ϣ��У�Ŷ~" << endl;
//	cout << "result ��" << result << endl; 
	return result; //���հѺ�׺���ʽstring���� 

}// end of in_to_post_order  

int *init_group(int *group1, int size){
	for(int i = 0; i < size; i++)
		group1[i] = 0;
	return group1;	
}
bool in_the_group(int id){
	for(int i = 0; i < current_players_amount; i++){
		if(id == current_players[i])
			return true; 
	}
	return false;
}
int *update_current_players(int *group_one, int *group_two, char op, int amount1, int amount2){
//	cout << "��������ӡ����������" << endl;
//	for(int i = 0; i < amount1; i++)
//		cout << group_one[i];
//	for(int i = 0; i < amount2; i++)
//		cout << group_two[i];
	
	int *new_group = (int *)malloc(sizeof(int) * 100);
	int flag = 0;
//	cout << new_group[0]<<"fjalskdjflskjdf";
	//��ǰ����û�и���new_group 
	int k = 0;// ��ʾnew_group���±� 
	for(int i = 0; i < current_players_amount; i++){
		new_group[i] = current_players[i];
		k++;
	}
		
	if(op == '&'){
		for(int i = 0; i < amount1; i++){
			for(int j = 0; j < amount2; j++){
				if(group_one[i] == group_two[j] && !in_the_group(group_one[i])){ 
					new_group[k] = group_one[i];
					k++; 
					current_players_amount++;
					flag = 1;
				} 
			}
		}
//		cout << "������" << new_group[k] << endl;
		if(flag == 1) 
			return new_group;
		else // û���κθ��ĵ�ʱ�� ���ص�ǰ��current_players 
			return current_players;	
	}
	
	if(op == '|'){// �����ȡ������ �Ƚ���һ��������ȫ���Ƹ��µģ��ڽ��ڶ��������в�ͬ��Ԫ�ظ�ֵ���µ�
//		cout << "The elements of group 1 are" << endl;
//		for(int i = 0; i < amount1; i++)
//			cout << group_one[i];
//		cout << "The elements of group 2 are" << endl;
//		for(int i = 0; i < amount2; i++)
//			cout << group_two[i];		
		
		//��ǰ���鱣��current_players 
		for(int i = 0; i < amount1; i++){
			if(!in_the_group(group_one[i])){
				new_group[k] = group_one[i]; 
//				cout << "���С��1�����Ԫ�ص�ǰ��Ա��������û������룬������" << new_group[k] << "����Ա" << endl; 
				current_players_amount++;
				k++;
			}			
			 
		}
		
		for(int i = 0; i < amount2; i++){
			if(!in_the_group(group_two[i])){ 
				new_group[k] = group_two[i];
//				cout << "���С��2�����Ԫ�ص�ǰ��Ա��������û������룬������" << new_group[k] << "����Ա" << endl; 		
				k++; 
				current_players_amount++;
			}	
		
		} 
//		cout << "k�Ĵ�С��" << k << "new_group ��" << endl;
//		for(int i = 0; i < k; i++)
//			cout << new_group[i] << " ";
//		cout << endl;
		return new_group;		
	}
}

bool club::advanced_search_player(struct command_for_compare[], int op1, int op2, char op){
//bool club::advanced_compare_to_search(struct command_for_compare compare[], int player_id, int command_number){
// ������������op1�ĺ���������op2�ģ��õ��������飬�ٽ��op��������в����᷽��Ķ�ɡ�����
	if(op1 != -13 && op2 != -13){
		int *group_one = (int *) malloc(sizeof(int) * 100); 
		int *group_two = (int *) malloc(sizeof(int) * 100);
		group_one = init_group(group_one, 100);
		group_two = init_group(group_two, 100);
//		cout << "lala";	
		int i = 0, j = 0;
		cout << club::get_player_amount();
		for(int k = 0; k < club::get_player_amount(); k++){
			if(advanced_compare_to_search(compare, k, op1)){// ��ӵ�k����Ա��������������С�� 
				group_one[i] = k;
//				cout << "group_one��, ������Ϊ" << op1 << "��ʱ" << k << "����Ա�������� " << players.at(k).get_name() << endl;
				i++;
			}
			
//			cout << " We path through the if..." << endl; 			
			//������������1����Ա����Ϊ i ��			
			if(advanced_compare_to_search(compare, k, op2)){
				group_two[j] = k;
//				cout << "group_two�У�������Ϊ" << op2 << "��ʱ" << k << "����Ա�������� " << players.at(k).get_name() << endl;
				j++;
			}
		}
//		cout << i << endl << j;
		current_players = update_current_players(group_one, group_two, op, i, j);		
//		cout << "��������" << current_players[0];
		
//		output_current_players();
	}
	
	else if(op1 == -13 && op2 != -13){
//		cout << "�����￩������" << endl;
		int *group = (int *) malloc(sizeof (int) * 100);
		group = init_group(group, 100);
		int i = 0;
		for(int k = 0; k < club::get_player_amount(); k++){
			if(advanced_compare_to_search(compare, k, op2)){// ��ӵ�k����Ա��������������С�� 
				group[i] = k;
				i++;
			}
		}
		
//		cout << "�������group��" << endl;
//		for(int n = 0; n < i; n++)
//			cout << group[n] << " ";
//		cout << "\nop ��" << op << "current_players ������" << endl;
//		for(int n = 0; n < current_players_amount; n++)
//			cout << current_players[n];
//		cout << endl;		
		
		
		
		current_players = update_current_players(current_players, group, op, current_players_amount, i);
	}
	
	else if(op2 == -13 && op1 != -13){
//		cout << "I'm here ��" << endl; 
		int *group = (int *) malloc(sizeof (int) * 100);
		group = init_group(group, 100);
		int i = 0;
		for(int k = 0; k < club::get_player_amount(); k++){
			if(advanced_compare_to_search(compare, k, op1)){// ��ӵ�k����Ա��������������С�� 
				group[i] = k;
//				cout << "ѡ��������" << players.at(k).get_name() << endl; 
				i++;
			}
		}
//		cout << "\n\n������\n\n";
		
//		cout << "The elements of group are" << endl;
//		for(int j = 0; j < i; j++)
//			cout << group[j];
//		cout << "The elements of ��ǰ��Ա�� are" << endl;
//		for(int j = 0; j < current_players_amount; j++)
//			cout << current_players[j];	 
//		cout << endl;
		
		current_players = update_current_players(group, current_players, op, i, current_players_amount);
	}
	
	else
		cout << "ERROR" << endl;

}
void club::get_players_number(string command){
	stack<char> st; 
	for(int i = 0; command[i] != NULL;){
		if((command[i] - '0') >= 0 && (command[i] - '0') <= 9 && command[i+1] == NULL){
//			cout << "��ջ�ַ�Ϊ" << command[i] << endl; 
			for(int k = 0; k < club::get_player_amount(); k++)
				if(compare_to_search(compare, k, 1)){// ��ӵ�k����Ա��������������С�� 
					current_players[current_players_amount] = k;
					current_players_amount++;
//					cout << "ֻ��һ������������" << k << "����Ա�������������� " << players.at(k).get_name() << endl;		
				}
		}
		
		if((command[i] - '0') >= 0 && (command[i] - '0') <= 9){
//			cout << "��ջ�ַ�Ϊ" << command[i] << endl; 
			st.push(command[i]); // command ��֮ǰ����string�����int k �� - '0' �󼴿ɵ�intʹ�� 
			i++;
		}	
//		else if(is_operator(command[i])){ 
		else{
//			cout << "�������ַ�Ϊ" << command[i] << endl; 			
			int op1, op2;
			op1 = st.top() - '0';// ����� ѹջһ��# ���ȡ����op��#��ֻ����������һ������ͬʱ���Ǵ�ʱ�ķ���&��|�����ĵ�ǰ��Ա���鼴�� 
//            cout << "op1 ��" << op1 << endl;
 //           cout << "op1 + 1 ��" << op1 + 1 << endl;
			st.pop();
			op2 = st.top() - '0';
  //          cout << "op2 ��" << op2 << endl;
 //           cout << "op2 + 1 ��" << op2 + 1 << endl;
			st.pop();
			
//			cout << "command[i]��" << command[i] << endl; 
			switch(command[i]){
				case '&':
					advanced_search_player(compare, op1, op2, '&');// ��&������ ����op1 op2�������������µ�ǰ����������Ա������� 
					break;
				case '|':
					advanced_search_player(compare, op1, op2, '|');			
					break;			
				default:
					cout << "�����������" << endl; 		 
					break;
			}
//			cout << "��ջ�ַ�Ϊ#" << endl;
			st.push('#'); 	
			i++;
		} // end of else
//		cout << "����if else ֮���commandΪ" << command[i] << endl;
		
	} // end of for
//	cout << "�� get_player_number�����еõ������з�����������Ա�����Ϊ:" << endl;
//	cout << "\n\n\n" << current_players_amount << "\n\n\n";
//	for(int i = 0; i < current_players_amount; i++)
//		cout << current_players[i] << "   ";
}// end of get_players_number
void club::output_current_players(){
	if(current_players_amount == 0)
		cout << "û���ҵ�������������Ա��" << endl;
	else{
		cout << "\n��ǰ������������Ա����Ϊ" << current_players_amount << " ������" << endl; 
		for(int i = 0; i < current_players_amount; i++)
		cout << current_players[i] << "����Ա" << players.at(current_players[i]).get_name() << endl;
		cout << endl;
	}	  
	
}

bool in_player_group(int op, int j){
	for(int i = 0; i < MaxPlayerAmount && player_group[op][i] != -1; i++){
		if(player_group[op][i] == j)
			return true;
	}
	return false;
	
}
bool club::advanced_compare_to_search(struct command_for_compare compare[], int player_id, int command_number){
//	cout << "blablabalbalbal �˶�Ա" << player_id << "�ŵ�����Ϊ" <<players.at(player_id).get_age() << endl; 
		int com = 0; 
		if(compare[command_number].content == "age") com = 1;
		if(compare[command_number].content == "salary") com = 2;
		if(compare[command_number].content == "transfer") com = 3;
		if(compare[command_number].content == "kick") com = 4;
		if(compare[command_number].content == "year") com = 5;		
	 
			
		switch (com){	
			case 1:
				if( (compare[command_number].symbol == '>' && compare[command_number].no == false 
				&& players.at(player_id).get_age() <= compare[command_number].number ) ||
				(compare[command_number].symbol == '<' && compare[command_number].no == false 
				&& players.at(player_id).get_age() >= compare[command_number].number ) )
					return false;
				else if( (compare[command_number].symbol == '>' && compare[command_number].no == true 
				&& players.at(player_id).get_age() > compare[command_number].number ) ||
				(compare[command_number].symbol == '<' && compare[command_number].no == true 
				&& players.at(player_id).get_age() < compare[command_number].number ) )
					return false;
				break;	
			case 2:
				if( (compare[command_number].symbol == '>' && compare[command_number].no == false 
				&& players.at(player_id).get_salary() <= compare[command_number].number ) ||
				(compare[command_number].symbol == '<' && compare[command_number].no == false 
				&& players.at(player_id).get_salary() >= compare[command_number].number ) )
					return false;
				else if( (compare[command_number].symbol == '>' && compare[command_number].no == true 
				&& players.at(player_id).get_salary() > compare[command_number].number ) ||
				(compare[command_number].symbol == '<' && compare[command_number].no == true 
				&& players.at(player_id).get_salary() < compare[command_number].number ) )
					return false;
				break;
			case 3:
				if( (compare[command_number].symbol == '>' && compare[command_number].no == false 
				&& players.at(player_id).get_transfer() <= compare[command_number].number ) ||
				(compare[command_number].symbol == '<' && compare[command_number].no == false 
				&& players.at(player_id).get_transfer() >= compare[command_number].number) )
					return false;
				else if( (compare[command_number].symbol == '>' && compare[command_number].no == true 
				&& players.at(player_id).get_transfer() > compare[command_number].number ) ||
				(compare[command_number].symbol == '<' && compare[command_number].no == true 
				&& players.at(player_id).get_transfer() < compare[command_number].number ) )
					return false;
				break;
			case 4:
				if( (compare[command_number].symbol == '>' && compare[command_number].no == false 
				&& players.at(player_id).get_score() <= compare[command_number].number ) ||
				(compare[command_number].symbol == '<' && compare[command_number].no == false 
				&& players.at(player_id).get_score() >= compare[command_number].number ) )
					return false;
				else if( (compare[command_number].symbol == '>' && compare[command_number].no == true 
				&& players.at(player_id).get_score() > compare[command_number].number ) ||
				(compare[command_number].symbol == '<' && compare[command_number].no == true 
				&& players.at(player_id).get_score() < compare[command_number].number ) )
					return false;
				break;
			case 5:
				if( (compare[command_number].symbol == '>' && compare[command_number].no == false 
				&& players.at(player_id).get_year() <= compare[command_number].number ) ||
				(compare[command_number].symbol == '<' && compare[command_number].no == false 
				&& players.at(player_id).get_year() >= compare[command_number].number ) )
					return false;
				else if( (compare[command_number].symbol == '>' && compare[command_number].no == true 
				&& players.at(player_id).get_year() > compare[command_number].number ) ||
				(compare[command_number].symbol == '<' && compare[command_number].no == true 
				&& players.at(player_id).get_year() < compare[command_number].number ) )
					return false;
				break;
			default:
//				cout << "compare �������� ���޷��Ƚϡ�" << endl;
				break;
		}// end of switch
		
	//����Ƚ����� �����true 
	return true;
}//end of compare
int *update_current_players_withnak(int *group_one, int *group_two, char op, int amount1, int amount2){

	
	int *new_group = (int *)malloc(sizeof(int) * 100);
	//��ʼ�� 
	for(int i = 0; i < 100; i++)
		new_group[i] = -1;
	int k = 0;// ��ʾnew_group���±� 		
	if(op == '&'){
		if(group_one[0] == -1 || group_two[0] == -1) // ��һ��Ԫ�ؾ���-1��˵�����Ͽգ����⵽������ȡ&��ֱ�ӷ��ؼ��� 
			return new_group;
		for(int i = 0; i < amount1; i++){
			for(int j = 0; j < amount2; j++){
				if(group_one[i] == group_two[j]){ 
					new_group[k] = group_one[i];
					k++; 
				} 
			}
		}
//		cout << "������" << endl;
		return new_group;
		
	}
	
	if(op == '|'){// �����ȡ������ �Ƚ���һ��������ȫ���Ƹ��µģ��ڽ��ڶ��������в�ͬ��Ԫ�ظ�ֵ���µ�
//		cout << "The elements of group 1 are" << endl;
//		for(int i = 0; i < amount1; i++)
//			cout << group_one[i];
//		cout << "The elements of group 2 are" << endl;
//		for(int i = 0; i < amount2; i++)
//			cout << group_two[i];		
		
		//��ǰ���鱣��current_players 
		for(int i = 0; i < amount1; i++){
			new_group[k] = group_one[i]; 
//			cout << "���С��1�����Ԫ�ص�ǰ��Ա��������û������룬������" << new_group[k] << "����Ա" << endl; 
			k++;			 
		}
		
		for(int i = 0; i < amount2; i++)
			for(int j = 0; j < amount1; j++){
				if(group_one[j] == group_two[i])
					break;
				else if(j+1 == amount1){ 
					new_group[k] = group_two[i];
//					cout << "���С��2�����Ԫ�ص�ǰ��Ա��������û������룬������" << new_group[k] << "����Ա" << endl; 		
					k++; 
				}	
			}
		 
//		cout << "k�Ĵ�С��" << k << "new_group ��" << endl;
//		for(int i = 0; i < k; i++)
//			cout << new_group[i] << " ";
//		cout << endl;
		return new_group;		
	}
} 

void club::advanced_search_player_withnak(struct command_for_compare[], char op1, char op2, char op){
	int *temp_group = (int *) malloc(sizeof(int) * 100);
	if(op1 != -13 && op2 != -13){
		int *group_one = (int *) malloc(sizeof(int) * 100); 
		int *group_two = (int *) malloc(sizeof(int) * 100);
		group_one = init_group(group_one, 100);
		group_two = init_group(group_two, 100);
//		cout << "lala";	
		int i = 0, j = 0;
//		cout << club::get_player_amount();
		if(op1 >= input_order_amount){ // ˵�����¼����orderС�飬�������� 
//			cout << "xixi1\n";			
			group_one = player_group[op1]; 
			int amount = 0;
			for(amount = 0; player_group[op1][amount] != -1; amount++);
			i = amount;			
		}
		if(op2 >= input_order_amount){ // ˵�����¼����orderС�飬�������� 
//			cout << "xixi2\n";
			group_two = player_group[op2];  
			int amount = 0;
			for(amount = 0; player_group[op1][amount] != -1; amount++);
			j = amount;
		}
		for(int k = 0; k < club::get_player_amount(); k++){
			if(advanced_compare_to_search(compare, k, op1) && op1 < input_order_amount){// ��ӵ�k����Ա��������������С�� 
				group_one[i] = k;
//				cout << "group_one��, ������Ϊ" << op1 << "��ʱ" << k << "����Ա�������� " << players.at(k).get_name() << endl;
				i++;
			}
			
//			cout << " We path through the if..." << endl; 			
			//������������1����Ա����Ϊ i ��			
			if(advanced_compare_to_search(compare, k, op2) && op2 < input_order_amount){
				group_two[j] = k;
//				cout << "group_two�У�������Ϊ" << op2 << "��ʱ" << k << "����Ա�������� " << players.at(k).get_name() << endl;
				j++;
			}
		}
//		cout << i << endl << j;
		temp_group = update_current_players_withnak(group_one, group_two, op, i, j);
		
		
		
		if(temp_group[0] == -1){// ˵���� 
			player_group[temp_order_amount][0] = -1;		
			return;
		}
		
		
		
		
		int k = 0;
		for(int i = 0; temp_group[i] != -1; i++){			
			player_group[temp_order_amount][k] = temp_group[i]; 
			k++;
		}
		return;
	}
	
	
	else
		cout << "ERROR" << endl;		
	
}
void club::get_players_number_with_nak(string command){
/*
	�ѷֱ�����1��current_order_amount �����������浽 player_group[0~current_order_amount][100]
	��ջ���㣨��&|��������µ�player_group�У������±귵��ѹջ 

*/ 
	int k = 0; // ������������ĳһ��order����Ա���� 
	temp_order_amount = 0;// ��ջ����ʱ��ǰָ��������ʼ��Ϊ0 
	for(int i = 0; i < current_order_amount; i++){
        k = 0;
		for(int j = 0; j < club::get_player_amount(); j++){ 	
			if(advanced_compare_to_search(compare, j, i)){
        		player_group[i][k] = j;
//        		cout << "player_group" << i << k << "��" << j <<endl;
				k++;
			}
		}
		temp_order_amount++;
	}
		

	stack<char> st;
	for(int i = 0; command[i] != NULL;){
		if((command[i] - '0') >= 0 && (command[i] - '0') <= 9){
//			cout << "��ջ�ַ�Ϊ" << command[i] << endl; 
			st.push(command[i]); // command ��֮ǰ����string�����int k �� - '0' �󼴿ɵ�intʹ�� 
			i++;
		}	
		else if(command[i] == '!'){
//			cout << "��ջ�ַ�Ϊ��ִ�е�ջ����"<< endl; 
			int op = st.top() - '0'; // ��ʱ������������Ա���� player_group[op][]�� 
//		 	cout << "����op��" << op << endl; 
//			cout << "��ǰָ�������" << temp_order_amount << endl; 
//			cout << "player_group[op][0] ��" << player_group[op][0] << endl;
			k = 0;
			
			if(player_group[op][0] == -1){ // ˵��û�� 
				for(int j = 0; j < club::get_player_amount(); j++){ // ȫ���Ա���� 
					player_group[temp_order_amount][k] = j;
//					cout << "plus" << j << "��" << endl; 
					k++;
				}
			}
			
			
			
			else if(player_group[op][0] != -1){  // ������ȡ���� 				
//				cout << player_group[op][0] << player_group[op][1] << player_group[op][2] << player_group[op][3] << endl;
//				cout << "wu"; 
				for(int j = 0; j < club::get_player_amount(); j++) //
					if(!in_player_group(op, j)){
//						cout << "wocao" << j << endl;
						player_group[temp_order_amount][k] = j;						
						k++;
					}	
			}
//			cout << player_group[temp_order_amount][0] << endl<<endl<<endl;
			//Ϊ-1�Ļ�˵���µ�player_groupΪ�ռ� 
			
			st.pop();// ��������ָ��� 
			st.push(temp_order_amount + '0');// ����֮���ָ���ѹջ 
//			cout << "ѹջָ���Ϊ" << temp_order_amount << endl;
			temp_order_amount++; 
			i++;
		}
		
		else{
//			cout << "�������ַ�Ϊ" << command[i] << endl; 			
			int op1, op2;
			op1 = st.top() - '0';// ����� ѹջһ��# ���ȡ����op��#��ֻ����������һ������ͬʱ���Ǵ�ʱ�ķ���&��|�����ĵ�ǰ��Ա���鼴�� 
  //          cout << "op1 ��" << op1 << endl;
 //           cout << "op1 + 1 ��" << op1 + 1 << endl;
			st.pop();
			op2 = st.top() - '0';
//            cout << "op2 ��" << op2 << endl;
 //           cout << "op2 + 1 ��" << op2 + 1 << endl;
			st.pop();
			
//			cout << "command[i]��" << command[i] << endl; 
			switch(command[i]){
				case '&':
					advanced_search_player_withnak(compare, op1, op2, '&');// ��&������ ����op1 op2�������������µ�ǰ����������Ա������� 
					//��������player_group[temp_order_amount]
					// temp_order_amount��ջ�� temp_order_amount++ 
					break;
				case '|':
					advanced_search_player_withnak(compare, op1, op2, '|');			
					break;			
				default:
					cout << "�����������" << endl; 		 
					break;
			}
//			cout << "��ջ�ַ�Ϊ#" << endl;
			st.push(temp_order_amount + '0'); 
			temp_order_amount++;	
			i++;
		} // end of else
//		cout << "����if else ֮���commandΪ" << command[i] << endl;
		
	} // end of for
	temp_order_amount--;
	if(player_group[temp_order_amount][0] == -1)
		cout << "û���ҵ�������������Ա��" << endl;
	else{
		int amount = 0;
		for(amount = 0; player_group[temp_order_amount][amount] != -1; amount++);
		cout << "\n��ǰ������������Ա����Ϊ" << amount << " ������" << endl; 
		for(int i = 0; i < amount; i++)
			cout << player_group[temp_order_amount][i] << "����Ա" << players.at(player_group[temp_order_amount][i]).get_name() << endl;
		cout << endl;
	}	  
	
	
		
}

void all_clear(){
	current_players = NULL;
	current_players_amount = 0;
}

int club::advanced_player_search(){
	init_compare();
	init_player_group();
	nak_amount = 0;
	current_players = (int *) malloc(sizeof(int) * 100);
	cout << "Please input your order for searching or input '0' to exit \n (Make sure you've in the English input condition!)" << endl; 
	string order, command;
	fflush(stdin);
	getline(cin, order);
	if(order == "0"){
		cout << "��лʹ�ã��ټ�!" << endl;  
		return 0;
	}
	
	
	command = in_to_Post_order(order);
//	cout << "here";
	if(command == "wrong")
		return -1;
//	cout << "main ������command ��" << command << endl;
	if(current_order_amount == 0){
		cout << "δ��⵽�����������������������룡" << endl;
		return -1;
	}
//	output_order(current_order_amount);
	input_order_amount = current_order_amount; 
//	cout << endl << endl << endl;
 	
	if(nak_amount == 0){
		get_players_number(command);
		output_current_players();
	}
	else{
		get_players_number_with_nak(command); 		
	}
 	
 	all_clear();
 	return 1;
}

void player_search(club Club[]){
	init_compare();
	int club_number;
	//int Id, string Name, int Age, string Abi, int sal, int tran, int sco, int ser
	cout << "Please input the number of the club you want to search: \n";
		for(int i = 0; i < current_club_amount; i++)
			cout << i+1 << "  " << Club[i].get_club_name() << endl;
	
	cin >> club_number;
	club_number--;
	cout << endl << club_number;
	
	if(Club[club_number].club_empty()){
		cout << "���ֲ�û���ˣ�������Ӿ��ֲ���Ա��" << endl;
		return;
	}
	string go_on = "1";
	int flag = 1;
	while(go_on == "1"){
		if(flag == 1)
			Club[club_number].advanced_player_search();
		fflush(stdin);
//		output_current_players();
		cout << "Do you still want to search a player in this club? (1 for yes, 0 for no)" << endl;
		getline(cin, go_on);
		if(go_on != "1" && go_on != "0"){
			cout << "������������������" << endl;
			go_on = "1";
			flag = 0;
		}
		else
			flag = 1;
	}
		
//	int find = Club[club_number].search_player(compare);
//	if(find == -1) 
//		cout << "�Ҳ���������������Ա";
//	else
//		cout << "�ҵ�������������Ա����idΪ" << find << "\n��Ա����Ϊ" << Club[club_number].get_player_name(find) << endl;	

}
//
void player_trade(club Club[]){
	int buyer = 0, seller = 0, goods = 0;		
	cout << "�밴˳�������򷽺��������ֲ�����ţ�"  << endl;
	for(int i = 0; i < current_club_amount; i++)
		cout << i+1 << "  " << Club[i].get_club_name() << endl;
	
	cin >> buyer >> seller;
	buyer--;
	seller--; 
	cout << "�������Ա���Ϊ��" << endl;
	cin >> goods; 		
	cout << "�򷽺��������ֲ������Ʒֱ�Ϊ" << Club[buyer].get_club_name() << "��" << Club[seller].get_club_name() << endl;
	player_purchase(Club[buyer], Club[seller], Club[seller].get_player(goods));	
}


void club_adding(club Club[]){
	string name;
	int asset = 0, order = 1;
	int go_out = 0;
	string command;
	while(order != 0){
		cout << "Please input the club's name, asset consequently: \n";
		fflush(stdin);
		getline(cin, command);
		int i = 0;
		while(command[i] == ' ') i++;		
		while(command[i] != ' '){
			name += command[i];
			i++;
		}
		
		while(command[i] == ' ') i++;		
		while(command[i] != NULL){
			if(command[i] < '0' || command[i] > '9'){
				cout << "Bad input! Try again!\n";
				go_out = 1;
				break;
			}
			else
				asset = 10 * asset + command[i] - '0';
			i++;	
		}
		
		if(go_out == 1){
			go_out = 0;
			cout << endl << "Do you still want to add clubs? 1 for yes; 0 for no:  \n";
			cin >> order;
		}
			
		else{
			Club[current_club_amount].init_club(name, asset);
			current_club_amount++;
			cout << "Successful adding!";
			cout << endl << "Do you still want to add clubs? 1 for yes; 0 for no:  \n";
			cin >> order;
		}		
	}
}

int is_a_club(string name, club Club[]){
	for(int i = 0; i < current_club_amount; i++)
		if(Club[i].get_club_name() == name){
			return i;
		}
			
	return -1;		
}

int output_all_players_in_the_group(club Club[]){
	if(current_club_amount == 0){
		cout << "No club has been established, please add a club first!\n";
		return -1;
	}		
	int i = 0;
	club_allPlayer_search_amount = 0;


	
//���ﲻҪÿ�ν��������壬����һ��ָ�룬Ȼ��ÿ�ν������ͷŲ�ָ���ÿ���ã�
//	string *club_allPlayer_search = (string *) malloc(sizeof(string) * current_club_amount); 
//	memset(club_allPlayer_search, 0, sizeof(string) * current_club_amount);
//	cout << "\n\n" << club_allPlayer_search[0] << " yi " << club_allPlayer_search[1] <<  endl;
	
	string *club_allPlayer_search = new string[current_club_amount + 1];
//	cout << "������" <<	current_club_amount + 1 << "��string�ռ�" << endl;
	
	for(int i = 0; i < Max_Club_Amount; i++)
	 	club_num[i] = -1;
	string order;
	fflush(stdin);
	cout << "Please input the clubs you want to search, with '||'between them:" << endl;
	getline(cin, order);
//	cout << order;
	i = 0; 
	while(order[i] != NULL){
//		cout << "while ǰ i=" << i << endl;
		while(order[i] == ' ') i++;
//		cout << "while �� i=" << i << endl;
		if(order[i] != '@'){
			cout << "��ʼ������������! \n";
//			cout << "�������" << order[i] << endl;
//			cout << "i = " << i << endl; 
			delete []club_allPlayer_search; 
//			cout << "�ͷſռ�" << endl;	
			return -1;
		}
		else
			i++;
		while(order[i] == ' ') i++;	
		if(order.substr(i, 4) != "club"){
			cout << "ָ����������\n";
			delete []club_allPlayer_search; 	
//			cout << "�ͷſռ�" << endl;
			return -1;
		}
		i = i + 4;
//		cout << "lalal" << order[i]; 
		while(order[i] == ' ') i++;	
		if(order[i] != '='){
			cout << "'='��������3\n";
			delete []club_allPlayer_search; 	
//			cout << "�ͷſռ�" << endl;
//			cout << "������" << order[i] << endl; 
			
			return -1;
		}
		else 
			i++;
//		cout << "here" << order[i]<<endl;
		while(order[i] == ' ') i++;	
		
		
//		cout << "bla";
		for(; (order[i] >= 'A' && order[i] <= 'Z') || (order[i] >= 'a' && order[i] <= 'z'); i++){/*��@����ĵ�һ���ǿո��ַ���ʼ*/
			club_allPlayer_search[club_allPlayer_search_amount] += order[i];		
//			cout<<order[i]<<endl;
		}
		
		if((club_num[club_allPlayer_search_amount] = is_a_club(club_allPlayer_search[club_allPlayer_search_amount], Club)) == -1){
			cout << "The club input not found, you have to try again!\n";
			delete []club_allPlayer_search; 	
//			cout << "�ͷſռ�" << endl;
			return -1; 
		}
//		cout << "1\n";
//		cout <<	club_allPlayer_search[club_allPlayer_search_amount];
		club_allPlayer_search_amount++;
		while(order[i] == ' ') i++;	
		if(club_allPlayer_search_amount == current_club_amount && order[i] != NULL){
			cout << "����ָ����࣡\n";
			delete []club_allPlayer_search; 	
//			cout << "�ͷſռ�" << endl;
			return -1; 
		}
//		cout << "2\n";
//		cout << i << " lala " << order[i] << endl; 
//		if(order[i] == NULL) cout << "yes";
		if(order[i] != NULL && order.substr(i, 2) != "||"){
			cout << "�������������\n";
			delete []club_allPlayer_search; 	
//			cout << "�ͷſռ�" << endl;
			return -1; 	
		}




//�ѵ� string���һ���ַ��ǿգ�������������������ַ��ֲ��ǿ��ˣ���	




	
		else if(order[i] == NULL)
			break;
		else	
			i += 2;
	}
//	 cout << "3\n";
	 delete []club_allPlayer_search; 
//	 cout << "�ͷſռ�" << endl;	
	 return club_allPlayer_search_amount;
}

void output_players_of_groups(club Club[]){
	int result = output_all_players_in_the_group(Club);
	if(result == -1){
		cout << "Please choose the order again! \n";
		return;
	}
	cout << "\n\n";
	for(int i = 0; i < club_allPlayer_search_amount; i++){
		if(Club[club_num[i]].get_player_amount() == 0){
			cout << "Club " << Club[club_num[i]].get_club_name() << " has no players currently!\n\n";
			continue;
		}
		cout << "The players of the club " << Club[club_num[i]].get_club_name() << " are:\n";
		for(int j = 0; j < Club[club_num[i]].get_player_amount(); j++)
			cout << Club[club_num[i]].get_player_name(j) << endl;
		cout << endl;
	}
	
}

void player_adding(club Club[], player Player[]){
	int club_number = -1, order = 1, age, salary, money_to_transfer, scores, service_year;
	string name, ability;
	cout << endl << "Which team do you want to add the player in? Please input the number of the club:\n";
	for(int i = 0; i < current_club_amount; i++){
		cout << i+1 << "  " << Club[i].get_club_name() << endl;
	}
	cin >> club_number;
	club_number--;// ��Ϊ1����ʵ��club[0] 
	while(order != 0){
		cout << endl << "Please input the player's name, age, ability, salary, money to transfer, total scores and exprience years consequently: \n";
		cin >> name >> age >> ability >> salary >> money_to_transfer >> scores >> service_year;
		Player[current_player_amount].init_player(current_player_amount, name, age, ability, salary, money_to_transfer, scores, service_year);
		Club[club_number].add_player(Player[current_player_amount]);
		current_player_amount++;
		cout << endl << "Do you still want to add player in this club? 1 for yes; 0 for no:  \n";
		cin >> order;
	}
	
}
string dim_search_procedure(club Club[]){
	if(current_club_amount == 0){
		cout << "No club has been established, please add a club first!\n";
		return "-1";
	}
	cout << "Please input your order to dim search(like: @name~abc)" << endl;
	string order;
	fflush(stdin);
	getline(cin, order);
	int i = 0;
	string sub_name;
	while(order[i] != NULL){
//		cout << "2333 \n";
		while(order[i] == ' ') i++;
//		cout << "what";
		if(order[i] != '@'){
			cout << "��ʼ������������! \n";
			return "-1";
		}
		else
			i++;
		while(order[i] == ' ') i++;	
		if(order.substr(i, 4) != "name"){
			cout << "ָ����������\n";
			return "-1";
		}
		i = i + 4;
		while(order[i] == ' ') i++;	
		if(order[i] != '~'){
			cout << "��ûд~��������\n";
			return "-1";
		}
		else
			i++;		
//		cout << "Ŷ\n";
		while(order[i] == ' ') i++;					
		while(order[i] != NULL){
			sub_name += order[i];
			i++;
		}
		cout << sub_name << endl;	
	
	} // end of while
	return sub_name;			
}
bool is_substring(string sub_name, string str){
	int sublength, length;
	for(sublength = 0; sub_name[sublength] != NULL; sublength++);// �Ӵ����� 
	for(length = 0; str[length] != NULL; length++);// ĸ������ 
	if(sublength > length)
		return false;
	for(int i = 0; i <= length - sublength; i++)
		if(str.substr(i, sublength) == sub_name)
			return true;
	return false;
}
void dim_search_players(club Club[]){
	string result = dim_search_procedure(Club);
	int found = 0;
//	cout << "out" << endl;
	if(result == "-1"){
		cout << "Please choose the order again! \n";
		return;
	}
	cout << "\n\n";
	for(int i = 0; i < current_club_amount; i++){
		cout << "In the club " << Club[i].get_club_name() << ":\n";
		for(int j = 0; j < Club[i].get_player_amount(); j++)
			if(is_substring(result, Club[i].get_player(j).get_name())){
				cout << Club[i].get_player(j).get_name() << endl;
				found = 1; 
			}
		if(found == 0)
			cout << "We can't find anyone in this club with the subname you've input!\n\n";
		found = 0;			
	}
}
void show_screen(){
	
	cout << endl << "Please input the order:" << endl << "1  Add a new club" << endl << 
	"2  Add a new player"<< endl << "3  Search for a player" << endl << "4  Player purchasing" 
	<< endl << "5  Search all the players in a group" << endl << "6  dim search players in all groups" 
	<< endl << "0  exit the system" << endl;
}

void read_file(){
	ifstream in("input.txt");
	int next = 0;
	in >> next;
	string name;
	int asset = 0;
	while(next != 0){
		in >> name >> asset;
		Club[current_club_amount].init_club(name, asset);
		current_club_amount++;
//		cout << endl << "Do you still want to add clubs? 1 for yes; 0 for no:  \n";
		in >> next;
	}
	
	
	int club_number = -1, order = 1, age, salary, money_to_transfer, scores, service_year;
	string ability;
//	cout << endl << "Which team do you want to add the player in? Please input the number of the club:\n";
//	for(int i = 0; i < current_club_amount; i++){
//		cout << i+1 << "  " << Club[i].get_club_name() << endl;
//	}
		
	in >> club_number;
	while(club_number != -1){
		while(order != 0){
	//		cout << endl << "Please input the player's name, age, ability, salary, money to transfer, total scores and exprience years consequently: \n";
			in >> name >> age >> ability >> salary >> money_to_transfer >> scores >> service_year;
			Player[current_player_amount].init_player(current_player_amount, name, age, ability, salary, money_to_transfer, scores, service_year);
			Club[club_number].add_player(Player[current_player_amount]);
			current_player_amount++;
	//		cout << endl << "Do you still want to add player in this club? 1 for yes; 0 for no:  \n";
			in >> order;
			
		}
		in >> club_number;
		if(club_number != -1) // ����while���Ž� 
			order = 1;
	}
	in.close();
}

void output_file(){
	ofstream out("output.txt");
	for(int i = 0; i < current_club_amount; i++){
		out << Club[i].get_club_name() << " Total asset: " << Club[i].get_cash() << endl;
		out << "All the players:\n";
		for(int j = 0; j < Club[i].get_player_amount(); j++){
			out << Club[i].get_player(j).get_name() << endl;
		}
		out << endl;		
	}
	out.close();
	
}

int main(){
//	player 	Messi 29 score 100000 200000 100 5
//			C_R 31 score 50000 190000 90 6
//			Zhengzhi(3, "Zhengzhi", 36, "score", 30000, 100000, 50, 8),
//			Wangdalei(4, "Wangdalei", 26, "defend", 50000, 130000, 3, 4),
//			Neymar(5, "Neymar", 24, "score", 110000, 180000, 70, 2);
//	Barcelona.add_player(Messi);
//	Barcelona.add_player(C_R);
//	Barcelona.add_player(Wangdalei);
//	Barcelona.add_player(Neymar);
//	cout <<Barcelona.get_player_amount(); 
// int Id, string Name, int Age, string Abi, int sal, int tran, int sco, int ser
//Barcelona 30000  1 Manchester 500000 0 1 Messi 29 score 100000 200000 100 5 1 C_R 31 score 50000 190000 90 6 0 1
//	

	char order = '1';
	char bad_input = 0;
	int just_input_bad = 0;
	current_player_amount = current_club_amount = 0;	
	
	read_file();
	cout << "Welcome to the Soccer Club Management System!" << endl;

	while(order != '0'){
		show_screen();
		if(just_input_bad == 1){
			fflush(stdin);
			just_input_bad = 0;
		}
		cin >> order;
		switch(order){
			case '1':				
				club_adding(Club);
				break;
			case '2':	
				player_adding(Club, Player);
				break;
			case '3':		
				player_search(Club);
				break;
			case '4':	
				player_trade(Club);
				break;
			case '5':
				output_players_of_groups(Club);
				break;	
			case '6':
				dim_search_players(Club);	
				break;
			case '0':
				cout << "You've aquired to leave the system" << endl;
				break;  
			default:
				while(bad_input != '\n'){
					bad_input = getchar();
				}
				cout << "bad aquirement, try again!" << endl;
				just_input_bad = 1;
				continue;	
		}	
	}
	output_file();
	cout << "\n We have put the information into the file output.txt. Thanks for your using, see you next time!";
	return 0;
}
/*
sometimes....
terminate called after throwing an instance of 'std::out_of_range'
  what():  vector::_M_range_check

This application has requested the Runtime to terminate it in an unusual way.
Please contact the application's support team for more information....
�����������vector��Խ�� 
*/
