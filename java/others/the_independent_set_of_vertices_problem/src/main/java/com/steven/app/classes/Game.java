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

	public List<Game> getGamesWithRecurringParticipants() {
		return gamesWithRecurringParticipants;
	}

	public String getConflictingGamesToPrint() {
		String conflictingGames = "";

		for (Game game : this.gamesWithRecurringParticipants) {
			conflictingGames += game.getName() + ", ";
		}
		try {
			return conflictingGames.substring(0, conflictingGames.length() - 2);
		} catch (StringIndexOutOfBoundsException e) {
			return "";
		}
	}

	public void addGameWithRecurringParticipants(Game gameWithRecurringParticipants) {
		if (!checkIfTheGamesAlreadyHaveRecurringParticipants(gameWithRecurringParticipants)) {
			this.gamesWithRecurringParticipants.add(gameWithRecurringParticipants);
			gameWithRecurringParticipants.addGameWithRecurringParticipants(this);
		}
	}

	private boolean checkIfTheGamesAlreadyHaveRecurringParticipants(Game gameWithRecurringParticipants) {
		for (Game game : this.gamesWithRecurringParticipants) {
			if (game.getId() == gameWithRecurringParticipants.getId()) {
				return true;
			}
		}
		return false;
	}
}
