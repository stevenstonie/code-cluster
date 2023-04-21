package com.steven.app;

import java.util.List;
import java.util.Set;

import com.steven.app.classes.Game;
import com.steven.app.classes.GamesGraph;
import com.steven.app.classes.Tools;

public class App {
    public static void main(String[] args) {
        subpoint1();

        subpoint2();
    }

    private static void subpoint1() {
        System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        GamesGraph allGames = Tools.createGames();

        Tools.addContestantsForTheFirstSubpoint(allGames);

        List<Game> maxIndependentSet = allGames.scheduleMaximumNbOfGamesFor12PM();

        System.out.println("for the games: ");
        for (Game game : allGames.getGames()) {
            System.out.println(game.getName() + " (" + game.getConflictingGamesToPrint() + ")");
        }

        System.out.println("the scheduled ones are:");
        for (Game game : maxIndependentSet) {
            System.out.println(game.getName());
        }
    }

    private static void subpoint2() {
        System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        GamesGraph allGames = Tools.createGames();

        Tools.addContestantsForTheSecondSubpoint(allGames);

        List<Game> maxIndependentSet = allGames.scheduleMaximumNbOfGamesFor12PM_2conflictsEach();

        System.out.println("for the games: ");
        for (Game game : allGames.getGames()) {
            System.out.println(game.getName() + " (" + game.getConflictingGamesToPrint() + ")");
        }

        System.out.println("the scheduled ones are:");
        for (Game game : maxIndependentSet) {
            System.out.println(game.getName());
        }
    }
}
