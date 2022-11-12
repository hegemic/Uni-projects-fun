package lotr;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author 19026013
 */
public abstract class Entity {
    private String name;
    private String symbol;
    private int x,y;
    //private World w;
    public Entity(String name, String symbol){
        this.name = name;
        this.symbol = symbol;
    }
    //getters and setters
     public int getX(){
        return x;
    }

    public void setX(int xPosition){
        x = xPosition;
    }

    public int getY(){
        return y;
    }

    public void setY(int yPosition){
        y = yPosition;
    }

    public String getName(){
        return name;
    }

    public void setName(String name){
        this.name = name;
    }
    
    public abstract void move();
    
    @Override
    public String toString() {
        return name + " " + symbol + " " + "x" + x + "y" + y;   
    }

}
