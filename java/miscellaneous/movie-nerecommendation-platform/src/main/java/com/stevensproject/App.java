package com.stevensproject;

import java.util.Scanner;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.Date;
import java.sql.DriverManager;
import java.sql.PreparedStatement; // https://www.baeldung.com/java-statement-preparedstatement
import java.sql.SQLException;

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
		}

		console.close();

		return connection;
	}

	public static void createTableMovies(Connection connection) throws SQLException {
		String queryCreateTable = "create table if not exists movies(movie_name varchar(40) not null, genre varchar(20) not null, release_date date not null, likes int not null);";
		PreparedStatement stmt = connection.prepareStatement(queryCreateTable);
		stmt.executeUpdate();
		// -maybe put try catch maybe??
		// -and maybe surely put queryOutput for table so if it exists then print "table
		// already exists" and if not "table created successfully"??
		stmt.close();
		System.out.println("table created successfully");
	}

	public static void insertIntoTable(Connection connection) {
		PreparedStatement stmt = null;
		ResultSet queryOutput = null;
		String queryInsert = "INSERT INTO table1 (movie_name, genre, release_date, likes) VALUES (?, ?, ?, ?);";
		String queryCount = "select count(*) from table1 where movie_name = 'Adventure Time';";
		try {
			stmt = connection.prepareStatement(queryCount);
			queryOutput = stmt.executeQuery();
			queryOutput.next();
			System.out.println(queryOutput.getInt(1));
			if (queryOutput.getInt(1) == 0) { // idk why but i have to make this reversed (it shouldve been '!= 0')
				stmt = connection.prepareStatement(queryInsert);
				stmt.setString(1, "Adventure Time");
				stmt.setString(2, "Cartoon");
				stmt.setDate(3, Date.valueOf("2010-04-05"));
				stmt.setInt(4, 100);
				stmt.executeUpdate();
			} else {
				System.out.println("Movie already exists in the table");
			}

			// stmt.setString(1, "GOT");
			// stmt.setString(2, "Fantasy");
			// stmt.setDate(3, Date.valueOf("2011-04-17"));
			// stmt.setInt(4, 80);
			// stmt.executeUpdate();

			// connection.commit(); --> org.postgresql.util.PSQLException: Cannot commit
			// when autoCommit is enabled.
			queryOutput.close();
			stmt.close();
		} catch (Exception e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
			System.exit(1);
		}
		System.out.println("Records created successfully");
	}

	public static void main(String[] args) throws SQLException {
		App app = new App();
		Connection connection = app.connect();
		createTableMovies(connection);
		// insertIntoTable(connection);
		connection.close();
	}
}