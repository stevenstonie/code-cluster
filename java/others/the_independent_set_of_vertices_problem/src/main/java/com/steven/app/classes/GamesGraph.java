package com.steven.app.classes;

import java.util.ArrayList;
import java.util.List;

public class GamesGraph {
	private List<Game> games;

	public GamesGraph(List<Game> games) {
		this.games = games;
	}

	public List<Game> getGames() {
		return games;
	}

	public void addGame(Game game) {
		games.add(game);
	}

	/*
	
	 */
	public List<Game> scheduleMaximumNbOfGamesFor12PM() {
		List<Game> independentSet = new ArrayList<>();
		List<Game> remainingGames = new ArrayList<>(this.games);

		remainingGames.sort((g1, g2) -> Integer.compare(g2.getGamesWithRecurringParticipants().size(),
				g1.getGamesWithRecurringParticipants().size()));

		while (!remainingGames.isEmpty()) {
			Game currentGame = remainingGames.remove(0);
			boolean isIndependent = true;
			for (Game independentGame : independentSet) {
				if (independentGame.getGamesWithRecurringParticipants().contains(currentGame)) {
					isIndependent = false;
					break;
				}
			}
			if (isIndependent) {
				independentSet.add(currentGame);
			}
		}

		return independentSet;
	}
}
