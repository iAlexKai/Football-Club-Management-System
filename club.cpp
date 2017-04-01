//string 读取一行的时候，最后的回车键读的是NULL 
//switch() 括号内只能是整形比方说 int、char之类的,不能是string 
/*
	如果不用所谓堆栈，只统计当前括号数量，遇到左括号+1，遇到右括号-1， 遇到 @获取条件后进行搜索 并结合之前输入的
	@@ ||确定符合条件球员的数组，　遇到连续的 && || 只是改变当前指令，遇到＼ｎ且括号数减为０正确停止，否则为
	错误输入情况 
	new 了之后一定记得释放 delete 务必的！否则直接越界报错 
	string *ptr = new string[amount]
	delete []ptr;
	
*/ 
/*
	强了！！ 
	完成！处理这一大项！！！！
	接下来处理简单的  @club=A 
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
int *current_players; // 保存高级搜索中当前符合条件的球员的序号, 初始化为全体球员 
int *club_to_search;
int current_club_amount_to_search;
int current_players_amount;// 初始化为0 
int current_order_amount;
int temp_order_amount;// 保存在进行栈操作时候当前指令数量 
int input_order_amount; // 用户输入的指令条数 
int player_group[MaxOrderAmount][MaxPlayerAmount];// 保存当前满足各种条件对应的球员数组 
int nak_amount;
int club_allPlayer_search_amount;
int club_num[Max_Club_Amount];

struct command_for_compare{
	string content;   // 比较对象，例如： age 
	bool no; // 表示前面那个! 
	char symbol; // 是大是小 ， 例如 > 
	int number; // 和多少比， 例如 12
	int result[Max_Player_Amount];// 存储符合此条件的球员的所有序号 
};
struct command_for_compare compare[10]; // 假设用户输入的限制条件的个数最大不超过10 


void init_compare(){
	for(int i = 0; i < 10; i++){  // string 类型默认为空串！ 
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
//			cout << "跳过了一个空格"; 	
		}
		else 
			return control;
	}
		
}


bool club::compare_to_search(struct command_for_compare compare[], int player_id, int order_amount){
//	cout << "blablabalbalbal 运动员" << player_id << "号的年龄为" <<players.at(player_id).get_age() << endl; 
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
				cout << "compare 输入有误 ，无法比较。" << endl;
				break;
		}// end of switch
		
	}// end of for,如果比较无误 则输出true 
	return true;
}//end of compare




void club::update_player(player updater) {
	int new_age, new_salary, new_transfer, new_score, new_year;
	char command[20];
	for (int i = 0; i < 20; i++)
		command[i] = 0;
	cout << "请输入要更改的该球员的信息，（eg：若要修改年龄则输入年龄前的编号1，条件之间用空格隔开）" << endl
		<< "1、年龄；2、年薪；3、转会费；4、进球总数；5、 服役年限" << endl;
	cin.getline(command, 20);
	for (int i = 0; i < 20 && command[i] != '\0'; i++) {
		if (command[i] == ' ')
			continue;
		else
			switch (command[i]) {
			case ' ':
				break;
			case '1':
				cout << "年龄更改为多少？" << endl;
				cin >> new_age;
				updater.reset_age(new_age);
				break;
			case '2':
				cout << "年薪更改为多少？" << endl;
				cin >> new_salary;
				updater.reset_salary(new_salary);
				break;
			case '3':
				cout << "转会费更改为多少？" << endl;
				cin >> new_transfer;
				updater.reset_money_to_transfer(new_transfer);
				break; 
			case '4':
				cout << "进球总数更改为多少？" << endl;
				cin >> new_score;
				updater.reset_scores(new_score);
				break;		
			case '5':
				cout << "服役年限更改为多少？" << endl;
				cin >> new_year;
				updater.reset_year(new_year);
				break;
			default:
				cout << "输入有误";
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
		cout << "买方资金不足，无法购买此球员，交易失败" << endl;
		return;
	}

	//交易成功时
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
    		cout << "运算符优先级比较时出错" << endl; 	
			return -2;
		}	
	}
	
    else if (op1 == '|'){
		if(op2 == '&' || op2 == '!')
    		return -1;
		else if(op2 == '|')
			return 0;
		else {
			cout << "运算符优先级比较时出错" << endl; 	
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
			cout << "运算符优先级比较时出错" << endl; 	
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
		遇到@存一个compare[]，入栈compare数组的下标，向后走到数字之后的一个字符	
*/
	int i = 0, j = 0, bracket_amount = 0;
	current_order_amount = 0; // 表示compare数组的下标 
	string result;
	char temp_order[20][20] = {0};
	char *temp = (char *) malloc (sizeof(char));
	stack<char> st;	
	
		
	for(;order[i] != NULL;){// string的最后一个字符是NULL	
		while(order[i] == ' ') { 
//		cout << "跳过空格\n"; 
		    i++;
		}	// 跳过空格
		if(order[i] == '('){
			bracket_amount++;
			st.push(order[i]);
//			cout << order[i] << "入栈" << endl;
			i++;
			while(order[i] == ' ') { 
			//cout << "跳过空格\n"; 
			    i++;
			}	// 跳过空格
		}
		//刚写完加入！ 
		
		
		
	 	else if(order[i] == ')'){
//	 		cout << "这儿倒是进来了" << endl;
			bracket_amount--;
			if(bracket_amount < 0){
				cout << "输入指令中右括号数量大于左括号，输入出错！" << endl;
				return "wrong";
			}
				 
//	 		cout << st.top() << endl;
			while(st.top() != '('){
//				cout << "here\n\n\n\n\n" << endl;
				result += st.top();// 字符的话，是可以直接加到string后面的 
//				cout << " The result is " << result[j] << endl << endl;
				st.pop();
			}
			
			st.pop();// 弹出左括号 
//			cout << "弹出一个左括号\n" ; 
			i++; 
		}
		
		else if (order[i] == '@'){//如果是一个判断条件compare 
			i++;
			while(order[i] == ' '){ 
//			cout << "跳过空格\n"; 
			    i++;}	// 跳过空格
			//检测下一个字符是不是正经字符 
			if(!(order[i] >= 'a' && order[i] <= 'z')){
				cout << "输入错误！" << endl;
				return "wrong";
			}
			
			for(j = 0; order[i] >= 'a' && order[i] <= 'z'; j++){/*从@后面的第一个非空格字符开始*/
				temp_order[current_order_amount][j] = order[i];
				i++;
			}
			
			compare[current_order_amount].content = temp_order[current_order_amount];
			if(!valid_compare(compare[current_order_amount].content)){
				cout << "输入错误!" << endl; 
				return "wrong";
			} 
			
			
			while(order[i] == ' ') { 
//			cout << "跳过空格\n"; 
			    i++;
			}	// 跳过空格
			
			//此时order指向 > < 号 
			if(order[i] == '>')
				compare[current_order_amount].symbol = '>';
			else if(order[i] == '<')
				compare[current_order_amount].symbol = '<';
			else{
				cout << "条件输入有误" << endl; 
				return "wrong";
			}
			i++;
			
		    while(order[i] == ' ') { 
//			cout << "跳过空格\n"; 
			    i++;
			}	// 跳过空格
			
			if(!(order[i] >= '0' && order[i] <= '9')){
				cout << "条件输入有误" << endl; 
				return "wrong";		
			} 
				
			compare[current_order_amount].number = 0;	
			for(j = 0/*从@后面的第一个字符开始*/; order[i] >= '0' && order[i] <= '9'; j++){
				compare[current_order_amount].number = (order[i] - '0') + compare[current_order_amount].number * 10;
				i++;
			}
			//完成一个compare的输入， 将下标输出， 注意 compare数组下标并不入栈 
//			cout << compare[current_order_amount].content << compare[current_order_amount].symbol << compare[current_order_amount].number << endl;
			
			itoa(current_order_amount, temp, 10); // 将int型 的k 转化为char* 
//			cout << "加入" << current_order_amount << endl; 
			result += temp;  // 将 k 插到string型后面 
			
//			cout << "current_order_amount 是 " << current_order_amount << endl;
			//注意 将result[j]强制转换为int型即可！！！！ 
			 //出上一个循环时候其实i指向的是数字后面的第一个字符，因此这里千万不要再加一个i++了 
			current_order_amount++; // 完成一个指令的输入，输入下一个 
		}//end of if(order[i] == '@')
			/* else栈非空且进来的符号（&& 或者 ||等）优先级小于或等于栈顶
			 输出栈顶并弹栈，最后将进来的符号入栈*/			
		else if((order[i] == '!') || (order[i] == '&' && order[i+1] == '&') || (order[i] == '|' && order[i+1] == '|')){
			if(order[i] == '!') nak_amount++;
			else if(order[i] != '!') i++;// 先走到第二个&的位置，将这个字符设为当前字符进行优先级比较 
			while(st.empty() == false && my_precedence(st.top(), order[i]) >= 0){
				if(my_precedence(st.top(), order[i]) == -2)
					return 0; 
				result += st.top();
//				cout << "加入" << st.top() << endl; 
//				cout << "result is " << result[j] << endl << endl;
				st.pop();	
			}
			st.push(order[i]);
//			cout << order[i] << "入栈" << endl;
			i++;
		} 
			
		else{ // 进来的字符不是 @ 或 | 或 &， 出错 
			cout << "Bad input!!出错字符为" << order[i] << endl;
			return "wrong";
			i++;	
		}// end of else 				
		while(order[i] == ' ') { 
//		cout << "跳过空格\n"; 
			i++;
		}	// 跳过空格
//		cout << "即将读取的字符是" << order[i] << "再下一个是" << order[i+1] << endl;
//		if(order[i] == ')')  
//			cout << i << endl;
	}// end of for
	
	while(st.empty() == false){// 字符串读取完毕，将栈里剩余的内容输出的result数组中
		result += st.top();		
		st.pop();
	}	
	if(bracket_amount != 0){
		cout << "输入左括号的数量大于右括号，输入有误，请重新输入！" << endl;
		return "wrong"; 
	}
