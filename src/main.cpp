/*!
\mainpage Democratic Primary Debate Transcript Analysis Tool
\n
This application uses the data set found here: https://www.kaggle.com/brandenciranni/democratic-debate-transcripts-2020.\n

This dataset contains the transcripts from each Democratic Primary debate from June 2019 to February 2020, broken up by each individual speech and encoded in CSV format. 
Each datum includes the date of the event, the event name, the section of the debate, the speaker's name, the words spoken, and the speech duration.

*/


/*!	\file main.cpp
*	\brief Debate Transcript Analysis tool
*
*   \b Author: Joseph Workoff\n
*   \b Filename: main.cpp\n
*   \n
*   This program will read the transcript data set into data structures, then present the user options to sort and view them based on several metrics.
*   
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include "event.h"

using namespace std;


/*!
*   \fn eventDetails
*	\param event* eventToStat - Pointer to Event to print
*	\return void
*   
*   \par Description
*   Prints an event's statistics, then displays a menu of sort options for the attendees.
*   Prints the attendees' statistics in the specified order.
*/   
void eventDetails(event* eventToStat);

/*!
*   \fn eventsMenu
*	\param vector<event*> &allSpeeches - Vector containing every event.
*	\return void
*   
*   \par Description
*   Displays a menu of sort options for the events.
*   Prints the events in the specified order.
*/   
void eventsMenu(vector<event*> &allSpeeches);

/*!
*   \fn getLength
*	\param string line - CSV line to read from
*	\param size_t &startPos - Line index to read from (called on the comma).
*	\return float - speaking time in seconds
*   
*   \par Description
*   Reads the speaking time length from the end of a line of the CSV. Updates the start position.
*/   
int getLength(string line, size_t &startPos);

/*!
*   \fn mainMenu
*	\param vector<event*> &allSpeeches
*	\return void
*   
*   \par Description
*   Displays a menu prompting for either speaker or event information.
*/   
void mainMenu(vector<event*> &allSpeeches);

/*!
*   \fn nextCSV
*	\param string line - CSV line to read from
*	\param size_t &startPos - Line index to read from (called after the comma).
*	\return string - CSV data
*   
*   \par Description
*   Reads next value from a line of the CSV file. Updates the start position.
*/   
string nextCSV(string line, size_t &startPos);

/*!
*   \fn printEventAttendeesStats
*	\param vector<pair<string,speakerStats>> &speakers - Vector containing pairs of <speaker name, speaker stats>
*	\param int mode - Determines what to print
*           - 0 - Called from eventDetails: Printing information pertaining only to that event (No total attendance)
*           - 1 - Called from speakerMenu: Printing information pertaining to every event (Total attendance)
*	\return void
*   
*   \par Description
*   Prints a table of stats for all attendees of a single event.
*/   
void printEventAttendeesStats(vector<pair <string, speakerStats> > &speakers, string name, int mode);

/*!
*   \fn printEvents
*	\param vector<event*> &allSpeeches - vector containing every event
*	\return void
*   
*   \par Description
*   Prints every event's statistics
*/   
void printEvents(vector<event*> &allSpeeches);

/*!
*   \fn readFile
*	\param vector<event*> &allSpeeches - Vector to contain every event
*	\return void
*   
*   \par Description
*   Reads the entire CSV file in the events vector
*/   
void readFile(vector<event*> &allSpeeches);

/*!
*   \fn speakerMenu
*	\param vector<event*> &allSpeeches - Vector containing every event
*	\return void
*   
*   \par Description
*   Collects each unique speaker from every event, talleying their individual stats. 
*   Then displays a menu of sort options.
*/   
void speakerMenu(vector<event*> &allSpeeches);

/*!
*   \fn Main
*	\param 
*	\return void
*   
*   \par Description
*   Instantiates the events vector. Reads in the event data. Displays the main menu.
*/   
int main(){
    vector<event*> allSpeeches;
    readFile(allSpeeches);
    mainMenu(allSpeeches);
}



int getLength(string line, size_t &startPos){
    int length;
    startPos++;

    //Some lines have no length; Default to 0.0

    //don't crash if reading in nothing
    try{
        length = stoi(line.substr(startPos, string::npos));
    }
    catch(const std::exception& e){
        return 0;
    }
    return length;
}



string nextCSV(string line, size_t &startPos){
    
    //starting after comma

    size_t newPos = 0;
    //Read until next quote
    if (line[startPos] == '"'){
        startPos++;
        newPos = line.find('"', startPos);
    }
    else //read until next comma
        newPos = line.find(',', startPos);

    if (newPos >= string::npos)
        return "Failure";
    else{
        string val = line.substr(startPos, newPos - startPos);
        startPos = newPos;
        if (line[startPos] == '"'){
            startPos++; //eat end quote
        }
        return val;
    }
}



