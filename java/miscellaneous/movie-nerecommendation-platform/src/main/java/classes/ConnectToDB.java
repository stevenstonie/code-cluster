package classes;

import com.stevensproject.App;

import java.sql.SQLException;

import java.sql.Connection;
import java.sql.DriverManager;

public class ConnectToDB {
	public Connection connectToDatabase(boolean isCheckingForAdmin) {
		final String db_url = "jdbc:postgresql://localhost/movie_recommendation_platform"; // name of database
		final String db_user = "postgres"; // default user
		final String db_password;
		if (isCheckingForAdmin == true) {
			System.out.print("input database password: ");
			db_password = App.console.nextLine();
		} else {
			db_password = "ThisIsAPassword1234!"; // password
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
}
