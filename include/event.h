/*!	\file event.h
*	\brief Event class header file
*
*   \b Author: Joseph Workoff\n
*   \b Filename: event.h\n
*   \b Purpose: Define a class for representing a single event.\n
*   \n
*   An event object contains statistics for one of the events in the data. \n
*   Events store references to all speeches that take place during that event, and tally statistics about them as they are created. 
*   
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <forward_list>
#include "speech.h"

using namespace std;

struct speakerStats{
    int timesSpoke = 0, totalWordCount = 0, totalSpeakingTime = 0;
    int appearances = 0;
};


class event{
    private:
        string date;
        string name;
        
        map<string, speakerStats> speakers;

        forward_list<speech> speeches;

        int speechCount;
        int totalWordCount;
        int totalSpeakingTime;
        int speakerCount;

    public:
        event();
        event(string, string);

        const string getDate() const;
        const string getName() const;
        const int getSpeakerCount() const;
        const int getSpeechCount() const;
        const int getWordCount() const;
        const int getTotalTime() const;

        void addAttendee(string);
        map<string, speakerStats> getSpeakers();

        int wordSearch();

        void addSpeech(speech);


        bool operator<(const event& eventObj) const{
            if (eventObj.date < this->date)
                return true;
        }

        bool operator=(const event& eventObj) const{
            if (eventObj.date == this->date)
                return true;
        }


        //comparators

        //sorting events
        struct sortEventName{ 
            bool operator()(event* const& e1, event* const& e2){
                return e1->getName() < e2->getName(); 
            }
        }; 

        struct sortEventDate{ 
            bool operator()(event* const& e1, event* const& e2){
                return e1->getDate() > e2->getDate(); 
            }
        }; 

        struct sortEventAttendance{ 
            bool operator()(event* const& e1, event* const& e2){
                return e1->speakerCount > e2->speakerCount; 
            }
        }; 


        //sorting speakers
        struct sortSpeakersName{ 
            bool operator()( std::pair<std::string, speakerStats> speaker1 , std::pair<std::string, speakerStats> speaker2){
                return speaker1.first < speaker2.first; 
            }
        }; 

        struct sortSpeakersAvgWC{ 
            bool operator()( std::pair<std::string, speakerStats> speaker1 , std::pair<std::string, speakerStats> speaker2){
                return (speaker1.second.totalWordCount / speaker1.second.timesSpoke)  > (speaker2.second.totalWordCount / speaker2.second.timesSpoke); 
            }
        }; 

        struct sortSpeakersHighWC{ 
            bool operator()( std::pair<std::string, speakerStats> speaker1 , std::pair<std::string, speakerStats> speaker2){
                return (speaker1.second.totalWordCount)  > (speaker2.second.totalWordCount); 
            }
        }; 

        struct sortSpeakersAvgTime{ 
            bool operator()( std::pair<std::string, speakerStats> speaker1 , std::pair<std::string, speakerStats> speaker2){
                return (speaker1.second.totalSpeakingTime / speaker1.second.timesSpoke)  > (speaker2.second.totalSpeakingTime / speaker2.second.timesSpoke); 
            }
        }; 

        struct sortSpeakersHighTime{ 
            bool operator()( std::pair<std::string, speakerStats> speaker1 , std::pair<std::string, speakerStats> speaker2){
                return (speaker1.second.totalSpeakingTime)  > (speaker2.second.totalSpeakingTime); 
            }
        }; 

        struct sortSpeakersAttendance{ 
            bool operator()( std::pair<std::string, speakerStats > speaker1 , std::pair<std::string, speakerStats > speaker2){
                return speaker1.second.appearances > speaker2.second.appearances; 
            }
        }; 



};


