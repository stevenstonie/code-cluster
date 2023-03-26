package com.stevenstonie.rc.classes;

public class Node {
	private String IP;
	private String name;

	public Node(String IP, String name) {
		this.IP = IP;
		this.name = name;
	}

	public String getIP() {
		return IP;
	}

	public String getName() {
		return name;
	}
}