//	if(nak_amount != 0)
//		cout << "表达式分析完毕，有！哦~" << endl;
//	cout << "result 是" << result << endl; 
	return result; //最终把后缀表达式string传出 

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
//	cout << "我们来打印下两个数组" << endl;
//	for(int i = 0; i < amount1; i++)
//		cout << group_one[i];
//	for(int i = 0; i < amount2; i++)
//		cout << group_two[i];
	
	int *new_group = (int *)malloc(sizeof(int) * 100);
	int flag = 0;
//	cout << new_group[0]<<"fjalskdjflskjdf";
	//当前错误，没有更改new_group 
	int k = 0;// 表示new_group的下标 
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
//		cout << "哈哈哈" << new_group[k] << endl;
		if(flag == 1) 
			return new_group;
		else // 没有任何更改的时候， 返回当前的current_players 
			return current_players;	
	}
	
	if(op == '|'){// 如果是取并集， 先将第一个数组完全复制给新的，在将第二个数组中不同的元素赋值给新的
//		cout << "The elements of group 1 are" << endl;
//		for(int i = 0; i < amount1; i++)
//			cout << group_one[i];
//		cout << "The elements of group 2 are" << endl;
//		for(int i = 0; i < amount2; i++)
//			cout << group_two[i];		
		
		//当前新组保存current_players 
		for(int i = 0; i < amount1; i++){
			if(!in_the_group(group_one[i])){
				new_group[k] = group_one[i]; 
//				cout << "如果小组1里面的元素当前球员数组里面没有则加入，加入了" << new_group[k] << "号球员" << endl; 
				current_players_amount++;
				k++;
			}			
			 
		}
		
		for(int i = 0; i < amount2; i++){
			if(!in_the_group(group_two[i])){ 
				new_group[k] = group_two[i];
//				cout << "如果小组2里面的元素当前球员数组里面没有则加入，加入了" << new_group[k] << "号球员" << endl; 		
				k++; 
				current_players_amount++;
			}	
		
		} 
//		cout << "k的大小是" << k << "new_group 是" << endl;
//		for(int i = 0; i < k; i++)
//			cout << new_group[i] << " ";
//		cout << endl;
		return new_group;		
	}
}

