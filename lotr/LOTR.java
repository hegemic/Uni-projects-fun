/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package lotr;

/**
 *
 * @author 19026013
 */
public class LOTR {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        Entity e = new Hobbit("Bilbo", 200);
        
        e.setX(20);
        e.setY(30);
        //System.out.println(e.getName() + e.getX() + e.getY());
        System.out.println(e.toString());
    }
    
}
