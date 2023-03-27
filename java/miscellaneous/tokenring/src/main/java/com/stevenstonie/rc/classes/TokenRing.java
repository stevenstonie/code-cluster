package com.stevenstonie.rc.classes;

import java.util.ArrayList;
import java.util.List;

public class TokenRing {
	private String ipSource;
	private String ipDestination;
	private String message;
	private boolean hasArrivedAtDestination;
	private boolean isOpen;
	private List<String> history;

	public TokenRing(String ipSource, String ipDestination, String message, boolean hasArrivedAtDestination,
			boolean isOpen, List<String> history) {
		this.ipSource = ipSource;
		this.ipDestination = ipDestination;
		this.message = message;
		this.hasArrivedAtDestination = hasArrivedAtDestination;
		this.isOpen = isOpen;
		this.history = history;
	}

	public TokenRing() {
		ipSource = ipDestination = message = null;
		hasArrivedAtDestination = isOpen = true;
		history = new ArrayList<String>();
	}

	public boolean isOpen() {
		return isOpen;
	}

	public void setOpen(boolean isOpen) {
		this.isOpen = isOpen;
	}

	public boolean hasArrivedAtDestination() {
		return hasArrivedAtDestination;
	}

	public void setHasArrivedAtDestination(boolean hasArrivedAtDestination) {
		this.hasArrivedAtDestination = hasArrivedAtDestination;
	}

	public String getIPSource() {
		return ipSource;
	}

	public void setIPSource(String ipSource) {
		this.ipSource = ipSource;
	}

	public String getIPDestination() {
		return ipDestination;
	}

	public void setIPDestination(String ipDestination) {
		this.ipDestination = ipDestination;
	}

	public String getMessage() {
		return message;
	}

	public void setMessage(String message) {
		this.message = message;
	}

	public List<String> getHistory() {
		return history;
	}

	public void resetHistory() {
		this.history = null;
	}

	public void addToHistory(String lastIPVisited) {
		this.history.add(lastIPVisited);
	}
}
