package classes;

import com.stevensproject.App;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

class PrintMenus {
	static void printUserMenuMenu2() {
		System.out.println("do you want to like the selected movie?");
	}

	static void printUserMenuMenu3() {
		System.out.println("how would you like to sort the feed?");
		System.out.println("1: by release date");
		System.out.println("2: by the numbers of likes");
	}

	static void printUserMenuMenu() {
		System.out.println("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		System.out.println("press 0 to bring back this menu");
		System.out.println("press 1 to search for a movie by name");
		System.out.println("press 2 to view your feed");
		System.out.println("press anything else to logout");
		System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	}

	static void printAdminMenuMenu2() {
		System.out.println("how would you like to add the movies?");
		System.out.println("1: by a specified file");
		System.out.println("2: by console");
	}

	static void printAdminMenuMenu() {
		System.out.println("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		System.out.println("press 0 to bring back this menu");
		System.out.println("press 1 to add movies in the database");
		System.out.println("press 2 to delete a movie from the database");
		System.out.println("press 3 to update a movie from the database");
		System.out.println("press anything else to logout");
		System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	}
}

public class Menus {
	class Funcs {
		private static boolean checkIfUserLikedTheMovieAlready(Connection connection, int user_id, int movie_id)
				throws SQLException {
			String querySearchIfUserLikedAMovie = "select count(*) from users_movies where user_id = " + user_id
					+ " and movie_id = " + movie_id + ";";
			PreparedStatement stmt = connection.prepareStatement(querySearchIfUserLikedAMovie);
			ResultSet queryOutput = stmt.executeQuery();
			queryOutput.next();

			if (queryOutput.getInt(1) == 1) {
				return true;
			} else {
				return false;
			}
		}

		private static void likeMovie(Connection connection, int user_id, int movie_id) throws SQLException {
			if (checkIfUserLikedTheMovieAlready(connection, user_id, movie_id) == true) {
				System.out.println("you already liked the movie before..");
				return;
			}

			String queryAddUserAndMovieToUsersMovies = "insert into users_movies(user_id, movie_id) values(" + user_id
					+ ", " + movie_id + ");";
			PreparedStatement stmt = connection.prepareStatement(queryAddUserAndMovieToUsersMovies);
			stmt.executeUpdate();
			System.out.println("you have added the movie to your like list");
		}

		private static int searchForMovieByName(Connection connection) throws SQLException {
			System.out.println("search for the movie: ");
			String movie_name = App.console.nextLine();
			String queryCheckIfMovieExists = "select count(*) from movies where name = '" + movie_name + "';";
			PreparedStatement stmt = connection.prepareStatement(queryCheckIfMovieExists);
			ResultSet queryOutput = stmt.executeQuery();
			queryOutput.next();
			if (queryOutput.getInt(1) == 0)
				return -1;
			// cant do: if (queryOutput.getString(1).equals(null))
			// it gives me the exception: ResultSet not positioned properly, perhaps you need to call next.
			// TODO ^^^
			// TODO: do search by regex
			String querySearchIdOfMovie = "select id from movies where name = '" + movie_name + "';";
			stmt = connection.prepareStatement(querySearchIdOfMovie);
			queryOutput = stmt.executeQuery();
			queryOutput.next();

			return queryOutput.getInt(1);
		}

		private static String searchForMovieGenreById(Connection connection, String movie_id) throws SQLException {
			String querySearchForMovieNameById = "select genre from movies where id = " + movie_id + " limit 1;";
			PreparedStatement stmt = connection.prepareStatement(querySearchForMovieNameById);
			ResultSet queryOutput = stmt.executeQuery();
			queryOutput.next();
			return queryOutput.getString(1);
		}

		private static String searchMovieCredentialsById(Connection connection, int movie_id) throws SQLException {
			String querySearchMovieCredentials = "select * from movies where id = " + movie_id + ";";
			PreparedStatement stmt = connection.prepareStatement(querySearchMovieCredentials);
			ResultSet queryOutput = stmt.executeQuery();
			queryOutput.next();

			return queryOutput.getString(2) + " | " + queryOutput.getString(3) + " | "
					+ queryOutput.getString(4)
					+ " | " + queryOutput.getString(5);
		}

		private static byte getIntFromUser() {

			String s_userInput = App.console.nextLine();

			for (int i = 0; i < s_userInput.length(); i++)
				if (!Character.isDigit(s_userInput.charAt(i)))
					return -1;

			int i_userInput = Integer.parseInt(s_userInput);
			if (i_userInput > Byte.MAX_VALUE)
				return -1;

			return (byte) i_userInput;
		}

		private static ArrayList<ArrayList<String>> insertFromDBin2dArray(Connection connection) throws SQLException {
			ArrayList<ArrayList<String>> allMovies = new ArrayList<ArrayList<String>>();
			PreparedStatement stmt = null;
			ResultSet queryOutput = null;
			String querySelectAllMoviesFromDB = "select name, genre, release_date, likes from movies;";

			stmt = connection.prepareStatement(querySelectAllMoviesFromDB);
			queryOutput = stmt.executeQuery();
			queryOutput.next();
			try {
				String[] movie = new String[4];
				while (true != false) {
					movie[0] = queryOutput.getString(1);
					movie[1] = queryOutput.getString(2);
					movie[2] = queryOutput.getString(3);
					movie[3] = queryOutput.getString(4);

					boolean exists = false;
					for (int i = 0; i < allMovies.size(); i++) {
						if (allMovies.get(i).get(0).equals(movie[1])) {
							allMovies.get(i).add(movie[0] + " | " + movie[1] + " | " + movie[2] + " | " + movie[3]);
							exists = true;
							break;
						}
					}
					if (!exists) {
						allMovies.add(new ArrayList<String>());
						allMovies.get(allMovies.size() - 1).add(movie[1]);
						allMovies.get(allMovies.size() - 1).add("0");
						allMovies.get(allMovies.size() - 1)
								.add(movie[0] + " | " + movie[1] + " | " + movie[2] + " | " + movie[3]);
					}

					queryOutput.next();
				}
			} catch (org.postgresql.util.PSQLException e) {
				// no more movies to read
			}

			return allMovies;
		}

		private static void addCurrentUserLikes(Connection connection, int user_id,
				ArrayList<ArrayList<String>> allMovies) throws SQLException {
			String queryGetCurrentUserLikedMoviesId = "select movie_id from users_movies where user_id = " + user_id
					+ ";";
			PreparedStatement stmt = connection.prepareStatement(queryGetCurrentUserLikedMoviesId);
			ResultSet queryOutput = stmt.executeQuery();
			queryOutput.next();
			Map<String, Integer> genresAndLikes = new HashMap<String, Integer>();
			try {
				while (true != false) {
					String currentMovieGenre = searchForMovieGenreById(connection, queryOutput.getString(1));
					if (genresAndLikes.containsKey(currentMovieGenre)) {
						genresAndLikes.put(currentMovieGenre, genresAndLikes.get(currentMovieGenre) + 1);
					} else {
						genresAndLikes.put(currentMovieGenre, 1);
					}
					queryOutput.next();
				}

			} catch (org.postgresql.util.PSQLException e) {
				// no more movies to read
			}

			for (int i = 0; i < allMovies.size(); i++) {
				if (genresAndLikes.containsKey(allMovies.get(i).get(0))) {
					allMovies.get(i).set(1, Integer.toString(genresAndLikes.get(allMovies.get(i).get(0))));
				}
			}
		}
	}

	public static void userMenu(Connection connection, int user_id) throws SQLException {
		boolean exit = false;
		byte option;

		PrintMenus.printUserMenuMenu();
		do {
			System.out.print(">");
			option = Funcs.getIntFromUser();

			switch (option) {
				case 0: {
					PrintMenus.printUserMenuMenu();
					break;
				}

				case 1: {
					int movie_id = Funcs.searchForMovieByName(connection);

					if (movie_id != -1) {
						System.out.println(Funcs.searchMovieCredentialsById(connection, movie_id) + "\n");
						PrintMenus.printUserMenuMenu2();
						String subOption = App.console.nextLine();
						if (subOption.equals("y") || subOption.equals("yes") || subOption.equals("true")
								|| subOption.equals("ye") || subOption.equals("1") || subOption.equals("ja")) {
							Funcs.likeMovie(connection, user_id, movie_id);
						}
					} else {
						System.out.println("the movie could not be found..\n");
					}
					break;
				}

				case 2: {
					PrintMenus.printUserMenuMenu3();
					int subOption = Funcs.getIntFromUser();
					if (subOption == 1 || subOption == 2) {
						ArrayList<ArrayList<String>> allMovies = Funcs.insertFromDBin2dArray(connection);
						Funcs.addCurrentUserLikes(connection, user_id, allMovies);
						// Funcs.prioritizeLikedMovies();
						// Funcs.sortMoviesByReleaseDate();
						// Funcs.sortMoviesByLikes();

					} else {
						System.out.println("unfortunately that is not an available option..");
					}
					break;
				}

				default: {
					exit = true;
					break;
				}
			}
		} while (exit == false);

		// // search by name (regex if possible)
		// // view feed (sort by release date or likes)
		// // like system (??)
		// // logout
		// when liking a movie insert into the users_movies the id of the user and the id of the movie
		// the feed priority is by how many likes a genre has so count genres and sort. then sort the individual movies in each genre by whatever the user wants

		System.out.println("logging out..");
	}

	public static void adminMenu(Connection connection) {
		boolean exit = false;
		byte option;

		PrintMenus.printAdminMenuMenu();
		do {
			System.out.print(">");
			option = Funcs.getIntFromUser();

		} while (exit == false);
		// if role is 'admin' => menu for admin
		// // add movies in the database by file or console
		// // maybe also delete from / update the database?
		// // logout

		System.out.println("logging out..");
	}
}
