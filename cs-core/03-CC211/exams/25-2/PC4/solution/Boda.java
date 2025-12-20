import java.util.GregorianCalendar;
import java.util.Calendar;
import java.util.Date;
import java.text.DateFormat;
import java.text.SimpleDateFormat;

public class Boda {
    static Date date;
    static SimpleDateFormat df = new SimpleDateFormat("d MMM. yyyy");

    public static void main(String[] args) {
        var ella = new GregorianCalendar(2001, 1, 14);  
        var yo = new GregorianCalendar(2000, 10, 15);

        System.out.println("Fechas de nacimientos");
        prin(ella, "Ella: ");
        prin(yo, "Yo  : ");

        System.out.println("\nFechas de cumpleaños");
        ella.set(Calendar.YEAR, 2025);
        yo.set(Calendar.YEAR, 2025);
        prin(ella, "Ella: ");
        prin(yo, "Yo  : ");

        var diaEllaDelAno = ella.get(Calendar.DAY_OF_YEAR);
        var diaYoDelAno = yo.get(Calendar.DAY_OF_YEAR);
        var medio = (diaEllaDelAno + diaYoDelAno) / 2;

        GregorianCalendar boda = new GregorianCalendar(2025, 0, 1);
        boda.set(Calendar.DAY_OF_YEAR, medio);

        System.out.println("\nFecha de Boda");
        prin(boda, "Boda: ");
    }

    static void prin(GregorianCalendar gc, String mensaje) {
        date = gc.getTime();
        System.out.println(mensaje + df.format(date));
    }
}
