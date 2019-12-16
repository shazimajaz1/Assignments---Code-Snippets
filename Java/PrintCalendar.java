//Print Calendar of the Requested Year //
//Or the current Year according to com-//
//-ter's date.                         //
//Created By: Shazim Ajaz              //
//Date Created: Feb 14, 2018           //
import java.util.*;
public class PrintCalendar {
   public static void main(String[] args) {
      int year = 0;
      int month = 0; 
      //Read a year:
      if(args.length == 0) {
         year = Calendar.getInstance().get(Calendar.YEAR);
         month = Calendar.getInstance().get(Calendar.MONTH);
      }   
      else
         year = Integer.parseInt(args[0]);
      print(year, month);
   }
   //Print Calendar of the Year
   public static void print(int year, int month) {
      int numOfDays;
      boolean leap = false;
      //Label the year
      System.out.printf("%12d", year);
      if(year % 1000 == 0) {
         if(year % 400 == 0) {
            System.out.printf("%12s","(Leap Year)");
            leap = true;
         }
      } else if(year % 4 == 0) {
         System.out.printf("%12s","(Leap Year)");
         leap = true;
      }
      System.out.println();
      //Repeat 12 Times
      for(int rep = 1; rep <= 12; rep++) {
         //Determine number of days and print months and week day names
         if(rep == month) System.out.println("----------------------");
         numOfDays = printMonth(rep);
         //Position the First Day:
         printDays(year, rep, numOfDays, leap);
         System.out.println();
         if(rep == month) System.out.println("----------------------");
      }       
  }
   //helps the printCalendar Method
   public static int printMonth(int number) {
      //Figure out the first day of the months
      
      int days = 0;
      switch(number) {
         case 1: days = 31;
            System.out.printf("%13s\n", "Januray");
            break;
         case 2: days = 28;
            System.out.printf("%13s\n", "February");
            break;
         case 3: days = 31;
            System.out.printf("%13s\n", " March");
            break;
         case 4: days = 30;
            System.out.printf("%13s\n", " April");
            break;
         case 5: days = 31;
            System.out.printf("%13s\n", " May");
            break;
         case 6: days = 30;
            System.out.printf("%13s\n", " June");
            break;
         case 7: days = 31;
            System.out.printf("%13s\n", " July");
            break;
         case 8: days = 31;
            System.out.printf("%13s\n", " August");
            break;
         case 9: days = 30;
            System.out.printf("%13s\n", "September");
            break;
         case 10: days = 31;
            System.out.printf("%13s\n", " October");
            break;
         case 11: days = 30;
            System.out.printf("%13s\n", " November");
            break;
         case 12: days = 31;
            System.out.printf("%13s\n", " December");
            break; 
      }
      System.out.println();
      System.out.printf("%4s", "  S  M  T  W  T  F  S");
      System.out.println();
      return days;
   }
   //This method operates with the loop above and prints out days
   //of the month with year, rep and days as paramenters.
   public static void printDays(int year, int rep, int days, boolean leap) {
      JulianDate jD = new JulianDate();
      int date = jD.toJulian(year, rep, 1);
      int dayOfWeek = (date+1)%7; // 0 means sunday, 1 means monday and so on.
      int counter = 1;
      while(counter <= days) {
         
         if(counter == 1) {
         for(int p = 0; p <= dayOfWeek - 1; p++)
            System.out.printf("%3s", "");
         }
         System.out.printf("%3d", counter );
         if(counter == 7 - dayOfWeek || counter == 14 - dayOfWeek || counter == 21 - dayOfWeek || counter == 28 - dayOfWeek || counter == 35 - dayOfWeek)
            System.out.println();
         counter++;
         //This makes sure that feburary prints 29 days in case of leap year and 28 otherwise.
         if(counter == 28 && rep == 2 && leap) {
            days++;
         }
      }
      
   }
}