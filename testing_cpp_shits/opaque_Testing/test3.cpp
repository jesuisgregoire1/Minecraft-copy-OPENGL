#include <iostream>
#include "test3.hpp"

struct ss {
    int x;
    float y;
};
typedef struct AHAHAHAHAH{
    int x=1000;
    int y=1000;
}test;
void animal_method(Animal a){
    std :: cout << a.a << std :: endl;
}
int addition(test* t){
    return t->x + t->y;
}
int substraction(test* t){
    return t->x - t->y;
}
void printing(test* t){
    std :: cout << "Value of x = " << t->x << std :: endl;
    std :: cout << "Value of y = " << t->y << std :: endl;
}
void change_value(test* t, int value){
    std :: cout << "Value of x = " << t->x << std :: endl;
    std :: cout << "Value of y = " << t->y << std :: endl;
    t->x = value;
    t->y = value;
    std :: cout << "Value of x = " << t->x << std :: endl;
    std :: cout << "Value of y = " << t->y << std :: endl;
    
}