// Comunicacion bluetooth (Maestro).
// www.Cambatronics.com
// soporte@cambatronics.com

#include <SoftwareSerial.h>
SoftwareSerial at09(3,4);                                                 // Tranasmite por pin 3, recibe por 4.
const int pinEmparejado = 2;                                              // Pin entrada activo si el dispositivo esta emparejado.
String str_ii = "";                             
int ii_0 = 0;                                         
String leerString = String(30);                                          // Variable donde guardaremos las tramas recibidas.
String auxLeerString = String(30);                                       // Variable donde guardaremos las tramas recibidas.
String control;
long auxTiempo=0;                                                        // Variable usada `para controlar el tiempo de reseteo de la trama.
int tiempoCiclo=1000;                                                    // Tiempo en msegundos en el que reseteara la trama.  

void setup() {  
  Serial.begin(9600);                                                   // Conexion con el monitor serial.
  at09.begin(9600);                                                     // Conexion con modulo bluetooth.
  pinMode(pinEmparejado,INPUT_PULLUP);                                  // Pin para chequeo de emparejamiento.
}

void loop() {
 if (!digitalRead(pinEmparejado)) {                                    // Si esta emparejado, pin valor alto.
  conexion();                                                          // Se intenta emparejar.
  Serial.println("conectando");                                        // Nos avisa de que esta conectandose.  
 }
  chequearPuerto();                                                    // Revisa si hay alguna orden para enviar.
 }

String at_cmd(String cmd_str,String desc_str){                        // Procedimiento envio de comandos AT de configuracion.
  str_ii = "";
  unsigned long t1 = millis();
  at09.println(cmd_str);
  while (true){
    char in_char = at09.read();
    if (int(in_char)==-1 or int(in_char)==42){
      if ((millis()-t1)>2000){                                       // 2 segundos tiempo de reseteo.
        return "Err";
      }
      continue;
    }
    if (in_char=='\n'){
      Serial.print("Bluetooth "+desc_str);
      Serial.println(str_ii.substring(0,str_ii.length()));
      return str_ii;
    }
    str_ii+=in_char;
  }
}



void conexion() {
 at_cmd("AT+RESET","");                                                  // reset modulo AT09.
 delay(1000); 
 at_cmd("AT+CONA587A6238CB48","resultado:");                             // Conexion con bluetooth nextion.
 delay(1000); 
}

void chequearPuerto () {
auxTiempo=millis();                                                     // Usamos millis para resetear una trama si no se cierra correctamente.       
if ( Serial.available() > 0) {                                          // revisa si se reciben datos por el puerto del bluetooth.
 char c ="";
  leerString="";  
    do {                                                                // Blucle hasta final de la trama que es un #. 
       if ( Serial.available()>0) {                                     // Si hay dato dispobible ...
        c =  Serial.read();                                             // Leemos dato.
        //Serial.print(c);                                              // impresion de testeo. Borrar.
        if (c!='#')leerString.concat(c);                                // Si no llego a final de la trama, suma caracter a lo ya reribido.
       }
      if (millis()> (auxTiempo+tiempoCiclo)) {                          // Este if es para detectar tramas que empiezan bien pero no se cierran, cuando pase el tiempo designado, anula la trama recibida y salta del bucle.
        leerString="";                                                  // Borra la trama por si hemos recibido una parte.
        break;                                                          // provoca la salida del bucle.  
      }
    } while (c!='#');                                                   // Si no llego ninal trama volvemos hacer el bucle. 
     leerString.concat(c);
    Serial.print(leerString);                                           // Imprime la trama leida correctamente.
    at09.print(leerString);
  }
  
} 
