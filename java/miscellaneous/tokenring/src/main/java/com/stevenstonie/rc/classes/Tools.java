package com.stevenstonie.rc.classes;

import java.util.List;
import java.util.random.RandomGenerator;

public class Tools {
	public static boolean isTheIPValid(IPAddress ip) {
		// check for the validity of the IP adress

		// split the IP address by the dots

		// 1. check if the IP adress has 4 parts

		// 2. check if each part is a number

		// 3. check if each part is between 0 and 255
		return false;
	}

	public static boolean isTheIPPartOfTheNetwork(IPAddress ip, IPAddress networkIP) {
		return false;
	}

	public static boolean isTheIPAlreadyUsed(IPAddress ip, List<Node> network) {
		return false;
	}

	public static IPAddress generateRandomIP() {
		RandomGenerator rand = RandomGenerator.getDefault();
		String ip = "";

		for (int i = 0; i < 4; i++) {
			ip += rand.nextInt(0, 256);
			ip += ".";
		}

		return new IPAddress(ip.substring(0, ip.length() - 1));
	}

	public static IPAddress generateRandomIPForNode(IPAddress networkIP) {
		RandomGenerator rand = RandomGenerator.getDefault();
		String ip = "";

		for (int nbOfBytes = 0, indexOfIPString = 0; nbOfBytes < 2;) {
			ip += networkIP.getIP().charAt(indexOfIPString++);

			if (networkIP.getIP().charAt(indexOfIPString) == '.')
				nbOfBytes++;
		}

		for (int i = 0; i < 2; i++) {
			ip += rand.nextInt(0, 256);
			ip += ".";
		}

		return new IPAddress(ip.substring(0, ip.length() - 1));
	}
}
