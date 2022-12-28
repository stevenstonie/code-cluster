package classes;

import java.sql.SQLException;
import java.util.Scanner;

import com.stevensproject.App;

import java.sql.PreparedStatement; // https://www.baeldung.com/java-statement-preparedstatement
import java.sql.ResultSet;
import java.io.File;
import java.io.FileNotFoundException;
import java.sql.Connection;
import java.sql.Date;
import java.sql.DriverManager;

public class AllClasses {
	// CONNECT + CREATES
	public Connection connectToDatabase(boolean isCheckingForAdmin) {
		final String db_url = "jdbc:postgresql://localhost/movie_recommendation_platform";
		final String db_user = "postgres";
		final String db_password;
		if (isCheckingForAdmin == true) {
			System.out.print("input database password: ");
			db_password = App.console.nextLine();
		} else {
			db_password = "ThisIsAPassword1234!";
		}
		Connection connection = null;

		try {
			connection = DriverManager.getConnection(db_url, db_user, db_password);
			System.out.println("Connected to the PostgreSQL server successfully.");
		} catch (SQLException e) {
			System.out.println(e.getMessage());
		}

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
			stmt = connection.prepareStatement(queryCreateTable);
			stmt.executeUpdate();
			System.out.println("table \"users_movies\" created successfully");
		} else {
			String queryCheckExistenceOfForeignKeys = "select count(1) from information_schema.table_constraints WHERE constraint_name=? AND table_name='users_movies';";
			stmt = connection.prepareStatement(queryCheckExistenceOfForeignKeys);
			stmt.setString(1, "users_movies_user_id_fkey");
			queryOutput = stmt.executeQuery();
			queryOutput.next();

			if (queryOutput.getString(1) == "0") {
				// insert user_id foreign key into users_movies table
				System.out.println("inserted user_id foreign key into users_movies table");
			}

			stmt = connection.prepareStatement(queryCheckExistenceOfForeignKeys);
			stmt.setString(1, "users_movies_movie_id_fkey");
			queryOutput = stmt.executeQuery();
			queryOutput.next();

			if (queryOutput.getString(1) == "0") {
				// insert movie_id foreign key into users_movies table
				System.out.println("inserted movie_id foreign key into users_movies table");
			}

			System.out.println("the table \"users_movies\" already exists");
		}

