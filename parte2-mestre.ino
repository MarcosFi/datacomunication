//mestre
const int DE_RE =  5;  // HIGH:TX, LOW:RX
void setup() 
{ 
  Serial.begin(9600);
  Serial.setTimeout(100);                //Tempo de espera de 100ms
  pinMode(DE_RE, OUTPUT);
  digitalWrite(DE_RE, HIGH); 
} 
void loop() 
{ 
  if (Serial.available()) {
    
   String comando = Serial.readString(); // Lê os comandos
   if(comando=="S1W"){                   // escrever
     Serial.print("1");                  // endereço do escravo
     delay(8);
     Serial.println("W");                // função escritor
    }
     if(comando=="S2W"){                 // escrever
     Serial.print("2");                  // endereço do escravo
     delay(8);
     Serial.println("W");                // função escritor
    }
     if(comando=="S1L"){                 // ler
    Serial.print("1");                   // endereço do escravo
    delay(8);
    Serial.print("L ");                  // função leitura
    Serial.flush();
    digitalWrite(DE_RE, LOW);            // RS485 como receptor
    delay(1000);
    int sensor=Serial.parseInt();
    Serial.println(sensor);
   if(Serial.find("i")){
       Serial.print("OK");
      delay(1000);
      //int sensor = Serial.read();
      int sensor=Serial.parseInt();      // recebe a leitura
      Serial.println(sensor);            // imprime na tela      
    }
    digitalWrite(DE_RE, HIGH);           // RS485 como Transmisor
    } 

   if(comando=="S2L"){                  // ler
    Serial.print("2");                  // endereço do escravo
    delay(8);
    Serial.print("L ");                 // função leitura
    Serial.flush();
    digitalWrite(DE_RE, LOW);           // RS485 como receptor
   if(Serial.find("i")){
     delay(10);
     int sensor=Serial.parseInt();      // recebe a leitura
     Serial.println(sensor);            // imprime na tela      
    }
    digitalWrite(DE_RE, HIGH);          //RS485 como Transmisor
    } 
  }
}
