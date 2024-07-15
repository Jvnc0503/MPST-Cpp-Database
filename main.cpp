#include <iostream>
#include "Movie.h"
#include "MovieDatabase.h"
#include "UserManager.h"
using std::cout, std::cin, std::max;

void displayMovieDetails(const Movie& movie) {
    cout << "Title: " << movie.getTitle() << "\nSynopsis: " << movie.getPlot() << "\nTags: ";
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
        int i = 1;
        while (i<=5 && iter != movies.end()) {
            cout << i << ". " << iter->getTitle() << '\n';
            ++i;
            ++iter;
        }
        while (true) {
            cout << "\n1. Select a movie\n2. Previous\n3. Exit\n";
            if (iter != movies.end()) {
                cout << "4. Next\n";
            }
            int choice;
            cin >> choice;

            if(choice == 1) {
                cout << "What movie would you like to select?\n";
                int select;
                cin >> select;
                if (select >= 1 && select <= i) {
                    handleMovieSelection(*(iter - 6 + select));
                }
                else {
                    cout << "Invalid choice\n";
                }
            }
            else if (choice == 2) {
                iter = max(movies.begin(), iter - i - 6);
                break;
            }
            else if (choice == 3) {
                iter = movies.end();
                cout << "Exiting\n";
                break;
            }
            else if (choice == 4) {
                break;
            }
            else {
                cout << "Invalid choice\n";
            }
        }
    }
}

int main() {
    MovieDatabase& database = MovieDatabase::getInstance();

    database.loadCSV("mpst_full_data_corrected.csv");

    displayMovies(database.searchByText("love"));
    return 0;
}