void readFile(vector<event*> &allSpeeches){
    ifstream transcriptFile;
    string fileName = "debate_transcripts_v3_2020-02-26.csv";

    string line;

    //open transcript file
    transcriptFile.open(fileName);
    if (!transcriptFile.is_open()){
        cout << "Failed to open file." << endl;
        exit(EXIT_FAILURE);
    }

    //move past the label line
    getline(transcriptFile, line);
    line.clear();


    int lineNumber = 1;
    int lineOfFile = 1;
    string date = "";
    string prevDate = "";
    string eventName, section, speaker, script = "";
    float length = 0.0;

    size_t pos = 0;

    event* eventObj;

    cout << "Reading in events from file. ";

    //read through entire file
    while (!transcriptFile.eof()){
        pos = 0;
        line.clear();
        lineOfFile++;

        getline(transcriptFile, line);

        // get the date
        date = nextCSV(line, pos);
        // cout << date << endl;
        if (date == "Failure"){
            printf("Bad Date: Line #%d of file.\n", lineOfFile);
            continue;
        }

        pos++;
        //get the event name
        eventName = nextCSV(line, pos);
        // cout << eventName << endl;
        if (eventName == "Failure"){
            printf("Bad Event: Line #%d of file.\n", lineOfFile);
            continue;
        }

        pos++;
        //get the section
        section = nextCSV(line, pos);
        // cout << section << endl;
        if (section == "Failure"){
            printf("Bad Section: Line #%d of file.\n", lineOfFile);
            continue;
        }
        
        pos++;
        //get the speaker name
        speaker = nextCSV(line, pos);
        // cout << speaker << endl;
        if (eventName == "Failure"){
            printf("Bad Speaker: Line #%d of file.\n", lineOfFile);
            continue;
        }

        pos++;
        //get the transcript
        script = nextCSV(line, pos);
        // cout << script << endl;
        if (eventName == "Failure"){
            printf("Bad Script: Line #%d of file.\n", lineOfFile);
            continue;
        }

        //get the speaking length
        length = getLength(line, pos);
        // cout << length << endl;
        if (length == -1){
            printf("Bad Length: Line #%d of file.\n", lineOfFile);
            continue;
        }

        
        //if line is from a new event, create a new event object
        if (date != prevDate){
            lineNumber = 1; //reset line number
            prevDate = date;

            //create new event object
            eventObj = new event(eventName, date);
            allSpeeches.emplace_back(eventObj);
        }
        else{
            lineNumber++;
        }

        //add new speech object to event object
        eventObj->addSpeech(speech(lineNumber, speaker, script, length));

    }//end while

    cout << "Finished Reading File. " << endl;

}//end readFile



void printEvents(vector<event*> &allSpeeches){
    cout << endl << "===================================================================" << endl;
    cout << "\tAll Events: " << endl;
    cout << "===================================================================" << endl;
    for (int i = 0; i < allSpeeches.size(); i++){
        cout << setw(3) << right << i + 1 << "| ";
        cout << setw(40) << left << allSpeeches[i]->getName() << " | ";
        cout << setw(11) << left << allSpeeches[i]->getDate() << " | ";
        cout << setw(3) << left << allSpeeches[i]->getSpeakerCount() << endl;
    }
    cout << endl;
}



void eventsMenu(vector<event*> &allSpeeches){

    printEvents(allSpeeches);
    cout << endl;

    string choice = " ";
    while (choice != "X"){
        cout << "Display All Events: " << endl;
        cout << "\tA) Sort by Name" << endl;
        cout << "\tB) Sort by Date" << endl;
        cout << "\tC) Sort by Number of Speakers" << endl;
        cout << "\t#) View Event Details" << endl;
        cout << "\tX) Go Back" << endl;
        cout << endl << "\t>>";

        cin >> choice;
        cin.ignore();
        cout << endl << endl;

        if (choice == "A" || choice == "a"){ //name
            sort(allSpeeches.begin(), allSpeeches.end(), event::sortEventName());
            printEvents(allSpeeches);
        }
        else if (choice == "B" || choice == "b"){ //date
            sort(allSpeeches.begin(), allSpeeches.end(), event::sortEventDate());
            printEvents(allSpeeches);
        }
        else if (choice == "C" || choice == "c"){ //number of speakers
            sort(allSpeeches.begin(), allSpeeches.end(), event::sortEventAttendance());
            printEvents(allSpeeches);
        }
        else if (choice == "X" || choice == "x"){
            break;
        }
        else{
            int opt = 0;
            try{ //check if number
               opt = stoi(choice);
            }
            catch(const std::exception& e){
                cout << "Invalid Option." << endl;
                continue;
            }
            opt--;
            if ((opt >= 0) && (opt < allSpeeches.size())){ //check if valid index
                eventDetails(allSpeeches[opt]);
            }
            else{
                cout << "Invalid Option." << endl;
                continue;
            }
        } //end switch
    }//end while
}//end printEvents



