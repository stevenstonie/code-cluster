package com.stevenstonie.rc.classes;

import java.util.List;
import java.util.Scanner;
import java.util.concurrent.locks.LockSupport;
import java.util.random.RandomGenerator;

public class Tools {
	public static void printThreeLoadingDotsInConsole() {
		LockSupport.parkNanos(java.util.concurrent.TimeUnit.MILLISECONDS.toNanos(300));
		System.out.print(".");
		LockSupport.parkNanos(java.util.concurrent.TimeUnit.MILLISECONDS.toNanos(300));
		System.out.print(".");
		LockSupport.parkNanos(java.util.concurrent.TimeUnit.MILLISECONDS.toNanos(300));
		System.out.println(".");
		LockSupport.parkNanos(java.util.concurrent.TimeUnit.MILLISECONDS.toNanos(300));
	}

	public static boolean setDirectionFromConsole(Scanner scanner) {
		boolean direction = true;

		System.out
				.println("If you want the token to move clockwise, enter 1, otherwise for counter-clockwise enter 0: ");
		try {
			direction = scanner.nextLine().charAt(0) == '1';
		} catch (Exception e) {
			System.out.println("Invalid input. The token will move clockwise.");
		}

		return direction;
	}

	public static String getIPFromUserName(String name, List<Node> network) {
		for (Node node : network)
			if (name.equals(node.getName()))
				return node.getIP();
		return null;
	}

	public static boolean checkIfTheUserExists(String nameOrIP, List<Node> network) {
		for (Node node : network)
			if (nameOrIP.equals(node.getIP()) || nameOrIP.equals(node.getName()))
				return true;
		return false;
	}

	public static boolean isTheIPValid(String nodeIP) {
		String[] IPAddressBytes = nodeIP.split("\\.");

		if (IPAddressBytes.length != 4)
			return false;

		for (String part : IPAddressBytes) {
			try {
				int integer = Integer.parseInt(part); // check if it is a number
				if (integer < 0 || integer > 255) // check if it is between 0 and 255
					return false;
			} catch (NumberFormatException e) {
				return false;
			}
		}

		return true;
	}

	public static boolean hasTheIPTheSignatureOfNetwork(String nodeIP, String networkIP) {
		String[] IPBytes = nodeIP.split("\\.");
		String[] networkIPBytes = networkIP.split("\\.");

		for (int i = 0; i < 2; i++)
			if (!IPBytes[i].equals(networkIPBytes[i]))
				return false;

		return true;
	}

	public static boolean isTheIPAlreadyUsed(String nodeIP, List<Node> network) {
		for (Node node : network)
			if (node.getIP().equals(nodeIP))
				return true;

		return false;
	}

	public static String generateRandomIP() {
		RandomGenerator rand = RandomGenerator.getDefault();
		String ip = "";

		for (int i = 0; i < 4; i++) {
			ip += rand.nextInt(0, 256);
			ip += ".";
		}

		return new String(ip.substring(0, ip.length() - 1));
	}

	public static String generateRandomIPForNode(String networkIP) {
		RandomGenerator rand = RandomGenerator.getDefault();
		String nodeIP = "";

		for (int nbOfBytes = 0, indexOfIPString = 0; nbOfBytes < 2;) {
			if (networkIP.charAt(indexOfIPString) == '.')
				nbOfBytes++;

			nodeIP += networkIP.charAt(indexOfIPString++);
		}

		for (int i = 0; i < 2; i++) {
			nodeIP += rand.nextInt(0, 256);
			nodeIP += ".";
		}

		return new String(nodeIP.substring(0, nodeIP.length() - 1));
	}
}
