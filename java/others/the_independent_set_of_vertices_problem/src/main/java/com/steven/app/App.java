package com.steven.app;

import java.util.Set;

import com.steven.app.classes.Game;
import com.steven.app.classes.GamesGraph;
import com.steven.app.classes.Tools;

public class App {
    public static void main(String[] args) {
        GamesGraph allGames = Tools.createGames();

        addContestantsForTheFirstSubpoint(allGames);

        Set<Game> maxIndependentSet = allGames.scheduleMaximumNbOfGamesFor12PM();

        System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        for (Game game : maxIndependentSet) {
            System.out.println(game.getName());
        }

        allGames = Tools.createGames();

        addContestantsForTheSecondSubpoint(allGames);

        maxIndependentSet = allGames.scheduleMaximumNbOfGamesFor12PM_2conflictsEach();

        System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        for (Game game : maxIndependentSet) {
            System.out.println(game.getName());
        }
    }

    private static void addContestantsForTheFirstSubpoint(GamesGraph allGames) {
        allGames.getGame(0).addGameWithRecurringParticipants(allGames.getGame(1));
        allGames.getGame(0).addGameWithRecurringParticipants(allGames.getGame(2));
        allGames.getGame(0).addGameWithRecurringParticipants(allGames.getGame(3));
        allGames.getGame(1).addGameWithRecurringParticipants(allGames.getGame(3));
        allGames.getGame(4).addGameWithRecurringParticipants(allGames.getGame(5));
    }

    private static void addContestantsForTheSecondSubpoint(GamesGraph allGames) {
        allGames.getGame(0).addGameWithRecurringParticipants(allGames.getGame(1));
        allGames.getGame(1).addGameWithRecurringParticipants(allGames.getGame(2));
        allGames.getGame(2).addGameWithRecurringParticipants(allGames.getGame(3));
        allGames.getGame(3).addGameWithRecurringParticipants(allGames.getGame(1));
        allGames.getGame(4).addGameWithRecurringParticipants(allGames.getGame(5));
        allGames.getGame(5).addGameWithRecurringParticipants(allGames.getGame(6));
        allGames.getGame(6).addGameWithRecurringParticipants(allGames.getGame(4));
    }
}
