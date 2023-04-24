#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// struct RichPerson
struct RichPerson
{
    int rank;
    string personName;
    string age;
    string finalWorth;
    string category;
    string countryOfCitizenship;
    string organization;
    bool selfMade;
    string gender;
    string birthDate;
    string title;
};

// Hàm đọc file
vector<RichPerson> readData(string filePath)
{
    vector<RichPerson> richPeople;

    ifstream inputFile(filePath);
    if (!inputFile.is_open())
    {
        cout << "Cannot open input file" << endl;
        return richPeople;
    }

    string line;
    getline(inputFile, line); // skip header line
    while (getline(inputFile, line))
    {
        istringstream iss(line);
        RichPerson person;
        string rankStr, selfMadeStr;

        getline(iss, rankStr, ',');
        person.rank = stoi(rankStr);

        getline(iss, person.personName, ',');

        getline(iss, person.age, ',');

        getline(iss, person.finalWorth, ',');

        getline(iss, person.category, ',');

        getline(iss, person.countryOfCitizenship, ',');

        getline(iss, person.organization, ',');

        getline(iss, selfMadeStr, ',');
        person.selfMade = (selfMadeStr == "True");
        getline(iss, person.gender, ',');

        getline(iss, person.birthDate, ',');

        getline(iss, person.title, ',');

        richPeople.push_back(person);
    }
    inputFile.close();
    return richPeople;
}

// Hàm in ra các tỷ phú có Category = Technology
void printTechRichPeople(const vector<RichPerson> &richPeople)
{
    for (const RichPerson &person : richPeople)
    {
        if (person.category == "Technology")
        {
            cout << "Rank: " << person.rank << endl
                 << "Name: " << person.personName << endl
                 << "Age: " << person.age << endl
                 << "Net worth: $" << person.finalWorth << " billion" << endl
                 << "Category: " << person.category << endl
                 << "Country: " << person.countryOfCitizenship << endl
                 << "Organization: " << person.organization << endl
                 << "Self-made: " << (person.selfMade == true ? "Yes" : "No") << endl
                 << "Gender: " << person.gender << endl
                 << "Birth date: " << person.birthDate << endl
                 << "Title: " << person.title << endl
                 << endl;
        }
    }
}

// Hàm in ra top n quốc gia có nhiều tỷ phú nhất
void printTopCountries(const vector<RichPerson> &richPeople, int numCountries)
{
    // tạo ra một map countryCounts, trong đó key là tên quốc gia và value là số lượng tỷ phú của quốc gia đó
    map<string, int> countryCounts;

    // duyệt qua mỗi đối tượng RichPerson trong vector richPeople và tăng giá trị tương ứng trong map countryCounts cho quốc gia của đối tượng đó.
    for (const RichPerson &person : richPeople)
    {
        countryCounts[person.countryOfCitizenship]++;
    }
    vector<pair<string, int>> sortedCounts(countryCounts.begin(), countryCounts.end());

    // sắp xếp các cặp key-value trong map theo thứ tự giảm dần của value sử dụng hàm sort
    // sử dụng một hàm lambda để so sánh các cặp key-value này theo value
    sort(sortedCounts.begin(), sortedCounts.end(),
         [](const pair<string, int> &a, const pair<string, int> &b)
         {
             return a.second > b.second;
         });
    // in ra thông tin của numCountries quốc gia có nhiều tỷ phú nhất bằng cách duyệt qua sortedCounts
    cout << "Top " << numCountries << " countries with the most billionaires:" << endl;
    for (int i = 0; i < numCountries && i < sortedCounts.size(); i++)
    {
        cout << i + 1 << ". " << sortedCounts[i].first << ": " << sortedCounts[i].second << endl;
    }
}


// Hàm xuất files
void outputFile(const vector<RichPerson> &richPeople, int age)
{
    ofstream outFile;
    outFile.open("./data/old_rich_people.txt", ios::out);
    if (!outFile.is_open())
    {
        cout << "Khong the mo file " << endl;
        return;
    }

    for (const RichPerson &person : richPeople)
    {
        if (stoi(person.age) >= age)
        {
            outFile << "Rank: " << person.rank << endl
                    << "Name: " << person.personName << endl
                    << "Age: " << person.age << endl
                    << "Net worth: $" << person.finalWorth << " billion" << endl
                    << "Category: " << person.category << endl
                    << "Country: " << person.countryOfCitizenship << endl
                    << "Organization: " << person.organization << endl
                    << "Self-made: " << (person.selfMade == true ? "Yes" : "No") << endl
                    << "Gender: " << person.gender << endl
                    << "Birth date: " << person.birthDate << endl
                    << "Title: " << person.title << endl
                    << endl;
        }
    }
    outFile.close();
}

int main(int argc, char *argv[])
{
    // if (argc != 3)
    // {
    //     cerr << "Usage: " << argv[0] << " path_to_file yearOld" << endl;
    //     return 1;
    // }

    // string path_to_file = argv[1];
    // int yearOld = stoi(argv[2]);

    string path_to_file = "./data/forbes_2022_billionaires.csv";
    int n = 5;


    vector<RichPerson> persons = readData(path_to_file);

    printTechRichPeople(persons);

    printTopCountries(persons, n);

    outputFile(persons, 80);

    return 0;
}