void eventDetails(event* eventToStat){

    //print event stats
    cout << endl << "===================================================================" << endl;
    cout << "\t" << eventToStat->getName() << " : " << eventToStat->getDate() << endl << endl;
    cout << setw(25) << left << "Total Word Count" << left << " | " << setw(5) << eventToStat->getWordCount() << endl;
    cout << setw(25) << left << "Average Word Count" << left << " | " << setw(5) << eventToStat->getWordCount() / eventToStat->getSpeechCount() << endl;
    cout << setw(25) << left << "Total Speaking Time" << left << " | " << setw(5) << eventToStat->getTotalTime() << endl;
    cout << setw(25) << left << "Average Speaking Time" << left << " | " << setw(5) << eventToStat->getTotalTime() / eventToStat->getSpeechCount() << endl;
    cout << "===================================================================" << endl;
   

    //push event's speakers into vector for sorting
    map<string,speakerStats> speakersMap = eventToStat->getSpeakers();
    vector<pair <string, speakerStats> > speakers;

    for (auto it = speakersMap.begin(); it != speakersMap.end(); it++){
        speakers.push_back({it->first, it->second});
    }

    //display sort menu
    char choice = 'Z';
    while (choice != 'X'){
        cout << "Display Speakers: " << endl;
        cout << "\tA) Sort by Name" << endl;
        cout << "\tB) Sort by Highest Word Count" << endl;
        cout << "\tC) Sort by Average Word Count" << endl;
        cout << "\tD) Sort by Longest Speaking Time" << endl;
        cout << "\tE) Sort by Average Speaking Time" << endl;
        cout << "\tX) Go Back" << endl;
        cout << endl << "\t>>";

        cin >> choice;
        cin.ignore();
        cout << endl;
        choice = toupper(choice);
       
        switch (choice){
            case 'A': //Name
                sort(speakers.begin(), speakers.end(), event::sortSpeakersName());
                printEventAttendeesStats(speakers, eventToStat->getName(), 0);
                break;
            case 'B': //High WC
                sort(speakers.begin(), speakers.end(), event::sortSpeakersHighWC());
                printEventAttendeesStats(speakers, eventToStat->getName(), 0);
                break;
            case 'C': //AVG WC
                sort(speakers.begin(), speakers.end(), event::sortSpeakersAvgWC());
                printEventAttendeesStats(speakers, eventToStat->getName(), 0);
                break;
            case 'D': //High Time
                sort(speakers.begin(), speakers.end(), event::sortSpeakersHighTime());
                printEventAttendeesStats(speakers, eventToStat->getName(), 0);
                break;
            case 'E': //AVG Time
                sort(speakers.begin(), speakers.end(), event::sortSpeakersAvgTime());
                printEventAttendeesStats(speakers, eventToStat->getName(), 0);
                break;
            case 'X': //Exit
                break;
            
            default:
                cout << "Invalid Option." << endl;
                break;
            }
    
    }//end while

}//end eventDetails



//presorted
void printEventAttendeesStats(vector<pair <string, speakerStats> > &speakers, string name, int mode){
    //heading

    cout << endl << "===================================================================" << endl;
    cout << "\t" << name << endl;
    cout << "===================================================================" << endl;

    cout << "    | " <<  setw(21) << left << "Speaker";
    if (mode == 1){
        cout << "| #EVENTS";
    }
    cout << "|   WC  " <<  "| AVG WC " << setw(6) << left << "| TOT TIME " << setw(10) << left <<"| AVG TIME " << endl;

    //print all speakers' stats
    for (int i = 0; i < speakers.size(); i++){
        string name = speakers[i].first;
        speakerStats stats = speakers[i].second;

        //number + name
        cout << setw(3) << left << i + 1 << " | " << setw(20) << left << name << " | ";

        //#appearances if mode 1
        if (mode == 1){
            cout << setw(6) << left << speakers[i].second.appearances << " | ";
        }

        //total/average WC
        cout << setw(5) << left <<  stats.totalWordCount << " | " << setw(6) << left << stats.totalWordCount / stats.timesSpoke << " | ";
        //total/average speaking time
        cout << setw(8) << setprecision(7) << left << stats.totalSpeakingTime << " | " << setw(7) << setprecision(7) << left << stats.totalSpeakingTime / stats.timesSpoke << endl;

    }
    cout << endl;
}



