#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
using namespace std;



int main(){
    srand(time(0));
    setlocale(0,"RUS");

    const short randarray_size=20;

    short randarray[randarray_size], min_arr=9999, min_arr_el, first_less,last_less, sum_4=0, count_more=0;

    for(int i=0;i<randarray_size;i++){
        randarray[i]=rand()%21-10;
        cout<<setw(4)<<"Element #"<<i+1<<" is "<<randarray[i]<<endl;
        if(min_arr>randarray[i]&&i%2==1&&i!=0){
            min_arr=randarray[i];
            min_arr_el=i;
        }
    }

    cout<<"\t\t\tArray 20: "<<endl;
    cout<<"Input K: "<<endl;
        cin>>first_less;
    cout<<"Input L: "<<endl;
        cin>>last_less;

    for(int i=first_less-1;i<=last_less-1;i++)
        sum_4+=randarray[i];

    cout<<"Sum is "<<sum_4<<endl<<endl;

    cout<<"\t\t\tArray 28: "<<endl;
    cout<<"Even array index and minimal value: "<<min_arr<<" is element #"<<min_arr_el+1<<endl<<endl;

    cout<<"\t\t\tArray 30: "<<endl;

    for(int i=0;i<randarray_size-1;i++){
        if(randarray[i]>randarray[i+1]){
            cout<<"Element # "<<i+1<<endl;
            count_more++;
        }
    }
    cout<<"All: "<<count_more<<endl;
return 0;}
