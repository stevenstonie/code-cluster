package com.stevenstonie.rc.classes;

import java.util.ArrayList;
import java.util.List;

public class TokenRing {
	private String ipSource;
	private String ipDestination;
	private String sentMessage;
	private boolean hasArrivedAtDestination;
	private boolean open;
	private List<String> history;

	public TokenRing(String ipSource, String ipDestination, String sentMessage, boolean hasArrivedAtDestination,
			boolean open, List<String> history) {
		this.ipSource = ipSource;
		this.ipDestination = ipDestination;
		this.sentMessage = sentMessage;
		this.hasArrivedAtDestination = hasArrivedAtDestination;
		this.open = open;
		this.history = history;
	}

	public TokenRing() {
		ipSource = ipDestination = sentMessage = null;
		hasArrivedAtDestination = open = false;
		history = new ArrayList<String>();
	}

	public boolean isOpen() {
		return open;
	}

	public void setOpen(boolean open) {
		this.open = open;
	}
}
