#include <iostream>
#include <vector>
#include <cpr/cpr.h>
#include <map>
#include <fstream>
#include "httplib.h"
#include "json.hpp"
#include <json/json.h>
#include "user.h"
#include "movie.h"
#include "priorityQueue.h"

using json = nlohmann::json;
using namespace httplib;
using namespace std;

// Function to calculate the movie rank based on user preferences
int calculateMovieRank(const User user, const Movie movie) {
    int rank = 0;

    // Year preference (penalize movies that are not in the user's preferred years)
    int yearDiffStart = abs(movie.getYear() - user.getStartYear());
    int yearDiffEnd = abs(movie.getYear() - user.getEndYear());

    if (yearDiffStart == 0 || yearDiffEnd == 0)
        rank += 30;  // Very high rank for movies released in the exact year of the user's start or end year
    else if ((yearDiffStart <= 2 && yearDiffEnd > 0) || (yearDiffStart > 0 && yearDiffEnd <= 2))
        rank += 25;  // Very high rank for movies released within 2 years from the start or end year
    else if ((yearDiffStart <= 5 && yearDiffEnd > 2) || (yearDiffStart > 2 && yearDiffEnd <= 5))
        rank += 20;  // High rank for movies released between 2 and 5 years from the start or end year
    else if ((yearDiffStart <= 10 && yearDiffEnd > 5) || (yearDiffStart > 5 && yearDiffEnd <= 10))
        rank += 15;  // Moderate rank for movies released between 5 and 10 years from the start or end year
    else if ((yearDiffStart <= 15 && yearDiffEnd > 10) || (yearDiffStart > 10 && yearDiffEnd <= 15))
        rank += 10;  // Lower rank for movies released between 10 and 15 years from the start or end year
    else 
        rank -= 30;  // Penalize movies released more than 15 years away from the start or end year

    // Rating preference
    if (user.getRating() == movie.getRated())
        rank += 25;

    // Runtime preference (penalize movies with significantly different runtimes)
    int runtimeDiff = abs(movie.getRuntime() - user.getRuntime());

    if (runtimeDiff <= 2)
        rank += 30; 
    else if (runtimeDiff <= 5)
        rank += 25;
    else if (runtimeDiff <= 10)
        rank += 20;
    else if (runtimeDiff <= 15)
        rank += 15;
    else
        rank -= 25; 

    // Language preference
    (user.getLanguage() == movie.getLanguage()) ? rank += 25 : rank -= 25;

    //Genre preference
    for (const string& userGenre : user.getGenres()) 
        for (const string& movieGenre : movie.getGenres()) 
            if (userGenre == movieGenre) 
                rank += 30; // Increase rank for each matching genre
    return rank;
}

//implement algorithm to rank movies
void rankMovies(User user, map<string, Movie> movies, priorityQueue& pq){
    //iterate through list of movies to process, storing only movie title and rank in priority queue
    for(const auto& movie : movies){
        movieNode temp(
        movie.second.getTitle(), // movie
        calculateMovieRank(user, movie.second), // rank
        movie.second.getYear(), // year
        movie.second.getRated(), // rating
        movie.second.getGenres(), // genres
        movie.second.getCountry(), // country
        movie.second.getDirectors(), // director
        movie.second.getWriters(), // writer
        movie.second.getActors(), // actor
        movie.second.getPlot(), // plot
        movie.second.getAwards(), // awards
        movie.second.getMetaScore(), // metascore
        movie.second.getBoxOffice(), // boxoffice
        movie.second.getDVD(), // DVD
        movie.second.getPoster() // poster
    );
        pq.insert(temp);
    }
}

