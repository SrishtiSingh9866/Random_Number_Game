#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm> // For std::find
#include <map>
#include <string>

using namespace std;

class Game {
public:
    void displayMenu() {
        int choice;

        do {
            printBoxTop();
            cout << "║***************************************************║\n";
            cout << "║**  —ฅ/ᐠ. ̫ .ᐟ\\ฅ                    —ฅ/ᐠ. ̫ .ᐟ\\ฅ**  ║\n";
            cout << "║**  Welcome to the Random Number Game!       **║\n";
            cout << "║***************************************************║\n";
            printBoxBottom();

            printBoxTop();
            cout << "║-----------------------------------------------║\n";
            cout << "║ 1. Play            | 2. View LeaderBoard | 3. Exit ║\n";
            cout << "║-----------------------------------------------║\n";
            printBoxBottom();

            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    playGame();
                    break;
                case 2:
                    viewLeaderboard();
                    break;
                case 3:
                    printBoxTop();
                    cout << "║ Thanks for Playing. Goodbye                  ║\n";
                    printBoxBottom();
                    break;
                default:
                    printBoxTop();
                    cout << "║ Please enter a valid Choice                  ║\n";
                    printBoxBottom();
                    break;
            }
        } while (choice != 3);
    }

private:
    int remainingGuesses;
    int remainingHints;
    string playerName;
    map<int, string, std::greater<int>> easyLeaderboard;
    map<int, string, std::greater<int>> mediumLeaderboard;
    map<int, string, std::greater<int>> hardLeaderboard;

    void playGame() {
        int difficulty, maxGuesses, randomNumber, guess;
        vector<string> hintsGiven;

        printBoxTop();
        cout << "║ Enter your name:                             ║\n";
        printBoxBottom();
        cin.ignore();
        getline(cin, playerName);

        printBoxTop();
        cout << "║::::::::::::::::::::::::::::║\n";
        cout << "║::     1-100 Guess??       ::║\n";
        cout << "║::  ▼・ᴥ・▼   ▼・ᴥ・▼  ::║\n";
        cout << "║::::::::::::::::::::::::::::║\n";
        printBoxBottom();

        printBoxTop();
        cout << "║-----------------------------------------------║\n";
        cout << "║ Select Difficulty:                          ║\n";
        cout << "║-----------------------------------------------║\n";
        cout << "║ 1. Easy            | 2. Medium         | 3. Hard ║\n";
        cout << "║-----------------------------------------------║\n";
        printBoxBottom();

        cout << "Enter your choice of difficulty: ";
        cin >> difficulty;

        switch (difficulty) {
            case 1:
                maxGuesses = 7;
                remainingHints = 3;
                break;
            case 2:
                maxGuesses = 5;
                remainingHints = 2;
                break;
            case 3:
                maxGuesses = 3;
                remainingHints = 1;
                break;
            default:
                printBoxTop();
                cout << "║ Invalid difficulty. Defaulting to Easy.      ║\n";
                printBoxBottom();
                maxGuesses = 7;
                remainingHints = 3;
                break;
        }

        randomNumber = rand() % 100 + 1;
        remainingGuesses = maxGuesses;

        while (remainingGuesses > 0) {
            printBoxTop();
            cout << "║ You have " << remainingGuesses << " guesses left. ║\n";
            cout << "║-----------------------------------------------║\n";
            cout << "║ Enter your guess:                           ║\n";
            printBoxBottom();

            cin >> guess;

            // Provide feedback on guess
            printBoxTop();
            if (guess == randomNumber) {
                cout << "║ Congratulations! You guessed the number!     ║\n";
                cout << "║ You have won the game.                      ║\n";
                printBoxBottom();
                int score = maxGuesses - remainingGuesses + 1;
                updateLeaderboard(difficulty, score);
                return;
            } else {
                if (abs(guess - randomNumber) <= 15) {
                    if (guess < randomNumber) {
                        cout << "║ Too close! You have guessed a lower number. ║\n";
                    } else {
                        cout << "║ Too close! You have guessed a higher number. ║\n";
                    }
                } else {
                    if (guess < randomNumber) {
                        cout << "║ Too far! You have guessed a lower number.   ║\n";
                    } else {
                        cout << "║ Too far! You have guessed a higher number.   ║\n";
                    }
                }
                printBoxBottom();
            }

            // Provide a hint if there are any left
            if (remainingHints > 0) {
                provideHint(randomNumber, guess, hintsGiven);
            } else {
                printBoxTop();
                cout << "║ No more hints available.                    ║\n";
                printBoxBottom();
            }

            remainingGuesses--;

            if (remainingGuesses == 0) {
                printBoxTop();
                cout << "║ You have lost!  Sad cat says:                ║\n";
                cout << "║  /(^._.^)/~  \n";
                cout << "║    / /     \n";
                cout << "║  (__)      ║\n";
                printBoxBottom();
                return;
            }
        }
    }

    void provideHint(int randomNumber, int guess, vector<string>& hintsGiven) {
        bool numberIsEven = (randomNumber % 2 == 0);
        bool numberIsPrime = isPrime(randomNumber);
        bool numberIsSquare = (sqrt(randomNumber) == floor(sqrt(randomNumber)));

        if (remainingHints > 0) {
            printBoxTop();
            cout << "║ Do you want a hint? (yes/no):                ║\n";
            printBoxBottom();

            string response;
            cin >> response;

            if (response == "yes") {
                printBoxTop();
                if (numberIsEven && find(hintsGiven.begin(), hintsGiven.end(), "even") == hintsGiven.end()) {
                    cout << "║ The number is even.                        ║\n";
                    hintsGiven.push_back("even");
                } else if (numberIsEven) {
                    for (int i = 1; i <= 10; ++i) {
                        string hint = "even and divisible by " + to_string(i);
                        if (randomNumber % i == 0 && find(hintsGiven.begin(), hintsGiven.end(), hint) == hintsGiven.end()) {
                            cout << "║ The number is even and divisible by " << i << ".║\n";
                            hintsGiven.push_back(hint);
                            break;
                        }
                    }
                } else if (!numberIsEven && find(hintsGiven.begin(), hintsGiven.end(), "odd") == hintsGiven.end()) {
                    cout << "║ The number is odd.                         ║\n";
                    hintsGiven.push_back("odd");
                } else if (!numberIsEven) {
                    for (int i = 1; i <= 10; ++i) {
                        string hint = "odd and divisible by " + to_string(i);
                        if (randomNumber % i == 0 && find(hintsGiven.begin(), hintsGiven.end(), hint) == hintsGiven.end()) {
                            cout << "║ The number is odd and divisible by " << i << ".║\n";
                            hintsGiven.push_back(hint);
                            break;
                        }
                    }
                } else if (numberIsPrime && find(hintsGiven.begin(), hintsGiven.end(), "prime") == hintsGiven.end()) {
                    cout << "║ The number is prime.                       ║\n";
                    hintsGiven.push_back("prime");
                } else if (numberIsSquare && find(hintsGiven.begin(), hintsGiven.end(), "perfect square") == hintsGiven.end()) {
                    cout << "║ The number is a perfect square.            ║\n";
                    hintsGiven.push_back("perfect square");
                } else {
                    cout << "║ No more hints available.                   ║\n";
                }
                remainingHints--;
                printBoxBottom();
            }
        }
    }

    bool isPrime(int num) {
        if (num <= 1) return false;
        if (num <= 3) return true;
        if (num % 2 == 0 || num % 3 == 0) return false;
        for (int i = 5; i * i <= num; i += 6) {
            if (num % i == 0 || num % (i + 2) == 0)
                return false;
        }
        return true;
    }

    void updateLeaderboard(int difficulty, int score) {
        switch (difficulty) {
            case 1:
                easyLeaderboard[score] = playerName;
                break;
            case 2:
                mediumLeaderboard[score] = playerName;
                break;
            case 3:
                hardLeaderboard[score] = playerName;
                break;
            default:
                cout << "Invalid difficulty level for leaderboard update.\n";
                break;
        }
    }

    void viewLeaderboard() {
        int choice;
        printBoxTop();
        cout << "║-----------------------------------------------║\n";
        cout << "║ Select LeaderBoard to View:                   ║\n";
        cout << "║-----------------------------------------------║\n";
        cout << "║ 1. Easy            | 2. Medium         | 3. Hard ║\n";
        cout << "║-----------------------------------------------║\n";
        printBoxBottom();

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                printBoxTop();
                cout << "║------------- EASY LEADERBOARD ----------------║\n";
                printBoxBottom();
                printLeaderboard("Easy", easyLeaderboard);
                break;
            case 2:
                printBoxTop();
                cout << "║------------- MEDIUM LEADERBOARD --------------║\n";
                printBoxBottom();
                printLeaderboard("Medium", mediumLeaderboard);
                break;
            case 3:
                printBoxTop();
                cout << "║------------- HARD LEADERBOARD ----------------║\n";
                printBoxBottom();
                printLeaderboard("Hard", hardLeaderboard);
                break;
            default:
                printBoxTop();
                cout << "║ Invalid choice. Returning to menu.           ║\n";
                printBoxBottom();
                break;
        }
    }

    void printLeaderboard(const string& difficulty, const map<int, string, std::greater<int>>& leaderboard) {
        printBoxTop();
        cout << "║ " << difficulty << " Leaderboard:                ║\n";
        printBoxBottom();

        if (leaderboard.empty()) {
            printBoxTop();
            cout << "║ Nobody dared to play yet.                   ║\n";
            printBoxBottom();
        } else {
            for (const auto& entry : leaderboard) {
                printBoxTop();
                cout << "║ Score: " << entry.first << " | Player: " << entry.second << " ║\n";
                printBoxBottom();
            }
        }
    }

    void printBoxTop() {
        cout << "╔═════════════════════════════════════════════╗\n";
    }

    void printBoxBottom() {
        cout << "╚═════════════════════════════════════════════╝\n";
    }
};

int main() {
    srand(time(0)); // Seed for random number generation
    Game game;
    game.displayMenu();
    return 0;
}