void speakerMenu(vector<event*> &allSpeeches){
    map<string, speakerStats> allSpeakers; //map to store info on all speakers
    map<string, speakerStats> tempSpeakers; //temp map for .getSpeakers() return value

    //get total stats from all speakers

    //loop through each event
    for (int i = 0; i < allSpeeches.size(); i++){
        tempSpeakers = allSpeeches[i]->getSpeakers();

        //loop through each event's speakers
        for (auto speaker = tempSpeakers.begin(); speaker != tempSpeakers.end(); speaker++){

            //add new speaker to map
            if (allSpeakers.count(speaker->first) == 0){
                allSpeakers[speaker->first].appearances = 1;
                allSpeakers[speaker->first].timesSpoke = speaker->second.timesSpoke;
                allSpeakers[speaker->first].totalWordCount = speaker->second.totalWordCount;
                allSpeakers[speaker->first].totalSpeakingTime = speaker->second.totalSpeakingTime;
            }

            //update speaker
            else{
                allSpeakers[speaker->first].appearances++;
                allSpeakers[speaker->first].timesSpoke += speaker->second.timesSpoke;
                allSpeakers[speaker->first].totalWordCount += speaker->second.totalWordCount;
                allSpeakers[speaker->first].totalSpeakingTime += speaker->second.totalSpeakingTime;
            }
        } //end speaker for
    } //end event for


    //push speaker info into vector for sorting
    vector<pair <string, speakerStats > > speakersVec;
    for (auto it = allSpeakers.begin(); it != allSpeakers.end(); it++){
        speakersVec.push_back({it->first, it->second});
    }


    //menu loop
    string choice = " ";
    while ((choice != "X") && (choice!="x")){
        //menu options
        cout << endl << "===================================================================" << endl;
        cout << "\tView Speakers" << endl;
        cout << "===================================================================" << endl;
        cout << "\tA) Sort by Name" << endl;
        cout << "\tB) Sort by Number of Events Attended" << endl;
        cout << "\tC) Sort by Highest Word Count" << endl;
        cout << "\tD) Sort by Average Word Count" << endl;
        cout << "\tE) Sort by Highest Speaking Time" << endl;
        cout << "\tF) Sort by Average Speaking Time" << endl;
        // cout << "\t#) View Speaker Details" << endl;
        cout << "\tX) Go Back" << endl;
        cout << endl << "\t>>";

        //get choice
        cin >> choice;
        cin.ignore();
        cout << endl;
        // choice = toupper(choice);

        string name = "All Events";

        if (choice == "A" || choice == "a"){ //name
            sort(speakersVec.begin(), speakersVec.end(), event::sortSpeakersName());
            printEventAttendeesStats(speakersVec, name, 1);
        }
        else if (choice == "B" || choice == "b"){ //attendance
            sort(speakersVec.begin(), speakersVec.end(), event::sortSpeakersAttendance());
            printEventAttendeesStats(speakersVec, name, 1);
        }
        else if (choice == "C" || choice == "c"){ //high word
            sort(speakersVec.begin(), speakersVec.end(), event::sortSpeakersHighWC());
            printEventAttendeesStats(speakersVec, name, 1);
        }
        else if (choice == "D" || choice == "d"){ //avg word
            sort(speakersVec.begin(), speakersVec.end(), event::sortSpeakersAvgWC());
            printEventAttendeesStats(speakersVec, name, 1);
        }
        else if (choice == "E" || choice == "e"){ //high time
            sort(speakersVec.begin(), speakersVec.end(), event::sortSpeakersHighTime());
            printEventAttendeesStats(speakersVec, name, 1);
        }
        else if (choice == "F" || choice == "f"){ //avg time
            sort(speakersVec.begin(), speakersVec.end(), event::sortSpeakersAvgTime());
            printEventAttendeesStats(speakersVec, name, 1);
        }
        else if (choice == "X" || choice == "x"){
            return;
        }
        else{
            cout << "Invalid Option" << endl;
        }
    }
} //end speakerMenu



void mainMenu(vector<event*> &allSpeeches){

    char opt = ' ';
    while (opt != 'X'){

        //display menu
        cout << endl << "===================================================================" << endl;
        cout << "\tMain Menu" << endl;
        cout << "===================================================================" << endl;
        cout << "\tA) View Events" << endl;
        cout << "\tB) View Speakers" << endl;
        cout << "\tX) Exit" << endl << endl;
        cout << "\t>>";

        //get choice
        opt = getchar();
        opt = toupper(opt);
        cout << endl;

        //display chosen menu
        switch (opt){
            case 'A':
                eventsMenu(allSpeeches);
                break;
            case 'B':
                speakerMenu(allSpeeches);
                break;
            case 'X':
                exit(0);
            default:
                cout << "Invalid Option." << endl;
        }
    }
}