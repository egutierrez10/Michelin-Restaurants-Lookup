// main.cpp
//
//  Name: Everardo Gutierrez
//  Program to read in Michelin restuarant data files and lookup 
//  based on criteria the user would like to. 

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// Restaurant structure
struct Restaurant{
    float lat, lon;
    string city, region, cuisine, price;
    string website;
};

/*
    Function: readFile 
    Read data from the file passed and create an instance of Restaurant structure type.
    Instance is then inserted into the map based on price level as its row index and then 
    saved into an inner map with the Restaurant instance saved with information of the michelin 
    restaurant.
    Parameters:
        fileName - string
        list - map of maps 
    Returns:
        boolean - true | false
*/
bool readFile(string filename, map<int, map<string, Restaurant>>& list){
    ifstream infile(filename);
    if(!infile.good()){
        cout << "**Error: Unable to open " << filename << "..." << endl;
        return false;
    }
    int restaurants = 0;
    string line;
    string name, dummy, lat, lon, city, region, cuisine, price, url;
    getline(infile, line);
    while(getline(infile, line)){
        stringstream s(line);
        getline(s, name, ',');
        getline(s, dummy, ',');
        getline(s, lat, ',');
        getline(s, lon, ',');
        getline(s, city, ',');
        getline(s, region, ',');
        getline(s, dummy, ',');
        getline(s, cuisine, ',');
        getline(s, price, ',');
        getline(s, url, ',');

        Restaurant r;
        r.lat = stof(lat);
        r.lon = stof(lon);
        r.city = city;
        r.region = region;
        r.cuisine = cuisine;
        r.website = url;
        if(price == "N/A"){
            list[0].insert(make_pair(name, r));
        }else{
            list[price.length()].insert(make_pair(name, r));
        }
        restaurants++;
    }
    cout << "# of restaurants: " << restaurants << endl; 
    return true;
}

/*
    Function: displayCommands 
    Display commands available for user to enter
    Parameters:
        none
    Returns:
        void
*/
void displayCommands(){
    cout << "Commands available to be entered:" << endl;
    cout << "   Search by city (ex. cChicago)" << endl;
    cout << "   Search by region (ex. rCalifornia)" << endl;
    cout << "   Search by cuisine (ex. fContemporary)" << endl;
    cout << "   Search by price (ex. $$$)" << endl;
    cout << "   Search by price unknown (ex. N/A)" << endl;
    cout << "   Search by name (ex. Alinea)" << endl; 
}

/*
    Function: searchCity 
    Search the map of maps for all michelin restaurants that reside in the city
    the user has entered to search for. Display all the restaurants that fit this criteria.
    Parameters:
        command - string
        list - map of maps
    Returns:
        void
*/
void searchCity(string command, map<int, map<string, Restaurant>>& list){
    cout << "Restaurants found for city of " << command << endl;
    for(int i = 0; i < list.size(); i++){ // loop through the outer map (look at it as the row for price)
        for(auto j: list[i]){ // look through the inner map where all the restaurants reside
            if(j.second.city == command){ // determine if our restaurant fits the criteria user wants
                // Display information about the michelin restaurant
                cout << "Name: " << j.first << endl;
                cout << "   Location: " << j.second.city << ", " << j.second.region << "(" << j.second.lat << ", " << j.second.lon << ")" << endl;
                cout << "   Cuisine: " << j.second.cuisine << endl;
                cout << "   Visit website for more info: " << j.second.website << endl;
                cout << endl;
            }
        }
    }
}

/*
    Function: searchRegion 
    Search the map of maps for all michelin restaurants that reside in the region
    the user has entered to search for. Display all the restaurants that fit this criteria.
    Parameters:
        command - string
        list - map of maps
    Returns:
        void
*/
void searchRegion(string command, map<int, map<string, Restaurant>>& list){
    cout << "Restaurants found for region of " << command << endl;
    for(int i = 0; i < list.size(); i++){
        for(auto j: list[i]){
            if(j.second.region == command){
                cout << "Name: " << j.first << endl;
                cout << "   Location: " << j.second.city << ", " << j.second.region << "(" << j.second.lat << ", " << j.second.lon << ")" << endl;
                cout << "   Cuisine: " << j.second.cuisine << endl;
                cout << "   Visit website for more info: " << j.second.website << endl;
                cout << endl;
            }
        }
    }
}

