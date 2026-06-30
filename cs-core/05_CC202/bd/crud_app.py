"""
Billetera Digital — Aplicación CRUD de Usuarios
Fase III – Proyecto Formativo Base de Datos (UNI)

Requisitos:
    pip install psycopg2-binary

Uso:
    python crud_app.py
"""

import tkinter as tk
from tkinter import ttk, messagebox
import psycopg2
from psycopg2 import OperationalError, DatabaseError

# ── Configuración de conexión ─────────────────────────────
DB_CONFIG = {
    "host":     "localhost",
    "port":     5432,
    "dbname":   "billetera_digital",
    "user":     "postgres",
    "password": "postgres",
}


def get_connection():
    return psycopg2.connect(**DB_CONFIG)


# ── Aplicación principal ──────────────────────────────────
class EWalletApp(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("Billetera Digital — Gestión de Usuarios")
        self.geometry("980x580")
        self.resizable(True, True)
        self.configure(bg="#f5f5f5")
        self._build_ui()
        self.refresh()

    # ──────────────────────────────────────────────────────
    # Construcción de la interfaz
    # ──────────────────────────────────────────────────────
    def _build_ui(self):
        # ── Título ────────────────────────────────────────
        tk.Label(
            self, text="Billetera Digital — CRUD Usuarios",
            font=("Arial", 14, "bold"), bg="#2196F3", fg="white",
            pady=8
        ).pack(fill="x")

        # ── Panel de formulario ───────────────────────────
        form = tk.LabelFrame(
            self, text="Datos del Usuario",
            font=("Arial", 10, "bold"), bg="#f5f5f5",
            padx=10, pady=8
        )
        form.pack(fill="x", padx=12, pady=(8, 4))

        fields = [
            ("DNI (8 dígitos)",    "dni"),
            ("Nombre",             "nombre"),
            ("Apellido",           "apellido"),
            ("Celular (9 dígitos)","celular"),
            ("Email",              "email"),
        ]
        self.entries: dict[str, tk.Entry] = {}
        for col, (label, key) in enumerate(fields):
            tk.Label(form, text=label, bg="#f5f5f5",
                     font=("Arial", 9)).grid(row=0, column=col * 2,
                                              sticky="e", padx=(6, 2))
            entry = tk.Entry(form, width=17, font=("Arial", 10))
            entry.grid(row=0, column=col * 2 + 1, padx=(0, 8))
            self.entries[key] = entry

        # ── Barra de botones ──────────────────────────────
        bar = tk.Frame(self, bg="#f5f5f5")
        bar.pack(fill="x", padx=12, pady=4)

        btn_cfg = [
            ("Insertar",        "#4CAF50", self.insert_user),
            ("Actualizar",      "#2196F3", self.update_user),
            ("Eliminar",        "#f44336", self.delete_user),
            ("Limpiar campos",  "#9E9E9E", self.clear_fields),
        ]
        for text, color, cmd in btn_cfg:
            tk.Button(
                bar, text=text, bg=color, fg="white",
                font=("Arial", 10, "bold"), relief="flat",
                padx=10, pady=4, cursor="hand2", command=cmd
            ).pack(side="left", padx=4)

        tk.Button(
            bar, text="Actualizar lista", bg="#607D8B", fg="white",
            font=("Arial", 10), relief="flat", padx=10, pady=4,
            cursor="hand2", command=self.refresh
        ).pack(side="right", padx=4)

        # ── Treeview (tabla de usuarios) ──────────────────
        tree_frame = tk.Frame(self, bg="#f5f5f5")
        tree_frame.pack(fill="both", expand=True, padx=12, pady=4)

        cols = ("id", "dni", "nombre", "apellido", "celular", "email",
                "fecha_registro", "estado")
        widths = (45, 85, 110, 110, 95, 190, 100, 80)
        headers = ("ID", "DNI", "Nombre", "Apellido", "Celular",
                   "Email", "Registro", "Estado")

        style = ttk.Style()
        style.configure("Treeview.Heading", font=("Arial", 10, "bold"))
        style.configure("Treeview", font=("Arial", 10), rowheight=24)
        style.map("Treeview", background=[("selected", "#BBDEFB")])

        self.tree = ttk.Treeview(
            tree_frame, columns=cols, show="headings",
            selectmode="browse"
        )
        for col, w, h in zip(cols, widths, headers):
            self.tree.heading(col, text=h)
            self.tree.column(col, width=w, anchor="center")

        vsb = ttk.Scrollbar(tree_frame, orient="vertical",
                             command=self.tree.yview)
        self.tree.configure(yscrollcommand=vsb.set)
        self.tree.pack(side="left", fill="both", expand=True)
        vsb.pack(side="right", fill="y")
        self.tree.bind("<<TreeviewSelect>>", self._on_select)

        # ── Barra de estado ───────────────────────────────
        self.status_var = tk.StringVar(value="Conectando…")
        tk.Label(
            self, textvariable=self.status_var, anchor="w",
            font=("Arial", 9), bg="#ECEFF1", relief="sunken", pady=3
        ).pack(fill="x", padx=12, pady=(0, 6))

    # ──────────────────────────────────────────────────────
    # Helpers
    # ──────────────────────────────────────────────────────
    def _get_fields(self) -> tuple:
        return (
            self.entries["dni"].get().strip(),
            self.entries["nombre"].get().strip(),
            self.entries["apellido"].get().strip(),
            self.entries["celular"].get().strip(),
            self.entries["email"].get().strip(),
        )

    def clear_fields(self):
        for entry in self.entries.values():
            entry.delete(0, "end")

    def _on_select(self, _event):
        sel = self.tree.selection()
        if not sel:
            return
        vals = self.tree.item(sel[0], "values")
        keys = ("dni", "nombre", "apellido", "celular", "email")
        for i, key in enumerate(keys):
            self.entries[key].delete(0, "end")
            self.entries[key].insert(0, vals[i + 1])

    def _set_status(self, msg: str):
        self.status_var.set(f"  {msg}")

    def _selected_id(self) -> int | None:
        sel = self.tree.selection()
        if not sel:
            messagebox.showwarning("Selección requerida",
                                   "Seleccione un usuario en la tabla.")
            return None
        return int(self.tree.item(sel[0], "values")[0])

    # ──────────────────────────────────────────────────────
    # CONSULTA – Listar todos los usuarios
    # ──────────────────────────────────────────────────────
    def refresh(self):
        for row in self.tree.get_children():
            self.tree.delete(row)
        try:
            conn = get_connection()
            cur = conn.cursor()
            cur.execute("""
                SELECT id_usuario, dni, nombre, apellido,
                       celular, email, fecha_registro, estado
                FROM Usuario
                ORDER BY id_usuario
            """)
            rows = cur.fetchall()
            for row in rows:
                self.tree.insert("", "end", values=row)
            cur.close()
            conn.close()
            n = len(rows)
            self._set_status(f"{n} usuario{'s' if n != 1 else ''} cargado{'s' if n != 1 else ''}")
        except OperationalError:
            messagebox.showerror(
                "Error de conexión",
                "No se pudo conectar a PostgreSQL.\n"
                "Verifique que el servidor esté activo y que DB_CONFIG sea correcto."
            )
            self._set_status("Error de conexión")
        except DatabaseError as exc:
            messagebox.showerror("Error de base de datos", str(exc))

    # ──────────────────────────────────────────────────────
    # INSERCIÓN
    # ──────────────────────────────────────────────────────
    def insert_user(self):
        dni, nombre, apellido, celular, email = self._get_fields()
        if not all([dni, nombre, apellido, celular, email]):
            messagebox.showwarning("Campos incompletos",
                                   "Todos los campos son obligatorios.")
            return
        try:
            conn = get_connection()
            cur = conn.cursor()

            # Insertar usuario usando cursor parametrizado
            cur.execute("""
                INSERT INTO Usuario(dni, nombre, apellido, celular, email)
                VALUES (%s, %s, %s, %s, %s)
                RETURNING id_usuario
            """, (dni, nombre, apellido, celular, email))
            nuevo_id = cur.fetchone()[0]

            # Crear billetera inicial con saldo 0
            cur.execute("""
                INSERT INTO Billetera(id_usuario, saldo, moneda,
                                      fecha_creacion, estado)
                VALUES (%s, 0.00, 'PEN', CURRENT_DATE, 'Activa')
            """, (nuevo_id,))

            conn.commit()
            cur.close()
            conn.close()
            self._set_status(
                f"Usuario insertado correctamente (id={nuevo_id}, billetera creada)"
            )
            self.clear_fields()
            self.refresh()
        except DatabaseError as exc:
            messagebox.showerror("Error al insertar", str(exc))

    # ──────────────────────────────────────────────────────
    # ACTUALIZACIÓN
    # ──────────────────────────────────────────────────────
    def update_user(self):
        user_id = self._selected_id()
        if user_id is None:
            return
        _, nombre, apellido, celular, email = self._get_fields()
        if not all([nombre, apellido, celular, email]):
            messagebox.showwarning("Campos incompletos",
                                   "Complete nombre, apellido, celular y email.")
            return
        try:
            conn = get_connection()
            cur = conn.cursor()
            cur.execute("""
                UPDATE Usuario
                SET nombre    = %s,
                    apellido  = %s,
                    celular   = %s,
                    email     = %s
                WHERE id_usuario = %s
            """, (nombre, apellido, celular, email, user_id))
            conn.commit()
            cur.close()
            conn.close()
            self._set_status(f"Usuario id={user_id} actualizado correctamente")
            self.refresh()
        except DatabaseError as exc:
            messagebox.showerror("Error al actualizar", str(exc))

    # ──────────────────────────────────────────────────────
    # ELIMINACIÓN
    # ──────────────────────────────────────────────────────
    def delete_user(self):
        user_id = self._selected_id()
        if user_id is None:
            return
        sel = self.tree.selection()[0]
        vals = self.tree.item(sel, "values")
        nombre_completo = f"{vals[2]} {vals[3]}"

        if not messagebox.askyesno(
            "Confirmar eliminación",
            f"¿Eliminar al usuario '{nombre_completo}' (id={user_id})?\n\n"
            "Esta acción no se puede deshacer.",
            icon="warning"
        ):
            return

        try:
            conn = get_connection()
            cur = conn.cursor()
            cur.execute("DELETE FROM Usuario WHERE id_usuario = %s",
                        (user_id,))
            conn.commit()
            cur.close()
            conn.close()
            self._set_status(f"Usuario id={user_id} eliminado")
            self.clear_fields()
            self.refresh()
        except DatabaseError as exc:
            messagebox.showerror(
                "Error al eliminar",
                str(exc) + "\n\nAsegúrese de eliminar primero los registros "
                "dependientes (billetera, notificaciones, contactos)."
            )


# ── Punto de entrada ──────────────────────────────────────
if __name__ == "__main__":
    app = EWalletApp()
    app.mainloop()
