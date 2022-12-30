package classes;

// import com.stevensproject.App;

import java.sql.SQLException;
import java.util.Scanner;

import java.sql.PreparedStatement; // https://www.baeldung.com/java-statement-preparedstatement
import java.sql.ResultSet;
import java.io.File;
import java.io.FileNotFoundException;
import java.sql.Connection;
import java.sql.Date;

public class InsertIntoTables {
	public static void insertIntoTableMoviesByFile(Connection connection) {
		PreparedStatement stmt = null;
		ResultSet queryCheckForMovieExistenceOutput = null;
		String queryInsertMovie = "insert into movies (name, genre, release_date, likes) values(?, ?, ?, ?);";
		String queryCheckForMovieExistence = "select count(*) from movies where name = ?;"; // + "'movie_name';"

		try {
			File movieList = new File("movie_list.in");
			Scanner fileReader = new Scanner(movieList);
			String line = fileReader.nextLine(); // ignore the first line (it contains the name of each column)

			while (fileReader.hasNextLine()) {
				line = fileReader.nextLine();
				String[] tokens = line.split(", ");

				stmt = connection.prepareStatement(queryCheckForMovieExistence);
				stmt.setString(1, tokens[0]);
				queryCheckForMovieExistenceOutput = stmt.executeQuery();
				queryCheckForMovieExistenceOutput.next();

				if (queryCheckForMovieExistenceOutput.getInt(1) == 0) {
					stmt = connection.prepareStatement(queryInsertMovie);
					stmt.setString(1, tokens[0]);
					stmt.setString(2, tokens[1]);
					stmt.setDate(3, Date.valueOf(tokens[2]));
					stmt.setInt(4, Integer.parseInt(tokens[3]));
					stmt.executeUpdate();
				} else {
					System.out.println("the movie \"" + tokens[0] + "\" already exists in the table");
				}
			}

			stmt.close();
			queryCheckForMovieExistenceOutput.close();
			fileReader.close();
		} catch (FileNotFoundException e) {
			System.out.println("The file could not be found...");
			e.printStackTrace();
		} catch (SQLException e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
		}

		System.out.println("Records created successfully");
	}

	/*public static void insertIntoTableMoviesByConsole(Connection connection) {
		PreparedStatement stmt = null;
		ResultSet queryCheckForMovieExistenceOutput = null;
		String queryInsertMovie = "insert into movies (name, genre, release_date, likes) values(?, ?, ?, ?);";
		String queryCheckForMovieExistence = "select count(*) from movies where name = ?;";
	
		int n;
		System.out.println("how many entries would you like to add to the database?");
		n = App.console.nextInt(); // Exception in thread "main" java.util.NoSuchElementException
		App.console.nextLine(); // ignores stray newline
	
		try {
			String text;
			for (int i = 1; i <= n; i++) {
				System.out.print("the name of the movie " + i + ": ");
				text = App.console.nextLine();
				stmt = connection.prepareStatement(queryCheckForMovieExistence);
				stmt.setString(1, text);
				queryCheckForMovieExistenceOutput = stmt.executeQuery();
				queryCheckForMovieExistenceOutput.next();
	
				if (queryCheckForMovieExistenceOutput.getInt(i) == 0) {
					stmt = connection.prepareStatement(queryInsertMovie);
					stmt.setString(1, text);
	
					System.out.print("what type of genre is the specified movie? ");
					text = App.console.nextLine();
					stmt.setString(2, text);
	
					System.out.print("when was the movie released? (insert yyyy-mm-dd) ");
					text = App.console.nextLine();
					stmt.setString(3, text);
	
					System.out.print("how many likes does the movie have? ");
					// make a check for string input
					text = App.console.nextLine();
					stmt.setString(4, text);
					// TODO: the setString adds '' around an int. the string should be for example 43 not '43'!!!!!!!!!!!!!!!!
					// org.postgresql.util.PSQLException: The column index is out of range: 2, number of columns: 1.
	
				} else {
					System.out.println("the movie " + text + " already exists.");
				}
			}
	
			stmt.close();
			queryCheckForMovieExistenceOutput.close();
		} catch (SQLException e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
		}
	}*/
}
