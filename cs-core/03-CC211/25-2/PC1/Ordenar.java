class Ordenar {
    int a = 4, b = 7, c = 2, d = 1;
    
    public static void main(String[] args) {
        Ordenar ordenar = new Ordenar();
        
        ordenar.mostrarValoresOriginales();
        ordenar.ordenarAscendente();
        ordenar.mostrarValoresOrdenados();
    }
    
    public void mostrarValoresOriginales() {
        System.out.println("Ordenar valores ascendentemente");
        System.out.println(" a  b  c  d");
        System.out.printf("%2d %2d %2d %2d\n", a, b, c, d);
    }
    
    public void ordenarAscendente() {
        if (a > b) intercambiar("a", "b");
        if (b > c) intercambiar("b", "c");
        if (c > d) intercambiar("c", "d");
        if (a > b) intercambiar("a", "b");
        if (b > c) intercambiar("b", "c");
        if (a > b) intercambiar("a", "b");
    }
    
    private void intercambiar(String var1, String var2) {
        int temp;

        if (var1.equals("a") && var2.equals("b")) {
            temp = a; a = b; b = temp;
        } else if (var1.equals("b") && var2.equals("c")) {
            temp = b; b = c; c = temp;
        } else if (var1.equals("c") && var2.equals("d")) {
            temp = c; c = d; d = temp;
        }
    }
    
    public void mostrarValoresOrdenados() {
        System.out.println("Valores ordenados");
        System.out.println(" a  b  c  d");
        System.out.printf("%2d %2d %2d %2d\n", a, b, c, d);
    }
}