//create json files based on rankings and send them to a database
void storeRankings(priorityQueue& pq) {
    ofstream file("../public/movieRecs.txt");
    // Loop through the movies in the priority queue
    while (!pq.isEmpty()) {
        movieNode movie = pq.deleteMax();
        // Write JSON object for each movie on a new line
        file << "\"movieTitle\":\"" << movie.getMovie() << "\","
             << "\"rank\":\"" << movie.getRank() << "\","
             << "\"year\":\"" << movie.getYear() << "\","
             << "\"rated\":\"" << movie.getRating() << "\","
             << "\"genre\":\"" << movie.getGenres().front() << "\","
             << "\"country\":\"" << movie.getCountry() << "\","
             << "\"director\":\"" << movie.getDirectors().front() << "\","
             << "\"writer\":\"" << movie.getWriters().front() << "\","
             << "\"actor\":\"" << movie.getActors().front() << "\","
             << "\"plot\":\"" << movie.getPlot() << "\","
             << "\"awards\":\"" << movie.getAwards() << "\","
             << "\"metascore\":\"" << movie.getMetascore() << "\","
             << "\"boxoffice\":\"" << movie.getBoxOffice() << "\","
             << "\"DVD\":\"" << movie.getDVD() << "\","
             << "\"poster\":\"" << movie.getPoster() << "\"" << endl;
    }
    file.close();
}

User handlePreferences() {
    ifstream userPreferencesFile("userPreferences.txt");
    if (!userPreferencesFile.is_open())
        cerr << "Error opening user preferences file." << std::endl;

    User user;  // Create a User object to store preferences

    string line;
    while (getline(userPreferencesFile, line)) {
        istringstream iss(line);
        string key, value;

        // Read key and value from each line
        if (iss >> key >> value) {
            // Process the key-value pair as needed
            if (key == "Year:") {
                size_t hyphenPos = value.find('-');
                if (hyphenPos != string::npos) {
                    // Extract the start and end year substrings
                    user.setStartYear(value.substr(1, hyphenPos));
                    user.setEndYear(value.substr(hyphenPos + 1, value.size()-2));
                } else
                    cerr << "Invalid year range format." << endl;
            } else if (key == "Rating:")
                user.setRating(value.substr(1, value.size() - 2));
            else if (key == "Length:")
                user.setRuntime(value.substr(1, value.size() - 2));
            else if (key == "Language:")
                user.setLanguage(value.substr(1, value.size() - 2));
            else if (key == "Genre:")
                user.setGenres(value.substr(1, value.size() - 2));
        } else
            cerr << "Error parsing line: " << line << std::endl;
    }

    userPreferencesFile.close();
    return user;
}

int main() {
    // Data structure to store movie information
    map<string, Movie> movies; //the vector of maps will be a temporary placeholder while i coode up the map data structure
    
    // Open the file
    ifstream inputFile("movieInfo.txt");
    if (!inputFile.is_open()) {
        cerr << "Error opening the file." << endl;
        return 1;
    }

    // Read each line from the file
    string line;
    while (getline(inputFile, line)) {
        // Parse the JSON data
        Json::CharReaderBuilder jsonReader;
        istringstream jsonStream(line);
        Json::Value jsonData;

        if (Json::parseFromStream(jsonReader, jsonStream, &jsonData, nullptr)) {
            // Check if the parsed data is a valid movie entry
            if (jsonData.isObject() && jsonData.isMember("Title")) {
                // Create a Movie object and populate its attributes
                Movie movie(
                    jsonData["Title"].asString(),
                    jsonData["Year"].asString(),
                    jsonData["Rated"].asString(),
                    jsonData["Released"].asString(),
                    jsonData["Language"].asString(),
                    jsonData["Country"].asString(),
                    jsonData["Runtime"].asString(),
                    jsonData["Genre"].asString(),
                    jsonData["Director"].asString(),
                    jsonData["Writer"].asString(),
                    jsonData["Actors"].asString(),
                    jsonData["Plot"].asString(),
                    jsonData["Awards"].asString(),
                    jsonData["Metascore"].asString(),
                    jsonData["BoxOffice"].asString(),
                    jsonData["DVD"].asString(),
                    jsonData["Poster"].asString()
                );

                // Add the Movie object to the map
                movies[movie.getTitle()] = movie;
            }
        } else 
            cerr << "Error parsing JSON data: " << line << endl;
    }
    
    //gather user preferences
    User user = handlePreferences();

    //rank movies according to preferences and store rankings in priority queue
    priorityQueue pq;
    rankMovies(user, movies, pq);

    //output json files and put them in a database so the web UI and get them and display them
    storeRankings(pq);
    return 0;
}

