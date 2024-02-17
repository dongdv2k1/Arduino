#define D0 4
void setup() {

 pinMode(D0, OUTPUT);
Serial.begin(9600);
   
}

void loop() {

if (Serial.available()){
  char data;
  data=Serial.read();
  Serial.println(data);

  if (data =='a'){
    digitalWrite(D0,HIGH); 
  }
  else if(data =='b'){
    digitalWrite(D0,LOW);
  }
}
  
}
