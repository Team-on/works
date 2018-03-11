#include <iostream>
using namespace std;

int main()          // #странно.    Code::Blocks приймає main лише як int
{
/* Завдання 1
int number;
for(;;){
    cout<<"Enter a six-digit number"<<endl;     cin>>number;
    if ((100000<=number&&1000000>number)||(-100000>=number&&-1000000<number)){          //Перевірка кількості цифр у числі.
        if(number%10+number%100/10+number%1000/100==number/1000%10+number/10000%10+number/100000&&0<number){
//Пожалів дві змінні для запису сум. А треба взагалі виводити суми лівої і правої частини? - Перечитай умову
            cout<<number<<" is a lucky number"<<endl;
        }
        else cout<<number<<" is an unlucky number"<<endl;
    }
    else if(0==number) cout<<"000000 is a lucky number"<<endl;      //Дивитися нижче
        else cout<<"ERROR\a"<<endl;                                 //Теж дивитися нижче
}
*/

// Завдання 2
int number;
char first,second,third,fourth;
for(;;){                                        //Краще не вводити букви і будь-що крім цифр!
    cout<<"Enter a four-digit number"<<endl;     cin>>number;
    if ((1000<=number&&10000>number)||(-1000>=number&&-10000<number)){
        first=number/1000;
        if(number<0){                           //Якщо число відємне, то відємність має зберегтися лише в першої цифри.
            second=-number/100%10;
            third=-number/10%10;
            fourth=-number%10;
        }
        else{                                   // Якщо юзверю не прийшло в голову ввести відємне число
            second=number/100%10;
            third=number/10%10;
            fourth=number%10;
        }
        cout<<int(second)<<int(first)<<int(fourth)<<int(third)<<endl;   // Як же вивести значення Char, а не код з ACSII?
    }
    else if(0==number) cout<<"0000"<<endl;      //Та сама помилка, що і у задачі 1. Незалежно від кількості нулів, cout з 0000 і 000000 все одно виводится. Як же зберегти введену кількість нулів? Може Char? - Бред! Все поміняв на чари, а потім сумував їх в number використовуючи int(first). Взагалі нічого не робить. Залишу і так.
        else cout<<"ERROR\a"<<endl;             // Чогось немає звуку. В першій задачі аналогічно.
}


return 0;
}
