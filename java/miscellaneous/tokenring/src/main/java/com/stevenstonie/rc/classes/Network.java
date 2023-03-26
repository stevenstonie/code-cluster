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
		for (; nameOfLastNode < 'A' + nbOfNodes; nameOfLastNode++) {
			// create a random ip address for the node
			String ip = Tools.generateRandomIPForNode(networkIP);

			if (Tools.isTheIPValid(ip) // fake verifications
					&& Tools.isTheIPPartOfTheNetwork(ip, networkIP)
					&& !Tools.isTheIPAlreadyUsed(ip, network))
				network.add(new Node(ip, String.valueOf(nameOfLastNode)));
		}
	}

	public List<Node> getNetwork() {
		return network;
	}
}
