#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

class speech{

private:
    int position;
    string speaker;
    string script;
    float length;
    int wordCount;

public:
    //constructors
    speech();
    speech(int, string, string, float);

    //methods
    int getPosition();
    const string getSpeaker() const; 
    const string getScript() const; 
    const int getLength() const; 
    const int getCount() const; 
    int countWord(string);

    //operators
    bool operator<(const speech& speechObj) const{
        if (speechObj.position < this->position)
            return true;
    }

};

