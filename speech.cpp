#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include "speech.h"

using namespace std;

//default constructor
speech::speech(){
    position = 0;
    speaker = "";
    script = "";
    length = 0.0;
    wordCount = 0;

}

//overloaded constructor
speech::speech(int pos, string speakerString, string scriptString, float lengthFloat){
    position = pos;
    speaker = speakerString;
    script = scriptString;
    length = lengthFloat;
    wordCount = countWord(script);
}

/************************************************************/
// Function name: countWord
// Description: Counts the number of words in the speech
// Parameters: string transcript - speech to count
// Return Value: int - number of word
/************************************************************/
int speech::countWord(string transcript){
    int count = 0;
    int pos = 0;

    pos = transcript.find_first_of(",. ");
    while (pos != string::npos){
        count++;
        pos = transcript.find_first_of(",. ", pos + 1);
        while (pos < transcript.length() && !isalnum(transcript[pos])){
            pos++;
        }
    }

    return count;
}

/************************************************************/
// Function name: getPosition
// Description: returns chronological position of speech in event
// Parameters: none
// Return Value: int - position
/************************************************************/
int speech::getPosition(){return position;}

/************************************************************/
// Function name: getSpeaker
// Description: returns speaker name
// Parameters: none
// Return Value: string - speaker name
/************************************************************/
const string speech::getSpeaker() const{return speaker;}

/************************************************************/
// Function name: getScript
// Description: returns script text
// Parameters: none
// Return Value: string -speaker name
/************************************************************/
const string speech::getScript() const {return script;}

/************************************************************/
// Function name: getLength
// Description: returns speaking time
// Parameters: none
// Return Value: int - speech time length
/************************************************************/
const int speech::getLength() const {return length;}

/************************************************************/
// Function name: getCount
// Description: returns word count
// Parameters: none
// Return Value: int - word count
/************************************************************/
const int speech::getCount() const {return wordCount;}
