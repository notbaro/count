#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

void search(map<string, int>& m, const string& s);
void put();
void print(const string& fileName);
void removeSymbol(string& s);

int main()
{
    print("text.txt");
    put();
}

//function to search if a string already exist in the map, if yes, increment the number of words
//if not, add it to the map and set the number to 1
void search(map<string, int>& m, const string& s)
{
    bool found = false;
    auto i = m.begin(); //iterator
    for (; i != m.end() && !found; i++)
    {
        if (i->first == s)
        {
            found = true;
            i->second++;
        }
    }
    if (i == m.end())
    {
        m.insert(pair<string, int>(s, 1));
    }
}

//function to ask for a filename, and use search() function to put the text file into the map
// and print out the number of words
void put()
{
    map<string, int> m;
    ifstream inF;
    string fileName, temp;
    do
    {
        cout << "Enter filename with .txt extension. (eg: text.txt) " << endl;
        cin >> fileName;
        inF.open(fileName.c_str());
        if (!inF.is_open())
        {
            cout << "Invalid file name entered. Please try again.";
        }
    } while (!inF.is_open());
    while (!inF.eof())
    {
        inF >> temp;
        removeSymbol(temp);
        if (temp[0] >= 'A' && temp[0] <= 'Z')  //decapitalize
            temp[0] += 'a' - 'A';
        if (temp != "")
            search(m, temp);
    }
    for (auto i : m)
    {
        cout << i.first << " " << i.second << endl;
    }
}

//helper function to print out the text file
void print(const string& fileName)
{
    vector<string> v;
    string s;
    ifstream inF;
    inF.open(fileName.c_str());
    while (getline(inF, s))
    {
        v.push_back(s);
    }
    for (string i : v)
        cout << i << endl;
}

//helper function to remove symbols before and after a word
//eg: Hello World! becomes Hello and World
void removeSymbol(string &s)
{
    string sy = ",.:'\";/[](){}-!";
    for (char i : sy)
    {
        if (i == s[0])
        {
            if (s.size() == 1)
                s = "";
            else
                s = s.substr(1, s.size() - 1);
        }
        if (s.size() >= 1 && i == s[s.size() - 1])
        {
            if (s.size() == 1)
                s = "";
            else
                s = s.substr(0, s.size() - 1);
        }
    }
}
