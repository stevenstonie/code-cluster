package com.stevenstonie.rc;

import java.util.Scanner;

import com.stevenstonie.rc.classes.Network;
import com.stevenstonie.rc.classes.TokenRing;
import com.stevenstonie.rc.classes.Tools;

public class RemoteMain {

	public static void simulateTokenRing() {
		Scanner scanner = new Scanner(System.in);

		Network network = new Network();
		network.addNodes(6);
		TokenRing tokenRing = new TokenRing();

		boolean direction = true;
		System.out.println(
				"If you want the token to move clockwise, enter 1, otherwise for counter-clockwise enter 0: ");
		try {
			direction = scanner.nextLine().charAt(0) == '1';
		} catch (Exception e) {
			System.out.println("Invalid input. The token will move clockwise.");
		}

		java.util.Random rand = new java.util.Random();
		int posOfToken = rand.nextInt(0, network.getNetwork().size());
		boolean isExit = false;
		boolean hasInstruction = false;
		char choice = '0';
		while (isExit != true) {
			System.out.println("~~~~ the token is currently at the node "
					+ network.getNetwork().get(posOfToken).getName() + ": "
					+ network.getNetwork().get(posOfToken).getIP() + " ~~~~");

			if (tokenRing.isOpen() && !hasInstruction) {
				System.out.println("to continue press 0\nto send a message press 1\nto exit press anything else\n");
				choice = scanner.nextLine().charAt(0);

				if (choice == '1')
					hasInstruction = true;
				else if (choice != '0')
					isExit = true;
			}
			if (tokenRing.isOpen() && hasInstruction) {
				String input;

				System.out.println("enter the name/ip of the sender: ");
				input = scanner.nextLine();
				if (Tools.checkIfTheUserExists(input, network.getNetwork())) {
					tokenRing.setIPSource(input);
				} else {
					System.out.println("the user does not exist...");
					continue;
				}

				System.out.println("enter the message to be sent: ");
				tokenRing.setMessage(scanner.nextLine());

				System.out.println("enter the name of the user to whom the message is to be directed to: ");
				input = scanner.nextLine();
				if (Tools.checkIfTheUserExists(input, network.getNetwork())) {
					tokenRing.setIPDestination(Tools.getIPFromUserName(input, network.getNetwork())); // sets the name instead of the ip
				} else {
					System.out.println("the user does not exist...");
					continue;
				}
				tokenRing.setOpen(false);
				tokenRing.setHasArrivedAtDestination(false);
				hasInstruction = false;
			} else if (!tokenRing.isOpen()) {
				String userNameAndIP = network.getNetwork().get(posOfToken).getName() + ": "
						+ network.getNetwork().get(posOfToken).getIP();
				tokenRing.addToHistory(userNameAndIP);

				if (tokenRing.getIPDestination().equals(network.getNetwork().get(posOfToken).getIP())) {
					System.out.println("the message \"" + tokenRing.getMessage() + "\" has been sent succesfully");
					tokenRing.setOpen(true);
					tokenRing.setIPSource(null);
					tokenRing.setIPDestination(null);
					tokenRing.setMessage(null);
					tokenRing.setHasArrivedAtDestination(true);
				}
			}
			if (direction) {
				++posOfToken;
				if (posOfToken == network.getNetwork().size())
					posOfToken = 0;
			} else {
				--posOfToken;
				if (posOfToken == -1)
					posOfToken = network.getNetwork().size() - 1;
			}
		}

		scanner.close();
	}
}
