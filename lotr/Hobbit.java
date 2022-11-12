/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package lotr;
import java.util.Random;

/**
 *
 * @author 19026013
 */
public class Hobbit extends Entity {
    private int health;
   
    public Hobbit(String name, int health){
        super(name, "#");
        this.health = health;
    }
    
    public int getHealth(){
        return health;
    }
    
    public void setHealth(int newHealth){
        health = newHealth;
    }
     
    @Override
    public void move(int x, int y){
        Random r = new Random();
        int rx = r.nextInt(3);
        int ry = r.nextInt(3);
        
        switch(rx){
            case 1:
                setX(getX()+1);
                break;
            case 2:
                setX(getX()-1);
                break;
        }
        switch(ry){
            case 1:
                setY(getY()+1);
                break;
            case 2:
                setY(getY()-1);
                break;
        }
        health--;
    }
    
    @Override
    public String toString() {
        String s = super.toString() + "\n";
        s+= "health" +  health;
        return s;
    }

}
