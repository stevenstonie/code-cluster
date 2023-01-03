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
		// solve messiness in code
		// also increment the number of likes of a certain movie if the user likes it? (or decrement if dislikes)
		// and maybe make a password generator?
		// and also a password censorer?
		// gui if i have some free time

		console.close();
		connection.close();
	}
}
