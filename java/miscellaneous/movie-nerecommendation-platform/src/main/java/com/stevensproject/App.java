package com.stevensproject;

import classes.AllClasses;
import java.sql.Connection;
import java.sql.SQLException;

public class App {

	public static void main(String[] args) throws SQLException {
		AllClasses app = new AllClasses();
		Connection connection = app.connectToDatabase();
		AllClasses.createTableUsers(connection);
		AllClasses.createTableMovies(connection);
		AllClasses.createTableUsersMovies(connection);
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

		connection.close();
	}
}

// have classes 
// one for menu 
// 

// SEE HOW TO CHANGE CLASSPATH FOR THIS PROJECT
