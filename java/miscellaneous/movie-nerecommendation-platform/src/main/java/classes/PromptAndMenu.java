package classes;

import com.stevensproject.App;

import java.sql.SQLException;

import java.sql.Connection;

public class PromptAndMenu {
	public static void printPromptUserMenu() {
		System.out
				.println(
						"to bring back this menu press 0\nif you are a new user press 1 to register.\nif you want to register as an admin press 2.");
		System.out.println(
				"if you are an existing user / admin press 3 to login.\nif you wish to exit the login process press anything else.\n");
	}

	// returns user_id. if id returned is -1 the user has not logged in
	public static int promptUser(Connection connection) throws SQLException {
		System.out.println("\n~~~~~~~~~~~ welcome to my movie recommendation platform! ~~~~~~~~~~~");
		int user_id = -1;
		boolean exit = false;
		byte option;

		printPromptUserMenu();
		do {
			// make string variable if user inputs letters instead of digits
			System.out.print(">");
			option = (byte) App.console.nextInt();
			App.console.nextLine(); // ignores stray newline
			switch (option) {
				case 0: {
					printPromptUserMenu();
					break;
				}
				case 1: {
					user_id = RegisterAndLoginUser.registerUser(connection, false);
					if (user_id != -1)
						exit = true;
					break;
				}

				case 2: {
					System.out.println("insert the database password in order to register with an admin account");
					ConnectToDB tempApp = new ConnectToDB();
					Connection tempConnection = tempApp.connectToDatabase(true);
					// check if this works
					if (tempConnection == null) {
						System.out.println("im sorry, but the inserted database password is not valid..");
					} else {
						user_id = RegisterAndLoginUser.registerUser(connection, true);
						if (user_id != -1)
							exit = true;
					}
					break;
				}

				case 3: {
					user_id = RegisterAndLoginUser.loginUser(connection);
					if (user_id != -1)
						exit = true;
					break;
				}
				default: {
					System.out.println("exiting program..");
					exit = true;
					break;
				}
			}
		} while (exit == false);
		return user_id;
	}

	public static void menu(Connection connection) throws SQLException {
		promptUser(connection);
		// LOOP

	}

	// count(something) ignores set limit ??????????
	// try to do checks without count

}
