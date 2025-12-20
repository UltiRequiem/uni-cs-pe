package uni.examen;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import utility.SwingValidator;

public class DeporteApp extends JFrame {
    
    // Nombre del alumno
    private JTextField txtAlumno; 
    // Los 3 saltos del alumno
    private JTextField txtSalto1;
    private JTextField txtSalto2;
    private JTextField txtSalto3;
    
    // Boton para registar un registro
    private JButton btnRegistrar;
    
    // Tabla con todos los registros
    private JTable taCompetencia;
    
    private DefaultTableModel tableModel;
    // Boton para calcular las estadisticas
    private JButton btnEstadisticas;
    // Area que displaya las estadisticas
    private JTextArea taEstadistica;
    
    private final SwingValidator validator;
    
    private final static String appName = "Salto Largo";

    public DeporteApp() {
        validator = new SwingValidator();
        
        initComponents();
        
        setTitle(appName);
        
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(600, 500);
        setLocationRelativeTo(null);
    }

    private void initComponents() {
        setLayout(new BorderLayout(10, 10));

        var panelEntrada = new JPanel(new GridBagLayout());
        
        panelEntrada.setBorder(BorderFactory.createTitledBorder("Registro de Salto Largo"));
        
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 5, 5, 5);
        gbc.fill = GridBagConstraints.HORIZONTAL;

        // Fila 1: Alumno
        gbc.gridx = 0;
        gbc.gridy = 0;
        panelEntrada.add(new JLabel("Alumno:"), gbc);
        
        gbc.gridx = 1;
        gbc.gridwidth = 3;
        txtAlumno = new JTextField(20);
        panelEntrada.add(txtAlumno, gbc);

        // Fila 2 Saltos
        gbc.gridwidth = 1;
        gbc.gridy = 1;
        
        gbc.gridx = 0;
        panelEntrada.add(new JLabel("Salto 1:"), gbc);
        gbc.gridx = 1;
        txtSalto1 = new JTextField(5);
        panelEntrada.add(txtSalto1, gbc);

        gbc.gridx = 2;
        panelEntrada.add(new JLabel("Salto 2:"), gbc);
        gbc.gridx = 3;
        txtSalto2 = new JTextField(5);
        panelEntrada.add(txtSalto2, gbc);

        gbc.gridx = 4;
        panelEntrada.add(new JLabel("Salto 3:"), gbc);
        gbc.gridx = 5;
        txtSalto3 = new JTextField(5);
        panelEntrada.add(txtSalto3, gbc);

        // Fila 3 Botón Registrar
        gbc.gridx = 0;
        gbc.gridy = 2;
        gbc.gridwidth = 6;
        gbc.fill = GridBagConstraints.NONE;
        gbc.anchor = GridBagConstraints.CENTER;
        btnRegistrar = new JButton("Registrar");
        panelEntrada.add(btnRegistrar, gbc);

        add(panelEntrada, BorderLayout.NORTH);

        // Panel central Tabla de competencia
        // aqui se displayaran nuestros registros
        String[] columnas = {"Alumno", "Salto 1", "Salto 2", "Salto 3"};
        tableModel = new DefaultTableModel(columnas, 0);
        taCompetencia = new JTable(tableModel);
        
        JScrollPane scrollTabla = new JScrollPane(taCompetencia);
        scrollTabla.setBorder(BorderFactory.createTitledBorder("Competencia"));
        add(scrollTabla, BorderLayout.CENTER);

        // Aqui daremos un resumen de las estadisticas
        JPanel panelEstadisticas = new JPanel(new BorderLayout(5, 5));
        panelEstadisticas.setBorder(BorderFactory.createTitledBorder("Estadísticas"));
        
        btnEstadisticas = new JButton("Estadísticas");
        panelEstadisticas.add(btnEstadisticas, BorderLayout.NORTH);
        
        taEstadistica = new JTextArea(6, 40);
        taEstadistica.setLineWrap(true);
        taEstadistica.setWrapStyleWord(true);
        taEstadistica.setEditable(false);
        JScrollPane scrollEstadistica = new JScrollPane(taEstadistica);
        panelEstadisticas.add(scrollEstadistica, BorderLayout.CENTER);

