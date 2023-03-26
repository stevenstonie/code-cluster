package com.stevenstonie.rc.classes;

import java.util.ArrayList;
import java.util.List;

public class TokenRing {
	private String ipSource;
	private String ipDestination;
	private String sentMessage;
	private Boolean hasArrivedAtDestination;
	private Boolean isOpen;
	private List<String> history;

	public TokenRing(String ipSource, String ipDestination, String sentMessage, Boolean hasArrivedAtDestination,
			Boolean isOpen, List<String> history) {
		this.ipSource = ipSource;
		this.ipDestination = ipDestination;
		this.sentMessage = sentMessage;
		this.hasArrivedAtDestination = hasArrivedAtDestination;
		this.isOpen = isOpen;
		this.history = history;
	}

	public TokenRing() {
		ipSource = ipDestination = sentMessage = null;
		hasArrivedAtDestination = isOpen = null;
		history = new ArrayList<String>();
	}
}
