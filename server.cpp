#include "path/to/cpp-httplib/httplib.h"


using namespace std;
using namespace httplib;

// Simple in-memory user database for demonstration purposes
struct User {
    string username;
    string password;
};

vector<User> users;

int main() {
    Server svr;

    // Endpoint for user registration
    svr.Post("/register", [](const Request& req, Response& res) {
        auto json = json::parse(req.body);
        string username = json["username"];
        string password = json["password"];

        // Check if the username is already taken
        for (const auto& user : users) {
            if (user.username == username) {
                res.status = 400;
                res.set_content("Username already taken", "text/plain");
                return;
            }
        }

        // Register the user
        users.push_back({username, password});
        res.set_content("User registered successfully", "text/plain");
    });

    // Endpoint for user login
    svr.Post("/login", [](const Request& req, Response& res) {
        auto json = json::parse(req.body);
        string username = json["username"];
        string password = json["password"];

        // Check if the username and password match
        for (const auto& user : users) {
            if (user.username == username && user.password == password) {
                res.set_content("Login successful", "text/plain");
                return;
            }
        }

        res.status = 401;
        res.set_content("Invalid username or password", "text/plain");
    });

    // Start the server on port 3000
    svr.listen("localhost", 3000);

    return 0;
}
