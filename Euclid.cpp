#include <iostream>


int euclid_algoritm(int a, int b){

    if(a == b){
        return a;
    }

    int _a = a < 0 ? -a : a;
    int _b = b < 0 ? -b : b; 

    while(_b != 0){
        int tmp = _b;
        _b = _a % _b;
        _a = tmp;
    }
    return _a;

}

int main(){

    int a = 12;
    int b = 16;

    int c = euclid_algoritm(-256 , 16);
    std::cout << c;
}
