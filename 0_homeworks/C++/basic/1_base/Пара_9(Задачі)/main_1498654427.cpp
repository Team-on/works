#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
using namespace std;



int main(){
    srand(time(0));
    setlocale(0,"RUS");
/*  Завдання 1


    const short randarray_size=20;

    short randarray[randarray_size+1];
        randarray[randarray_size+1]=10000;


    for(int i=0;i<randarray_size;i++){
        randarray[i]=rand()%100+1;
        cout<<setw(4)<<"Element #"<<i+1<<" is "<<randarray[i]<<endl;

        if(randarray[randarray_size+1]/100>randarray[i])
            randarray[randarray_size+1]=randarray[i]*100+i+1;

        if(randarray[0]/100<randarray[i])
            randarray[0]=randarray[i]*100+i+1;
    }

    cout<<endl<<"Min of this array: "<<randarray[randarray_size+1]/100<<endl;
    cout<<"\tAnd is element #"<<randarray[randarray_size+1]%100<<endl;
    cout<<endl<<"Max of this array: "<<randarray[0]/100<<endl;
    cout<<"\tAnd is element #"<<randarray[0]%100<<endl;

*/

/*  Завдання 2
    const short array_size=12;

    int income[array_size], max_inc, min_inc;
    short first_month, last_month, max_month, min_month;

    for(int i=0;i<array_size;i++){
        cout<<"Inpute you income for "<<i+1<<" month "<<endl;
            cin>>income[i];

    }

    repeat:

    cout<<"\nEnter the first month of time interval"<<endl;
        cin>>first_month;
    cout<<"Enter the last month of time interval"<<endl;
        cin>>last_month;

    if(first_month<=0||last_month>12)
            goto repeat;

    max_inc=income[0];
    min_inc=income[0];
    max_month=1;
    min_month=1;

    for(int i=first_month-1;i<last_month-1;i++){
        if(min_inc>income[i]){
            min_inc=income[i];
            min_month=i+1;
        }

        if(max_inc<income[i]){
            max_inc=income[i];
            max_month=i+1;
        }
    }

    cout<<endl<<"Min income: "<<min_inc<<endl;
    cout<<"\tAnd is month #"<<min_month<<endl;
    cout<<endl<<"Max income: "<<max_inc<<endl;
    cout<<"\tAnd is month #"<<max_month<<endl;
*/



    const short randarray_size=20;

    short randarray[randarray_size], sum_less=0, min_arr=9999, max_arr=-9999, min_arr_el, max_arr_el,obmen, first_less=0,last_less=0, sum_4=0;
    long long multiple=1, multiple_even=1;

    for(int i=0;i<randarray_size;i++){
        randarray[i]=rand()%21-10;
        cout<<setw(4)<<"Element #"<<i+1<<" is "<<randarray[i]<<endl;

        if(randarray[i]<0)
            sum_less+=randarray[i];

        if(min_arr>randarray[i]){
            min_arr=randarray[i];
            min_arr_el=i;
        }
        if(max_arr<randarray[i]){
            max_arr=randarray[i];
            max_arr_el=i;
        }
    }

    cout<<endl<<"Сумма отрицательных элементов: "<<sum_less<<endl<<endl;
    cout<<"min: "<<min_arr<<endl<<"\tElement #"<<min_arr_el+1<<endl;
    cout<<"max: "<<max_arr<<endl<<"\tElement #"<<max_arr_el+1<<endl;

    if(min_arr_el>max_arr_el){
        obmen=min_arr_el;
        min_arr_el=max_arr_el;
        max_arr_el=obmen;
    }

    for(int i=min_arr_el;i<=max_arr_el;i++)
        multiple*=randarray[i];

    for(int i=2;i<randarray_size;i+=2)
        multiple_even*=randarray[i];

    for(int i=0;i<randarray_size;i++){
        if(randarray[i]<0){
            first_less=i;
            break;
        }
    }

    for(int i=first_less;i<randarray_size;i++)
        if(randarray[i]<0)
            last_less=i;

    for(int i=first_less;i<last_less;i++)
        sum_4+=randarray[i];


    cout<<"Произведение элементов, находящихся между min и max элементами: "<<multiple<<endl<<endl;
    cout<<endl<<"Произведение элементов с четными номерами: "<<multiple_even<<endl<<endl;
    cout<<"Сумма элементов, находящихся между первым и последним отрицательными элементами("<<first_less+1<<";"<<last_less+1<<"): "<<randarray[0]%100<<endl<<endl;

return 0;}