        add(panelEstadisticas, BorderLayout.SOUTH);

        // Utilizando lambdas por legibilidad
        btnRegistrar.addActionListener(e -> registrar());
        btnEstadisticas.addActionListener(e -> calcularEstadisticas());
    }

    private void registrar() {
        if (!validator.isPresent(txtAlumno, "Alumno")) return;
        if (!validator.isInteger(txtSalto1, "Salto 1")) return;
        if (!validator.isInteger(txtSalto2, "Salto 2")) return;
        if (!validator.isInteger(txtSalto3, "Salto 3")) return;

        var alumno = txtAlumno.getText();
        var salto1 = txtSalto1.getText();
        var salto2 = txtSalto2.getText();
        var salto3 = txtSalto3.getText();

        Object[] fila = {alumno, salto1, salto2, salto3};
        tableModel.addRow(fila);

        txtAlumno.setText("");
        txtSalto1.setText("");
        txtSalto2.setText("");
        txtSalto3.setText("");
        txtAlumno.requestFocusInWindow();
    }

    
    private void calcularEstadisticas() {
        var filas = tableModel.getRowCount();
        
        if (filas == 0) {
            taEstadistica.setText("No hay datos registrados.");
            return;
        }

        var saltoMaximo = Integer.MIN_VALUE;
        var saltoMinimo = Integer.MAX_VALUE;
        
        var mejorAtleta = "";
        var mejorSaltoAtleta = 0;
        var sumaTotalSaltos = 0;
        var totalSaltos = 0;

        var sb = new StringBuilder();

        // Generar reportes con matematica
        for (int i = 0; i < filas; i++) {
            var alumno = (String) tableModel.getValueAt(i, 0);
            var s1 = Integer.parseInt((String) tableModel.getValueAt(i, 1));
            var s2 = Integer.parseInt((String) tableModel.getValueAt(i, 2));
            var s3 = Integer.parseInt((String) tableModel.getValueAt(i, 3));

            // Mejor salto de este atleta
            int mejorDelAtleta = Math.max(s1, Math.max(s2, s3));
            
            // Promedio de este atleta
            double promedioAtleta = (s1 + s2 + s3) / 3.0;
            
            sb.append("Atleta: ").append(alumno).append("\n");
            sb.append("  Mejor salto: ").append(mejorDelAtleta).append(" cm\n");
            sb.append("  Promedio: ").append(String.format("%.2f", promedioAtleta)).append(" cm\n\n");

            // Actualizar máximo global
            if (s1 > saltoMaximo) saltoMaximo = s1;
            if (s2 > saltoMaximo) saltoMaximo = s2;
            if (s3 > saltoMaximo) saltoMaximo = s3;

            // Actualizar mínimo global
            if (s1 < saltoMinimo) saltoMinimo = s1;
            if (s2 < saltoMinimo) saltoMinimo = s2;
            if (s3 < saltoMinimo) saltoMinimo = s3;

            // mejor atleta
            if (mejorDelAtleta > mejorSaltoAtleta) {
                mejorSaltoAtleta = mejorDelAtleta;
                mejorAtleta = alumno;
            }

            sumaTotalSaltos += s1 + s2 + s3;
            totalSaltos += 3;
        }

        double promedioGeneral = (double) sumaTotalSaltos / totalSaltos;

        sb.append("Total participantes: ").append(filas).append("\n");
        sb.append("Salto máximo: ").append(saltoMaximo).append(" cm\n");
        sb.append("Salto mínimo: ").append(saltoMinimo).append(" cm\n");
        sb.append("Promedio general: ").append(String.format("%.2f", promedioGeneral)).append(" cm\n");
        sb.append("Ganador(a): ").append(mejorAtleta).append(" con ").append(mejorSaltoAtleta).append(" cm.");

        taEstadistica.setText(sb.toString());
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
           var app = new DeporteApp();
           
           app.setVisible(true);
        });
    }
}
