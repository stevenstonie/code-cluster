package com.steven.app.classes;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

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
	 * this algorithm descendingly sorts the entries and then 
	 */
	public Set<Game> scheduleMaximumNbOfGamesFor12PM() {
		Set<Game> independentSet = new HashSet<>();
		List<Game> remainingGames = new ArrayList<>(this.games);

		remainingGames.sort((g1, g2) -> Integer.compare(g2.getGamesWithRecurringParticipants().size(),
				g1.getGamesWithRecurringParticipants().size()));

		while (!remainingGames.isEmpty()) {
			Game currentGame = remainingGames.remove(0);
			boolean isIndependent = true;
			for (Game gameAddedToTheSet : independentSet) {
				if (gameAddedToTheSet.getGamesWithRecurringParticipants().contains(currentGame)) {
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

	/*
	 * this algorithm iterates through all the games and for those that are not visited
	 * it adds them to the independent set + marks them and their 'neighbours' as visited
	 */
	public Set<Game> scheduleMaximumNbOfGamesFor12PM_2conflictsEach() {
		Set<Game> independentSet = new HashSet<>();
		Set<Game> visited = new HashSet<>();

		for (Game game : games) {
			if (!visited.contains(game)) {
				independentSet.add(game);
				visited.add(game);
				visited.addAll(game.getGamesWithRecurringParticipants());
			}
		}

		return independentSet;
	}
}
