#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    int chan = 0, le = 0, am = 0;
    
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        
        if (x < 0) am++;
        
        // Dung x % 2 != 0 de tranh bap lay duu so am o C++
        if (x % 2 != 0) {
            le++;
        } else {
            chan++;
        }
    }
    
    cout << "chẵn " << chan << ", lẻ " << le << ", âm " << am << endl;
    
    return 0;
}