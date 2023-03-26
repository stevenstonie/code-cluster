package com.stevenstonie.rc;

import com.stevenstonie.rc.classes.Network;

public class App {
    public static void main(String... args) {
        Network network = new Network();
        network.addNodes(15);

        for (int i = 0; i < network.getNetwork().size(); i++) {
            System.out.println(network.getNetwork().get(i).getIP());
            System.out.println(network.getNetwork().get(i).getName());
            System.out.println();
        }

        // all computers are initialized with a random unique ip address
        // the token ring is initialized

        // does the ring have to move constantly around the network?
        // if yes then create a function (which gets called every 0.5 sec) that will have two instances:
        // 1. the token ring is moving in the background and the user can insert commands
        // 2. the token ring is moving while the command is being executed and the user waits for the command to finish
        // 
    }
}
