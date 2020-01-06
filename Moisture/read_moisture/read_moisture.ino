
float val = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
}

void loop() {
  val = analogRead(A0);
  Serial.println(val);
  delay(1000);
}
