package com.stevenstonie.rc;

import java.util.Scanner;

import com.stevenstonie.rc.classes.Network;
import com.stevenstonie.rc.classes.TokenRing;

public class RemoteMain {
	public static void simulateTokenRing() {
		Network network = new Network();
		network.addNodes(15);

		// the token ring is initialized
		TokenRing tokenRing = new TokenRing();

		// does the ring have to move constantly around the network?

		// now the problem i havent solved from the start is how to map the token Ring to the network

		// maybe a for loop with an index from on which the position is the token's position in that network

		// so the index will be called posOfToken and depending on the user's choice of the direction the 
		// token is moving, the index will either increment or decrement

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
		while (isExit != true) {
			// the token's movement will be controlled by a breakpoint for now until i figure out how to make the loop run every 0.5 sec

			if (tokenRing.isOpen()) {
				// user is prompted to enter a command
			} else {
				// user is unable to say anything as a boulder is about to crush his family's heads
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
		// if yes then create a function (which gets called every 0.5 sec) that will have two instances:
		// 1. the token ring is moving in the background and the user can insert commands
		// 2. the token ring is moving while the command is being executed and the user waits for the command to finish
		// 
	}
}
