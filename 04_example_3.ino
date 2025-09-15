#define PIN_LED 13

unsigned int count, toggle;

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(115200);
  while(!Serial){
    ;
  }
  Serial.println("Hello World!");
  count = toggle = 0;
  digitalWrite(PIN_LED, toggle);
}

void loop() {
  if(toggle==0){
    toggle=1;
  }
  else{
    toggle=0;
  }
  Serial.println(++count);
  Serial.println(toggle);
  digitalWrite(PIN_LED, toggle);
  delay(1000);
  }

int toggle_state(int toggle){
  
  return toggle;
}
