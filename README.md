# POO-26-PDs

Repositorio oficial para actividades individuales de la asignatura **Programación Orientada a Objetos**.

Este curso está dirigido a estudiantes de **tercer semestre de Ingeniería en Software**, con antecedentes en algoritmia, lógica computacional básica y programación estructurada.

## Tarea de Programación 1

**Título:** Stands - Listas Simplemente Ligadas  
**Deadline:** TBD  
**Modalidad:** Individual

### Objetivos

- Verificar conocimientos previos de programación estructurada en C.
- Promover el uso de apuntadores y memoria dinámica.
- Introducir el uso de repositorios en GitHub para envío de tareas.
- Promover comunicación técnica al explicar el código desarrollado.

### Contexto

Una compañía necesita un sistema para vender stands en una Feria de Libros (FILEY App).

Se debe construir una lista simplemente ligada ordenada para administrar los stands.

### Datos de la estructura `Stand`

- Número de stand
- Ancho del stand (metros)
- Largo del stand (metros)
- Estado del stand (`Disponible`, `Reservado`, `Vendido`)

> El criterio de ordenamiento de la lista será por **área** del stand (`ancho x largo`).

### Operaciones mínimas requeridas

- Insertar stand
- Borrar stand
- Actualizar stand
- Buscar stand
- Imprimir lista completa

### Requisitos de implementación

- Lenguaje C.
- Usar apuntadores y memoria dinámica.
- Mantener modularidad y responsabilidad única por función.
- Incluir comentarios para mejorar legibilidad.
- Probar el comportamiento en `main` con un bloque de simulación tipo pruebas unitarias.

### Código base incluido en este repositorio

- `src/stand.h`: estructura `Stand`, enum de estado y prototipos de funciones.
- `src/stand.c`: implementación base de operaciones de lista simplemente ligada.
- `src/main.c`: bloque de pruebas para insertar, buscar, actualizar, borrar e imprimir.
- `Makefile`: compilación y ejecución rápida.

## Compilación y ejecución

```bash
make
make run
```

## Entregables para estudiantes

Cada estudiante debe trabajar en su repositorio personal (clon o fork, según acuerdo con el docente) y entregar:

1. Código fuente funcional con las operaciones solicitadas.
2. Documentación mínima en Markdown (por ejemplo, descripción del diseño y decisiones).
3. Sección **Video** en el README con la URL del video donde:
   - Explica el código construido.
   - Muestra la ejecución final del bloque de pruebas.

### Plantilla sugerida para sección Video

```md
## Video
- URL: https://...
```

## Opciones de mejora sugeridas

- Definir rúbrica de evaluación con porcentajes (correctitud, legibilidad, uso de memoria dinámica, explicación técnica).
- Agregar casos límite obligatorios (lista vacía, elemento duplicado, actualización de stand inexistente).
- Incluir una segunda versión opcional con ordenamiento por número de stand para comparar decisiones de diseño.
