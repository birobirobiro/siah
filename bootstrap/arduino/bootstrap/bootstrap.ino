#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0x90, 0xA2, 0xDA, 0x0D, 0xA6, 0x09 }; // mac address
byte ip[] = {192, 168, 0, 177 }; // ip lan
byte gateway[] = {192, 168, 0, 1 }; // gatway
byte subnet[] = {255, 255, 255, 0 }; //subnet mask
EthernetServer server(80); //server port

int saida1 = 3;
int saida2 = 4;
int saida3 = 6;
int saida4 = 7;
int saida5 = 8;
int entrada1 = A0; //LDR


float temperatura;
int ldr;
String final_ldr;

String readString;

void setup(){

  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.begin(9600);

  pinMode(saida1, OUTPUT);
  pinMode(saida2, OUTPUT);
  pinMode(saida3, OUTPUT);
  pinMode(saida4, OUTPUT);
  pinMode(saida5, OUTPUT);
  pinMode(entrada1, INPUT);
}

void loop(){
  sensor_luz();
  sensor_temperatura();
  displayWeb();
}

void displayWeb(){
EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        //read char by char HTTP request
        if (readString.length() < 100) {

          //store characters to string
          readString += c;
          //Serial.print(c);
        }

        //RECEBE A INFORMAÇÃO PELA URL PARA ENVIAR AS INFORMAÇÕES PARA AS PORTAS UTILIZADAS
        if (c == '\n') {

          Serial.println(readString);
       
          if(readString.indexOf("?S1Ligado") >0) {
            digitalWrite(saida1, HIGH);
          }
          if(readString.indexOf("?S1Desligado") >0) {
            digitalWrite(saida1, LOW);
          }

          if(readString.indexOf("?S2Ligado") >0) {
            digitalWrite(saida2, HIGH);
          }
          if(readString.indexOf("?S2Desligado") >0) {
            digitalWrite(saida2, LOW);
          }

          if(readString.indexOf("?S3Ligado") >0) {
            digitalWrite(saida3, HIGH);
          }
          if(readString.indexOf("?S3Desligado") >0) {
            digitalWrite(saida3, LOW);
          }

          if(readString.indexOf("?S4Ligado") >0) {
            digitalWrite(saida4, HIGH);
          }
          if(readString.indexOf("?S4Desligado") >0) {
            digitalWrite(saida4, LOW);
          }

          if(readString.indexOf("?S5Ligado") >0) {
            digitalWrite(saida5, HIGH);
          }
          if(readString.indexOf("?S5Desligado") >0) {
            digitalWrite(saida5, LOW);
          }

          //S serve para apontar no codigo html se esta ligado ou desligado;
          int S1 = digitalRead(saida1);
          int S2 = digitalRead(saida2);
          int S3 = digitalRead(saida3);
          int S4 = digitalRead(saida4);
          int S5 = digitalRead(saida5);
          
          client.println(F("HTTP/1.1 200 OK")); //send new page
          client.println(F("Content-Type: text/html"));
          client.println();

          client.println(F("<HTML>"));
          client.println(F("<HEAD>"));
          client.println(F("<title>SIAH</title>"));
          client.println(F("<meta http-equiv='Content-Type' content='text/html; charset=utf-8'>"));
          client.println(F("<link href='http://localhost/automacao tcc/bootstrap/bootstrap.min.css' rel='stylesheet'></link>"));

          client.println(F("</head>"));
          client.println(F("<body>"));
          
          // menu
          client.println(F("<nav class='navbar navbar-default navbar-fixed-top' role='navigation'>"));
          client.println(F("<div class='navbar-header'>"));
          client.println(F("<a class='navbar-brand' rel='home' href=''>SIAH</a>"));
          client.println(F("</div>"));
          client.println(F("<div class='collapse navbar-collapse'>"));
          client.println(F("<ul class='nav navbar-nav'>"));
          client.println(F("<li><a href='http://localhost/automacao%20tcc/login/login.php'>Sair</a></li>"));
          client.println(F("</ul>"));
          client.println(F("</div>"));
          client.println(F("</nav>"));
          // final menu

          //painel de botões
          client.println(F("<div class='container-fluid'>")); 
          client.println(F("<div class='col-sm-6 col-sm-offset-3'>"));
          client.println(F("<h2>Painel controle</h2>"));
          client.println(F("<div class='panel panel-default'>"));
          client.println(F("<div class='panel-heading'>Controles da Casa</div>"));
          client.println(F("<div class='panel-body'>"));
          
          client.println(F("<table class='table table-bordered'>"));
          client.println(F("<tbody>"));
          
          //client.println(F("<tr><td width=100px>"));
          client.println(F("</td><td>Status"));
          client.println(F("</td></tr>"));

          //Saida 1
          client.println(F("<tr><td width=100px>Quarto 1 -"));
          if(S1 == HIGH){
            client.println(F("Ligado"));
            client.println(F("</td><td>"));
            client.println(F("<a class='btn btn-danger btn-lg' href='?S1Desligado'>Desligar</buttLigado>"));
          }else{
            client.println(F("Desligado"));
            client.println(F("</td><td>"));
            client.println(F("<a class='btn btn-success btn-lg' href='?S1Ligado'>Ligar</buttLigado>"));      
          }      
          client.println(F("</td></tr>"));

          //Saida 2
          client.println(F("<tr><td width=100px>Sala -"));
          if(S2 == HIGH){
            client.println(F("Ligado"));
            client.println(F("</td><td>"));
            client.println(F("<a class='btn btn-danger btn-lg' href='?S2Desligado'>Desligar</buttLigado>"));
          }else{
            client.println(F("Desligado"));
            client.println(F("</td><td>"));
            client.println(F("<a class='btn btn-success btn-lg' href='?S2Ligado'>Ligar</buttLigado>"));      
          }      
          client.println(F("</td></tr>"));

          //Saida 3
          client.println(F("<tr><td width=100px>Copas -"));
          if(S3 == HIGH){
            client.println(F("Ligado"));
            client.println(F("</td><td>"));
            client.println(F("<a class='btn btn-danger btn-lg' href='?S3Desligado'>Desligar</buttLigado>"));
          }else{
            client.println(F("Desligado"));
            client.println(F("</b></td><td>"));
            client.println(F("<a class='btn btn-success btn-lg' href='?S3Ligado'>Ligar</buttLigado>"));      
          }      
          client.println(F("</td></tr>"));


//Saida 4
          client.println(F("<tr><td width=100px>Cozinha -"));
          if(S4 == HIGH){
            client.println(F("Ligado"));
            client.println(F("</td><td>"));
            client.println(F("<a class='btn btn-danger btn-lg' href='?S4Desligado'>Desligar</buttLigado>"));
          }else{
            client.println(F("Desligado"));
            client.println(F("</td><td>"));
            client.println(F("<a class='btn btn-success btn-lg' href='?S4Ligado'>Ligar</buttLigado>"));      
          }      
          client.println(F("</td></tr>"));


          //Saida 5
          client.println(F("<tr><td width=100px>Piscina -"));
          if(S5 == HIGH){
            client.println(F("Ligado"));
            client.println(F("</td><td>"));
            client.println(F("<a class='btn btn-danger btn-lg' href='?S5Desligado'>Desligar</buttLigado>"));
          }else{
            client.println(F("Desligado"));
            client.println(F("</td><td>"));
            client.println(F("<a class='btn btn-success btn-lg' href='?S5Ligado'>Ligar</buttLigado>"));      
          }      
          client.println(F("</td></tr>"));

          client.println(F("</tbody>"));
          client.println(F("</table>"));
          client.println(F("</div>"));
          client.println(F("</div>"));
          client.println(F("<hr>"));
          //Final painel dos botões

          //Painel de temperatura
          client.println(F("<div class='panel panel-default'>"));
          client.println(F("<div class='panel-heading'>Temperatura do Ambiente</div>"));
          client.println(F("<div class='panel-body'>"));
          client.println(F("<table class='table table-bordered'>"));
          client.println(F("<tbody>"));
          client.println(F("<tr><td width=175px>Temperatura"));
          client.println(F("</td><td>"));
          client.println("ºC");
          client.println(F("</td></tr>"));
//          client.println(F("<tr><td width=175px>Luz Ambiente"));
//          client.println(F("</td><td>"));
//          client.println(F("</td></tr>"));
          client.println(F("</tbody>"));
          client.println(F("</table>"));
          client.println(F("</div>"));
          client.println(F("</div>"));
//          Final painel de retorno
          
          client.println(F("</body>"));
          client.println(F("</html>"));

          delay(1);
          //stopping client
          client.stop();

          //clearing string for next read
          readString="";
        }
      }
    }
  }
}

