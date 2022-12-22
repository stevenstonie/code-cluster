package com.stevensproject;

import classes.AllClasses;
import java.sql.Connection;
import java.sql.SQLException;

public class App {

	public static void main(String[] args) throws SQLException {
		AllClasses app = new AllClasses();
		Connection connection = app.connectToDatabase();
		// createTableUsers (in case the table doesnt exist)
		AllClasses.createTableMovies(connection);
		AllClasses.insertIntoTableMoviesByFile(connection);

		connection.close();
	}
}
// start
// connect to database
// check if tables exist
// if not create them
// prompt user for login
// "press 0 for login"
// "if new user press 1 for registering"
// check database if credentials either exist or not for both options 

// make a menu

// for users
// // search by name (regex if possible)
// // view feed (sort by release date or likes)
// // like system (??)
// // logout

// for admins
// // add movies in the database by file or console
// // maybe also delete from / update the database?

//

// have a table user
// name, password, role, likes

// have classes 
// one for making connection to server
// one for initializing tables (movies / users)
// one for inserting into database (file/console)
// one for menu 
// 

// determine if the user can log in as admin if he knows the password of the database?
// ==> get a parameter "password" to the database. if true user is admin. if not true user cant login as admin ==> so return a bool?
// maybe make a password generator?
// and also a password censorer?
// gui if i have some free time

// SEE HOW TO CHANGE CLASSPATH FOR THIS PROJECT
