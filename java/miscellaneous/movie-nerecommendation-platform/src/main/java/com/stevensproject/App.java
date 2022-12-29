package com.stevensproject;

import classes.PromptAndMenu;
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

		PromptAndMenu.menu(connection);

		// prompt user for login
		// "press 0 for login"
		// "press 1 for registering"
		// "press 2 for admin login"
		// check database if credentials either exist or not for all three options

		// if successfull make a menu

		// for users
		// // search by name (regex if possible)
		// // view feed (sort by release date or likes)
		// // like system (??)
		// // logout

		// for admins
		// // add movies in the database by file or console
		// // maybe also delete from / update the database?
		// // logout
		// determine if the user can log in as admin if he knows the password of the database?
		// ==> get a parameter "password" to the database. if true user is admin. if not true user cant login as admin ==> so return a bool?
		// maybe make a password generator?
		// and also a password censorer?
		// gui if i have some free time

		console.close();
		connection.close();
	}
}
