#define LED0 0
#define LED1 2
#define LED2 13
#define GPIO14_OR 14


void setup() {
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(GPIO14_OR, OUTPUT);
  digitalWrite(GPIO14_OR, HIGH);     // always on 
  Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop() {
  Serial.println(ESP.getChipId());  
  Serial.println("all low");    
  digitalWrite(LED0, LOW);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);  
  delay(200); // wartet fuer 200 Millisekunden
  Serial.println("high 0");                                                                        
  digitalWrite(LED0, HIGH);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  delay(200);
  Serial.println("high 1");    
  digitalWrite(LED0, HIGH);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);  
  delay(200);
  Serial.println("high 2");                                                                        
  digitalWrite(LED0, HIGH);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  delay(200);
                        
}
