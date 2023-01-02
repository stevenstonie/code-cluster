package classes.auxiliaryclasses;

public class PrintMenus {
	public static void printPromptUserMenu() {
		System.out.println("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		System.out.println("to bring back this menu press 0");
		System.out.println("if you are a new user press 1 to register");
		System.out.println("if you want to register as an admin press 2");
		System.out.println("if you are an existing user / admin press 3 to login");
		System.out.println("if you wish to exit the login process press anything else");
		System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	}

	public static void printIfUserWantsToLikeTheMovie() {
		System.out.println("do you want to like the selected movie?");
	}

	public static void printIfUserWantsToDislikeTheMovie() {
		System.out.println("do you want to dislike the selected movie?");
	}

	public static void printUserMenuMenu3() {
		System.out.println("how would you like to sort the feed?");
		System.out.println("1: by the number of likes");
		System.out.println("2: by release date");
	}

	public static void printUserMenuMenu() {
		System.out.println("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		System.out.println("press 0 to bring back this menu");
		System.out.println("press 1 to search for a movie by name");
		System.out.println("press 2 to view your feed");
		System.out.println("press 3 to view your liked movies list");
		System.out.println("press anything else to logout");
		System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	}

	public static void printAdminMenuMenu2() {
		System.out.println("how would you like to add the movies?");
		System.out.println("1: by a specified file");
		System.out.println("2: by console");
	}

	public static void printAdminMenuMenu() {
		System.out.println("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		System.out.println("press 0 to bring back this menu");
		System.out.println("press 1 to add movies in the database");
		System.out.println("press 2 to delete a movie from the database");
		System.out.println("press anything else to logout");
		System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	}
}
