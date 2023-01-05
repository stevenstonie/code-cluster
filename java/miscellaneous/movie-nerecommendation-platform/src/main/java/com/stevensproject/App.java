package com.stevensproject;

import classes.LoginPromptAndMainMenu;
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

		CreateTables.createAllTables(connection);

		LoginPromptAndMainMenu.mainMenu(connection);

		// solve messiness in code -> literally impossible
		// also increment the number of likes of a certain movie if the user likes it? (or decrement if dislikes) --> should be done only in case more users are connected to the same database
		// maybe make a password generator?
		// gui if i have some free time

		console.close();
		connection.close();
	}
}
