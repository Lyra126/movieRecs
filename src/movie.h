#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class Movie{
    private:
        string title;
        int year;
        string rated;
        string releaseDate;
        string language;
        int runtime;
        vector<string> genres;
        string country;
        vector<string> directors;
        vector<string> writers;
        vector<string> actors;
        string plot;
        string awards;
        string metascore;
        string boxoffice;
        string DVD;
        string poster;
        
    public:
        //default constructor
        Movie(): title(""), year(0), rated(""), releaseDate(""), language(""), runtime(0), country(""), plot(""), awards(""), metascore(""), boxoffice(""), DVD(""), poster(""){}
        
        Movie(string title, string year, string rated, string releaseDate, string language, string country, string runtimeStr, string genresStr, string directorStr, string writerStr, string actorStr, string plot, string awards, string metascore, string boxoffice, string DVD, string poster){
            setTitle(title);
            setYear(year);
            setRated(rated);
            setReleaseDate(releaseDate);
            setLanguage(language);
            setCountry(country);
            setPlot(plot);
            setAwards(awards);
            setMetaScore(metascore);
            setBoxOffice(boxoffice);
            setDVD(DVD);
            setPoster(poster);
            setRuntime(runtimeStr);
            setGenres(genresStr);
            setDirectors(directorStr);
            setWriters(writerStr);
            setActors(actorStr);
        }

        //accessors
        string getTitle() const
            { return this->title; }
        int getYear() const
            { return this->year; }
        string getRated() const
            { return this->rated; }
        string getReleaseDate() const
            { return this->releaseDate; }
        string getLanguage() const
            { return this->language; }
        string getCountry() const
            { return this->country; }
        string getPlot() const
            { return this->plot; }
        string getAwards() const
            { return this->awards; }
        string getMetaScore() const
            { return this->metascore; }
        string getBoxOffice() const
            { return this->boxoffice; }
        string getDVD() const
            { return this->DVD; }
        string getPoster() const
            { return this->poster; }
        int getRuntime() const
            { return this->runtime; }
        vector<string> getGenres() const
            { return this->genres; }
        vector<string> getDirectors() const
            { return this->directors; }
        vector<string> getWriters() const
            { return this->writers; }
        vector<string> getActors() const
            { return this->actors; }
        

        //mutators
        void setTitle(string title)
            { this->title = title; }
        void setYear(string yearStr) {
            // Find the position of the first digit
            size_t pos = yearStr.find_first_of("0123456789");

            if (pos != string::npos) {
                // Extract the numeric part of the year string
                string numStr = yearStr.substr(pos);

                // Check if the numeric part contains a hyphen
                size_t hyphenPos = numStr.find_first_of("-");
                if (hyphenPos != string::npos) 
                    numStr = numStr.substr(0, hyphenPos); //extract

                // Convert the numeric part to an integer
                this->year = stoi(numStr);
            } else {
                // If no digit is found, set the year to 0 or any default value
                this->year = 0;
            }
        }
        void setRated(string rated)
            { this->rated = rated; }
        void setReleaseDate(string releaseDate)
            { this->releaseDate = releaseDate; }
        void setLanguage(string language)
            { this->language = language; }
        void setCountry(string country)
            { this->country = country; }
        void setPlot(string plot)
            { this->plot = plot; }
        void setAwards(string awards)
            { this->awards = awards; }
        void setMetaScore(string metascore)
            { this->metascore = metascore; }
        void setBoxOffice(string boxoffice)
            { this->boxoffice = boxoffice; }
        void setDVD(string DVD)
            { this->DVD = DVD; }
        void setPoster(string poster)
            { this->poster = poster; }
        void setRuntime(string runtimeStr) {
            size_t pos = runtimeStr.find_first_of("0123456789");
            if (pos != string::npos) {
                string numStr = runtimeStr.substr(pos);
                this->runtime = stoi(numStr);
            } else
                this->runtime = 0;
        }

        void setGenres(string genresStr){
            genres.clear();
            istringstream ss(genresStr);
            string genre;
            while (getline(ss, genre, ',')) {
                size_t start = genre.find_first_not_of(" \t\n");
                size_t end = genre.find_last_not_of(" \t\n");
                if (start != std::string::npos && end != std::string::npos)
                    genres.push_back(genre.substr(start, end - start + 1));
            }
        }
        void setDirectors(string directorStr){
            directors.clear();
            istringstream ss(directorStr);
            string director;
            while (getline(ss, director, ',')) {
                size_t start = director.find_first_not_of(" \t\n");
                size_t end = director.find_last_not_of(" \t\n");
                if (start != std::string::npos && end != std::string::npos)
                    directors.push_back(director.substr(start, end - start + 1));
            }
        }
        void setWriters(string writerStr){
            writers.clear();
            istringstream ss(writerStr);
            string writer;
            while (getline(ss, writer, ',')) {
                size_t start = writer.find_first_not_of(" \t\n");
                size_t end = writer.find_last_not_of(" \t\n");
                if (start != std::string::npos && end != std::string::npos)
                    writers.push_back(writer.substr(start, end - start + 1));
            }
        }
        void setActors(string actorStr){
            actors.clear();
            istringstream ss(actorStr);
            string actor;
            while (getline(ss, actor, ',')) {
                size_t start = actor.find_first_not_of(" \t\n");
                size_t end = actor.find_last_not_of(" \t\n");
                if (start != std::string::npos && end != std::string::npos)
                    actors.push_back(actor.substr(start, end - start + 1));
            }
        }

        void toString() const {
            std::cout << "Title: " << title
                << "\nYear: " << year
                << "\nRated: " << rated
                << "\nRelease Date: " << releaseDate
                << "\nLanguage: " << language
                << "\nRuntime: " << runtime << " mins"
                << "\nGenres: ";
            
            for (size_t i = 0; i < genres.size(); ++i) {
                std::cout << genres[i];
                if (i < genres.size() - 1)
                    std::cout << ", ";
            }

            std::cout << "\nCountry: " << country
                << "\nDirectors: ";
            
            for (size_t i = 0; i < directors.size(); ++i) {
                std::cout << directors[i];
                if (i < directors.size() - 1)
                    std::cout << ", ";
            }

            std::cout << "\nWriters: ";
            
            for (size_t i = 0; i < writers.size(); ++i) {
                std::cout << writers[i];
                if (i < writers.size() - 1)
                    std::cout << ", ";
            }

            std::cout << "\nActors: ";
            
            for (size_t i = 0; i < actors.size(); ++i) {
                std::cout << actors[i];
                if (i < actors.size() - 1)
                    std::cout << ", ";
            }

            std::cout << "\nPlot: " << plot
                << "\nAwards: " << awards
                << "\nMetascore: " << metascore
                << "\nBox Office: " << boxoffice
                << "\nDVD: " << DVD
                << "\nPoster: " << poster
                << "\n";
        }
};