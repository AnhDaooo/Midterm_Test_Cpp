#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> findTopNumbers(string s, int n) {
    stringstream ss(s);

    vector<int> numbers;

    int number = 0;

    while(ss >> number){
        numbers.push_back(number);
    }
    // sắp xếp các số trong vector theo thứ tự giảm dần
    sort(numbers.begin(), numbers.end(), greater<int>());

    // trả về một vector chứa n số lớn nhất.
    return vector<int>(numbers.begin(), numbers.begin() + n);
}

int main(int argc, char const *argv[])
{
    string s = "1 2 45 2 0 9 3 2 7 8 7";
    int n = 5;
    vector<int> topNumber = findTopNumbers(s, n);

    cout << "Top " << n << " numbers: " << endl;\

    for(auto top : topNumber){
        cout << top << " ";
    }

    cout << endl;
    
    return 0;
}
