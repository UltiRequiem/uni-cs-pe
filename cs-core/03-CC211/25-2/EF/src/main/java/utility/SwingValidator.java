package utility;

import javax.swing.*;
import javax.swing.text.JTextComponent;

public class SwingValidator {
    
    public boolean isPresent(JTextComponent c, String fieldName) {
        if (c.getText().length() == 0) {
            showMessage(c, fieldName + " es un campo requerido.");
            c.requestFocusInWindow();
            return false;
        }
        
        return true;
    }

    public boolean isInteger(JTextComponent c, String fieldName) {
        try {
            // aqui podriamos utilizar una variable no nombrada
            // dado que este resultado solo es 
            // necesario para comprobar que el texto
            // es un integer, en realidad, no usamos el valor
            // Pero vamos a dejarlo como estaba en el codigo
            // del examen por su recomendacion.
            
            int i = Integer.parseInt(c.getText());
            
            // Como decidi dejar la variable i,
            // aproveche para anadir validaciones,
            // De esta manera, el numero siempre
            // Sera mayor a 0.
            
            if (i <= 0){
                throw new IllegalArgumentException("El numero debe ser mayoy a 0.");
            }
            
            return true;
        } catch (NumberFormatException e) {
            showMessage(c, fieldName + " debe ser entero.");
            c.requestFocusInWindow();
            return false;
        } catch (IllegalArgumentException e){
            showMessage(c, fieldName + " debe ser mayor a 0.");
            c.requestFocusInWindow();
            return false;
        }
    }

    public boolean isDouble(JTextComponent c, String fieldName) {
        try {
            double d = Double.parseDouble(c.getText());
            
            // Validamos al igual que arriba.
            if (d <= 0){
                throw new IllegalArgumentException("El numero debe ser mayoy a 0.");
            }
            
            return true;
        } catch (NumberFormatException e) {
            showMessage(c, fieldName + " debe ser un número válido.");
            c.requestFocusInWindow();
            return false;
        } catch (IllegalArgumentException e){
            showMessage(c, fieldName + " debe ser mayor a 0.");
            c.requestFocusInWindow();
            return false;
        }
    }

    private void showMessage(JTextComponent c, String message) {
        JOptionPane.showMessageDialog(c, message);
    }
}
