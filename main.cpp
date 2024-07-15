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
            switch (choice) {
                case 1:
                    cout << "What movie would you like to select?\n";
                    int select;
                    cin >> select;
                    if (select >= 1 && select <= 5) {
                        handleMovieSelection(*(iter - 5 + select));
                    } else {
                        cout << "Invalid choice\n";
                    }
                    break;
                case 2:
                    iter -= 10;
                    break;
                case 3:
                    iter = movies.end();
                    cout << "Exiting\n";
                    break;
                case 4:
                    break;
                default:
                    cout << "Invalid choice\n";
                    break;
            }
        }
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}