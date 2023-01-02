package classes;

// import com.stevensproject.App;
// import classes.Inutils;

import java.sql.SQLException;

import classes.auxiliaryclasses.ConnectToDB;
import classes.auxiliaryclasses.Inutils;
import classes.auxiliaryclasses.RegisterAndLoginUser;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class PromptAndMainMenu {
	private static void printPromptUserMenu() {
		System.out.println("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		System.out.println("to bring back this menu press 0");
		System.out.println("if you are a new user press 1 to register");
		System.out.println("if you want to register as an admin press 2");
		System.out.println("if you are an existing user / admin press 3 to login");
		System.out.println("if you wish to exit the login process press anything else");
		System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	}

	private static String getRoleOfUser(Connection connection, int user_id) throws SQLException {
		String queryFindRoleOfUser = "select role from users where id = " + Integer.toString(user_id) + ";";
		PreparedStatement stmt = connection.prepareStatement(queryFindRoleOfUser);
		ResultSet queryFindRoleOfUserOutput = stmt.executeQuery();
		queryFindRoleOfUserOutput.next();

		return queryFindRoleOfUserOutput.getString(1);
	}

	// returns user_id. if id returned is -1 the user has not logged in
	private static int promptUser(Connection connection) throws SQLException {
		System.out.println("\n~~~~~~~~~~~ login window ~~~~~~~~~~~");
		int user_id = -1;
		boolean exit = false;
		short option;

		printPromptUserMenu();
		do {
			System.out.print(">");
			option = Inutils.getSmallIntInputFromUser();

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
			Menus.userMenu(connection, user_id);
		}

		if (user_role.equals("admin")) {
			Menus.adminMenu(connection);
		}
	}

	// count(something) ignores set limit ??????????
	//TODO: try to do the checking without count
}
