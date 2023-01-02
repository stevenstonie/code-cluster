package classes.mainclasses;

import com.stevensproject.App;
// import classes.InsertIntoTables;
// import classes.Inutils;

import classes.secondaryclasses.InsertIntoTables;
import classes.secondaryclasses.Inutils;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Collections;

class PrintMenus {
	static void printIfUserWantsToLikeTheMovie() {
		System.out.println("do you want to like the selected movie?");
	}

	static void printIfUserWantsToDislikeTheMovie() {
		System.out.println("do you want to dislike the selected movie?");
	}

	static void printUserMenuMenu3() {
		System.out.println("how would you like to sort the feed?");
		System.out.println("1: by the numbers of likes");
		System.out.println("2: by release date");
	}

	static void printUserMenuMenu() {
		System.out.println("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		System.out.println("press 0 to bring back this menu");
		System.out.println("press 1 to search for a movie by name");
		System.out.println("press 2 to view your feed");
		System.out.println("press 3 to view your liked movies list");
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
		System.out.println("press anything else to logout");
		System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	}
}

public class Menus {
	static class Genres {
		static class Movies {
			private String name;
			private String genre;
			private String release_date;
			private int likes;

			public Movies(String name, String genre, String release_date, int likes) {
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

		private String name;
		private int likesOfUser;
		ArrayList<Movies> movies = new ArrayList<>();

		public Genres(String name, int likesOfUser) {
			this.name = name;
			this.likesOfUser = likesOfUser;
		}

		public void sortMoviesByReleaseDate() {
			movies.sort((Movies m1, Movies m2) -> m2.getReleaseDate().compareTo(m1.getReleaseDate()));
		}

		public void sortMoviesByLikes() {
			movies.sort((Movies m1, Movies m2) -> m2.getLikes() - m1.getLikes());
		}

		public String getName() {
			return name;
		}

		public Integer getLikesOfUser() {
			return likesOfUser;
		}

		public void addMovie(Movies movie) {
			movies.add(movie);
		}

		public ArrayList<Movies> getMovies() {
			return movies;
		}
	}

	class Funks {
		private static void likeMovie(Connection connection, int user_id, int movie_id) throws SQLException {
			if (checkIfUserLikedTheMovieAlready(connection, user_id, movie_id) == true) {
				System.out.println("you already liked the movie before..");
				return;
			}

			String queryAddUserAndMovieToUsersMovies = "insert into users_movies(user_id, movie_id) values("
					+ user_id
					+ ", " + movie_id + ");";
			PreparedStatement stmt = connection.prepareStatement(queryAddUserAndMovieToUsersMovies);
			stmt.executeUpdate();
			System.out.println("you have added the movie to your likes list");
		}

		private static void dislikeMovie(Connection connection, int user_id, int movie_id) throws SQLException {
			if (checkIfUserLikedTheMovieAlready(connection, user_id, movie_id) == false) {
				System.out.println("you dont have the specified movie in your likes list..");
				return;
			}

			String queryDeleteUserAndMovieFromUsersMovies = "delete from users_movies where user_id = " + user_id
					+ " and movie_id = " + movie_id + ";";
			PreparedStatement stmt = connection.prepareStatement(queryDeleteUserAndMovieFromUsersMovies);
			stmt.executeUpdate();
			System.out.println("you have deleted the movie from your likes list");
		}

		private static void sortGenresByLikes(ArrayList<Genres> genres) {
			genres.sort((Genres g1, Genres g2) -> g2.getLikesOfUser() - g1.getLikesOfUser());
		}

		private static void sortMoviesByLikes(ArrayList<Genres> genres) {
			for (Genres genre : genres) {
				if (genre.getLikesOfUser() > 0) // only those which have genres liked by the user
					genre.sortMoviesByLikes();
			}
		}

		private static void sortMoviesByReleaseDate(ArrayList<Genres> genres) {
			for (Genres genre : genres) {
				if (genre.getLikesOfUser() > 0) // only those which have genres liked by the user
					genre.sortMoviesByReleaseDate();
			}
		}

		private static void printFeed(ArrayList<Genres> genres) {
			for (Genres genre : genres) {
				for (Genres.Movies movie : genre.getMovies()) {
					System.out
							.println(movie.getName() + " | " + movie.getGenre() + " | " + movie.getReleaseDate() + " | "
									+ movie.getLikes());
				}
			}
		}