/*******************************************
  sensor de temperatura
*******************************************/
void sensor_temperatura(){
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  float celsius, fahrenheit;
  

switch (addr[0]) {
    case 0x10:
      //Serial.println("  Chip = DS18S20");  // or old DS1820
      type_s = 1;
      break;
    case 0x28:
      //Serial.println("  Chip = DS18B20");
      type_s = 0;
      break;
    case 0x22:
      //Serial.println("  Chip = DS1822");
      type_s = 0;
      break;
    default:
      Serial.println("Sensor no eh da familia dos DS18x20");
      return;
  } 

  delay(1000);
  // podemos fazer um ds.depower () aqui, mas o resto vai cuidar dela.


  for ( i = 0; i < 9; i++) {           // necessario 9 bytes

  }
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; 
    if (data[7] == 0x10) {
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    if (cfg == 0x00) raw = raw & ~7;  // 9 bits, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
  }
  celsius = (float)raw / 16.0;
  fahrenheit = celsius * 1.8 + 32.0;
  //Serial.println("");
  //Serial.print("  Temperature = ");
  //Serial.print(celsius);
  //Serial.print(" Celsius");
  temperatura = celsius;
  //Serial.print(fahrenheit);
  //Serial.println(" Fahrenheit");
}

/*******************************************
   Sensor Iluminação
*******************************************/
void sensor_luz(){
  ldr = analogRead(entrada1);
  Serial.println(ldr);
  //delay(1000);

  if(ldr < 100){
    final_ldr = "Noite";
  }else{
    final_ldr = "Dia";
  }
}
