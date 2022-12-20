package com.stevensproject;

import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement; // https://www.baeldung.com/java-statement-preparedstatement
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Date;

public class App {
	public Connection connect() {
		Scanner console = new Scanner(System.in);
		final String url = "jdbc:postgresql://localhost/movie_recommendation_platform";
		final String user = "postgres";
		final String password;
		System.out.println("insert password: ");
		password = console.nextLine();
		Connection connection = null;

		try {
			connection = DriverManager.getConnection(url, user, password);
			System.out.println("Connected to the PostgreSQL server successfully.");
		} catch (SQLException e) {
			System.out.println(e.getMessage());
			System.exit(1);
		}

		console.close();
		return connection;
	}

	public static void createTableMovies(Connection connection) throws SQLException {
		String queryCreateTable = "SELECT to_regclass('public.movies');";
		PreparedStatement stmt = connection.prepareStatement(queryCreateTable);
		ResultSet queryOutput = stmt.executeQuery();
		queryOutput.next();
		if (queryOutput.getString(1) == null) {
			queryCreateTable = "create table if not exists movies(movie_name varchar(40) not null, genre varchar(20) not null, release_date date not null, likes int not null);";
			stmt = connection.prepareStatement(queryCreateTable);
			stmt.executeUpdate();
			System.out.println("table \"movies\" created successfully");
		} else {
			System.out.println("the table \"movies\" already exists");
		}

		stmt.close();
	}

	public static void insertIntoTableByConsole(Connection connection) {
		PreparedStatement stmt = null;
		ResultSet queryOutput = null;
		String queryInsert = "";
	}
	// finish it

	public static void insertIntoTableByFile(Connection connection) {
		PreparedStatement stmt = null;
		ResultSet queryOutput = null;
		String queryInsert = "insert into movies (movie_name, genre, release_date, likes) values (?, ?, ?, ?);";
		String queryCount1 = "select count(*) from movies where movie_name = ?;"; // + "'movie_name';"

		try {
			File movieList = new File("movie_list.in");
			Scanner fileReader = new Scanner(movieList);
			String line = fileReader.nextLine(); // ignore the first line (it contains the name of each column)

			while (fileReader.hasNextLine()) {
				line = fileReader.nextLine();
				String[] tokens = line.split(", ");

				stmt = connection.prepareStatement(queryCount1);
				stmt.setString(1, tokens[0]);
				queryOutput = stmt.executeQuery();
				queryOutput.next();

				if (queryOutput.getInt(1) == 0) {
					stmt = connection.prepareStatement(queryInsert);
					stmt.setString(1, tokens[0]);
					stmt.setString(2, tokens[1]);
					stmt.setDate(3, Date.valueOf(tokens[2]));
					stmt.setInt(4, Integer.parseInt(tokens[3]));
					stmt.executeUpdate();
				} else {
					System.out.println("the movie \"" + tokens[0] + "\" already exists in the table");
				}

				// connection.commit(); --> org.postgresql.util.PSQLException: Cannot commit when autoCommit is enabled.
			}

			stmt.close();
			queryOutput.close();
			fileReader.close();
		} catch (FileNotFoundException e) {
			System.out.println("The file could not be found...");
			e.printStackTrace();
		} catch (SQLException e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
		}

		System.out.println("Records created successfully");
	}

	public static void main(String[] args) throws SQLException {
		App app = new App();
		Connection connection = app.connect();
		createTableMovies(connection);
		insertIntoTableByFile(connection);
		// make a menu

		connection.close();
	}
}