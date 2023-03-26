package com.stevenstonie.rc.classes;

import java.util.List;
import java.util.random.RandomGenerator;

public class Tools {
	public static boolean isTheIPValid(String nodeIP) {
		String[] IPAddressBytes = nodeIP.split(".");

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

	public static boolean isTheIPPartOfTheNetwork(String nodeIP, String networkIP) {
		String[] IPBytes = nodeIP.split(".");
		String[] networkIPBytes = networkIP.split(".");

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
			nodeIP += networkIP.charAt(indexOfIPString++);

			if (networkIP.charAt(indexOfIPString) == '.')
				nbOfBytes++;
		}

		for (int i = 0; i < 2; i++) {
			nodeIP += rand.nextInt(0, 256);
			nodeIP += ".";
		}

		return new String(nodeIP.substring(0, nodeIP.length() - 1));
	}
}
