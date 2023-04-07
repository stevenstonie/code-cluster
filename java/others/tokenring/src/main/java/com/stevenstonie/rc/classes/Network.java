package com.stevenstonie.rc.classes;

import java.util.List;
import java.util.random.RandomGenerator;
import java.util.LinkedList;

public class Network {
	private List<Node> network;
	private String networkIP;
	private char nameOfLastNode;

	public Network() {
		network = new LinkedList<Node>();

		networkIP = generateRandomIP();

		nameOfLastNode = 'A';
	}

	public void addNodes(int nbOfNodes) {
		while (nameOfLastNode < 'A' + nbOfNodes) {
			String ip = generateRandomIPForNode(networkIP);

			if (Tools.isTheIPValid(ip) // fake verifications
					&& Tools.hasTheIPTheSignatureOfNetwork(ip, networkIP)
					&& !Tools.isTheIPAlreadyUsed(ip, network))
				network.add(new Node(ip, String.valueOf(nameOfLastNode)));

			nameOfLastNode++;
		}
	}

	public List<Node> getNodes() {
		return network;
	}

	public void printAllNodes() {
		for (Node node : network) {
			System.out.println(node.getName() + ": " + node.getIP());
		}
	}

	private String generateRandomIP() {
		RandomGenerator rand = RandomGenerator.getDefault();
		String ip = "";

		for (int i = 0; i < 4; i++) {
			ip += rand.nextInt(0, 256);
			ip += ".";
		}

		return new String(ip.substring(0, ip.length() - 1));
	}

	private String generateRandomIPForNode(String networkIP) {
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
