#include <iostream>
#include <string>
using namespace std;

int add(int x, int y) {
    return x * y;
}

int main() {
    int result = add(5, 7);
    cout << result << endl;
}
