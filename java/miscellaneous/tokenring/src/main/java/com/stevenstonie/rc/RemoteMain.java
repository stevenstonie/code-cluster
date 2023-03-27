package com.stevenstonie.rc;

import java.util.Scanner;

import com.stevenstonie.rc.classes.Network;
import com.stevenstonie.rc.classes.Node;
import com.stevenstonie.rc.classes.TokenRing;
import com.stevenstonie.rc.classes.Tools;

public class RemoteMain {

	public static void simulateTokenRing() {
		Scanner scanner = new Scanner(System.in);

		Network network = new Network();
		network.addNodes(6);
		TokenRing tokenRing = new TokenRing();
		network.printAllNodes();

		boolean direction = Tools.setDirectionFromConsole(scanner);

		java.util.Random rand = new java.util.Random();
		int posOfToken = rand.nextInt(0, network.getNetwork().size());
		boolean isExit = false;
		char choice = '0';
		while (isExit != true) {
			System.out.println("~~~~ the token is currently at the node "
					+ network.getNetwork().get(posOfToken).getName() + ": "
					+ network.getNetwork().get(posOfToken).getIP() + " ~~~~");

			if (tokenRing.isOpen()) {
				System.out.println("to continue press 0\nto send a message press 1\nto exit press anything else\n");
				choice = scanner.nextLine().charAt(0);

				if (choice == '1') {
					processInstruction(scanner, network, tokenRing, network.getNetwork().get(posOfToken));
				} else if (choice != '0')
					isExit = true;
			}
			if (!tokenRing.isOpen()) {
				tokenRing.addToHistory(network.getNetwork().get(posOfToken).getName() + ": "
						+ network.getNetwork().get(posOfToken).getIP());

				checkIfDestinationIsReached(tokenRing, network.getNetwork().get(posOfToken));
			}

			Tools.printThreeLoadingDotsInConsole();
			posOfToken = changePositionOfToken(posOfToken, direction, network.getNetwork().size());
		}

		scanner.close();
	}

	private static int changePositionOfToken(int posOfToken, boolean direction, int sizeOfNetwork) {
		if (direction) {
			++posOfToken;
			if (posOfToken == sizeOfNetwork)
				posOfToken = 0;
		} else {
			--posOfToken;
			if (posOfToken == -1)
				posOfToken = sizeOfNetwork - 1;
		}

		return posOfToken;
	}

	private static void checkIfDestinationIsReached(TokenRing tokenRing, Node node) {
		if (tokenRing.getIPDestination().equals(node.getIP())) {
			System.out.println("the message \"" + tokenRing.getMessage() + "\" has been sent succesfully");
			tokenRing.setDefaultValuesForAllMembers();
		}
	}

	private static boolean isTheSenderTheCurrentNode(String senderName, Node currentNode) {
		return senderName.equals(currentNode.getName());
	}

	private static void processInstruction(Scanner scanner, Network network, TokenRing tokenRing, Node currentNode) {
		String input;

		System.out.println("enter the name of the sender: ");
		input = scanner.nextLine();
		if (Tools.checkIfTheUserExists(input, network.getNetwork())) {
			if (isTheSenderTheCurrentNode(input, currentNode)) {
				tokenRing.setIPSource(Tools.getIPFromUserName(input, network.getNetwork()));
			} else {
				System.out.println("the current node is not the sender...");
				return;
			}
		} else {
			System.out.println("the user does not exist...");
			return;
		}

		System.out.println("enter the message to be sent: ");
		tokenRing.setMessage(scanner.nextLine());

		System.out.println("enter the name of the user to whom the message is to be directed to: ");
		input = scanner.nextLine();
		if (Tools.checkIfTheUserExists(input, network.getNetwork())) {
			tokenRing.setIPDestination(Tools.getIPFromUserName(input, network.getNetwork()));
		} else {
			System.out.println("the user does not exist...");
			return;
		}
		tokenRing.setOpen(false);
		tokenRing.setHasArrivedAtDestination(false);
	}
}

// TODO: the history is currently not used
