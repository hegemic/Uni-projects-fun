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
public class World {
    private ArrayList <Entity> entities;
    private String name;
    
    public World(String name){
        this.name = name;
        entities = new ArrayList<>();
    }
    
    public void addEntity(Entity e){
        entities(e);
    }
}