		private static void printUserLikedMoviesList(Connection connection, int user_id) throws SQLException {
			String queryGetMoviesLikedByUser = "select movies.name, movies.genre, movies.release_date, movies.likes from movies inner join "
					+ " users_movies on movies.id = users_movies.movie_id where user_id = " + user_id + ";";
			PreparedStatement stmt = connection.prepareStatement(queryGetMoviesLikedByUser);
			ResultSet queryOutput = stmt.executeQuery();
			queryOutput.next();

			try {
				while (true != false) {
					System.out.println(queryOutput.getString(1) + " | " + queryOutput.getString(2) + " | "
							+ queryOutput.getString(3) + " | " + queryOutput.getString(4));

					queryOutput.next();
				}
			} catch (org.postgresql.util.PSQLException e) {
				// no more liked movies to read
			}

			stmt.close();
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

		private static void promptUserForLike(Connection connection, int user_id, int movie_id) throws SQLException {
			PrintMenus.printIfUserWantsToLikeTheMovie();

			String subOption = App.console.nextLine();
			if (subOption.equals("y") || subOption.equals("yes") || subOption.equals("true")
					|| subOption.equals("ye") || subOption.equals("1") || subOption.equals("ja")) {
				likeMovie(connection, user_id, movie_id);
			}
		}

		private static void promptUserForDislike(Connection connection, int user_id, int movie_id) throws SQLException {
			PrintMenus.printIfUserWantsToDislikeTheMovie();

			String subOption = App.console.nextLine();
			if (subOption.equals("y") || subOption.equals("yes") || subOption.equals("true")
					|| subOption.equals("ye") || subOption.equals("1") || subOption.equals("ja")) {
				dislikeMovie(connection, user_id, movie_id);
			}
		}

		private static int getMovieIdFromGivenName(Connection connection) throws SQLException {
			System.out.println("search for the movie: ");
			String movie_name = App.console.nextLine();
			String queryCheckIfMovieExists = "select count(*) from movies where name = '" + movie_name + "';";
			PreparedStatement stmt = connection.prepareStatement(queryCheckIfMovieExists);
			ResultSet queryOutput = stmt.executeQuery();
			queryOutput.next();
			if (queryOutput.getInt(1) == 0)
				return -1;
			// TODO: do search by regex
			String querySearchIdOfMovie = "select id from movies where name = '" + movie_name + "';";
			stmt = connection.prepareStatement(querySearchIdOfMovie);
			queryOutput = stmt.executeQuery();
			queryOutput.next();

			stmt.close();
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

		private static void addUnlikedGenresToGenreArray(Connection connection, ArrayList<Genres> genres)
				throws SQLException {
			ArrayList<String> unlikedGenres = new ArrayList<String>();
			String queryGetAllGenres = "select distinct genre from movies;";
			PreparedStatement stmt = connection.prepareStatement(queryGetAllGenres);
			ResultSet queryOutput = stmt.executeQuery();
			queryOutput.next();
			try {
				while (true != false) {
					boolean genreExists = false;
					for (Genres genre : genres) {
						if (genre.getName().equals(queryOutput.getString(1))) {
							genreExists = true;
							break;
						}
					}
					if (genreExists == false) {
						unlikedGenres.add(queryOutput.getString(1));
					}
					queryOutput.next();
				}
			} catch (org.postgresql.util.PSQLException e) {
				// no more movies to read
				Collections.shuffle(unlikedGenres);
				for (String newGenre : unlikedGenres) {
					genres.add(new Genres(newGenre, 0));
				}

				addMoviesFromDbToGenres(connection, genres);
			}
		}

		private static ArrayList<Genres> insertFromDBinGenreArray(Connection connection, int user_id)
				throws SQLException {
			String queryGetAllGenresLikedByUser = "select genre, count(*) from movies join users_movies on movies.id = users_movies.movie_id where user_id = "
					+ user_id + " group by genre;";
			PreparedStatement stmt = connection.prepareStatement(queryGetAllGenresLikedByUser);
			ResultSet queryOutput = stmt.executeQuery();
			ArrayList<Genres> genres = new ArrayList<>();
			queryOutput.next();

			try {
				while (true != false) {
					genres.add(new Genres(queryOutput.getString(1), queryOutput.getInt(2)));
					queryOutput.next();
				}
			} catch (org.postgresql.util.PSQLException e) {
				// no more movies liked by the user to read
			}
			sortGenresByLikes(genres);

			addUnlikedGenresToGenreArray(connection, genres);

			stmt.close();
			return genres;
		}

		private static void addMoviesFromDbToGenres(Connection connection, ArrayList<Genres> genres)
				throws SQLException {
			for (Genres genre : genres) {
				String queryGetAllMoviesFromGenre = "select * from movies where genre = '" + genre.getName() + "';";
				PreparedStatement stmt = connection.prepareStatement(queryGetAllMoviesFromGenre);
				ResultSet queryOutput = stmt.executeQuery();
				queryOutput.next();

				try {
					while (true != false) {
						genre.addMovie(new Genres.Movies(queryOutput.getString(2), queryOutput.getString(3),
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
					int movie_id = Funks.getMovieIdFromGivenName(connection);

					if (movie_id != -1) {
						System.out.println(Funks.searchMovieCredentialsById(connection, movie_id) + "\n");

						// prompt user for like
						Funks.promptUserForLike(connection, user_id, movie_id);

						// prompt user for dislike
						Funks.promptUserForDislike(connection, user_id, movie_id);
					} else {
						System.out.println("the movie could not be found..\n");
					}
					break;
				}

				case 2: {
					PrintMenus.printUserMenuMenu3();
					short subOption = Inutils.getSmallIntInputFromUser();
					if (subOption == 1 || subOption == 2) {
						ArrayList<Genres> genres = Funks.insertFromDBinGenreArray(connection, user_id);

						if (subOption == 1) {
							Funks.sortMoviesByLikes(genres);
						} else {
							Funks.sortMoviesByReleaseDate(genres);
						}
						Funks.printFeed(genres);
					} else {
						System.out.println("unfortunately that is not an available option..");
					}
					break;
				}

				case 3: {
					Funks.printUserLikedMoviesList(connection, user_id);
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
