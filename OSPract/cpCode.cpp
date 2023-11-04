#include<iostream>
using namespace std;
int main(){
int x=50;
int y=25;
int z=9;
if (x>y){
    if(x>z)
    cout<<"x is the big no";
    else{
        cout<<"z is the biggest no";
    }
}
else{
        if(y>z){
            cout<<"y is the biggest no";
        }
        else{
            cout<<"z is the biggest no";
        }
    }
return 0;
}