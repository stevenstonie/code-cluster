package classes;

import com.stevensproject.App;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class Menus {
	public static byte getIntFromUser() {
		String s_userInput = App.console.nextLine();

		for (int i = 0; i < s_userInput.length(); i++)
			if (!Character.isDigit(s_userInput.charAt(i)))
				return -1;

		int i_userInput = Integer.parseInt(s_userInput);
		if (i_userInput > Byte.MAX_VALUE)
			return -1;

		return (byte) i_userInput;
	}

	private static void printUserMenuMenu2() {
		System.out.println("if you wish to like the movie press 1");
		System.out.println("to search for another movie press 2");
		System.out.println("to go back press anything else");
	}

	private static void printUserMenuMenu3() {
		System.out.println("how would you like to sort the feed?");
		System.out.println("1: by release date");
		System.out.println("2: by the numbers of likes");
	}

	private static void printUserMenuMenu() {
		System.out.println("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		System.out.println("press 0 to bring back this menu");
		System.out.println("press 1 to search for a movie by name");
		System.out.println("press 2 to view your feed");
		System.out.println("press anything else to logout");
		System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	}

	private static void printAdminMenuMenu2() {
		System.out.println("how would you like to add the movies?");
		System.out.println("1: by a specified file");
		System.out.println("2: by console");
	}

	private static void printAdminMenuMenu() {
		System.out.println("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		System.out.println("press 0 to bring back this menu");
		System.out.println("press 1 to add movies in the database");
		System.out.println("press 2 to delete a movie from the database");
		System.out.println("press 3 to update a movie from the database");
		System.out.println("press anything else to logout");
		System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	}

	public static void userMenu(Connection connection) {
		boolean exit = false;
		byte option;

		printUserMenuMenu();
		do {
			System.out.print(">");
			option = getIntFromUser();

			switch (option) {
				case 0: {
					printUserMenuMenu();
					break;
				}

				case 1: {
					// function to search for a movie by name and return its id
					// function to print if the user wants like it, search for another one or go back
					// function to run the shite
					break;
				}

				case 2: {
					// function to print asking how the feed should be shown
					// function to show the feed as the user asked
					break;
				}

				default: {
					exit = true;
					break;
				}
			}
		} while (exit == false);

		// // search by name (regex if possible)
		// // view feed (sort by release date or likes)
		// // like system (??)
		// // logout
		// when liking a movie insert into the users_movies the id of the user and the id of the movie
		// the feed priority is by how many likes a genre has so count genres and sort. then sort the individual movies in each genre by whatever the user wants
	}

	public static void adminMenu(Connection connection) {
		boolean exit = false;
		byte option;

		printAdminMenuMenu();
		do {
			System.out.print(">");
			option = getIntFromUser();

		} while (exit == false);
		// if role is 'admin' => menu for admin
		// // add movies in the database by file or console
		// // maybe also delete from / update the database?
		// // logout
	}
}
