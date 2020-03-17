byte humidity_sensor_pin = A1;
byte humidity_sensor_vcc = 6;
byte int ledpin = 13;
void setup() {
    pinMode(ledpin,OUTPUT);
    pinMode(humidity_sensor_vcc, OUTPUT);
    digitalWrite(humidity_sensor_vcc, LOW);

    while (!Serial);
    delay(1000);
    Serial.begin(9600);
}
int read_humidity_sensor() {
    digitalWrite(humidity_sensor_vcc, HIGH);
    delay(500);
    int value = analogRead(humidity_sensor_pin);
    digitalWrite(humidity_sensor_vcc, LOW);
    return 1023 - value;
}
void loop() {
    if(read_humidity_sensor()>250){
        digitalWrite(ledpin,HIGH);
    }else{
        digitalWrite(ledpin,LOW);
    }
    Serial.println(read_humidity_sensor()); 
    delay(4500);
}