package com.stevenstonie.rc.classes;

import java.util.List;
import java.util.LinkedList;

public class Network {
	private List<Node> network;
	private String networkIP;
	private char nameOfLastNode;

	public Network() {
		network = new LinkedList<Node>();

		networkIP = Tools.generateRandomIP();

		nameOfLastNode = 'A';
	}

	public void addNodes(int nbOfNodes) {
		while (nameOfLastNode < 'A' + nbOfNodes) {
			String ip = Tools.generateRandomIPForNode(networkIP);

			if (Tools.isTheIPValid(ip) // fake verifications
					&& Tools.hasTheIPTheSignatureOfNetwork(ip, networkIP)
					&& !Tools.isTheIPAlreadyUsed(ip, network))
				network.add(new Node(ip, String.valueOf(nameOfLastNode)));

			nameOfLastNode++;
		}
	}

	public List<Node> getNetwork() {
		return network;
	}

	public void printAllNodes() {
		for (Node node : network) {
			System.out.println(node.getName() + ": " + node.getIP());
		}
	}
}
