#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct movieNode{
    string movie;
    int rank;
    int year;
    string rating;
    vector<string> genres;
    string country;
    vector<string> directors;
    vector<string> writers;
    vector<string> actors;
    string plot;
    string awards;
    string metascore;
    string boxOffice;
    string DVD;
    string poster;

    public:
        //constructors
        movieNode(): movie(""), rank(0), year(0), rating(""), country(""), plot(""), awards(""), metascore(""), boxOffice(""), DVD(""), poster(""){}
        movieNode(string movie, int rank, int year, string rating, vector<string> genres, string country, vector<string> directors, vector<string> writers, vector<string> actors, string plot, string awards, string metascore, string boxOffice, string DVD, string poster){
            this->movie = movie;
            this->rank = rank;
            this->year = year;
            this->rating = rating;
            this->genres = genres;
            this->country = country;
            this->directors = directors;
            this->writers = writers;
            this->actors = actors;
            this->plot = plot;
            this->awards = awards;
            this->metascore = metascore;
            this->boxOffice = boxOffice;
            this->DVD = DVD;
            this->poster = poster;
        }

         // Accessors
        string getMovie() const { return movie; }
        int getRank() const { return rank; }
        int getYear() const { return year; }
        string getRating() const { return rating; }
        vector<string> getGenres() const { return genres; }
        string getCountry() const { return country; }
        vector<string> getDirectors() const { return directors; }
        vector<string> getWriters() const { return writers; }
        vector<string> getActors() const { return actors; }
        string getPlot() const { return plot; }
        string getAwards() const { return awards; }
        string getMetascore() const { return metascore; }
        string getBoxOffice() const { return boxOffice; }
        string getDVD() const { return DVD; }
        string getPoster() const { return poster; }

        // Mutators
        void setMovie(string movie) { this->movie = movie; }
        void setRank(int rank) { this->rank = rank; }
        void setYear(int year) { this->year = year; }
        void setRating(string rating) { this->rating = rating; }
        void setGenres(vector<string> genres) { this->genres = genres; }
        void setCountry(string country) { this->country = country; }
        void setDirectors(vector<string> directors) { this->directors = directors; }
        void setWriters(vector<string> writers) { this->writers = writers; }
        void setActors(vector<string> actors) { this->actors = actors; }
        void setPlot(string plot) { this->plot = plot; }
        void setAwards(string awards) { this->awards = awards; }
        void setMetascore(string metascore) { this->metascore = metascore; }
        void setBoxOffice(string boxOffice) { this->boxOffice = boxOffice; }
        void setDVD(string DVD) { this->DVD = DVD; }
        void setPoster(string poster) { this->poster = poster; }
};

class priorityQueue{
    private:
        /*
        left child at position: 2p + 1
        right child at position: 2p + 2
        parent at position: floor(p - 1 / 2)
        */
        vector<movieNode> items;
        
    public:
        //will be implementing max heap, so first element is the highest priority one
        priorityQueue(){}
        bool isEmpty();
        int getSize();
        movieNode front();
        void insert(const movieNode& newMovie);
        void heapifyUp(int index);
        void heapifyDown(int index);
        movieNode deleteMax();
        void print();
};

bool priorityQueue::isEmpty()
   {return items.empty(); }

int priorityQueue::getSize()
   {return items.size();}


movieNode priorityQueue::front()
    {return items[0];}

void priorityQueue::insert(const movieNode& newMovie) {
    items.push_back(newMovie);
    heapifyUp(getSize() - 1);
}

void priorityQueue::heapifyUp(int index){
    // Continuously compare the inserted node with the parent node and move it up if it is of higher rank
    while (index > 0) {
        int parentIndex = (index - 1) / 2;

        // If the rank of the child is greater than the parent, swap their positions
        if (items[index].getRank() > items[parentIndex].getRank()) {
            swap(items[index], items[parentIndex]);
            index = parentIndex; // Update index as well
        } else
            break; // Break the loop if the heap property is satisfied
    }
}

movieNode priorityQueue::deleteMax(){
    //deleting the first element and returning it
    movieNode temp = items[0];
    items.erase(items.begin());
    heapifyDown(0);
    return temp;
}

void priorityQueue::heapifyDown(int index){
    int size = getSize();
    int maxIndex = index;
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;

    //check if left child exists and had higher rank than the current rank
    if(leftChild < size && items[leftChild].getRank() > items[maxIndex].getRank())
        maxIndex = leftChild;

    //check if right child exists and had higher rank than the current rank
    if(rightChild < size && items[rightChild].getRank() > items[maxIndex].getRank())
        maxIndex = rightChild;

    //if max index is different from current, swap and continue
    if(maxIndex != index){
        swap(items[index], items[maxIndex]);
        heapifyDown(maxIndex);
    }
}

void priorityQueue::print() {
    for (const auto& movie : items) {
        cout << "Movie: " << movie.getMovie() << endl;
        cout << "Rank: " << movie.getRank() << endl;
        cout << "Year: " << movie.getYear() << endl;
        cout << "Rating: " << movie.getRating() << endl;
        cout << "Genres: ";
        for (const auto& genre : movie.getGenres()) 
            cout << genre << ", ";
        cout << endl;
        cout << "Country: " << movie.getCountry() << endl;
        cout << "Directors: ";
        for (const auto& director : movie.getDirectors())
            cout << director << ", ";
        cout << endl;
        cout << "Writers: ";
        for (const auto& writer : movie.getWriters()) 
            cout << writer << ", ";
        cout << endl;
        cout << "Actors: ";
        for (const auto& actor : movie.getActors())
            cout << actor << ", ";
        cout << endl;
        cout << "Plot: " << movie.getPlot() << endl;
        cout << "Awards: " << movie.getAwards() << endl;
        cout << "Metascore: " << movie.getMetascore() << endl;
        cout << "Box Office: " << movie.getBoxOffice() << endl;
        cout << "DVD: " << movie.getDVD() << endl;
        cout << "Poster: " << movie.getPoster() << endl;
        cout << "------------------------" << endl;
    }
}

