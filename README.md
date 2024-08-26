# Comunicación entre Procesos con Pipes en C

Este repositorio contiene un ejemplo sencillo de cómo dos procesos en C pueden comunicarse utilizando pipes (`tuberías`). En este caso, el proceso padre envía mensajes al proceso hijo, y el proceso hijo responde después de procesar el mensaje.

## Descripción del Código

- **Proceso Padre (Emisor):** 
  - Incrementa un valor compartido `i` y envía un mensaje al proceso hijo a través de una tubería.
  - Espera una respuesta del proceso hijo antes de continuar.

- **Proceso Hijo (Receptor):**
  - Recibe el mensaje del proceso padre, lo procesa, y decrementa el valor compartido `i`.
  - Envía una respuesta al proceso padre después de procesar el mensaje.

## Funcionalidad

1. El proceso padre envía un mensaje incrementado hasta que se alcance un valor límite.
2. El proceso hijo recibe el mensaje, lo procesa y envía una respuesta al padre.
3. Ambos procesos utilizan `pipes` para la comunicación y una variable compartida (`i`) para demostrar la interacción.

## Ejecución

Para compilar y ejecutar el programa:

```bash
gcc -o comunicacion_procesos comunicacion_procesos.c
./comunicacion_procesos
