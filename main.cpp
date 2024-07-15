#include <iostream>
#include "Movie.h"
#include "MovieDatabase.h"
#include "UserManager.h"
using std::cout, std::cin;

void displayMovieDetails(const Movie& movie) {
    cout << "Title: " << movie.getTitle() << ", Synopsis: " << movie.getPlot() << ", Tags: ";
    for (const auto& tag: movie.getTags()) {
        cout << tag << ", ";
    }
    cout << '\n';
}

void handleMovieSelection(const Movie& movie) {
    UserManager *userManager = UserManager::getInstance();
    int choice = 0;
    while (choice != 3) {
        cout << "Selected movie: \n";
        displayMovieDetails(movie);
        cout << "1. Add to likes\n2. Add to watch later\n3. Back\n";
        cin >> choice;
        if (choice == 1) {
            userManager->addToLikes(movie);
        }
        else if (choice == 2) {
            userManager->addToWatchLater(movie);
        }
        else if (choice != 3) {
            cout << "Invalid choice\n";
        }
    }
}

void displayMovies(const vector<Movie>& movies) {
    auto iter = movies.begin();
    while (iter != movies.end()) {
        for (int i=1; i<=5 && iter != movies.end(); i++) {
            cout << i << ". " << iter->getTitle() << '\n';
            ++iter;
        }
        int choice = 0;
        while (choice < 2 & choice > 4) {
            cout << "\n1. Select a movie\n2. Previous\n3. Exit\n";
            if (iter != movies.end()) {
                cout << "4. Next\n";
            }
            cin >> choice;
            if (choice == 1) {
                cout << "What movie would you like to select?\n";
                cin >> choice;
                if (choice >= 1 && choice <=5) {
                    handleMovieSelection(*(iter - 5 + choice));
                }
                else {
                    cout << "Invalid choice\n";
                }
            }
            else if (choice == 2) {
                iter-=10;
            }
            else if (choice == 3) {
                iter = movies.end();
            }
            else if (choice != 4) {
                cout << "Invalid choice\n";
            }
        }
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}