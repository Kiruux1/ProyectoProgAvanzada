# Proyecto Pipeline ETL en C++: Procesamiento de Datos de Admisión

## 1. Objetivo Principal

Este proyecto implementa un pipeline de Extracción, Transformación y Carga (ETL) en C++. Su finalidad es procesar el archivo `Admission_Predict.csv`, realizar análisis estadísticos sobre los datos y generar archivos de salida en formato de texto y binario. Esta versión opera con el archivo CSV de forma local.

## 2. Flujo de Trabajo del Pipeline

El pipeline ejecuta las siguientes etapas secuencialmente:

### 2.1. Extracción
* El sistema está configurado para acceder al archivo `Admission_Predict.csv` ubicado en el directorio de ejecución.
* El módulo `DataTransformer` se encarga de la lectura del archivo CSV, procesando cada línea y campo delimitado por comas. Se omite la fila de encabezado durante la carga de datos.

### 2.2. Transformación
* Los datos extraídos del CSV son convertidos y almacenados en memoria como un vector de estructuras `Student`, donde cada estructura representa un registro.
* Se presenta un menú interactivo en la consola que permite al usuario solicitar las siguientes operaciones:
    * **Estadísticas Generales:** Muestra el número total de registros y el número de atributos por registro.
    * **Estadísticas Descriptivas:** Calcula y muestra métricas como media, mediana, desviación estándar, mínimo y máximo para las columnas numéricas significativas (`GRE Score`, `TOEFL Score`, `CGPA`, `Chance of Admit`, etc.).
    * **Análisis de Correlación:** Calcula y muestra el coeficiente de correlación de Pearson entre pares de variables predefinidas para identificar relaciones lineales (e.g., `GRE Score` vs. `Chance of Admit`).
* Los resultados de los análisis estadísticos pueden ser exportados.

### 2.3. Carga
El pipeline genera dos tipos de archivos de salida:
* **Informe de Análisis en Texto:** Un archivo (`analysis_report.txt`) que consolida los resultados de las estadísticas generales, descriptivas y el análisis de correlación en un formato legible.
* **Archivo Binario de Datos:** Un archivo (`students.dat`) que almacena los registros de los estudiantes. Este archivo inicia con un encabezado de 32 bits sin signo que indica el número total de registros, seguido por la serialización binaria de cada estructura `Student`.

## 3. Estructura de Archivos del Proyecto

El código fuente está organizado en los siguientes módulos:

* **`Student.h`, `Student.cpp`**:
    * Define la estructura `Student` que modela los datos de cada registro.
    * Implementa operadores para la serialización y deserialización de objetos `Student` hacia/desde flujos binarios.
* **`EnvLoader.h`, `EnvLoader.cpp`**:
    * Proporciona la configuración del sistema, actualmente simplificado para devolver la ruta del archivo CSV local (`Admission_Predict.csv`).
* **`SFTPClient.h`, `SFTPClient.cpp`**:
    * Módulo con funciones stub (vacías) originalmente destinadas a la interacción SFTP. En esta versión local, su funcionalidad de descarga está inactiva.
* **`DataTransformer.h`, `DataTransformer.cpp`**:
    * Responsable de la lectura y el parsing del archivo CSV.
    * Convierte las filas del CSV en objetos `Student`.
    * Incluye manejo básico de errores para formatos de datos incorrectos en el CSV.
* **`AnalysisModule.h`, `AnalysisModule.cpp`**:
    * Contiene la lógica para realizar los cálculos estadísticos: generales, descriptivos (media, mediana, desviación estándar, min, max) y correlación de Pearson.
    * Genera el contenido para el informe de análisis textual.
* **`ConversionModule.h`, `ConversionModule.cpp`**:
    * Gestiona la escritura del vector de objetos `Student` al archivo binario (`students.dat`), incluyendo el encabezado con el conteo de registros.
* **`pipeline.cpp`**:
    * Archivo principal que contiene la función `main`.
    * Orquesta el flujo ETL completo y maneja el menú interactivo para el usuario.
* **`Admission_Predict.csv`**:
    * Archivo de entrada con los datos a procesar. Debe estar en el mismo directorio que el ejecutable.

## 4. Compilación

**Requisitos:**
* Un compilador de C++ que soporte el estándar C++17 (e.g., g++).

**Comando de Compilación (usando g++ en la terminal/shell):**
Para compilar el proyecto, navegue al directorio que contiene todos los archivos fuente (`.cpp` y `.h`) y ejecute el siguiente comando:

```bash
g++ -std=c++17 -o mi_pipeline pipeline.cpp Student.cpp EnvLoader.cpp SFTPClient.cpp DataTransformer.cpp AnalysisModule.cpp ConversionModule.cpp

seguido de ./mi_pipeline