bool club::advanced_search_player(struct command_for_compare[], int op1, int op2, char op){
//bool club::advanced_compare_to_search(struct command_for_compare compare[], int player_id, int command_number){
// 先找满足条件op1的和满足条件op2的，得到两个数组，再结合op对数组进行操作会方便的多吧。。。
	if(op1 != -13 && op2 != -13){
		int *group_one = (int *) malloc(sizeof(int) * 100); 
		int *group_two = (int *) malloc(sizeof(int) * 100);
		group_one = init_group(group_one, 100);
		group_two = init_group(group_two, 100);
//		cout << "lala";	
		int i = 0, j = 0;
		cout << club::get_player_amount();
		for(int k = 0; k < club::get_player_amount(); k++){
			if(advanced_compare_to_search(compare, k, op1)){// 球队的k号球员符合条件，加入小组 
				group_one[i] = k;
//				cout << "group_one中, 条件号为" << op1 << "此时" << k << "号球员符合条件 " << players.at(k).get_name() << endl;
				i++;
			}
			
//			cout << " We path through the if..." << endl; 			
			//最终满足条件1的球员数量为 i 个			
			if(advanced_compare_to_search(compare, k, op2)){
				group_two[j] = k;
//				cout << "group_two中，条件号为" << op2 << "此时" << k << "号球员符合条件 " << players.at(k).get_name() << endl;
				j++;
			}
		}
//		cout << i << endl << j;
		current_players = update_current_players(group_one, group_two, op, i, j);		
//		cout << "噢噢噢噢" << current_players[0];
		
//		output_current_players();
	}
	
	else if(op1 == -13 && op2 != -13){
//		cout << "进这里咯啦啦啦" << endl;
		int *group = (int *) malloc(sizeof (int) * 100);
		group = init_group(group, 100);
		int i = 0;
		for(int k = 0; k < club::get_player_amount(); k++){
			if(advanced_compare_to_search(compare, k, op2)){// 球队的k号球员符合条件，加入小组 
				group[i] = k;
				i++;
			}
		}
		
//		cout << "这会儿这个group是" << endl;
//		for(int n = 0; n < i; n++)
//			cout << group[n] << " ";
//		cout << "\nop 是" << op << "current_players 数组是" << endl;
//		for(int n = 0; n < current_players_amount; n++)
//			cout << current_players[n];
//		cout << endl;		
		
		
		
		current_players = update_current_players(current_players, group, op, current_players_amount, i);
	}
	
	else if(op2 == -13 && op1 != -13){
//		cout << "I'm here 亲" << endl; 
		int *group = (int *) malloc(sizeof (int) * 100);
		group = init_group(group, 100);
		int i = 0;
		for(int k = 0; k < club::get_player_amount(); k++){
			if(advanced_compare_to_search(compare, k, op1)){// 球队的k号球员符合条件，加入小组 
				group[i] = k;
//				cout << "选出来的是" << players.at(k).get_name() << endl; 
				i++;
			}
		}
//		cout << "\n\n在外面\n\n";
		
//		cout << "The elements of group are" << endl;
//		for(int j = 0; j < i; j++)
//			cout << group[j];
//		cout << "The elements of 当前球员们 are" << endl;
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
//			cout << "入栈字符为" << command[i] << endl; 
			for(int k = 0; k < club::get_player_amount(); k++)
				if(compare_to_search(compare, k, 1)){// 球队的k号球员符合条件，加入小组 
					current_players[current_players_amount] = k;
					current_players_amount++;
//					cout << "只有一个条件，并且" << k << "号球员符合条件，姓名 " << players.at(k).get_name() << endl;		
				}
		}
		
		if((command[i] - '0') >= 0 && (command[i] - '0') <= 9){
//			cout << "入栈字符为" << command[i] << endl; 
			st.push(command[i]); // command 是之前插入string后面的int k ， - '0' 后即可当int使用 
			i++;
		}	
//		else if(is_operator(command[i])){ 
		else{
//			cout << "读到的字符为" << command[i] << endl; 			
			int op1, op2;
			op1 = st.top() - '0';// 运算后 压栈一个# 如果取出的op是#则只需满足另外一个条件同时考虑此时的符号&或|，更改当前球员数组即可 
//            cout << "op1 是" << op1 << endl;
 //           cout << "op1 + 1 是" << op1 + 1 << endl;
			st.pop();
			op2 = st.top() - '0';
  //          cout << "op2 是" << op2 << endl;
 //           cout << "op2 + 1 是" << op2 + 1 << endl;
			st.pop();
			
//			cout << "command[i]是" << command[i] << endl; 
			switch(command[i]){
				case '&':
					advanced_search_player(compare, op1, op2, '&');// 在&条件下 关于op1 op2条件搜索，更新当前满足条件球员序号数组 
					break;
				case '|':
					advanced_search_player(compare, op1, op2, '|');			
					break;			
				default:
					cout << "运算符有问题" << endl; 		 
					break;
			}
//			cout << "入栈字符为#" << endl;
			st.push('#'); 	
			i++;
		} // end of else
//		cout << "出了if else 之后的command为" << command[i] << endl;
		
	} // end of for
