package com.stevenstonie.rc;

import java.util.Scanner;

import com.stevenstonie.rc.classes.Network;
import com.stevenstonie.rc.classes.TokenRing;

public class RemoteMain {
	public static void simulateTokenRing() {
		Network network = new Network();
		network.addNodes(15);
		TokenRing tokenRing = new TokenRing();

		boolean direction = true;
		System.out.println(
				"If you want the token to move clockwise, enter 1, otherwise for counter-clockwise enter 0: ");
		try (Scanner scanner = new Scanner(System.in)) {
			direction = scanner.nextInt() == 1;
		} catch (Exception e) {
			System.out.println("Invalid input. The token will move clockwise.");
		}

		java.util.Random rand = new java.util.Random();
		int posOfToken = rand.nextInt(0, network.getNetwork().size());
		boolean isExit = false;
		boolean hasInstruction = false;
		while (isExit != true) {
			// the token's movement will be controlled by a breakpoint for now until i figure out how to make the loop run every 0.5 sec

			// user is prompted to enter a command
			// 1. enter the name of the user.
			//// 1.1 hasInstruction = true;
			// 2. exit.
			//// 2.1. isExit = true;
			if (tokenRing.isOpen() && hasInstruction) {
				//// 1.2. enter the message
				//// 1.3. enter the name of the user to whom the command is to be directed
				//// 1.4. isOpen() = false;
				//// 1.5. hasInstruction = false;
			} else if (!tokenRing.isOpen()) {
				// user is unable to say anything as a boulder is about to crush his family's heads

				// update the history of the token

				// check if the posOfToken is at the destination
				//// if yes then isOpen() = true;
				//// ipSource and ipDestination = null;
				//// sentMessage = null;
				//// atDestination = false;
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

			// maybe print the token's position in the network
		}
		// if yes then create a function (which gets called every 0.5 sec) that will have two instances:
		// 1. the token ring is moving in the background and the user can insert commands
		// 2. the token ring is moving while the command is being executed and the user waits for the command to finish
		// 
	}
}
