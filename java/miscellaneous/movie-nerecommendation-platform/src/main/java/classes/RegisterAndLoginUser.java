package classes;

import com.stevensproject.App;

import java.sql.SQLException;

import java.sql.PreparedStatement; // https://www.baeldung.com/java-statement-preparedstatement
import java.sql.ResultSet;
import java.sql.Connection;

public class RegisterAndLoginUser {
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
		System.out.print("reenter the password: ");
		String password2 = App.console.nextLine();

		if (!password.equals(password2)) {
			System.out.println("the passwords do not match. please try again..");
			return -1;
		}

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

}
