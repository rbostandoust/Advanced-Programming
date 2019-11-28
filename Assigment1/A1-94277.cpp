#include <iostream>
#include <vector>
#include <string.h>
#include <stdlib.h>

using namespace std;

#define PROCESS_TRANSACTION 1
#define END_BLOCK 2
#define PRINT_ACCOUNTS 3
#define PRINT_BLOCK 4

const string table[16][16]={
        {"0C","B4","64","B0","C1","18","87","09","76","50","29","3E","34","E9","7B","75"},
        {"9A","23","CC","24","5F","9C","E2","61","77","A6","35","12","98","A2","A4","E8"},
        {"DE","02","E3","EB","47","E4","32","33","19","6C","06","D9","DA","F0","C6","6D"},
        {"84","37","AD","A1","48","B6","DD","B2","89","1E","7D","58","E7","B5","9B","FA"},
        {"C7","17","DB","F5","F9","43","EF","71","C8","67","F7","27","5D","01","9F","D0"},
        {"AE","DF","66","7A","99","21","94","7E","0B","68","53","5E","3A","4A","8E","57"},
        {"9D","8B","72","E6","3C","AA","60","97","C3","00","DC","A8","39","BB","6A","38"},
        {"D7","11","FB","E0","7F","FE","EC","D4","D2","CD","70","78","3D","0E","14","F6"},
        {"8F","69","BD","3B","45","90","93","EA","F3","4C","4D","D8","2D","D1","1F","F1"},
        {"B3","2A","D6","86","07","22","D5","46","AC","E5","0F","96","74","3F","D3","80"},
        {"26","CB","54","73","B9","44","0D","C0","41","8A","AB","15","2E","83","08","ED"},
        {"CE","16","6B","03","C5","52","FD","81","AF","8D","A0","BF","F2","10","5A","4E"},
        {"A3","4F","FC","88","9E","25","95","5C","A5","92","8C","51","BA","56","6E","31"},
        {"40","1B","91","85","7C","49","79","C2","2B","BC","42","6F","28","F8","FF","CF"},
        {"59","63","1A","C9","BE","E1","C4","13","F4","55","EE","65","B8","B7","20","A7"},
        {"30","2F","4B","A9","04","05","CA","2C","0A","36","62","5B","1D","1C","B1","82"}
};
struct User
{
	int ID;
	string name;
	int investment; 
};
struct Transaction
{
	int recieverID;
	int senderID;
	int amount;
	int Timestamp;
	string octet;
};
struct Block
{
	vector<Transaction> transactions;	
};

int numLen(int num);
void showMembers(vector<User> users);
void printSpace(int num);
void printDash(int num);
void showTransInBlock(vector<Block> blocks,vector<User> users);
User returnUser(int id,vector<User> users);
void addAccounts(vector<User>& users);
void stringToCharArray(char* charArray,string text);
int readCommand();
void processTheCommand(int commandNum,vector<User>& users,vector<Block>& blocks);
void newTransaction(vector<User>& users,vector<Block>& blocks);
bool isTransactionValid(Transaction trans,vector<User>& users,vector<Block>& blocks);
void sortTransactions(Block& current);
void swapTransactions(Transaction& first,Transaction& second);
void endBlock(vector<Block>& blocks);
void verification(vector<Block>& blocks);
string decimalToBinary(int n);
void merge(vector<Block>& blocks);
string lookUp(int n);
string hexToBinary(char hex);
int binaryToDecimal(string binary,int length);

int main(){
	vector<User> users;
	vector<Block> blocks(1);
	int commandNum;
	addAccounts(users);
	while(true){
		commandNum=readCommand();
		processTheCommand(commandNum,users,blocks);
	}
	return 0;
}

