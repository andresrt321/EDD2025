Descripción Extendida 
Título Sugerido: Proyecto EDD2025: Sistema de Gestión de Pasajeros con Listas Enlazadas Dinámicas ✈️
Este proyecto es una implementación en lenguaje C para el curso de Estructuras de Datos, que simula el sistema de venta y abordaje de tiquetes de una aerolínea. El objetivo principal es demostrar la comprensión y aplicación del manejo de memoria dinámica (malloc y free) y la manipulación de Listas Enlazadas Simples.

Detalles Técnicos Clave
Estructura de Datos: Se utiliza una Lista Enlazada Simple para almacenar la información de cada pasajero como un nodo. Esta estructura fue seleccionada por su eficiencia al manejar un número variable e impredecible de registros, a diferencia de los arreglos estáticos.

Asignación de Memoria: Cada registro se crea de forma dinámica (malloc), optimizando el uso de la memoria del sistema.

Principio FIFO: La función de inserción (agregarPasajero) garantiza que los nuevos nodos se añadan al final de la lista, manteniendo el orden estricto de "Primero en registrarse, primero en abordar."

Liberación Responsable: El programa incluye una función crítica (liberarMemoria) que recorre toda la lista antes de finalizar para asegurar que cada bloque de memoria asignado con malloc sea liberado con free, previniendo fugas de memoria.

Lógica de la Aerolínea
La simulación incorpora una lógica de negocio fundamental en el sector de la aviación:

Implementación de Overbooking: Se permite la venta de un 10% adicional sobre la capacidad real del avión. Esta capacidad máxima de venta es el límite para la inserción de nodos en la lista.

Simulación de Abordaje: Durante el proceso de abordaje, la lista se recorre, pero solo se permite el acceso a un número de pasajeros igual a la capacidad real del avión, demostrando el efecto y el reporte del overbooking.
