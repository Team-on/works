#include <iostream>
using namespace std;
void main()
{
setlocale(0,"RUS");

int rik,a,b,c;
cout<<"Vvedit rik"<<endl;
cin>>rik;
a=rik%60;
b=a/12;
c=a%12;
cout<<b<<endl;
switch(b){
	case 0:
		cout<<"зеленый";
	break;
	case 1:
		cout<<"красный";
	break;
	case 2:
		cout<<"желтый";
	break;
	case 3:
		cout<<"белый";
	break;
	case 4:
		cout<<"черный";
	break;
}
switch(c){
	case 0:
		cout<<" крысы"<<endl;
	break;
	case 1:
		cout<<" коровы"<<endl;
	break; 
	case 2:
		cout<<" тигра"<<endl;
	break;
	case 3:
		cout<<" зайца"<<endl;
	break;
	case 4:
		cout<<" дракона"<<endl;
	break;
	case 5:
		cout<<" змеи"<<endl;
	break;
	case 6:
		cout<<" лошади"<<endl;
	break;
	case 7:
		cout<<" овцы"<<endl;
	break;
	case 8:
		cout<<" обезьяны"<<endl;
	break;
	case 9:
		cout<<" курицы"<<endl;
	break;
	case 10:
		cout<<" собаки"<<endl;
	break;
	case 11:
		cout<<" свиньи"<<endl;
	break;
}
/*
int mast, dost;
cout<<"input mast"<<endl;
cin>>mast;
cout<<"input dost"<<endl;
cin>>dost;

switch(mast){
	case 1:
		cout<<"    __"<<endl;
		cout<<"   /  \\"<<endl;
		cout<<"  /    \\"<<endl;
		cout<<" /      \\"<<endl;
		cout<<"|       |"<<endl;
		cout<<"|       |"<<endl;
		cout<<" \\_/|\\_/"<<endl;
		cout<<"    |   "<<endl;
	break; 
	case 2:
		cout<<"     _ "<<endl;
		cout<<"    / \\ "<<endl;
		cout<<"   |   |   "<<endl;
		cout<<"  _ \\ /_ "<<endl;
		cout<<" / \\||/ \\ "<<endl;
		cout<<"|        | "<<endl;
		cout<<" \\_/\\|\\_/ "<<endl;
		cout<<"     |   "<<endl;
		cout<<"     |   "<<endl;
	break;
	case 3:
		cout<<"    /\\"<<endl;
		cout<<"   /  \\"<<endl;
		cout<<"  /    \\"<<endl;
		cout<<" /      \\"<<endl;
		cout<<" \\      /"<<endl;
		cout<<"  \\    /"<<endl;
		cout<<"   \\  /"<<endl;
		cout<<"    \\/   "<<endl;
	break;
	case 4:
		cout<<"  __ __"<<endl;
		cout<<" /  |  \\"<<endl;
		cout<<"|       |"<<endl;
		cout<<"|       |"<<endl;
		cout<<" \\      /"<<endl;
		cout<<"  \\    /"<<endl;
		cout<<"   \\__/"<<endl;
	break;
}
cout<<endl;
cout<<endl;
switch(dost){
	case 11:
		cout<<" |\\"<<endl;
		cout<<" |  |"<<endl;
		cout<<" |  /"<<endl;
		cout<<" |-- "<<endl;
		cout<<" | \\"<<endl;
		cout<<" | |"<<endl;
		cout<<" |/"<<endl;

	break;
	case 12:
		cout<<" |\\"<<endl;
		cout<<" | \\"<<endl;
		cout<<" |  |"<<endl;
		cout<<" |  |"<<endl;
		cout<<" |  |"<<endl;
		cout<<" | /"<<endl;
		cout<<" |/"<<endl;
	break;
	case 13:
		cout<<" |   /"<<endl;
		cout<<" |  /"<<endl;
		cout<<" | /"<<endl;
		cout<<" |-"<<endl;
		cout<<" | \\"<<endl;
		cout<<" |  \\"<<endl;
		cout<<" |   \\"<<endl;
	break;
	case 14:
		cout<<" _______"<<endl;
		cout<<"    |"<<endl;
		cout<<"    |"<<endl;
		cout<<"    |"<<endl;
		cout<<"    |"<<endl;
		cout<<"    |"<<endl;
		cout<<"    |"<<endl;
	break;
	default:
		cout<<dost<<endl;
	break;
}
*/

}
/*В восточном календаре принят 60-летний цикл, состоящий из 12-лет-
них подциклов, обозначаемых названиями цвета: зеленый, красный, жел-
тый, белый и черный. В каждом подцикле годы носят названия животных:
крысы, коровы, тигра, зайца, дракона, змеи, лошади, овцы, обезьяны, ку-
рицы, собаки и свиньи. По номеру года определить его название, если 1984
год — начало цикла: «год зеленой дракон». */