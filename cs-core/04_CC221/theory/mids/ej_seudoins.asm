        .data
nums:       .float 551845.8931, 725234.4311, 9526400.2176, 2221775.1796, 1011333.7743, 9990111.6677
count:      .word 6
msgMax:     .asciiz "El número mayor del listado es: "
msgMin:     .asciiz "\nEl número menor del listado es: "

        .text
        .globl main
main:
        # --- Inicializar max y min con el primer elemento ---
        la      $t0, nums        # $t0 apunta al inicio de nums
        l.s     $f2, 0($t0)      # $f2 = max
        l.s     $f4, 0($t0)      # $f4 = min

        li      $t1, 1           # índice = 1
        lw      $t2, count       # $t2 = número de elementos

loop:
        bge     $t1, $t2, imprimir  # si índice >= count, saltar a imprimir
        sll     $t3, $t1, 2         # offset = índice * 4 bytes
        l.s     $f6, 0($t0,$t3)     # carga nums[indice] en $f6

        # comparar $f6 con max ($f2)
        c.lt.s  $f2, $f6            # ¿max < actual?
        bc1t    actualizar_max

        # comparar $f6 con min ($f4)
        c.lt.s  $f6, $f4            # ¿actual < min?
