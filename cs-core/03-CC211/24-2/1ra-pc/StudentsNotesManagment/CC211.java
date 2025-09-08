import java.util.Random;
import java.util.Arrays;


class Alumno{
  public int code;
  public String name;
  public int[] practicesScores;
  public int[] calificadaScores;
  public float finalGrade;

  public Alumno(int code, String name){
    this.code = code;
    this.name = name;

    this.practicesScores = new int[5];
    this.calificadaScores = new int[3];
  }

  public void setPractica(int index, int note){
    // TODO: add validations
    this.practicesScores[index] = note;
  }
  public void setExamen(int index, int note){
    // TODO: add validations


    this.calificadaScores[index] = note;
  }

  void setNotaFinal(){
    Arrays.sort(this.practicesScores);
    Arrays.sort(this.calificadaScores);

    float practicesPromedy = (this.practicesScores[1] + this.practicesScores
        [2] + this.practicesScores[3] + this.practicesScores[4])/4;

    this.finalGrade = (practicesPromedy + this.calificadaScores[1] + this.calificadaScores[2])/3;
  }

   public void print() {
        System.out.printf("%-3d %-5s ", code, name);
        for (int i = 0; i < 5; i++) {
            System.out.printf("%2d ", practicesScores[i]);
        }
        for (int i = 0; i < 3; i++) {
            System.out.printf("%2d ", calificadaScores[i]);
        }
        System.out.printf("%2f\n", finalGrade);
    }

  // public void print(){
  //   System.out.println();

  //   System.out.printf(
  //     "Alumno: %s con codigo %d tiene nota final %f", 
  //     this.name, this.code, this.finalGrade
  //   );
    
  //   System.out.println();


  //   System.out.printf("Sus notas de practica fueron %d, %d, %d, %d, %d",
  //     this.practicesScores[0], this.practicesScores[1], this.practicesScores[2],
  //           this.practicesScores[3], this.practicesScores[4]
  //   );

        
  //   System.out.println();

  //   System.out.printf("Sus notas de examen fueron %d, %d, %d",
  //     this.calificadaScores[0], this.calificadaScores[1], this.calificadaScores[2]
  //   );

  //   System.out.println();
  // }

}

public class CC211 {
  public static void main(String[] args){
    var rng = new Random();
    var alumnQuantity = rng.nextInt(10) + 1;

    Alumno[] als = new Alumno[alumnQuantity];

    for (int i = 0;i< alumnQuantity;i++){
        var alumno = new Alumno(i+1,"AL" + (i+1));

        for (int j = 0; j < 5; j++){
          int practiceNote =rng.nextInt(9)+6;
        //  System.out.println(practiceNote);
          alumno.setPractica(j,practiceNote);
        }

        for (int j = 0; j < 3; j++){
          int examGrade = rng.nextInt(9) + 7;
        //  System.out.println(examGrade);
          alumno.setExamen(j, examGrade);
        }

        alumno.setNotaFinal();

       als[i] = alumno; 
      }

    for (int i = 0; i < alumnQuantity;i++){
      var al = als[i];
      al.print();
    }
  }
}
