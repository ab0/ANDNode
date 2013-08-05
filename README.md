#ANDNode

##Manejador simple de servidores Node.js

ANDNode es un programa completamente portable hecho para desarrolladores, con el fin de encargarse de gestionar los servidores hechos en Node.js, de una forma fácil simple y organizada, para que así los desarrolladores se enfoquen más en su proyecto y menos en comandos de consola.

###Descripción del Proyecto

El proyecto esta creado en lenguaje C++ y compilado con las herramientas de embarcadero (Embarcadero C++ builder XE4+), el proyecto está separado principalmente en las carpetas:

####Código
Esta carpeta contiene el código perteneciente a la aplicación de pruebas y temas carpeta “_” y a al programa en la carpeta “ANDNode”. La carpeta ANDNode. 

####Recursos
Esta carpeta contiene recursos usados en la compilación o creación del programa, cosas como los vectores de los iconos y diseño de la aplicación (*.ai), paleta de colores usada en la aplicación (*.ase, *.apc), archivos de recursos (*.res), y archivos de temas editables (*.style).

###Compilación y ejecución
Se da por hecho que ya se tiene instalada la versión del compilador adecuada, siendo así únicamente se requiere abrir el archivo “ANDNode v0.1.groupproj” en el compilador.

###Información de contacto
Puedes contactarme para cualquier duda, sugerencia, crítica constructiva o reporte de errores al email: [ab0.ednmail.com](mailto:ab0.edn@gmail.com)

##Forma de Uso
La barra de títulos del programa, es la que concentra la funcionalidad de este y se separa en tres secciones, el nombre de la aplicación, el archivo de proyecto que se encuentra abierto y la zona de botones del menú.

###Menú nuevo
En este menú le indicaremos, la carpeta del proyecto, el archivo del js para ejecutar el servidor, y los navegadores que queramos refrescar automáticamente en la vigilancia.

###Menú abrir
En este menú podemos indicar un archivo de proyecto (archivos *.asn), el cual ya contiene todos los datos con los que se ha trabajado. O también podremos introducir la dirección del archivo js con el que se iniciara el servidor.

###Botón guardar
Este botón te guarda un archivo con el estado del programa (carpeta del proyecto, archivo js, navegadores a refrescar, etc), en el archivo nativo del programa (archivo *.asn).

###Menú control
En este menú (aun en aumento), aparece el botón de asociación de archivo, lo cual asocia los archivos *.asn al programa (esto para que los archivos *.asn tengan un icono asociado y se habrán con doble click).

###Menú consola
En este menú (aun en aumento), veremos los botones de guardar consola, que nos guarda los datos de la consola en texto plano y el botón de limpiar consola, que nos borrara los datos que vayan apareciendo en consola (similar al cls de Windows).

###Menú manejo de errores
En este menú (aun en aumento), veremos el botón de vigilancia de errores, cuando este botón este activo/presionado, el programa mantendrá el servidor en marcha aun después de que haya habido un error.

###Botón micro
Reduce la ventana del programa a una versión más manejable e ignorable.

###Botón refrescar servidor
Refresca el servidor, bastante útil para cuando editamos js que tengan que ver con el funcionamiento del servidor.

###Botón vigilar cambios
Cuando este botón está activo/presionado, el programa vigila todos los archivos que estén dentro de la carpeta del proyecto (señalada en el menú nuevo), por si alguno sufre un cambio, refrescar el servidor y la pestaña activa de los navegadores señalados en el menú nuevo.

###Botón iniciar y parar el servidor.

###Puedes ver un video de su funcionamiento en: [http://youtu.be/7XpGaW5qvYA](http://youtu.be/7XpGaW5qvYA)
