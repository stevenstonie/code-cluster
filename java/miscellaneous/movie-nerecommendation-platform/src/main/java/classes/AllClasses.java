package classes;

import java.sql.SQLException;
import java.util.Scanner;
import java.sql.PreparedStatement; // https://www.baeldung.com/java-statement-preparedstatement
import java.sql.ResultSet;
import java.io.File;
import java.io.FileNotFoundException;
import java.sql.Connection;
import java.sql.Date;
import java.sql.DriverManager;

public class AllClasses {
	public Connection connectToDatabase() {
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
			queryCreateTable = "create table movies(id serial primary key, name varchar(40) not null, genre varchar(20) not null, release_date date not null, likes int not null);"; // "if not exists" not necessary here (already checked above)
			stmt = connection.prepareStatement(queryCreateTable);
			stmt.executeUpdate();
			System.out.println("table \"movies\" created successfully");
		} else {
			System.out.println("the table \"movies\" already exists");
		}

		stmt.close();
	}

	public static void createTableUsers(Connection connection) throws SQLException {
		String queryCreateTable = "Select to_regclass('public.users');";
		PreparedStatement stmt = connection.prepareStatement(queryCreateTable);
		ResultSet queryOutput = stmt.executeQuery();
		queryOutput.next();

		if (queryOutput.getString(1) == null) {
			queryCreateTable = "create table users(id serial primary key ,name varchar(40) not null, password varchar(40) not null, role varchar(10) not null);"; // "if not exists" not necessary here (already checked above)
			stmt = connection.prepareStatement(queryCreateTable);
			stmt.executeUpdate();
			System.out.println("table \"users\" created successfully");
		} else {
			System.out.println("the table \"users\" already exists");
		}

		stmt.close();
	}

	public static void createTableUsersMovies(Connection connection) throws SQLException {
		String queryCreateTable = "select to_regclass('public.users_movies');";
		PreparedStatement stmt = connection.prepareStatement(queryCreateTable);
		ResultSet queryOutput = stmt.executeQuery();
		queryOutput.next();

		if (queryOutput.getString(1) == null) {
			queryCreateTable = "create table users_movies(id serial primary key, user_id int not null, movie_id int not null, foreign key (user_id) references users(id), foreign key (movie_id) references movies(id));"; // "if not exists" not necessary here (already checked above)
		} else {
			System.out.println("the table \"users_movies\" already exists");
		}
	}

	//

	public static void insertIntoTableMoviesByFile(Connection connection) {
		PreparedStatement stmt = null;
		ResultSet queryCountOutput = null;
		String queryInsert = "insert into movies (name, genre, release_date, likes) values(?, ?, ?, ?);";
		String queryCount = "select count(*) from movies where name = ?;"; // + "'movie_name';"

		try {
			File movieList = new File("movie_list.in");
			Scanner fileReader = new Scanner(movieList);
			String line = fileReader.nextLine(); // ignore the first line (it contains the name of each column)

			while (fileReader.hasNextLine()) {
				line = fileReader.nextLine();
				String[] tokens = line.split(", ");

				stmt = connection.prepareStatement(queryCount);
				stmt.setString(1, tokens[0]);
				queryCountOutput = stmt.executeQuery();
				queryCountOutput.next();

				if (queryCountOutput.getInt(1) == 0) {
					stmt = connection.prepareStatement(queryInsert);
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
			queryCountOutput.close();
			fileReader.close();
		} catch (FileNotFoundException e) {
			System.out.println("The file could not be found...");
			e.printStackTrace();
		} catch (SQLException e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
		}

		System.out.println("Records created successfully");
	}

	/*public static void insertIntoTableByConsole(Connection connection) {
		PreparedStatement stmt = null;
		ResultSet queryCountOutput = null;
		String queryInsert = "insert into movies (name, genre, release_date, likes) values(?, ?, ?, ?);";
		String queryCount = "select count(*) from movies where name = ?;";
	
		int n;
		Scanner console = new Scanner(System.in);
		System.out.println("how many entries would you like to add to the database?");
		n = console.nextInt(); // Exception in thread "main" java.util.NoSuchElementException
	
		try {
			String text;
			for (int i = 1; i <= n; i++) {
				System.out.print("the name of the movie " + i + ": ");
				text = console.nextLine();
				stmt = connection.prepareStatement(queryCount);
				stmt.setString(1, text);
				queryCountOutput = stmt.executeQuery();
				queryCountOutput.next();
	
				if (queryCountOutput.getInt(i) == 0) {
					stmt = connection.prepareStatement(queryInsert);
					stmt.setString(1, text);
	
					System.out.print("what type of genre is the specified movie? ");
					text = console.nextLine();
					stmt.setString(2, text);
	
					System.out.print("when was the movie released? (insert yyyy-mm-dd) ");
					text = console.nextLine();
					stmt.setString(3, text);
	
					System.out.print("how many likes does the movie have? ");
					text = console.nextLine();
					stmt.setString(4, text);
	
				} else {
					System.out.println("the movie " + text + " already exists.");
				}
			}
	
			console.close();
			stmt.close();
			queryCountOutput.close();
		} catch (SQLException e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
		}
	
	}*/
	/// !!!!!!!!!!!!!!!!! EXCEPTION THROWN AT READING
}
