package classes;

import com.stevensproject.App;

import java.sql.SQLException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Connection;

public class PromptAndMainMenu {
	private static void printPromptUserMenu() {
		System.out
				.println(
						"to bring back this menu press 0\nif you are a new user press 1 to register.\nif you want to register as an admin press 2.");
		System.out.println(
				"if you are an existing user / admin press 3 to login.\nif you wish to exit the login process press anything else.\n");
	}

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

	private static String getRoleOfUser(Connection connection, int user_id) throws SQLException {
		String queryFindRoleOfUser = "select role from users where id = " + Integer.toString(user_id) + ";";
		PreparedStatement stmt = null;
		ResultSet queryFindRoleOfUserOutput = null;

		stmt = connection.prepareStatement(queryFindRoleOfUser);
		queryFindRoleOfUserOutput = stmt.executeQuery();
		queryFindRoleOfUserOutput.next();

		return queryFindRoleOfUserOutput.getString(1);
	}

	// returns user_id. if id returned is -1 the user has not logged in
	private static int promptUser(Connection connection) throws SQLException {
		System.out.println("\n~~~~~~~~~~~ login window ~~~~~~~~~~~");
		int user_id = -1;
		boolean exit = false;
		byte option;

		printPromptUserMenu();
		do {
			System.out.print(">");
			option = getIntFromUser();

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
					exit = true;
					break;
				}
			}
		} while (exit == false);
		return user_id;
	}

	public static void mainMenu(Connection connection) throws SQLException {
		int user_id = promptUser(connection);
		if (user_id == -1) {
			System.out.println("login unsuccessful. exiting program..");
			return;
		}

		System.out.println("\n~~~~~~~~~~~ welcome to my movie recommendation platform! ~~~~~~~~~~~");

		String user_role = getRoleOfUser(connection, user_id);

		if (user_role.equals("user")) {
			Menus.userMenu(connection);
		}

		if (user_role.equals("admin")) {
			Menus.adminMenu(connection);
		}
	}

	// count(something) ignores set limit ??????????
	//TODO: try to do the checking without count

}
