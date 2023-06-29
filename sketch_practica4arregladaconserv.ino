#include <SoftwareSerial.h> //librerias que se usan
#include <Adafruit_NeoPixel.h>
#include <LedControl.h>
#include <Servo.h>

int bluetoothTx = 2; // bluetooth tx para 10 pin
int bluetoothRx = 3; // bluetooth rx para 11 pin

SoftwareSerial elbt(bluetoothTx, bluetoothRx); /*configuracion del bluetooth*/

char letra;
int numero;/**/

int ledm = 9;/*configuracion de las leds*/
int ledr = 8;
int ledv = 7;
int leda = 6;
int ledn = 12;

bool estado = 0;
bool estadoa = 0;
bool estadon = 0;
bool estadod = 0;
bool estadoi = 0;/**/

Adafruit_NeoPixel tira = Adafruit_NeoPixel(12,4);//configuracion del neopixel

LedControl MATLED = LedControl(11,13,10,3);	/*configuracion de la matriz*/

byte caracter[8] = {
  0xfe, 0xff, 0x67, 0x63, 0x63, 0x67, 0xff, 0xfe
};

byte caracter_2[8] = {
  0x1c, 0x22, 0x41, 0x82, 0x82, 0x41, 0x22, 0x1c
};

byte caracter_3[8] = {
  0xff, 0xff, 0x6, 0xc, 0xc, 0x6, 0xff, 0xff/**/
};

Servo myservo; //configuracion del servo 

void setup()
{
  Serial.begin(9600);//activar el monitor serial
  
  elbt.begin(9600);//activar el monitor del bluetooth

  pinMode(ledm,OUTPUT);/*configuracion de las leds*/
  pinMode(ledr,OUTPUT);
  pinMode(ledv,OUTPUT);
  pinMode(leda,OUTPUT);
  pinMode(ledn,OUTPUT);/**/

  tira.begin();/*configuracion del neopixel*/
  tira.show();/**/

  MATLED.shutdown(0,false);			// enciende la matriz
  MATLED.setIntensity(0,10);			// establece brillo
  MATLED.clearDisplay(0);			// blanquea matriz

  myservo.attach(5); //configuracion del servo

}

void loop()
{
 
  if (elbt.available() > 0){//activa el bluetooth
    letra = elbt.read(); //hace que letra tenga los valores del bluetooth
    
    elbt.println(letra); //imprime  letra en su monitor digamos
    

    if(letra == 'a'){   //configuracion del boton a la led para que nege el estado asi este sera el que encienda y apage la led
      estado = !estado;
      digitalWrite(ledm,estado);
    }

    if(letra == 'n'){   //configuracion del boton a la led para que nege el estado asi este sera el que encienda y apage la led
      estadoa = !estadoa;
      digitalWrite(leda,estadoa);
    }  

    if(letra == 'd'){   //configuracion del boton a la led para que nege el estado asi este sera el que encienda y apage la led
      estadon = !estadon;
      digitalWrite(ledr,estadon);
    }

    if(letra == 'h'){   //configuracion del boton a la led para que nege el estado asi este sera el que encienda y apage la led
      estadod = !estadod;
      digitalWrite(ledv,estadod);
    }

    if(letra == 'r'){   //configuracion del boton a la led para que nege el estado asi este sera el que encienda y apage la led
      estadoi = !estadoi;
      digitalWrite(ledn,estadoi);
    }

    if(letra == 's'){ //funciona para activar el neopixel
      neopixel();
    }

    if(letra == 'e'){   //activa el patron en la matriz
      matriz_1();
      delay(5000);
      MATLED.clearDisplay(0);
    }

    if(letra == 'm'){   //activa el patron en la matriz
      matriz_2();
      delay(5000);
      MATLED.clearDisplay(0);
    }

    if(letra == 'i'){   //activa el patron en la matriz
      matriz_3();
      delay(5000);
      MATLED.clearDisplay(0);
    }

  }

  /*if(char numero = Serial.read()> '0'){ /*todos estos fueron las pruebas de como mover el servo que realize*/
      /*myservo.write(numero);
      Serial.println(numero);
    }*/
    //movimiento();/**/

    if(elbt.available()> 0 ) // recive el numero del bluetooth
  {
    int servopos = elbt.read(); // guarda la poscicion del numero para el servo
    Serial.println(servopos); // smuestra en el monitor serial el numero que esta actual
    myservo.write(servopos); // gira el servo dependiendo del numero
  } 
  

}

/*void movimiento(){ /*prueva del servo*/
  /*while(elbt.available() > 0){
    numero = elbt.read();
    Serial.println(numero);
    myservo.write(numero);
    delay(10);
  }
}*/

void neopixel(){  //funcion sin retorno para el neopixel
  for(int i = 0; i<12; i = i+2 ){
    tira.setBrightness(100);
    tira.setPixelColor(i, 0,255,255);
    tira.show();
      delay(100);
    }

    for(int i = 12; i>=-1; i = i-2) {
    tira.setBrightness(100);
    tira.setPixelColor(i, 0,0,255);
    tira.show();
      delay(100);
    } 

    for(int i = 0; i<12; i++) {
    tira.setBrightness(100);
    tira.setPixelColor(i, 255,0,0);
    tira.show();
      delay(100);
    }
    for(int i = 0; i<12; i++) {
    tira.setBrightness(100);
    tira.setPixelColor(i, 0,0,0);
    tira.show();
      delay(100);
    }
}

void matriz_1(){
  for (int i = 0; i < 8; i++)  		// bucle itegra 8 veces por el array
  {
    MATLED.setRow(0,i,caracter[i]);
  }
}

void matriz_2(){
  for (int i = 0; i < 8; i++)  		// bucle itegra 8 veces por el array
  {
    MATLED.setRow(0,i,caracter_2[i]);
  }
}

void matriz_3(){
  for (int i = 0; i < 8; i++)  		// bucle itegra 8 veces por el array
  {
    MATLED.setRow(0,i,caracter_3[i]);
  }
}

