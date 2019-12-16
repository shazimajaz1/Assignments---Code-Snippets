//Created by Shaim Ajaz
//CSC 20 Finals Project
//Date Last Modified: 04/09/2018
//This class keeps the record for each student's id and score

public class Student {
   
   
   //Behaviors
   private String id;
   private int[] scores;;
   
   //Constructor 1: This creats an object with the id provided as the parameter
   //of the new call and also takes an array of lab scores for the parameter with
   //maximum size of 5.
   public Student(String studentId, int[] labScores) {
      id = studentId;
      setScores(labScores);
      
   }
   //This method return the id
   public String getID() {
      return id;
   }
   
   //This method returns the scores
   public int[] getScores() {
     
      return scores;
   }
   public String toString() {
      return id + " " + scores;
   }
   public void setScores(int[] a) {
      scores = new int[a.length];
      for(int i = 0; i < a.length; i++) {
         scores[i] = a[i];
      }
   }
   
   
   
   
}