int numLen(int num){
	int len=0;
	do{
		len++;
		num/=10;
	}while(num>0);
	return len;
}
void showMembers(vector<User> users){
	int len;
	cout <<"UID";
	printSpace(12-3);
	cout <<"Name";
	printSpace(43-16);
	cout <<"Balance"<<endl;
	printDash(50);
	cout <<endl;
	for(int i=0;i<users.size();i++){
		cout<<users[i].ID;
		len=numLen(users[i].ID);
		printSpace(12-len);
		cout<<users[i].name;
		len=users[i].name.length();
		printSpace(50-12-len-numLen(users[i].investment));
		cout<<users[i].investment<<endl;
	}
}
void printSpace(int num){
	for(int i=1;i<=num;i++)
		cout<<" ";
}
void printDash(int num){
	for(int i=1;i<=num;i++)
		cout<<"-";
}
void showTransInBlock(vector<Block> blocks,vector<User> users){
	int len;
	User temp;
	cout<<"Block";
	printSpace(4);
	cout<<":"<<blocks.size()-1;
	printSpace(19-10-numLen(blocks.size()-1));
	cout<<"Transaction Count";
	printSpace(4);
	cout<<":"<<blocks[blocks.size()-1].transactions.size();
	printSpace(50-41-numLen(blocks[blocks.size()-1].transactions.size()));
	cout<<"Last Timestamp";
	len=blocks[blocks.size()-1].transactions[blocks[blocks.size()-1].transactions.size()-1].Timestamp;
	printSpace(80-numLen(len)-14-51);
	cout<<":"<<len<<endl;
	printDash(80);
	cout<<endl;
	for(int i=0;i<blocks[blocks.size()-1].transactions.size();i++){
		len=blocks[blocks.size()-1].transactions[i].Timestamp;
		cout<<len;
		printSpace(16-numLen(len));
		temp=returnUser(blocks[blocks.size()-1].transactions[i].senderID,users);
		cout<<temp.name;
		printSpace(42-16-temp.name.length());
		temp=returnUser(blocks[blocks.size()-1].transactions[i].recieverID,users);
		cout<<temp.name;
		printSpace(80-42-temp.name.length()-numLen(blocks[blocks.size()-1].transactions[i].amount));
		cout<<blocks[blocks.size()-1].transactions[i].amount<<endl;
	}
}
User returnUser(int id,vector<User> users){
	for(int i=0;i<users.size();i++){
		if(users[i].ID==id)
			return users[i];
	}
	User temp;
	temp.name="";
	return temp;
}
void addAccounts(vector<User>& users){
	int n;
	User tempUser;
	cin>>n;
	char charArray[50];
	string temp,part1,part2,mainPart;
	getline(cin,temp);
	for(int i=0;i<n;i++){
		getline(cin,temp);
		part1=temp.substr(0, temp.find(','));
		part2=temp.substr(0, temp.find(' '));
		if(part1.length()>part2.length())
			mainPart=part2;
		else
			mainPart=part1;
		while(mainPart[mainPart.length()-1]==' ')
			mainPart.erase(mainPart.length()-1);
		stringToCharArray(charArray,mainPart);
		tempUser.ID=atoi(charArray);
		temp.erase(0,mainPart.length()+1);
		while(temp[0]==' '||temp[0]==',')
			temp.erase(temp.begin());
		mainPart=temp.substr(0, temp.find(','));
		temp.erase(0,mainPart.length()+1);
		while(mainPart[mainPart.length()-1]==' ')
			mainPart.erase(mainPart.length()-1);
		tempUser.name=mainPart;
		while(temp[0]==' '||temp[0]==',')
			temp.erase(temp.begin());
		stringToCharArray(charArray,temp);
		tempUser.investment=atoi(charArray);
		users.push_back(tempUser);
	}
}
void stringToCharArray(char* charArray,string text){
	int i;
	for (i = 0; i < text.length(); i++)
	{
		charArray[i]=text[i];
	}
	charArray[i]='\0';
}
int readCommand(){
	char command[25]="";
	cin >> command;
	if(command=="")
		return 0;
	if(strcmp(command,"process_transaction")==0)
		return PROCESS_TRANSACTION;
	if(strcmp(command,"end_block")==0)
		return END_BLOCK;
	if(strcmp(command,"print_accounts")==0)
		return PRINT_ACCOUNTS;
	if(strcmp(command,"print_block")==0)
		return PRINT_BLOCK;
	else
		return 0;
}
void processTheCommand(int commandNum,vector<User>& users,vector<Block>& blocks){
	switch(commandNum){
		case PROCESS_TRANSACTION:
			newTransaction(users,blocks);
			break;
		case END_BLOCK:
			endBlock(blocks);
			break;
		case PRINT_ACCOUNTS:
			showMembers(users);
			break;
		case PRINT_BLOCK:
			showTransInBlock(blocks,users);
			break;
	}
}
void newTransaction(vector<User>& users,vector<Block>& blocks){
	int sender,reciever,amount,date,senderIndex,recieverIndex;
	Transaction tempTrans;
	cin>>sender>>reciever>>amount>>date;
	tempTrans.recieverID=reciever;
	tempTrans.senderID=sender;
	tempTrans.amount=amount;
	tempTrans.Timestamp=date;
	if(isTransactionValid(tempTrans,users,blocks)){
		for(int i=0;i<users.size();i++){
			if(users[i].ID==reciever)
				recieverIndex=i;
			if(users[i].ID==sender)
				senderIndex=i;
		}
		users[recieverIndex].investment+=amount;
		users[senderIndex].investment-=amount;
		blocks[blocks.size()-1].transactions.push_back(tempTrans);
		sortTransactions(blocks[blocks.size()-1]);
	}
}
bool isTransactionValid(Transaction trans,vector<User>& users,vector<Block>& blocks){
	User temp;
	temp=returnUser(trans.recieverID,users);
	if(temp.name==""){
		temp=returnUser(trans.senderID,users);
		if(temp.name==""){
			cout<< "ERR: no reciever and sender found with that ID"<<endl;
			return 0;
		}
		cout<< "ERR: no reciever found with that ID"<<endl;
		return 0;
	}
	temp=returnUser(trans.senderID,users);
	if(temp.name==""){
		cout<< "ERR: no sender found with that ID"<<endl;
		return 0;
	}
	if(temp.investment<trans.amount){
		cout<< "ERR: not enough money to process the transaction"<<endl;
		return 0;
	}
	if(blocks.size()!=1){
		if(blocks[blocks.size()-2].transactions[blocks[blocks.size()-2].transactions.size()-1].Timestamp
			>= trans.Timestamp){
			cout<< "ERR: The timestamp isn't Valid"<<endl;
			return 0;
		}
	}
	return 1;
}
void sortTransactions(Block& current){
	for(int i=0;i<current.transactions.size();i++)
    	for(int j=0;j<current.transactions.size()-i-1;j++)
      		if(current.transactions[j].Timestamp>current.transactions[j+1].Timestamp)
        		swapTransactions(current.transactions[j],current.transactions[j+1]);
}
void swapTransactions(Transaction& first,Transaction& second){
	Transaction temp;
	temp.recieverID=first.recieverID;
	temp.senderID=first.senderID;
	temp.amount=first.amount;
	temp.Timestamp=first.Timestamp;
	first.recieverID=second.recieverID;
	first.senderID=second.senderID;
	first.amount=second.amount;
	first.Timestamp=second.Timestamp;
	second.recieverID=temp.recieverID;
	second.senderID=temp.senderID;
	second.amount=temp.amount;
	second.Timestamp=temp.Timestamp;
}
void endBlock(vector<Block>& blocks){
	verification(blocks);//tabe dorosti sanji
	Block temp;
	blocks.push_back(temp);
}
void verification(vector<Block>& blocks){
	int m,p,q;
	Transaction kk;
	string modelString;
	string octet,temp;
	//cout<<blocks[blocks.size()-1].transactions.size()<<endl;
	for(int i=0;i<blocks[blocks.size()-1].transactions.size();i++){
		//cout<<"block "<<blocks.size()-1<<", transactions "<<i<<endl;
		m=blocks[blocks.size()-1].transactions[i].senderID * blocks[blocks.size()-1].transactions[i].recieverID;
		p=m%blocks.size();
		q=blocks[blocks.size()-1].transactions[i].amount % blocks[p].transactions.size();
		//cout<<"m:"<<m<<" p:"<<p<<" q:"<<q<<endl;
		kk=blocks[p].transactions[q];
		modelString=decimalToBinary(kk.senderID);
		modelString+=decimalToBinary(kk.recieverID);
		temp=decimalToBinary(kk.amount);
		for(int j=16;j<48-temp.length();j++)
			modelString+='0';
		modelString+=temp;
		//cout<<modelString<<endl;
		blocks[blocks.size()-1].transactions[i].octet=modelString.substr((i+1)*(blocks.size())%41,8);
	}
	merge(blocks);
}
string decimalToBinary(int n){
	int counter=0;
	string result;
	int bit;
	while(n>1){
		bit=n%2;
		n/=2;
		if(bit==0)
			result[counter]='0';
		else
			result[counter]='1';
		counter++;
	}
	if(n==0)
		result[counter]='0';
	else
		result[counter]='1';
	for (int i = 1; i < 8-(counter%8); i++)
	{
		result[counter+i]='0';
	}
	char charArray[33];
	int i;
	for (i = 0; i < counter+8-(counter%8); i++)
	{
		charArray[counter+8-(counter%8)-1-i]=result[i];
	}
	charArray[i]='\0';
	return charArray;
}
void merge(vector<Block>& blocks){
	int maxR0=0,maxRn=0,R,octet;
	char result[9];
	string temp;
	for(int i=0;i<256;i++){
		R=i;
		//cout<<"\tFor R="<<R<<endl;
		for(int j=0;j<blocks[blocks.size()-1].transactions.size();j++){
			octet=binaryToDecimal(blocks[blocks.size()-1].transactions[j].octet,8);
			//cout<<"R:"<<R<<",octet: "<<blocks[blocks.size()-1].transactions[j].octet<<" , "<<octet<<"^:R^octet"<<(R^octet)<<endl;
			temp=lookUp(R^octet);
			stringToCharArray(result,temp);
			R=binaryToDecimal(result,temp.length());
		}
		if(maxRn<=R){
			maxRn=R;
			maxR0=i;
		}
	}
	cout<<"Best hash achievable when R0 = "<< maxR0 << endl;
}
string lookUp(int n){
	string searchKey,i,j;
	char charArray[9];
	searchKey=decimalToBinary(n);
	//cout<<searchKey<<":"<<binaryToDecimal(searchKey,8)<<endl;
	j=searchKey.substr(4,4);
	i=searchKey.substr(0,4);
	//cout<<"i:"<<binaryToDecimal(i,4)<<",j:"<<binaryToDecimal(j,4)<<endl;
	string hex;
	hex=table[binaryToDecimal(i,4)][binaryToDecimal(j,4)];
	string binary;
	binary=hexToBinary(hex[0]);
	binary+=hexToBinary(hex[1]);
	//cout<<hexToBinary(hex[1])<<","<<hexToBinary(hex[0])<<endl;
	//cout<<"next R:"<<binary<<":"<<binaryToDecimal(binary,8)<<endl;
	stringToCharArray(charArray,binary);
	return charArray;
}
string hexToBinary(char hex){
	switch(hex){
		case '0':
			return "0000";
		case '1':
			return "0001";
		case '2':
			return "0010";
		case '3':
			return "0011";
		case '4':
			return "0100";
		case '5':
			return "0101";
		case '6':
			return "0110";
		case '7':
			return "0111";
		case '8':
			return "1000";
		case '9':
			return "1001";
		case 'A':
			return "1010";
		case 'B':
			return "1011";
		case 'C':
			return "1100";
		case 'D':
			return "1101";
		case 'E':
			return "1110";
		case 'F':
			return "1111";
	}
}
int binaryToDecimal(string binary,int length){
	int bit,decimal=0,power=1;
	for (int i = length-1; i >=0; i-- ){
			bit=binary[i]-'0';
			decimal += bit * power;
			power *= 2;
	}
	return decimal;
}
