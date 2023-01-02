package classes.secondaryclasses;

import com.stevensproject.App;

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
		String queryCheckForMovieExistence = "select count(*) from movies where name = ?;";

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

			fileReader.close();
			try {
				stmt.close();
				queryCheckForMovieExistenceOutput.close();
			} catch (java.lang.NullPointerException e2) {
				// ignore exception in case the admin doesnt insert any records
			}
		} catch (FileNotFoundException e) {
			System.out.println("The file could not be found...");
			e.printStackTrace();
		} catch (SQLException e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
		}

		System.out.println("Records created successfully");
	}

	public static void insertIntoTableMoviesByConsole(Connection connection) {
		PreparedStatement stmt = null;
		ResultSet queryCheckForMovieExistenceOutput = null;

		int n;
		System.out.println("how many entries would you like to add to the database?");
		n = App.console.nextInt();
		App.console.nextLine(); // ignores stray newline

		try {
			for (int i = 1; i <= n; i++) {
				String textInput;
				String queryInsertMovie = "insert into movies (name, genre, release_date, likes) values(";
				String queryCheckForMovieExistence = "select count(*) from movies where name = ?;";

				System.out.print("the name of the movie " + i + ": ");
				textInput = App.console.nextLine();
				stmt = connection.prepareStatement(queryCheckForMovieExistence);
				stmt.setString(1, textInput);
				queryCheckForMovieExistenceOutput = stmt.executeQuery();
				queryCheckForMovieExistenceOutput.next();

				if (queryCheckForMovieExistenceOutput.getString(1).equals("0")) {
					queryInsertMovie += "\'" + textInput + "\', ";

					System.out.print("what type of genre is the specified movie? ");
					textInput = App.console.nextLine();
					queryInsertMovie += "\'" + textInput + "\', ";

					System.out.print("when was the movie released? (insert yyyy-mm-dd) ");
					textInput = App.console.nextLine();
					queryInsertMovie += "\'" + textInput + "\', ";

					System.out.print("how many likes does the movie have? ");
					textInput = App.console.nextLine();
					queryInsertMovie += textInput + ");";
					// couldnt use setString() as it places '' around the insertion which is wrong in this case;

					stmt = connection.prepareStatement(queryInsertMovie);
					stmt.executeUpdate();

				} else {
					System.out.println("the movie " + textInput + " already exists.");
				}
			}

			try {
				stmt.close();
				queryCheckForMovieExistenceOutput.close();
			} catch (java.lang.NullPointerException e2) {
				// ignore exception in case the admin doesnt insert any records
			}

			System.out.println("Records created successfully");
		} catch (SQLException e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
		}
	}
}
