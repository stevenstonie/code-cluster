package classes;

import java.sql.SQLException;

import java.sql.PreparedStatement; // https://www.baeldung.com/java-statement-preparedstatement
import java.sql.ResultSet;
import java.sql.Connection;

public class CreateTables {
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

			String queryCheckExistenceOfForeignKeys = "select count(1) from information_schema.table_constraints WHERE constraint_name = ? AND table_name = 'users_movies';";
			stmt = connection.prepareStatement(queryCheckExistenceOfForeignKeys);
			stmt.setString(1, "users_movies_user_id_fkey");
			queryOutput = stmt.executeQuery();
			queryOutput.next();
			if (queryOutput.getString(1).equals("0")) {
				// with "alter table users_movies add constraint ? foreign key(user_id) references users(id);"
				//TODO: stmt.setString(1, "users_movies_user_id_fkey"); doesnt work as it inserts '' around the string (which is not allowed in this case)
				String queryAddUserForeignKey = "alter table users_movies add constraint users_movies_user_id_fkey foreign key(user_id) references users(id);";
				stmt = connection.prepareStatement(queryAddUserForeignKey);
				stmt.executeUpdate();

				System.out.println("inserted user_id foreign key into users_movies table");
			}

			stmt = connection.prepareStatement(queryCheckExistenceOfForeignKeys);
			stmt.setString(1, "users_movies_movie_id_fkey");
			queryOutput = stmt.executeQuery();
			queryOutput.next();
			if (queryOutput.getString(1).equals("0")) {
				// same thing as above
				String queryAddMovieForeignKey = "alter table users_movies add constraint users_movies_movie_id_fkey foreign key(movie_id) references movies(id);";
				stmt = connection.prepareStatement(queryAddMovieForeignKey);
				stmt.executeUpdate();

				System.out.println("inserted movie_id foreign key into users_movies table");
			}

			System.out.println("the table \"users_movies\" already exists");
		}

		stmt.close();
	}

}