/*
    Function: searchCuisine 
    Search the map of maps for all michelin restaurants fall under the user entered cuisine
    category. Display all the restaurants that fit this criteria.
    Parameters:
        command - string
        list - map of maps
    Returns:
        void
*/
void searchCuisine(string command, map<int, map<string, Restaurant>>& list){
    cout << "Restaurants found for cuisine of " << command << endl;
    for(int i = 0; i < list.size(); i++){
        for(auto j: list[i]){
            if(j.second.cuisine == command){
                cout << "Name: " << j.first << endl;
                cout << "   Location: " << j.second.city << ", " << j.second.region << "(" << j.second.lat << ", " << j.second.lon << ")" << endl;
                cout << "   Cuisine: " << j.second.cuisine << endl;
                cout << "   Visit website for more info: " << j.second.website << endl;
                cout << endl;
            }
        }
    }
}

/*
    Function: searchPrice 
    Search the map of maps for all michelin restaurants fall under the user entered price
    level. Display all the restaurants that fit this criteria.
    Parameters:
        command - string
        list - map of maps
    Returns:
        void
*/
void searchPrice(string command, map<int, map<string, Restaurant>>& list){
    int index = command == "N/A" ? 0 : command.length();
    cout << "Restaurants found for price of " << command << endl;
    for(auto i: list[index]){
        cout << "Name: " << i.first << endl;
        cout << "   Location: " << i.second.city << ", " << i.second.region << "(" << i.second.lat << ", " << i.second.lon << ")" << endl;
        cout << "   Cuisine: " << i.second.cuisine << endl;
        cout << "   Visit website for more info: " << i.second.website << endl;
        cout << endl;
    }
}

/*
    Function: searchName 
    Default search in the map of maps for all michelin restaurants that have the string entered by the user
    in the name of the michelin restaurants. Display all the restaurants that possibly could be what the 
    user is searching for.
    Parameters:
        command - string
        list - map of maps
    Returns:
        void
*/
void searchName(string command, map<int, map<string, Restaurant>>& list){
    cout << "Restaurants found for name of " << command << endl;
    for(int i = 0; i < list.size(); i++){
        for(auto j: list[i]){
            if(j.first.find(command) != string::npos){
                cout << "Name: " << j.first << endl;
                cout << "   Location: " << j.second.city << ", " << j.second.region << "(" << j.second.lat << ", " << j.second.lon << ")" << endl;
                cout << "   Cuisine: " << j.second.cuisine << endl;
                cout << "   Visit website for more info: " << j.second.website << endl;
                cout << endl;
            }
        }
    }
}

int main(){
    map<int, map<string, Restaurant>> list; // map of maps
    string fileName, choice;
    // prompt user for choice of star level restaurants to look in
    cout << "*** Michelin Restaurant Lookup ***" << endl;
    cout << "Choose Michelin Restaurant filename." << endl;
    cout << "   1 = One Star Michelin Restaurants" << endl;
    cout << "   2 = Two Star Michelin Restaurants" << endl;
    cout << "   3 = Three Star Michelin Restaurants" << endl;
    cout << "Enter your choice: ";
    getline(cin, choice);
    
    //determine which data file to read from
    if(choice == "1")
        fileName = "one-star-michelin.csv";
    else if(choice == "2")
        fileName = "two-star-michelin.csv";
    else 
        fileName = "three-star-michelin.csv";
    
    //read in data file and determine if we were successful at doing so
    bool success = readFile(fileName, list);
    if(!success){
        cout << "Could not read file " << fileName << endl;
        cout << "Terminating program..." << endl;
        return 0;
    }

    // success we had so display commands user can enter and prompt for inital command
    displayCommands();
    string command;
    cout << "Enter a command, help to display commands, or # to quit>";
    getline(cin, command);
    while(command != "#"){ // keep looping and prompting for user commands to search by
        if(command == "help"){
            displayCommands();
        }else if(command[0] == 'c'){ // search by city
            command = command.erase(0,1);
            searchCity(command, list);
        }else if(command[0] == 'r'){ //search by region
            command = command.erase(0,1);
            searchRegion(command, list);
        }else if(command[0] == 'f'){ //search by cuisine
            command = command.erase(0,1);
            searchCuisine(command, list);
        }else if(command[0] == '$' || command == "N/A"){ //search by price - specific or unknown
            searchPrice(command, list);
        }else{ // search by name
            searchName(command,list);
        }
        cout << "Enter a command, help to display commands, or # to quit>";
        getline(cin, command);
    }
    return 0;
}