#include <LiquidCrystal_I2C.h> //Biblioteca para o display LCD 16x2
#include <DHT.h> //Biblioteca para o sensor de umidade e temperatura DHT11
#include <Adafruit_Sensor.h> //Para o sensor DHT11

//DHT11
#define portaDHT11 A1 //a entrada que o sensor DHT11 está conectada
#define modeloDHT DHT11 // o modelo do sensor no caso DHT11 

//Sensor de Umidade do solo
#define sensorUmidade A0 //a entrada que o sensor de Umidade do solo está conectada

// LEDS
#define ledVermelho 7
#define ledAmarelo 6
#define ledVerde 5

DHT dht(portaDHT11, modeloDHT); // Passar informações para do sensor DHT11
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE); //Passar informações para do display

//variaveis que vao receber os dados dos sensores
int valorSolo;
int umidadeAr;
int temperatura; 

void setup() {
 iniciar();
}

void loop() {
  
  receberValores(); // peencher as variaveis com os valores dos sensores
  mostrarNoDisplay(); // valores da temperatura para aparecer no display
  umidadeSolo(); //acender os leds de acordo com umidade do solo
  delay(500);
}

void iniciar(){
  
  //Serial.begin(9600);
  lcd.begin(16,2); //display
  dht.begin(); //sensor de umidade e temperatura
  pinMode(sensorUmidade, INPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
   
}

void receberValores(){
  
  valorSolo = analogRead(sensorUmidade); //comando para pegar o valor que a porta A0 esta recebendo do sensor de solo
  umidadeAr = dht.readHumidity();
  temperatura = dht.readTemperature();
  
}

void mostrarNoDisplay(){
 
 if(umidadeAr <10 || temperatura <10){ //para nao deixar valores fantasmas no display
  lcd.clear();
 }
 
 lcd.setCursor(0,0);
 lcd.print("Umidade AR:");
 lcd.setCursor(13,0);
 lcd.print(umidadeAr);
 lcd.setCursor(0,1);
 lcd.print("Temperatura:");
 lcd.setCursor(13,1); 
 lcd.print(temperatura);

}

void umidadeSolo(){
  
 if(valorSolo > 0 && valorSolo < 400){ //Solo umido, acende o led verde
   apagarLeds();
   digitalWrite(ledVerde, HIGH);
 }else if (valorSolo > 400 && valorSolo < 800){ //Solo moderado, acende o led amarelo
   apagarLeds();
   digitalWrite(ledAmarelo, HIGH);
 }else if(valorSolo > 800 && valorSolo < 1024){ //Solo seco, acende o led vermelho
   apagarLeds();
   digitalWrite(ledVermelho, HIGH);
 }
 
}

void apagarLeds(){
  
  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledVerde, LOW);

}
