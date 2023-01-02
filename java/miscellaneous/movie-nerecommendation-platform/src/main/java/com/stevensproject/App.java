package com.stevensproject;

import classes.PromptAndMainMenu;
import classes.ConnectToDB;
import classes.CreateTables;

import java.sql.Connection;
import java.sql.SQLException;
import java.util.Scanner;

public class App {
	public static Scanner console = new Scanner(System.in);

	public static void main(String[] args) throws SQLException {
		ConnectToDB app = new ConnectToDB();
		Connection connection = app.connectToDatabase(false);
		CreateTables.createTableUsers(connection);
		CreateTables.createTableMovies(connection);
		CreateTables.createTableUsersMovies(connection);

		PromptAndMainMenu.mainMenu(connection);
		// add the unliked genres separately and randomized
		// maybe make a function to unlike a movie?
		// add thread sleep to the loading bar
		// also increase the number of the likes if the users likes the movies? (or decrease if dislikes)
		// and maybe make a password generator?
		// and also a password censorer?
		// gui if i have some free time

		console.close();
		connection.close();
	}
}
