#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
#include "json.hpp"

using json = nlohmann::json;

void clearScreen()
{
#ifdef _WIN32
    if (std::system("cls") != 0) {
        // fallback in case Wine doesn't handle cls
        std::cout << "\033[2J\033[1;1H";
    }
#else
    std::cout << "\033[2J\033[1;1H";
#endif
}

void QandA(json& database, const std::string& filename)
{
    std::string question;
    // Prompt user for question
    std::cout << "User: ";
    std::getline(std::cin, question);

    // Special command checking
    if (question == "ok" || question == "Ok") return;
    if (question == "quit" || question == "exit") std::exit(0);
    if (question == "clear") { clearScreen(); return; }
    if (question == "list db") { std::cout << database.dump(2) << std::endl; return; }

    // The painful
    if (question == "reset db") {
    database = { {"hello", "hi"} };
    std::ofstream outFile(filename);
    outFile << database.dump(4); // save the reset database
    std::cout << "Bot: Database reset!\n";
    return;
}


    // Search database for question
    if (database.contains(question))
    {
        std::cout << "Bot: " << database[question].get<std::string>() << std::endl;
    } 
    else 
    {
        std::cout << "Bot: Answer not found, teach me:\n";
        std::string answer;
        std::cout << "Answer: ";
        std::getline(std::cin, answer);

        if (answer == "skip") return;

        // Save into database
        database[question] = answer;

        // Write back to file
        std::ofstream outFile(filename);
        outFile << database.dump(4); // indent for readability
        std::cout << "Saved new response!\n";
    }
}

int main()
{
    // Variables
    std::string filename;
    json database;

    // Database selection prompt
    std::cout << "Enter database filename: ";
    std::getline(std::cin, filename);

    // Automatically add .json if not present
    if (filename.size() < 5 || filename.substr(filename.size() - 5) != ".json") {
        filename += ".json";
    }

    std::ifstream inFile(filename);
    if (inFile)
    {
        inFile >> database;
        std::cout << "Database parsed successfully!\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    else
    {
        std::cout << "No existing database found. Starting new one.\n";
    }

    clearScreen();
    std::cout << "Hello world!\n";
    while (true)
    {
        QandA(database, filename);
    }

    return 0;
}
