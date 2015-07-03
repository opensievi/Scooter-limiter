// Software version and date
#define SWVERSION "0.1"
#define SWDATE "07-15"

// Pin layout
#define TLED_PIN 13 // Trigger led
#define ALED_PIN 9 // Activation led
#define SENSOR_PIN A1 // Hall sensor
#define POT_PIN A2 // Potentiometer
#define SENS_LIMIT 700

void setup()
{
	char version[20];	

	Serial.begin(9600);
	Serial.println("OpenSievi Scooter-limiter");
	Serial.print("Version: ");
	Serial.print(SWVERSION);
	Serial.print(" ");
	Serial.println(SWDATE);

	pinMode(TLED_PIN, OUTPUT);
	pinMode(ALED_PIN, OUTPUT);
	pinMode(SENSOR_PIN, INPUT);
	pinMode(POT_PIN, INPUT);

	digitalWrite(ALED_PIN, HIGH);
	digitalWrite(TLED_PIN, HIGH);
	delay(300);
	digitalWrite(TLED_PIN, LOW);
	digitalWrite(ALED_PIN, LOW);
	delay(300);
	digitalWrite(TLED_PIN, HIGH);
	digitalWrite(ALED_PIN, HIGH);
	delay(300);
	digitalWrite(TLED_PIN, LOW);
	digitalWrite(ALED_PIN, LOW);

}

int trigger_counter = 0;
int milli_counter = 0;
int sensor_state = 0;

void loop() 
{

	int sensor = analogRead(SENSOR_PIN);
	int adjust = analogRead(POT_PIN);
	int millis_now = millis();

	adjust = map(adjust, 10, 970, 20, 1);

	if(sensor < SENS_LIMIT) {
		digitalWrite(TLED_PIN, HIGH);
		if(sensor_state==0) {
			trigger_counter++;
			sensor_state=1;
		}
	} else {
		digitalWrite(TLED_PIN, LOW);
		if(sensor_state==1) {
			sensor_state=0;
		}
	}

	if( millis_now - milli_counter > 1000 ) {
		if(trigger_counter > adjust) {
			digitalWrite(ALED_PIN,HIGH);
			Serial.println("OVERSPEED");
		} else {
			digitalWrite(ALED_PIN,LOW);
		}
		trigger_counter = 0;
		milli_counter = millis_now;
	}
}


