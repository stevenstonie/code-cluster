package com.stevenstonie.rc;

import com.stevenstonie.rc.classes.Network;
import com.stevenstonie.rc.classes.TokenRing;

public class App {
    public static void main(String... args) {
        Network network = new Network();
        network.addNodes(15);

        // the token ring is initialized
        TokenRing tokenRing = new TokenRing();

        // does the ring have to move constantly around the network?

        // now the problem i havent solved from the start is how to map the token Ring to the network

        // maybe a for loop with an index from on which the position is the token's position in that network

        // so the index will be called posOfToken and depending on the user's choice of the direction the 
        // token is moving, the index will either increment or decrement

        // if yes then create a function (which gets called every 0.5 sec) that will have two instances:
        // 1. the token ring is moving in the background and the user can insert commands
        // 2. the token ring is moving while the command is being executed and the user waits for the command to finish
        // 
    }
}
