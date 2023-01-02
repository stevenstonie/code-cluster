package classes;

import classes.auxiliaryclasses.MenusFuncs;
import classes.auxiliaryclasses.PrintMenus;
// import com.stevensproject.App;
// import classes.InsertIntoTables;
// import classes.Inutils;

import classes.auxiliaryclasses.InsertIntoTables;
import classes.auxiliaryclasses.Inutils;

import java.sql.Connection;
// import java.sql.PreparedStatement;
// import java.sql.ResultSet;
// import java.util.Collections;
import java.sql.SQLException;
import java.util.ArrayList;

public class Menus extends MenusFuncs {

	public static void userMenu(Connection connection, int user_id) throws SQLException {
		boolean exit = false;
		short option;

		PrintMenus.printUserMenuMenu();
		do {
			System.out.print(">");
			option = Inutils.getSmallIntInputFromUser();

			switch (option) {
				case 0: {
					PrintMenus.printUserMenuMenu();
					break;
				}

				case 1: {
					int movie_id = getMovieIdFromGivenName(connection);

					if (movie_id != -1) {
						System.out.println(searchMovieCredentialsById(connection, movie_id) + "\n");

						// prompt user for like
						promptUserForLike(connection, user_id, movie_id);

						// prompt user for dislike
						promptUserForDislike(connection, user_id, movie_id);
					} else {
						System.out.println("the movie could not be found..\n");
					}
					break;
				}

				case 2: {
					PrintMenus.printUserMenuMenu3();
					short subOption = Inutils.getSmallIntInputFromUser();
					if (subOption == 1 || subOption == 2) {
						ArrayList<Genres> genres = insertFromDBinGenreArray(connection, user_id);

						if (subOption == 1) {
							sortMoviesByLikes(genres);
						} else {
							sortMoviesByReleaseDate(genres);
						}
						printFeed(genres);
					} else {
						System.out.println("unfortunately that is not an available option..");
					}
					break;
				}

				case 3: {
					printUserLikedMoviesList(connection, user_id);
					break;
				}

				default: {
					exit = true;
					break;
				}
			}
		} while (exit == false);

		System.out.println("logging out..");
	}

	public static void adminMenu(Connection connection) {
		boolean exit = false;
		short option;

		PrintMenus.printAdminMenuMenu();
		do {
			System.out.print(">");
			option = Inutils.getSmallIntInputFromUser();
			switch (option) {
				case 0: {
					PrintMenus.printAdminMenuMenu();
					break;
				}

				case 1: {
					PrintMenus.printAdminMenuMenu2();
					short subOption = Inutils.getSmallIntInputFromUser();
					if (subOption == 1) {
						InsertIntoTables.insertIntoTableMoviesByFile(connection);
					} else if (subOption == 2) {
						InsertIntoTables.insertIntoTableMoviesByConsole(connection);
					} else {
						System.out.println("unfortunately that is not an available option..");
					}

					break;
				}

				case 2: {
					// function to delete movie from the database
					break;
				}

				default: {
					exit = true;
					break;
				}
			}

		} while (exit == false);

		System.out.println("logging out..");
	}
}

// TODO: genres that are not liked shouldnt print movies as the genres would be randomized but the movies not. when 
// printing the feed the movies are grouped by randomized genres, when they shouldnt be. or so i think, but it might make the code messier so idk