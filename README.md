# C Codes Practice

Monorepo de proyectos en C para practicar y aprender el lenguaje a través de diferentes ejercicios y aplicaciones.

## Estructura

Este repositorio contiene múltiples proyectos independientes, cada uno en su propio directorio:

- **random-walker**: Simulación de camino aleatorio con múltiples agentes que se mueven de forma estocástica por la pantalla.
- **function-plotter**: Graficador de funciones matemáticas que utiliza tinyexpr para evaluar expresiones y renderizarlas en un plano cartesiano.
- **bouncy-ball-animation**: Simulación física de una pelota que rebota con gravedad y trazado de trayectoria.

## Requisitos

Todos los proyectos requieren SDL2 instalado en el sistema:

```bash
# Ubuntu/Debian
sudo apt-get install libsdl2-dev

# Arch Linux
sudo pacman -S sdl2
```

## Compilación

Cada proyecto se compila de forma independiente desde su directorio:

```bash
cd <nombre-proyecto>
gcc -o programa *.c -lSDL2 -lm
```

## Ejecución

Cada proyecto tiene su propia forma de ejecutarse. Consulta los archivos fuente para ver los parámetros específicos de cada uno.
