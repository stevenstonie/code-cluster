package classes.auxiliaryclasses;

import com.stevensproject.App;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.apache.commons.lang3.mutable.MutableBoolean;
import org.apache.commons.lang3.mutable.MutableInt;

public class MenusFuncs {
	protected static class Genres {
		protected static class Movies {
			private int id;
			private String name;
			private String genre;
			private String release_date;
			private int likes;

			protected Movies(int id, String name, String genre, String release_date, int likes) {
				this.id = id;
				this.name = name;
				this.genre = genre;
				this.release_date = release_date;
				this.likes = likes;
			}

			protected int getId() {
				return id;
			}

			protected String getName() {
				return name;
			}

			protected String getGenre() {
				return genre;
			}

			protected String getReleaseDate() {
				return release_date;
			}

			protected int getLikes() {
				return likes;
			}
		}

		private String name;
		private int likesOfUser;
		ArrayList<Movies> movies = new ArrayList<>();

		protected Genres(String name, int likesOfUser) {
			this.name = name;
			this.likesOfUser = likesOfUser;
		}

		protected void sortMoviesByReleaseDate() {
			movies.sort((Movies m1, Movies m2) -> m2.getReleaseDate().compareTo(m1.getReleaseDate()));
		}

		protected void sortMoviesByLikes() {
			movies.sort((Movies m1, Movies m2) -> m2.getLikes() - m1.getLikes());
		}

		protected String getName() {
			return name;
		}

		protected Integer getLikesOfUser() {
			return likesOfUser;
		}

		protected void addMovie(Movies movie) {
			movies.add(movie);
		}

		protected ArrayList<Movies> getMovies() {
			return movies;
		}
	}

	class Auxs {
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

		private static boolean likeMovie(Connection connection, int user_id, int movie_id) throws SQLException {
			if (checkIfUserLikedTheMovieAlready(connection, user_id, movie_id) == true) {
				System.out.println("you already liked the movie before..");
				return false;
			}

			String queryAddUserAndMovieToUsersMovies = "insert into users_movies(user_id, movie_id) values("
					+ user_id
					+ ", " + movie_id + ");";
			PreparedStatement stmt = connection.prepareStatement(queryAddUserAndMovieToUsersMovies);
			stmt.executeUpdate();

			System.out.println("you have added the movie to your likes list");
			return true;
		}

		private static void dislikeMovie(Connection connection, int user_id, int movie_id) throws SQLException {
			if (Auxs.checkIfUserLikedTheMovieAlready(connection, user_id, movie_id) == false) {
				System.out.println("you dont have the specified movie in your likes list..");
				return;
			}

			String queryDeleteUserAndMovieFromUsersMovies = "delete from users_movies where user_id = " + user_id
					+ " and movie_id = " + movie_id + ";";
			PreparedStatement stmt = connection.prepareStatement(queryDeleteUserAndMovieFromUsersMovies);
			stmt.executeUpdate();
			System.out.println("you have deleted the movie from your likes list");
		}

		private static boolean promptUserForLike(Connection connection, int user_id, int movie_id)
				throws SQLException {
			PrintMenus.printIfUserWantsToLikeTheMovie();

			String subOption = App.console.nextLine();
			if (subOption.equals("y") || subOption.equals("yes") || subOption.equals("true")
					|| subOption.equals("ye") || subOption.equals("1") || subOption.equals("ja")) {
				if (likeMovie(connection, user_id, movie_id) == false)
					return false;

				return true;
			}

			return false;
		}

		private static void promptUserForDislike(Connection connection, int user_id, int movie_id)
				throws SQLException {
			PrintMenus.printIfUserWantsToDislikeTheMovie();

			String subOption = App.console.nextLine();
			if (subOption.equals("y") || subOption.equals("yes") || subOption.equals("true")
					|| subOption.equals("ye") || subOption.equals("1") || subOption.equals("ja")) {
				Auxs.dislikeMovie(connection, user_id, movie_id);
			}
		}

		private static void sortGenresByLikes(ArrayList<Genres> genres) {
			genres.sort((Genres g1, Genres g2) -> g2.getLikesOfUser() - g1.getLikesOfUser());
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
			}
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
						genre.addMovie(new Genres.Movies(Integer.parseInt(queryOutput.getString(1)),
								queryOutput.getString(2), queryOutput.getString(3),
								queryOutput.getString(4), Integer.parseInt(queryOutput.getString(5))));

