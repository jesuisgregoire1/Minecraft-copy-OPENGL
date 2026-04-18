#include <iostream>

class Number{
    public:
        int number;
};

void change(Number numbers[])
{
    for(int i=0 ; i<10; ++i){
        numbers[i].number = i;
    }
}
int main(){
    Number numbers[10];
    change(numbers);
    for(int i=0 ; i<10; ++i){
        std :: cout << "numbers[i].number = " << numbers[i].number << std :: endl;
    }
    int* p;
    p[0] = 10;
    std :: cout << *p;
}