//	cout << "在 get_player_number函数中得到了所有符合条件的球员的序号为:" << endl;
//	cout << "\n\n\n" << current_players_amount << "\n\n\n";
//	for(int i = 0; i < current_players_amount; i++)
//		cout << current_players[i] << "   ";
}// end of get_players_number
void club::output_current_players(){
	if(current_players_amount == 0)
		cout << "没有找到符合条件的球员！" << endl;
	else{
		cout << "\n当前符合条件的球员数量为" << current_players_amount << " 他们是" << endl; 
		for(int i = 0; i < current_players_amount; i++)
		cout << current_players[i] << "号球员" << players.at(current_players[i]).get_name() << endl;
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
//	cout << "blablabalbalbal 运动员" << player_id << "号的年龄为" <<players.at(player_id).get_age() << endl; 
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
//				cout << "compare 输入有误 ，无法比较。" << endl;
				break;
		}// end of switch
		
	//如果比较无误 则输出true 
	return true;
}//end of compare
int *update_current_players_withnak(int *group_one, int *group_two, char op, int amount1, int amount2){

	
	int *new_group = (int *)malloc(sizeof(int) * 100);
	//初始化 
	for(int i = 0; i < 100; i++)
		new_group[i] = -1;
	int k = 0;// 表示new_group的下标 		
	if(op == '&'){
		if(group_one[0] == -1 || group_two[0] == -1) // 第一个元素就是-1，说明集合空，主意到这里是取&，直接返回即可 
			return new_group;
		for(int i = 0; i < amount1; i++){
			for(int j = 0; j < amount2; j++){
				if(group_one[i] == group_two[j]){ 
					new_group[k] = group_one[i];
					k++; 
				} 
			}
		}
//		cout << "哈哈哈" << endl;
		return new_group;
		
	}
	
	if(op == '|'){// 如果是取并集， 先将第一个数组完全复制给新的，在将第二个数组中不同的元素赋值给新的
//		cout << "The elements of group 1 are" << endl;
//		for(int i = 0; i < amount1; i++)
//			cout << group_one[i];
//		cout << "The elements of group 2 are" << endl;
//		for(int i = 0; i < amount2; i++)
//			cout << group_two[i];		
		
		//当前新组保存current_players 
		for(int i = 0; i < amount1; i++){
			new_group[k] = group_one[i]; 
//			cout << "如果小组1里面的元素当前球员数组里面没有则加入，加入了" << new_group[k] << "号球员" << endl; 
			k++;			 
		}
		
		for(int i = 0; i < amount2; i++)
			for(int j = 0; j < amount1; j++){
				if(group_one[j] == group_two[i])
					break;
				else if(j+1 == amount1){ 
					new_group[k] = group_two[i];
//					cout << "如果小组2里面的元素当前球员数组里面没有则加入，加入了" << new_group[k] << "号球员" << endl; 		
					k++; 
				}	
			}
		 
//		cout << "k的大小是" << k << "new_group 是" << endl;
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
		if(op1 >= input_order_amount){ // 说明是新加入的order小组，跳过查找 
//			cout << "xixi1\n";			
			group_one = player_group[op1]; 
			int amount = 0;
			for(amount = 0; player_group[op1][amount] != -1; amount++);
			i = amount;			
		}
		if(op2 >= input_order_amount){ // 说明是新加入的order小组，跳过查找 
//			cout << "xixi2\n";
			group_two = player_group[op2];  
			int amount = 0;
			for(amount = 0; player_group[op1][amount] != -1; amount++);
			j = amount;
		}
		for(int k = 0; k < club::get_player_amount(); k++){
			if(advanced_compare_to_search(compare, k, op1) && op1 < input_order_amount){// 球队的k号球员符合条件，加入小组 
				group_one[i] = k;
//				cout << "group_one中, 条件号为" << op1 << "此时" << k << "号球员符合条件 " << players.at(k).get_name() << endl;
				i++;
			}
			
//			cout << " We path through the if..." << endl; 			
			//最终满足条件1的球员数量为 i 个			
			if(advanced_compare_to_search(compare, k, op2) && op2 < input_order_amount){
				group_two[j] = k;
//				cout << "group_two中，条件号为" << op2 << "此时" << k << "号球员符合条件 " << players.at(k).get_name() << endl;
				j++;
			}
		}
//		cout << i << endl << j;
		temp_group = update_current_players_withnak(group_one, group_two, op, i, j);
		
		
		
		if(temp_group[0] == -1){// 说明空 
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
	把分别满足1到current_order_amount 的所有条件存到 player_group[0~current_order_amount][100]
	弹栈计算（！&|）后存入新的player_group中，并将下标返回压栈 

*/ 
	int k = 0; // 保存符合输入的某一个order的球员个数 
	temp_order_amount = 0;// 堆栈操作时当前指令条数初始化为0 
	for(int i = 0; i < current_order_amount; i++){
        k = 0;
		for(int j = 0; j < club::get_player_amount(); j++){ 	
			if(advanced_compare_to_search(compare, j, i)){
        		player_group[i][k] = j;
//        		cout << "player_group" << i << k << "是" << j <<endl;
				k++;
			}
		}
		temp_order_amount++;
	}
		

	stack<char> st;
	for(int i = 0; command[i] != NULL;){
		if((command[i] - '0') >= 0 && (command[i] - '0') <= 9){
//			cout << "入栈字符为" << command[i] << endl; 
			st.push(command[i]); // command 是之前插入string后面的int k ， - '0' 后即可当int使用 
			i++;
		}	
		else if(command[i] == '!'){
//			cout << "入栈字符为！执行弹栈操作"<< endl; 
			int op = st.top() - '0'; // 此时满足条件的球员都在 player_group[op][]中 
//		 	cout << "这会儿op是" << op << endl; 
//			cout << "当前指令个数是" << temp_order_amount << endl; 
//			cout << "player_group[op][0] 是" << player_group[op][0] << endl;
			k = 0;
			
			if(player_group[op][0] == -1){ // 说明没人 
				for(int j = 0; j < club::get_player_amount(); j++){ // 全体成员加入 
					player_group[temp_order_amount][k] = j;
//					cout << "plus" << j << "号" << endl; 
					k++;
				}
			}
			
			
			
			else if(player_group[op][0] != -1){  // 有人则取补集 				
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
			//为-1的话说明新的player_group为空集 
			
			st.pop();// 将被！的指令弹出 
			st.push(temp_order_amount + '0');// 将！之后的指令号压栈 
//			cout << "压栈指令号为" << temp_order_amount << endl;
			temp_order_amount++; 
			i++;
		}
		
		else{
//			cout << "读到的字符为" << command[i] << endl; 			
			int op1, op2;
			op1 = st.top() - '0';// 运算后 压栈一个# 如果取出的op是#则只需满足另外一个条件同时考虑此时的符号&或|，更改当前球员数组即可 
  //          cout << "op1 是" << op1 << endl;
 //           cout << "op1 + 1 是" << op1 + 1 << endl;
			st.pop();
			op2 = st.top() - '0';
//            cout << "op2 是" << op2 << endl;
 //           cout << "op2 + 1 是" << op2 + 1 << endl;
			st.pop();
			
//			cout << "command[i]是" << command[i] << endl; 
			switch(command[i]){
				case '&':
					advanced_search_player_withnak(compare, op1, op2, '&');// 在&条件下 关于op1 op2条件搜索，更新当前满足条件球员序号数组 
					//结果数组给player_group[temp_order_amount]
					// temp_order_amount入栈后 temp_order_amount++ 
					break;
				case '|':
					advanced_search_player_withnak(compare, op1, op2, '|');			
					break;			
				default:
					cout << "运算符有问题" << endl; 		 
					break;
			}
//			cout << "入栈字符为#" << endl;
			st.push(temp_order_amount + '0'); 
			temp_order_amount++;	
			i++;
		} // end of else
//		cout << "出了if else 之后的command为" << command[i] << endl;
		
	} // end of for
	temp_order_amount--;
	if(player_group[temp_order_amount][0] == -1)
		cout << "没有找到符合条件的球员！" << endl;
	else{
		int amount = 0;
		for(amount = 0; player_group[temp_order_amount][amount] != -1; amount++);
		cout << "\n当前符合条件的球员数量为" << amount << " 他们是" << endl; 
		for(int i = 0; i < amount; i++)
			cout << player_group[temp_order_amount][i] << "号球员" << players.at(player_group[temp_order_amount][i]).get_name() << endl;
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
		cout << "感谢使用，再见!" << endl;  
		return 0;
	}
	
	
	command = in_to_Post_order(order);
//	cout << "here";
	if(command == "wrong")
		return -1;
//	cout << "main 函数中command 是" << command << endl;
	if(current_order_amount == 0){
		cout << "未检测到条件，输入有误，请重新输入！" << endl;
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
		cout << "俱乐部没有人，请先添加俱乐部成员！" << endl;
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
			cout << "输入有误，请重新输入" << endl;
			go_on = "1";
			flag = 0;
		}
		else
			flag = 1;
	}
		
//	int find = Club[club_number].search_player(compare);
//	if(find == -1) 
//		cout << "找不到符合条件的球员";
//	else
//		cout << "找到符合条件的球员，其id为" << find << "\n球员姓名为" << Club[club_number].get_player_name(find) << endl;	

}
//
void player_trade(club Club[]){
	int buyer = 0, seller = 0, goods = 0;		
	cout << "请按顺序输入买方和卖方俱乐部的序号："  << endl;
	for(int i = 0; i < current_club_amount; i++)
		cout << i+1 << "  " << Club[i].get_club_name() << endl;
	
	cin >> buyer >> seller;
	buyer--;
	seller--; 
	cout << "购买的球员序号为：" << endl;
	cin >> goods; 		
	cout << "买方和卖方俱乐部的名称分别为" << Club[buyer].get_club_name() << "、" << Club[seller].get_club_name() << endl;
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


	
//这里不要每次进来都定义，定义一次指针，然后每次结束都释放并指针置空最好！
//	string *club_allPlayer_search = (string *) malloc(sizeof(string) * current_club_amount); 
//	memset(club_allPlayer_search, 0, sizeof(string) * current_club_amount);
//	cout << "\n\n" << club_allPlayer_search[0] << " yi " << club_allPlayer_search[1] <<  endl;
	
	string *club_allPlayer_search = new string[current_club_amount + 1];
//	cout << "分配了" <<	current_club_amount + 1 << "个string空间" << endl;
	
	for(int i = 0; i < Max_Club_Amount; i++)
	 	club_num[i] = -1;
	string order;
	fflush(stdin);
	cout << "Please input the clubs you want to search, with '||'between them:" << endl;
	getline(cin, order);
//	cout << order;
	i = 0; 
	while(order[i] != NULL){
//		cout << "while 前 i=" << i << endl;
		while(order[i] == ' ') i++;
//		cout << "while 后 i=" << i << endl;
		if(order[i] != '@'){
			cout << "起始符号输入有误! \n";
//			cout << "输入的是" << order[i] << endl;
//			cout << "i = " << i << endl; 
			delete []club_allPlayer_search; 
//			cout << "释放空间" << endl;	
			return -1;
		}
		else
			i++;
		while(order[i] == ' ') i++;	
		if(order.substr(i, 4) != "club"){
			cout << "指令输入有误！\n";
			delete []club_allPlayer_search; 	
//			cout << "释放空间" << endl;
			return -1;
		}
		i = i + 4;
//		cout << "lalal" << order[i]; 
		while(order[i] == ' ') i++;	
		if(order[i] != '='){
			cout << "'='输入有误！3\n";
			delete []club_allPlayer_search; 	
//			cout << "释放空间" << endl;
//			cout << "输入了" << order[i] << endl; 
			
			return -1;
		}
		else 
			i++;
//		cout << "here" << order[i]<<endl;
		while(order[i] == ' ') i++;	
		
		
//		cout << "bla";
		for(; (order[i] >= 'A' && order[i] <= 'Z') || (order[i] >= 'a' && order[i] <= 'z'); i++){/*从@后面的第一个非空格字符开始*/
			club_allPlayer_search[club_allPlayer_search_amount] += order[i];		
//			cout<<order[i]<<endl;
		}
		
		if((club_num[club_allPlayer_search_amount] = is_a_club(club_allPlayer_search[club_allPlayer_search_amount], Club)) == -1){
			cout << "The club input not found, you have to try again!\n";
			delete []club_allPlayer_search; 	
//			cout << "释放空间" << endl;
			return -1; 
		}
//		cout << "1\n";
//		cout <<	club_allPlayer_search[club_allPlayer_search_amount];
		club_allPlayer_search_amount++;
		while(order[i] == ' ') i++;	
		if(club_allPlayer_search_amount == current_club_amount && order[i] != NULL){
			cout << "输入指令过多！\n";
			delete []club_allPlayer_search; 	
//			cout << "释放空间" << endl;
			return -1; 
		}
//		cout << "2\n";
//		cout << i << " lala " << order[i] << endl; 
//		if(order[i] == NULL) cout << "yes";
		if(order[i] != NULL && order.substr(i, 2) != "||"){
			cout << "运算符输入有误！\n";
			delete []club_allPlayer_search; 	
//			cout << "释放空间" << endl;
			return -1; 	
		}




//难道 string最后一个字符是空，但如果再往后走两个字符又不是空了？？	




	
		else if(order[i] == NULL)
			break;
		else	
			i += 2;
	}
//	 cout << "3\n";
	 delete []club_allPlayer_search; 
//	 cout << "释放空间" << endl;	
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
	club_number--;// 因为1号其实是club[0] 
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
			cout << "起始符号输入有误! \n";
			return "-1";
		}
		else
			i++;
		while(order[i] == ' ') i++;	
		if(order.substr(i, 4) != "name"){
			cout << "指令输入有误！\n";
			return "-1";
		}
		i = i + 4;
		while(order[i] == ' ') i++;	
		if(order[i] != '~'){
			cout << "你没写~输入有误！\n";
			return "-1";
		}
		else
			i++;		
//		cout << "哦\n";
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
	for(sublength = 0; sub_name[sublength] != NULL; sublength++);// 子串长度 
	for(length = 0; str[length] != NULL; length++);// 母串长度 
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
		if(club_number != -1) // 开启while的门禁 
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
此问题出在了vector的越界 
*/
