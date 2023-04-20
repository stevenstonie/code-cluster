package com.steven.app.classes;

import java.util.List;
import java.util.ArrayList;

public class Game {
	private int id;
	private String name;
	private List<Game> gamesWithRecurringParticipants;

	public Game(int id, String name) {
		this.id = id;
		this.name = name;
		this.gamesWithRecurringParticipants = new ArrayList<>();
	}

	public int getId() {
		return id;
	}

	public String getName() {
		return name;
	}

	public List<Game> get() {
		return gamesWithRecurringParticipants;
	}

	public void addGameWithRecurringParticipants(Game gameWithRecurringParticipants) {
		this.gamesWithRecurringParticipants.add(gameWithRecurringParticipants);
	}
}
