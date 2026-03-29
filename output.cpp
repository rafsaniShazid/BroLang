#include <iostream>
#include <string>
using namespace std;

int main() {
    int i = 0;
    string name;
    cout << "Enter your name without spaces" << endl;
    cin >> name;
    string s = " hello guys what's up";
    float x = 3.2;
    int y = 5;
    float sum = x + y;
    while(i < 6) {
    if(i == 2) {
    cout << " reached 2" << endl;
    break;
    }
    i++;
    }
    cout << sum << endl;
    cout << name << endl;
}
