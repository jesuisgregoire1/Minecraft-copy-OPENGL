#include <iostream>
#include <string>

int main(){
    // char ch1[50] = "Ana are mere";
    // std :: cout << ch1 << std :: endl;

    // ch1[2] = 'b';
    // std :: cout << ch1 << std :: endl;

    // char *ch2 = ch1;
    // std :: cout << ch2 << std :: endl;

    // std::string example = "HAHAHAH THIS IS JUST AN EXAMPLE";
    // example[0] = 'F';
    // std :: cout << example << std :: endl;
    // std :: cout << example.length() << std :: endl;
    // std :: cout << example.size() << std :: endl;
    // example = example + std::to_string(1);
    // std :: cout << example << std :: endl;
    std :: string something_temporary = "HAHAHAHA just something temproary";
    const char *ch = (something_temporary.c_str());
    std :: cout << ch << std :: endl;
    // for(uint8_t i=0; i<4; ++i){
    //     std::string temporary_string="light[" + std::to_string(i) + "].position";
    //     char ch[50];
    //     ch = temporary_string.c_str();
    //     std :: cout<<temporary_string << std :: endl;
    // }

    // int temp = 6; 
    // int *number = new int(temp);
    // int *ptr = &temp;
    // std :: cout << *number << std :: endl;
    // std :: cout << number << std :: endl;
    // std :: cout << &temp << std :: endl;
    // if(number == &temp){
    //     std::cout << "Same addres" << std :: endl;
    // }
    // if(ptr == &temp){
    //     std::cout << "Same addres" << std :: endl;
    // }
    // delete number;

}