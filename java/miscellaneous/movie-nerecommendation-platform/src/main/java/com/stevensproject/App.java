package com.stevensproject;

import classes.PromptAndMainMenu;
import classes.auxiliaryclasses.ConnectToDB;
import classes.auxiliaryclasses.CreateTables;

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

		// add thread sleep to the loading bar
		// populate database
		// beautify the feed
		// place those Menus functions in a separate class to tidy code
		// solve messiness in code
		// also increase the number of the likes if the users likes the movies? (or decrease if dislikes)
		// and maybe make a password generator?
		// and also a password censorer?
		// gui if i have some free time

		console.close();
		connection.close();
	}
}
