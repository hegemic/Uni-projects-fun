/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package life;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Scanner;

/**
 *
 * @author p0073862
 */
public class Main {

    /**
     * @param args the command line arguments
     * @throws java.io.FileNotFoundException
     */
    public static void main(String[] args) throws FileNotFoundException {
        Game game = new Game(70,70);
        readFromFile(game, "cells.txt");
        Display display = new Display(game, 10,100);
        display.start();
    }
    
    public static void readFromFile(Game game, String file) throws FileNotFoundException {
        FileInputStream fileIn = new FileInputStream(file);
        Scanner scan = new Scanner(fileIn);
        while(scan.hasNextInt()) {
            int x = scan.nextInt();
            int y = scan.nextInt();
            game.makeCellLive(x, y);
        }
    }
}
