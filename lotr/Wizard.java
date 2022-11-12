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
public class Wizard extends Entity{
    private int wisdom, age;
    
    public Wizard(String name, int wisdom, int age){
        super(name, "@");
        this.wisdom = wisdom;
        this.age = age;
    }
    
    public Wizard(String name, int age){
        super(name, "@");
        this.age = age;
        wisdom = 100;
    }
    
    public int getWisdom(){
        return wisdom;
    }
    
    public void setWisdom(int newWisdom){
        wisdom = newWisdom;
    }
    
    public int getAge(){
        return age;
    }
    
    public void setAge(int newAge){
        age = newAge;
    }
    
    public void move(){
        Random r = new Random();
        if (age < 100){
            setX(r.nextInt(100));
            setY(r.nextInt(100));
        } else {
            int sign = r.nextInt(2);    // + or - 
            int jump = r.nextInt(6);
            if (sign == 0){
                setX(getX()-jump);
                setY(getY()-jump);
            } else {
                setX(getX()+jump);
                setY(getY()+jump);
            }
        }
    }
    
    @Override
    public String toString(){
        String s = super.toString() + "\n";
        s += "wisdom" + wisdom;
        s += "age" + age;
        return s;
    }
}
