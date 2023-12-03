#include <iostream>
#include "httplib.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace httplib;
using namespace std;

void handlePreferences(const Request& req, Response& res, Server& server) {
    // Parse JSON data from the request body
    string json_data = req.body;

    try {
        // Parse JSON data
        auto preferences = json::parse(json_data);
        // Open a file to store user preferences
        ofstream userPreferencesFile("userPreferences.txt");
        if (userPreferencesFile.is_open()) {
            // Write received preferences to the file
            for (auto& entry : preferences.items()) 
                userPreferencesFile << entry.key() << ": " << entry.value() << "\n";
            // Close the file
            userPreferencesFile.close();
            // Print a message to the console
            cout << "Preferences stored in userPreferences.txt\n";
            // Send a response
            res.set_content("Preferences received and stored successfully", "text/plain");
            server.stop();
        } else {
            cerr << "Error opening user preferences file." << endl;
            res.set_content("Error storing preferences", "text/plain");
        }
    } catch (const json::parse_error& e) {
        cerr << "Error parsing JSON: " << e.what() << endl;
        res.set_content("Error parsing JSON", "text/plain");
    }
}


int main() {
    Server server;
    // Handle POST requests to the /preferences endpoint
    server.Post("/preferences", [&server](const Request& req, Response& res) {
        handlePreferences(req, res, server);
    });
    // Start the server on port 8080
    server.listen("localhost", 3000);
    return 0;
}
