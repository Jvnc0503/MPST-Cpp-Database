#include <iostream>
#include "Movie.h"
#include "MovieDatabase.h"
#include "UserManager.h"

using std::cout, std::cin, std::max;

// Muestra información detallada de una película
void displayMovieDetails(const Movie &movie) {
	cout << "Title: " << movie.getTitle() << "\nSynopsis: " << movie.getPlot() << "\nTags: ";
	for (const auto &tag: movie.getTags()) {
		cout << tag << ", ";
	}
	cout << '\n';
}

// Maneja la interacción del usuario para seleccionar una película y realizar acciones sobre ella
void handleMovieSelection(const Movie &movie) {
	UserManager &userManager = UserManager::getInstance(); // Instancia singleton de UserManager
	int choice = 0;
	while (choice != 3) {
		cout << "Selected movie: \n";
		displayMovieDetails(movie);
		cout << "\nOptions:\n1. Add to likes\n2. Add to watch later\n3. Back\n";
		cin >> choice;
		if (choice == 1) {
			userManager.addToLikes(movie);
		} else if (choice == 2) {
			userManager.addToWatchLater(movie);
		} else if (choice != 3) {
			cout << "Invalid choice\n";
		}
	}
}

// Muestra una lista de películas y maneja la paginación y selección
void displayMovies(const vector<Movie> &movies) {
	auto iter = movies.begin();
	while (iter != movies.end()) {
		auto start = iter;
		int i = 1;
		while (i <= 5 && iter != movies.end()) { // Muestra hasta 5 películas a la vez
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

			if (choice == 1) {
				cout << "What movie would you like to select?\n";
				int select;
				cin >> select;
				if (select >= 1 && select < i) {
					handleMovieSelection(*(start + select - 1));
				} else {
					cout << "Invalid choice\n";
				}
			} else if (choice == 2) {
				iter = max(movies.begin(), iter - i - 6); // Navega a la página anterior
				break;
			} else if (choice == 3) {
				iter = movies.end(); // Sale del bucle
				cout << "Exiting\n";
				break;
			} else if (choice == 4) {
				break; // Procede a la siguiente página
			} else {
				cout << "Invalid choice\n";
			}
		}
	}
}

int main() {
	MovieDatabase &database = MovieDatabase::getInstance(); // Instancia singleton de MovieDatabase
	database.loadCSV("mpst_full_data_corrected.csv"); // Carga datos de películas desde CSV
	const UserManager &userManager = UserManager::getInstance(); // Instancia singleton de UserManager

	while (true) {
		cout
				<< "\nMenu:\n1. Search by text\n2. Search by tag\n3. Show likes\n4. Show Watch Later\n5. Show recomendations\n6. Exit\n\nEnter your choice: ";
		int choice;
		cin >> choice;
		cout << '\n';
		switch (choice) {
			case 1: {
				cout << "Enter text to search: ";
				string text;
				cin.ignore(); // Limpia el carácter de nueva línea del búfer de entrada
				getline(cin, text); // Lee la línea completa de texto
				cout << "\nResults for: " << text << '\n';
				displayMovies(database.searchByText(text)); // Muestra películas que coinciden con el texto de búsqueda
				break;
			}
			case 2: {
				cout << "Enter tag: ";
				string tag;
				cin.ignore(); // Limpia el carácter de nueva línea del búfer de entrada
				getline(cin, tag); // Lee la línea completa de la etiqueta
				cout << "\nResults for: " << tag << '\n';
				displayMovies(database.searchByTag(tag)); // Muestra películas que coinciden con la etiqueta
				break;
			}
			case 3: {
				cout << "Likes:\n";
				displayMovies(database.searchByIds(userManager.getLikes())); // Muestra películas gustadas
				break;
			}
			case 4: {
				cout << "Watch Later:\n";
				displayMovies(database.searchByIds(userManager.getWatchLater())); // Muestra la lista de ver más tarde
				break;
			}
			case 5: {
				if (userManager.getLikes().empty()) {
					cout << "Please add some movies to likes first\n";
					break;
				}
				cout << "Recommendations:\n";
				displayMovies(database.getRecommendations(
						userManager.getTagPreferences())); // Muestra películas recomendadas basadas en las preferencias del usuario
				break;
			}
			case 6:
				return 0;
			default:
				cout << "Invalid choice\n";
		}
	}
}
