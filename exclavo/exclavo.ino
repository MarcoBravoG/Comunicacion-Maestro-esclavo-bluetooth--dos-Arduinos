// Comunicacion bluetooth (Maestro).
// www.Cambatronics.com
// soporte@cambatronics.com

#include <SoftwareSerial.h>
SoftwareSerial puertoAT09(3, 4);                                          // RX, TX para el puerto virual para la comunicacion con el bluetooth.  
String trama;
String leerString = String(30);                                           // Variable donde guardaremos las tramas recibidas.
String control;
long auxTiempo=0;                                                         // Variable usada `para controlar el tiempo de reseteo de la trama.
int tiempoCiclo=1000;                                                     // Tiempo en msegundos en el que reseteara la trama.  
const int ledRojo = 8;
const int ledNaranja = 9;
const int ledAmarillo = 10;
const int ledVerde = 11;
const int ledAzul = 12;
const int ledBlanco = 13;

void setup() {
 pinMode(ledRojo, OUTPUT);                                               // LedRojo como salida.
 digitalWrite(ledRojo, LOW);                                             // Apagamos led rojo.
 pinMode(ledNaranja, OUTPUT);                                                        
 digitalWrite(ledNaranja, LOW);                                                                  
 pinMode(ledAmarillo, OUTPUT);                                                                   
 digitalWrite(ledAmarillo, LOW);                                                                   
 pinMode(ledVerde, OUTPUT);                                                                   
 digitalWrite(ledVerde, LOW);                                                                     
 pinMode(ledAzul, OUTPUT);                                                                    
 digitalWrite(ledAzul, LOW);                                                                      
 pinMode(ledBlanco, OUTPUT);                                                                    
 digitalWrite(ledBlanco, LOW);                                                                      
 trama = String("Prueba de funcionamiento");                          
 Serial.begin(9600);                                                     // Iniciamos puerto serie a 9600 bps.
 puertoAT09.begin(9600);                                                 // Iniciamos puerto donde conectamos el bluetooth  a 9600 bps.
 leerString ="";                                                         // Borramos el strings de recepcion de datos.
}

void loop() {
                                               
chequearPuerto();                                                        // Verificamos si llega algun dato al puerto serie del bluetooth.
}

void chequearPuerto () {
auxTiempo=millis();                                                     // Usamos millis para resetear una trama si no se cierra correctamente.       
if ( puertoAT09.available() > 0) {                                      // revisa si se reciben datos por el puerto del bluetooth.
   // int conta = 0;                                                    //
   char c =  puertoAT09.read();                                         // Lee un caracter del puerto serial.
   //Serial.println(char);
  if (c=='*') {                                                         // Verificamos si se trata del caracter "*" usado como cabecera de la trama. 
   leerString="";                                                       // Borramos el string para comenzar de nuevo.
    do {                                                                // Blucle hasta final de la trama que es un #. 
       if ( puertoAT09.available()>0) {                                 // Si hay dato dispobible ...
        c =  puertoAT09.read();                                         // Leemos dato.
        //Serial.print(c);                                              // impresion de testeo. Borrar.
        if (c!='#')leerString.concat(c);                                // Si no llego a final de la trama, suma caracter a lo ya reribido.
       }
      if (millis()> (auxTiempo+tiempoCiclo)) {                          // Este if es para detectar tramas que empiezan bien pero no se cierran, cuando pase el tiempo designado, anula la trama recibida y salta del bucle.
        leerString="";                                                  // Borra la trama por si hemos recibido una parte.
        break;                                                          // provoca la salida del bucle.  
      }
    } while (c!='#');                                                   // Si no llego ninal trama volvemos hacer el bucle. 
    Serial.println(leerString);                                         // Imprime la trama leida correctamente.
    controlLeds();                                                      // Fincion que verifica orden recibida.
  }
 }
}


void controlLeds() {                                                    // Funcion para revisar las ordenes recibidas. 
  
if (leerString=="led1on") {                                             // Si se cumple encendemos led rojo y enviamos aviso por puerto serial.
  digitalWrite(ledRojo, HIGH);
  Serial.println("Encendiendo led rojo pin 8 arduino");
  puertoAT09.println("Encendiendo led rojo pin 8 arduino");
}
if (leerString=="led1off") {                                           // Si se cumple apagamos led rojo y enviamos aviso por puerto serial.
  digitalWrite(ledRojo, LOW);
  Serial.println("Apagado led rojo pin 8 arduino");
  puertoAT09.println("Apagado Led rojo pin 8 arduino");
}
if (leerString=="led2on") {                                            
  digitalWrite(ledNaranja, HIGH);
  Serial.println("Encendiendo led naranja pin 9 arduino");
  puertoAT09.println("Encendiendo led naranja pin 9 arduino");
}
if (leerString=="led2off") {                                            
  digitalWrite(ledNaranja, LOW);
  Serial.println("Apagado led naranja pin 9 arduino");
  puertoAT09.println("Apagado Led naranja pin 9 arduino");
}
if (leerString=="led3on") {                                            
  digitalWrite(ledAmarillo, HIGH);
  Serial.println("Encendiendo led amarillo pin 10 arduino");
  puertoAT09.println("Encendiendo led qmqrillo pin 10 arduino");
}
if (leerString=="led3off") {
  digitalWrite(ledAmarillo, LOW);
  Serial.println("Apagado led amarillo pin 10 arduino");
  puertoAT09.println("Apagado Led amarillo pin 10 arduino");
}

if (leerString=="led4on") {
  digitalWrite(ledVerde, HIGH);
  Serial.println("Encendiendo led verde pin 11 arduino");
  puertoAT09.println("Encendiendo led verde pin 11 arduino");
}
if (leerString=="led4off") {
  digitalWrite(ledVerde, LOW);
  Serial.println("Apagado led verde pin 11 arduino");
  puertoAT09.println("Apagado Led verde pin 11 arduino");
}

if (leerString=="led5on") {
  digitalWrite(ledAzul, HIGH);
  Serial.println("Encendiendo led azul pin 12 arduino");
  puertoAT09.println("Encendiendo led azul  pin 12 arduino");
}
if (leerString=="led5off") {
  digitalWrite(ledAzul, LOW);
  Serial.println("Apagado led azul pin 12 arduino");
  puertoAT09.println("Apagado Led azul pin 12 arduino");
}

if (leerString=="led6on") {
  digitalWrite(ledBlanco, HIGH);
  Serial.println("Encendiendo led blanco pin 13 arduino");
  puertoAT09.println("Encendiendo led blanco pin 13 arduino");
}
if (leerString=="led6off") {
  digitalWrite(ledBlanco, LOW);
  Serial.println("Apagado led blanco pin 13 arduino");
  puertoAT09.println("Apagado Led blanco pin 13 arduino");
}
   
}
