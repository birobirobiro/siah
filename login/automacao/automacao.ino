#include <Ethernet.h>
#include <SPI.h>

String readString;
 
byte pino_rele1 = 3;
byte pino_rele2 = 4;
byte pino_rele3 = 5;
byte pino_rele4 = 6;
boolean ligado = true;
boolean ligado_2 = true;
boolean ligado_3 = true;
boolean ligado_4 = true;
 
//Informacoes de endereco IP, gateway, mascara de rede
byte mac[] = { 0xA4, 0x28, 0x72, 0xCA, 0x55, 0x2F };
byte ip[] = { 10, 68, 103, 16 };
byte gateway[] = { 10, 68, 102, 1 };
byte subnet[] = { 255, 255, 254, 0 };
 
EthernetServer server(80);
 
void setup()
{
  Serial.begin(9600);
  pinMode(pino_rele1, OUTPUT);
  pinMode(pino_rele2, OUTPUT);
  pinMode(pino_rele3, OUTPUT);
  pinMode(pino_rele4, OUTPUT);
 
  //Inicializa Ethernet Shield
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
 
  Serial.println("SIAH - Automacao Residencial"); 
 
  //Desliga os dois reles
  digitalWrite(pino_rele1, HIGH);
  digitalWrite(pino_rele2, HIGH);
  digitalWrite(pino_rele3, HIGH);
  digitalWrite(pino_rele4, HIGH);
}
void loop(){
  EthernetClient client = server.available();
  if (client) {
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        if (readString.length() < 100) {
          readString += c;
        }
        if (c == '\n')
        {
          //Controle do rele1
          Serial.println(readString);
          //Liga o Rele 1
          if (readString.indexOf("?ligar") > 0)
          {
            digitalWrite(pino_rele1, LOW);
            Serial.println("Rele 1 Ligado");
            ligado = false;
          }
          else
          {
            //Desliga o Rele 1
            if (readString.indexOf("?desligar") > 0)
            {
              digitalWrite(pino_rele1, HIGH);
              Serial.println("Rele 1 Desligado");
              ligado = true;
            }
          }
 
          //Controle do rele2
          Serial.println(readString);
          //Liga o Rele 2
          if (readString.indexOf("?2_ligar") > 0)
          {
            digitalWrite(pino_rele2, LOW);
            Serial.println("Rele 2 Ligado");
            ligado_2 = false;
          }
          else
          {
            //Desliga o Rele 2
            if (readString.indexOf("?2_desligar") > 0)
            {
              digitalWrite(pino_rele2, HIGH);
              Serial.println("Rele 2 Desligado");
              ligado_2 = true;
            }
          }

          //Controle do rele1
          Serial.println(readString);
          //Liga o Rele 3
          if (readString.indexOf("?3_ligar") > 0)
          {
            digitalWrite(pino_rele3, LOW);
            Serial.println("Rele 3 Ligado");
            ligado_3 = false;
          }
          else
          {
            //Desliga o Rele 3
            if (readString.indexOf("?3_desligar") > 0)
            {
              digitalWrite(pino_rele3, HIGH);
              Serial.println("Rele 3 Desligado");
              ligado_3 = true;
            }
          }

          //Controle do rele1
          Serial.println(readString);
          //Liga o Rele 4
          if (readString.indexOf("?4_ligar") > 0)
          {
            digitalWrite(pino_rele4, LOW);
            Serial.println("Rele 4 Ligado");
            ligado_4 = false;
          }
          else
          {
            //Desliga o Rele 4
            if (readString.indexOf("?4_desligar") > 0)
            {
              digitalWrite(pino_rele4, HIGH);
              Serial.println("Rele 4 Desligado");
              ligado_4 = true;
            }
          }
          readString = "";
 
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          
// A partir daqui começa os códigos html.
client.println("<html>");
client.println("<head>");
client.println("<title>SIAH - Automacao Residencial</title>");
client.println("<meta http-equiv='Content-Type' content='text/html; charset=ISO-8859-1'>");
client.println("<meta name='viewport' content='width=720, initial-scale=0.5' />");
client.println("<link rel='stylesheet' type='text/css' href='http://localhost/automacao/automacao_residencial.css' />");
client.println("<script type='text/javascript' src='http://localhost/automacao/automacao_residencial.js'></script>");
client.println("</head>");
client.println("<body>");
client.println("<div id='wrapper'><img alt='SIAH' <img src='http://localhost/automacao/siahhh.jpg' width='400' height='178' /><br/>");
client.println("<div id='div1'>Sala</div>");
client.println("<div id='div2'>Quarto</div>");
client.println("<div id='div3'>Banheiro</div>");
client.println("<div id='div4'>Garagem</div>");
client.println("<div id='rele'></div>");
client.println("<div id='estado' style='visibility: hidden;'> </div>");
client.println("<div id='botao'></div>");
client.println("<div id='rele_2'></div>");
client.println("<div id='estado_2' style='visibility: hidden;'></div>");
client.println("<div id='botao_2'></div>");
client.println("<div id='rele_3'></div>");
client.println("<div id='estado_3' style='visibility: hidden;'> </div>");
client.println("<div id='botao_3'></div>");
client.println("<div id='rele_4'></div>");
client.println("<div id='estado_4' style='visibility: hidden;'></div>");
client.println("<div id='botao_4'></div>");
client.println("</div>");
client.println("<script>AlteraRele1()</script>");
client.println("<script>AlteraRele2()</script>");
client.println("<script>AlteraRele3()</script>");
client.println("<script>AlteraRele4()</script>");
client.println("</div>");
client.println("</body>");
client.println("</html>");
          delay(1);
          client.stop();
        }
      }
    }
  }
}        
         
