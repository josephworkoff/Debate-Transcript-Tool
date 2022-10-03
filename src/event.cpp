#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include "event.h"

using namespace std;

//default constructor
event::event(){
    date = "";
    name = "";

    speakerCount = 0;
    speechCount = 0;
    totalWordCount = 0;
    totalSpeakingTime = 0;

}

//overloaded constructor
event::event(string nameString, string dateString){
    name = nameString;
    date = dateString;

    speakerCount = 0;
    speechCount = 0;
    totalWordCount = 0;
    totalSpeakingTime = 0;

}

/************************************************************/
// Function name: addSpeech
// Description: Adds a speech to the event's speeches list. Adds the speaker to the speaker map if necessary.
// Parameters: speech - speech object to add
// Return Value: none
/************************************************************/
void event::addSpeech(speech sp){

    speeches.push_front(sp);

    auto it = speeches.front();

    //update event
    speechCount++;
    totalWordCount += sp.getCount();
    totalSpeakingTime += sp.getLength();

    string speaker = sp.getSpeaker();

    //add new speaker
    if (speakers.count(speaker) == 0){
        speakers[speaker] = speakerStats();
        speakerCount++;
    }

    //update speaker stats
    speakers[speaker].timesSpoke++;
    speakers[speaker].totalWordCount += sp.getCount();
    speakers[speaker].totalSpeakingTime += sp.getLength();
    
}

/************************************************************/
// Function name: getDate
// Description: returns date of event
// Parameters: none
// Return Value: string - event date
/************************************************************/
const string event::getDate() const {return date;}
/************************************************************/
// Function name: getName
// Description: returns name of the event
// Parameters: none
// Return Value: string - event name
/************************************************************/
const string event::getName() const {return name;}

/************************************************************/
// Function name: getSpeakerCount
// Description: returns number of speakers in the event
// Parameters: none
// Return Value: int - speaker count
/************************************************************/
const int event::getSpeakerCount() const {return speakerCount;}

/************************************************************/
// Function name: getSpeechCount
// Description: returns number of of speeches in the event
// Parameters: none
// Return Value: int - speech count
/************************************************************/
const int event::getSpeechCount() const {return speechCount;}

/************************************************************/
// Function name: getWordCount
// Description: returns totalWordCount
// Parameters: none
// Return Value: int - word count
/************************************************************/
const int event::getWordCount() const {return totalWordCount;}

/************************************************************/
// Function name: getTotalTime
// Description: returns totalSpeakingTime
// Parameters: none
// Return Value: int - total speaking time of event
/************************************************************/
const int event::getTotalTime() const {return totalSpeakingTime;}

/************************************************************/
// Function name: getSpeakers
// Description:
// Parameters: none
// Return Value: map<string, speakerStats> - map of <speaker name, speaker stats>
/************************************************************/
map<string, speakerStats> event::getSpeakers() {return speakers;};

