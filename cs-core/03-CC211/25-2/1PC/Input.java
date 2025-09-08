import java.util.Scanner;  

class Input {
  public static void main(String[] args) {
    Scanner myObj = new Scanner(System.in);

    System.out.println("Enter username");

    var userName = myObj.nextLine();  
    System.out.println("Username is: " + userName);  

    myObj.close();
  }
}