						queryOutput.next();
					}
				} catch (org.postgresql.util.PSQLException e) {
					// no more movies to read
				}
			}
		}

		private static void getLongestMovieNameAndGenre(Connection connection, MutableInt longestMovieName,
				MutableInt longestGenreName)
				throws SQLException {
			String getNameAndGenreOfAllMovies = "select name, genre from movies;";
			PreparedStatement stmt = connection.prepareStatement(getNameAndGenreOfAllMovies);
			ResultSet queryOutput = stmt.executeQuery();
			queryOutput.next();

			try {
				while (true != false) {
					if (queryOutput.getString(1).length() > longestMovieName.getValue())
						longestMovieName.setValue(queryOutput.getString(1).length());
					if (queryOutput.getString(2).length() > longestGenreName.getValue())
						longestGenreName.setValue(queryOutput.getString(2).length());

					queryOutput.next();
				}
			} catch (org.postgresql.util.PSQLException e) {
				// no more movies to read
			}
		} // not as efficient as if 'longestMovieName' / 'longestGenreName' were calculated at movie inserting but it's more readable and another function also needed to get this value

		private static String concatenateToString(String string, String add, int length) {
			for (int i = 0; i < length; i++)
				string += add;
			return string;
		}

	}

	protected static Object[] findMovie(Connection connection, ArrayList<Genres> genres, MutableBoolean exists) {
		System.out.println("search for the movie: ");
		String movie_name_input = App.console.nextLine();
		Object[] movieCredentials = new Object[5];
		Pattern pattern = Pattern.compile(movie_name_input, Pattern.CASE_INSENSITIVE);

		for (Genres genre : genres) {
			for (Genres.Movies movie : genre.getMovies()) {
				Matcher matcher = pattern.matcher(movie.getName());
				boolean matchFound = matcher.find();

				if (matchFound == true) {
					exists.setValue(true);
					movieCredentials[0] = movie.getId();
					movieCredentials[1] = movie.getName();
					movieCredentials[2] = movie.getGenre();
					movieCredentials[3] = movie.getReleaseDate();
					movieCredentials[4] = movie.getLikes();
					break;
				}
			}
		}
		return movieCredentials;
	}

	protected static String searchMovieCredentialsById(Connection connection, int movie_id) throws SQLException {
		String querySearchMovieCredentials = "select * from movies where id = " + movie_id + ";";
		PreparedStatement stmt = connection.prepareStatement(querySearchMovieCredentials);
		ResultSet queryOutput = stmt.executeQuery();
		queryOutput.next();

		// dont close stmt here
		return queryOutput.getString(2) + " | " + queryOutput.getString(3) + " | "
				+ queryOutput.getString(4)
				+ " | " + queryOutput.getString(5);
	}

	protected static void promptUserForLikeAndDislike(Connection connection, int user_id, int movie_id)
			throws SQLException {
		boolean likedSuccessfully = Auxs.promptUserForLike(connection, user_id, movie_id);
		if (likedSuccessfully == false) // theres no reason to dislike a movie the user just liked
			Auxs.promptUserForDislike(connection, user_id, movie_id);
	}

	protected static ArrayList<Genres> insertFromDBinGenreArray(Connection connection, int user_id)
			throws SQLException {
		String queryGetAllGenresLikedByUser = "select genre, count(*) from movies join users_movies on movies.id = users_movies.movie_id where user_id = "
				+ user_id + " group by genre;";
		PreparedStatement stmt = connection.prepareStatement(queryGetAllGenresLikedByUser);
		ResultSet queryOutput = stmt.executeQuery();
		queryOutput.next();
		ArrayList<Genres> genres = new ArrayList<>();

		try {
			while (true != false) {
				genres.add(new Genres(queryOutput.getString(1), queryOutput.getInt(2)));
				queryOutput.next();
			}
		} catch (org.postgresql.util.PSQLException e) {
			// no more movies liked by the user to read
		}
		Auxs.sortGenresByLikes(genres);

		Auxs.addUnlikedGenresToGenreArray(connection, genres);

		Auxs.addMoviesFromDbToGenres(connection, genres);

		stmt.close();
		return genres;
	}

	protected static void sortMoviesByLikes(ArrayList<Genres> genres) {
		for (Genres genre : genres) {
			if (genre.getLikesOfUser() > 0) // only those which have genres liked by the user
				genre.sortMoviesByLikes();
		}
	}

	protected static void sortMoviesByReleaseDate(ArrayList<Genres> genres) {
		for (Genres genre : genres) {
			if (genre.getLikesOfUser() > 0) // only those which have genres liked by the user
				genre.sortMoviesByReleaseDate();
		}
	}

	protected static void printFeed(Connection connection, ArrayList<Genres> genres) throws SQLException {
		MutableInt longestMovieName = new MutableInt();
		MutableInt longestGenreName = new MutableInt();
		Auxs.getLongestMovieNameAndGenre(connection, longestMovieName, longestGenreName);

		for (Genres genre : genres) {
			for (Genres.Movies movie : genre.getMovies()) {
				// add spaces to the movie name so that all the movies are aligned
				String spacingOfMovieName = Auxs.concatenateToString("", " ",
						longestMovieName.getValue() - movie.getName().length());
				String spacingOfGenreName = Auxs.concatenateToString("", " ",
						longestGenreName.getValue() - genre.getName().length());

				System.out
						.println(movie.getName() + spacingOfMovieName + " | " + movie.getGenre() + spacingOfGenreName
								+ " | " + movie.getReleaseDate() + " | " + movie.getLikes());

				// does spacing before the movie name look better??	what if the name is too long? hmmm
				// System.out.println("--------------------------------------------------------------------------"); ??
			}
		}
	}

	protected static void printUserLikedMoviesList(Connection connection, int user_id) throws SQLException {
		String queryGetMoviesLikedByUser = "select movies.name, movies.genre, movies.release_date, movies.likes from movies inner join "
				+ " users_movies on movies.id = users_movies.movie_id where user_id = " + user_id + ";";
		PreparedStatement stmt = connection.prepareStatement(queryGetMoviesLikedByUser);
		ResultSet queryOutput = stmt.executeQuery();
		queryOutput.next();
		MutableInt longestMovieName = new MutableInt();
		MutableInt longestGenreName = new MutableInt();
		Auxs.getLongestMovieNameAndGenre(connection, longestMovieName, longestGenreName);

		try {
			while (true != false) {
				String spacingOfMovieName = Auxs.concatenateToString("", " ", longestMovieName.getValue()
						- queryOutput.getString(1).length());
				String spacingOfGenreName = Auxs.concatenateToString("", " ",
						longestGenreName.getValue() - queryOutput.getString(2).length());

				System.out.println(queryOutput.getString(1) + spacingOfMovieName + " | " + queryOutput.getString(2)
						+ spacingOfGenreName + " | "
						+ queryOutput.getString(3) + " | " + queryOutput.getString(4));

				queryOutput.next();
			}
		} catch (org.postgresql.util.PSQLException e) {
			// no more liked movies to read
		}

		stmt.close();
	}
}
