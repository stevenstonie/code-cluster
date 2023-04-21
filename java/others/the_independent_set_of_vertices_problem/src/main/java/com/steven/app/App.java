package com.steven.app;

import java.util.Set;

import com.steven.app.classes.Game;
import com.steven.app.classes.GamesGraph;
import com.steven.app.classes.Tools;

public class App {
    public static void main(String[] args) {
        GamesGraph allGames = Tools.createGames();

        Tools.addContestantsForTheFirstSubpoint(allGames);

        Set<Game> maxIndependentSet = allGames.scheduleMaximumNbOfGamesFor12PM();

        System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        for (Game game : maxIndependentSet) {
            System.out.println(game.getName());
        }

        allGames = Tools.createGames();

        Tools.addContestantsForTheSecondSubpoint(allGames);

        maxIndependentSet = allGames.scheduleMaximumNbOfGamesFor12PM_2conflictsEach();

        System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        for (Game game : maxIndependentSet) {
            System.out.println(game.getName());
        }
    }
}
