#define PIN_LED 7
int i =0;
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
  digitalWrite(PIN_LED, 0);
  delay(1000);
  while(i<11){
  if(toggle==0){
    toggle=1;
  }
  else{
    toggle=0;
  }
  Serial.println(toggle);
  digitalWrite(PIN_LED, toggle);
  delay(100);
  i+=1;
  }
  while(1) {}
}

int toggle_state(int toggle){
  
  return toggle;
}
