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
		static class Movie {
			private String name;
			private String genre;
			private String release_date;
			private int likes;

			public Movie(String name, String genre, String release_date, int likes) {
				this.name = name;
				this.genre = genre;
				this.release_date = release_date;
				this.likes = likes;
			}

			public String getName() {
				return name;
			}

			public String getGenre() {
				return genre;
			}

			public String getReleaseDate() {
				return release_date;
			}

			public int getLikes() {
				return likes;
			}
		}

		static class Genre {
			private String name;
			private int likesOfUser;
			ArrayList<Movie> movies = new ArrayList<>();

			public Genre(String name, int likesOfUser) {
				this.name = name;
				this.likesOfUser = likesOfUser;
			}

			public String getName() {
				return name;
			}

			public Integer getLikesOfUser() {
				return likesOfUser;
			}

			public void addMovie(Movie movie) {
				movies.add(movie);
			}

			public ArrayList<Movie> getMovies() {
				return movies;
			}
		}

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

		private static ArrayList<Genre> insertFromDBinGenreArray(Connection connection, int user_id)
				throws SQLException {
			String queryGetAllGenresLikedByUser = "select genre, count(*) from movies join users_movies on movies.id = users_movies.movie_id where user_id = "
					+ user_id + " group by genre;";
			PreparedStatement stmt = connection.prepareStatement(queryGetAllGenresLikedByUser);
			ResultSet queryOutput = stmt.executeQuery();
			ArrayList<Genre> genres = new ArrayList<>();
			queryOutput.next();

			try {
				while (true != false) {
					genres.add(new Genre(queryOutput.getString(1), queryOutput.getInt(2)));
					queryOutput.next();
				}
			} catch (org.postgresql.util.PSQLException e) {
				// no more movies liked by the user to read
			}
			String queryGetAllGenres = "select distinct genre from movies;";
			stmt = connection.prepareStatement(queryGetAllGenres);
			queryOutput = stmt.executeQuery();
			queryOutput.next();
			try {
				while (true != false) {
					// use contains to check if the genre already exists in the array
					boolean genreExists = false;
					for (Genre genre : genres) {
						if (genre.getName().equals(queryOutput.getString(1))) {
							genreExists = true;
							break;
						}
					}
					if (genreExists == false) {
						genres.add(new Genre(queryOutput.getString(1), 0));
					}
					queryOutput.next();
				}
			} catch (org.postgresql.util.PSQLException e) {
				// no morer movies to read
				return genres;
			}
		}

		private static void addMoviesFromDbToGenres(Connection connection, ArrayList<Genre> genres)
				throws SQLException {
			for (Genre genre : genres) {
				String queryGetAllMoviesFromGenre = "select * from movies where genre = '" + genre.getName() + "';";
				PreparedStatement stmt = connection.prepareStatement(queryGetAllMoviesFromGenre);
				ResultSet queryOutput = stmt.executeQuery();
				queryOutput.next();

				try {
					while (true != false) {
						genre.addMovie(new Movie(queryOutput.getString(2), queryOutput.getString(3),
								queryOutput.getString(4), Integer.parseInt(queryOutput.getString(5))));
						queryOutput.next();
					}
				} catch (org.postgresql.util.PSQLException e) {
					// no more movies to read
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
						ArrayList<Funcs.Genre> genres = Funcs.insertFromDBinGenreArray(connection, user_id);

						Funcs.addMoviesFromDbToGenres(connection, genres);

						for (Funcs.Genre genre : genres) {
							for (Funcs.Movie movie : genre.getMovies()) {
								System.out.println(
										movie.getName() + " | " + movie.getGenre() + " | " + movie.getReleaseDate()
												+ " | " + movie.getLikes());
							}
						}

						// (done) take the movies from the db and put them in an array of genres
						// (done) each genre has an array of movies
						// (done) when adding a new genre always check the users_movies table to add how many likes has the genre from the user
						// (done) sort the array of genres based on those likes
						// then based on the subOption sort the movies array of each genre based on release date or likes			

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