		stmt.close();
	}

	// INSERTS

	public static void insertIntoTableMoviesByFile(Connection connection) {
		PreparedStatement stmt = null;
		ResultSet queryCountOutput = null;
		String queryInsertMovie = "insert into movies (name, genre, release_date, likes) values(?, ?, ?, ?);";
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

	/*public static void insertIntoTableMoviesByConsole(Connection connection) {
		PreparedStatement stmt = null;
		ResultSet queryCountOutput = null;
		String queryInsertMovie = "insert into movies (name, genre, release_date, likes) values(?, ?, ?, ?);";
		String queryCount = "select count(*) from movies where name = ?;";
	
		int n;
		System.out.println("how many entries would you like to add to the database?");
		n = App.console.nextInt(); // Exception in thread "main" java.util.NoSuchElementException
		App.console.nextLine(); // ignores stray newline
	
		try {
			String text;
			for (int i = 1; i <= n; i++) {
				System.out.print("the name of the movie " + i + ": ");
				text = App.console.nextLine();
				stmt = connection.prepareStatement(queryCount);
				stmt.setString(1, text);
				queryCountOutput = stmt.executeQuery();
				queryCountOutput.next();
	
				if (queryCountOutput.getInt(i) == 0) {
					stmt = connection.prepareStatement(queryInsertMovie);
					stmt.setString(1, text);
	
					System.out.print("what type of genre is the specified movie? ");
					text = App.console.nextLine();
					stmt.setString(2, text);
	
					System.out.print("when was the movie released? (insert yyyy-mm-dd) ");
					text = App.console.nextLine();
					stmt.setString(3, text);
	
					System.out.print("how many likes does the movie have? ");
					text = App.console.nextLine();
					stmt.setString(4, text);
	
				} else {
					System.out.println("the movie " + text + " already exists.");
				}
			}
	
			stmt.close();
			queryCountOutput.close();
		} catch (SQLException e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
		}
	
	}*/
	/// !!!!!!!!!!!!!!!!! EXCEPTION THROWN AT READING

	// PROMPT + MENU

	public static int registerUser(Connection connection, boolean isAdmin) throws SQLException {
		String queryCheckForUserExistence = "select count (name) from users where name = ?;";
		String queryGetIdFromUser = "select id from users where name = ? ;";
		String queryInsertUser = "insert into users(name, password, role) values(?, ?, ?);";
		PreparedStatement stmt = null;
		ResultSet queryOutput = null;
		int user_id = -1;

		System.out.print("input name: ");
		String name = App.console.nextLine();
		System.out.print("input password: ");
		String password = App.console.nextLine();

		stmt = connection.prepareStatement(queryCheckForUserExistence);
		stmt.setString(1, name);
		queryOutput = stmt.executeQuery();
		queryOutput.next();
		if (queryOutput.getInt(1) == 0) {
			stmt = connection.prepareStatement(queryInsertUser);
			stmt.setString(1, name);
			stmt.setString(2, password);
			if (isAdmin == true)
				stmt.setString(3, "admin");
			else
				stmt.setString(3, "user");
			stmt.executeUpdate();

			stmt = connection.prepareStatement(queryGetIdFromUser);
			stmt.setString(1, name);
			queryOutput = stmt.executeQuery();
			queryOutput.next();
			user_id = queryOutput.getInt(1);

			System.out.println("the user has been succesfully added!");
			return user_id;
		} else {
			System.out.println("the user already exists. please try again with another username..");
			return -1;
		}
	}

	public static int loginUser(Connection connection) throws SQLException {
		String queryCheckForUserExistence = "select count (name) from users where name = ?;";
		String queryCheckForUserAndPassExistence = "select count (name) from users where name = ? and password = ?;";
		String queryGetIdFromUser = "select id from users where name = ?;";
		PreparedStatement stmt = null;
		ResultSet queryOutput = null;
		int user_id = -1;

		System.out.print("input name: ");
		String name = App.console.nextLine();
		System.out.print("input password: ");
		String password = App.console.nextLine();

		stmt = connection.prepareStatement(queryCheckForUserExistence);
		stmt.setString(1, name);
		queryOutput = stmt.executeQuery();
		queryOutput.next();

		if (queryOutput.getInt(1) == 0) {
			System.out.println("the user doesnt exist..");
			return -1;
		} else {
			stmt = connection.prepareStatement(queryCheckForUserAndPassExistence);
			stmt.setString(1, name);
			stmt.setString(2, password);
			queryOutput = stmt.executeQuery();
			queryOutput.next();

			if (queryOutput.getInt(1) == 0) {
				System.out.println("the password is not valid");
				return -1;
			} else {
				stmt = connection.prepareStatement(queryGetIdFromUser);
				stmt.setString(1, name);
				queryOutput = stmt.executeQuery();
				queryOutput.next();
				user_id = queryOutput.getInt(1);

				System.out.println("login successful!");
				return user_id;
			}
		}
	}

	public static void printPromptUserMenu() {
		System.out
				.println(
						"to bring back this menu press 0\nif you are a new user press 1 to register.\nif you want to register as an admin press 2.");
		System.out.println(
				"if you are an existing user / admin press 3 to login.\nif you wish to exit the login process press anything else.\n");
	}

	// returns user_id. if id returned is -1 the user has not logged in
	public static int promptUser(Connection connection) throws SQLException {
		System.out.println("\n~~~~~~~~~~~ welcome to my movie recommendation platform! ~~~~~~~~~~~");
		int user_id = -1;
		boolean exit = false;
		byte option;

		printPromptUserMenu();
		do {
			// make string variable if user inputs letters instead of digits
			System.out.print(">");
			option = (byte) App.console.nextInt();
			App.console.nextLine(); // ignores stray newline
			switch (option) {
				case 0: {
					printPromptUserMenu();
					break;
				}
				case 1: {
					user_id = AllClasses.registerUser(connection, false);
					if (user_id != -1)
						exit = true;
					break;
				}

				case 2: {
					System.out.println("insert the database password in order to register with an admin account");
					AllClasses tempApp = new AllClasses();
					Connection tempConnection = tempApp.connectToDatabase(true);
					// check if this works
					if (tempConnection == null) {
						System.out.println("im sorry, but the inserted database password is not valid..");
					} else {
						user_id = AllClasses.registerUser(connection, true);
						if (user_id != -1)
							exit = true;
					}
					break;
				}

				case 3: {
					user_id = AllClasses.loginUser(connection);
					if (user_id != -1)
						exit = true;
					break;
				}
				default: {
					System.out.println("exiting program..");
					exit = true;
					break;
				}
			}
		} while (exit == false);
		return user_id;
	}

	public static void menu(Connection connection) throws SQLException {
		promptUser(connection);
		// LOOP

	}

	// count(something) ignores set limit ??????????
	// try to do checks without count

}
