class A {
    public A() {
        System.out.println("Constructor A");
        metodoA();
    }

    public void metodoA() {
        System.out.println("Método de la clase A");
    }
}

class AA extends A {
    public AA() {
        System.out.println("Constructor AA");
        metodoAA();
    }

    public void metodoAA() {
        System.out.println("Método de la clase AA");
    }
}

class AAA extends AA {
    public AAA() {
        System.out.println("Constructor AAA");
        metodoAAA();
    }

    public void metodoAAA() {
        System.out.println("Método de la clase AAA");
    }
}

public class Test {
    public static void main(String[] _args) {
        // Crear una nueva instancia ejecutara el constructor de AAA,
        // Que a su vez ejecutara los constructores superiores.
        // Orden de impresion: A, AA y finalmente AAA.
        new AAA();
    }
}
