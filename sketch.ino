/***************************************************************************************************
/ Universidade Federal do Rio de Janeiro
/ PAME 24.1
/ Candidato : Mateus Barbosa Vila Nova Camara
/ 
/ PROJETO DE AR-CONDICIONADO
/ CODIGO DO ARDUINO MASTER
/***************************************************************************************************/
#include <Wire.h>


#define SENSOR_1_ECHO					8
#define SENSOR_2_ECHO					9
#define SENSOR_3_ECHO					10
#define SENSOR_4_ECHO					11

#define SENSOR_1_TRIG					0
#define SENSOR_2_TRIG					1
#define SENSOR_3_TRIG					2
#define SENSOR_4_TRIG					3

#define DIREITA						    1
#define ESQUERDA				    	2
#define FRENTE							3
#define TRAS							4

void setup()
{
    Wire.begin(8);
    Serial.begin(9600);

    pinMode(SENSOR_1_ECHO,INPUT);
    pinMode(SENSOR_2_ECHO,INPUT);
    pinMode(SENSOR_3_ECHO,INPUT);
    pinMode(SENSOR_4_ECHO,INPUT);
  
    pinMode(SENSOR_1_TRIG,OUTPUT);
    pinMode(SENSOR_2_TRIG,OUTPUT);
    pinMode(SENSOR_3_TRIG,OUTPUT);
    pinMode(SENSOR_4_TRIG,OUTPUT);
  
    digitalWrite(SENSOR_1_TRIG,LOW);
    digitalWrite(SENSOR_2_TRIG,LOW);
    digitalWrite(SENSOR_3_TRIG,LOW);
    digitalWrite(SENSOR_4_TRIG,LOW);
}

void loop()
{
  /*Distancia medida pelo sensor n*/

  float sensor1Val;
  float sensor2Val;
  float sensor3Val;
  float sensor4Val;
  
  /*Tempo de demora para enviar e receber o sinal*/

  float tempo1;
  float tempo2;
  float tempo3;
  float tempo4;
  
  /*Envio e captacao do sinal*/

  digitalWrite(SENSOR_1_TRIG,LOW);
  digitalWrite(SENSOR_2_TRIG,LOW);
  digitalWrite(SENSOR_3_TRIG,LOW);
  digitalWrite(SENSOR_4_TRIG,LOW);
  
  delayMicroseconds(2);
  
  digitalWrite(SENSOR_1_TRIG,HIGH);
  digitalWrite(SENSOR_2_TRIG,HIGH);
  digitalWrite(SENSOR_3_TRIG,HIGH);
  digitalWrite(SENSOR_4_TRIG,HIGH);
  
  delayMicroseconds(10);
  
  digitalWrite(SENSOR_1_TRIG,LOW);
  digitalWrite(SENSOR_2_TRIG,LOW);
  digitalWrite(SENSOR_3_TRIG,LOW);
  digitalWrite(SENSOR_4_TRIG,LOW);
  
  /*Calculo das distancias*/

  tempo1 = pulseIn(SENSOR_1_ECHO,HIGH);
  tempo2 = pulseIn(SENSOR_2_ECHO,HIGH);
  tempo3 = pulseIn(SENSOR_3_ECHO,HIGH);
  tempo4 = pulseIn(SENSOR_4_ECHO,HIGH);
  
  sensor1Val = tempo1 * 0.017;
  sensor2Val = tempo2 * 0.017;
  sensor3Val = tempo3 * 0.017;
  sensor4Val = tempo4 * 0.017;
  
  if(sensor1Val < 50 || sensor2Val < 50) /*Obstaculo a frente*/
  {
    if(sensor3Val > 50) /*Direita livre*/
    {
      Wire.beginTransmission(8);
      Wire.write(DIREITA);
      Wire.endTransmission();      
    }
    else if(sensor4Val > 50) /*Esquerda livre*/
    {
      Wire.beginTransmission(8);
      Wire.write(ESQUERDA);
      Wire.endTransmission();
    }
  }
  
  else /*Caminho livre*/
  {
    Wire.beginTransmission(8);
    Wire.write(FRENTE);
    Wire.endTransmission();
  }
}
