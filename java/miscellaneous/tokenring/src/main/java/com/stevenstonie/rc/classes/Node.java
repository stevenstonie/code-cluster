package com.stevenstonie.rc.classes;

public class Node {
	private IPAddress IP;
	private String name;

	public Node(String IP = -1) {
		generateRandomIP();
	}

	private void generateRandomIP() {
		// randomly generate an IP adress

		// while it is already in use, generate a new one
	}
}
