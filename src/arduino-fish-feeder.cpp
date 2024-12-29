/* 
 * Automatic Fish Feeder
 * This in intended to accompany the 3D-printed fish feeder from <https://www.thingiverse.com/thing:2539750>
 * 
 * Built using a TowerPro SG92R Micro Servo
 * (Make sure to bind the servo ground to the Particle device ground)
 */

// Include Particle Device OS APIs
#include "Particle.h"

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(AUTOMATIC);

// Run the application and system concurrently in separate threads
SYSTEM_THREAD(ENABLED);

// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
SerialLogHandler logHandler(LOG_LEVEL_INFO);

// The Feeder is a conventional servo (position-control)
Servo Feeder;

// PIN definitions
const pin_t FEEDER_PIN = D1;

const int LOAD = 1;
const int DUMP = 2;
int currentPosition = LOAD;

// 60 * 60 * 24 = 86400 seconds in 24 hours 
// 86400 * 2 = 172800 seconds in 48 hours
// unsigned long waitTimeBetweenFeedingsMs = 172800 * 1000; // Multiply by 1000 to convert to milliseconds
unsigned long waitTimeBetweenFeedings = 10000; // 10 seconds for testing

void moveToLoad() {
    Log.info("Moving to LOAD");
    Feeder.write(130); 
    currentPosition = LOAD;
}

void moveToDump() {
    Log.info("Moving to DUMP");
    Feeder.write(80); 
    currentPosition = DUMP;
}

void toggleServoPosition() {
    if (currentPosition == LOAD) {
        moveToDump();
    } else {
        moveToLoad();
    }
}


void feed() {
    Log.info("Feeding start...");

    Feeder.attach(FEEDER_PIN);
    pinMode(FEEDER_PIN, OUTPUT);

    moveToDump();
    delay(500);
    moveToLoad();
    delay(500);

    // Detach to avoid jittering while the servo can just be "limp"
    Feeder.detach();

    Log.info("...Feeding done");
}

// This function can be invoked from the Particle cloud dashboard. It must accept a String argument, even though we don't use it.
int manualFeed(String command) {
    Log.info("Manual feed command received");
    feed();
    
    // Particle cloud functions must return an integer
    return 1;
}

// setup() runs once, when the device is first turned on
void setup() {
    Feeder.attach(FEEDER_PIN);
    pinMode(FEEDER_PIN, OUTPUT);

    // Register a cloud function that can be invoked remotely
    Particle.function("feed", manualFeed);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {

    feed();

    // Wait for the next feeding cycle
    delay(waitTimeBetweenFeedings);

    // Publish an event to cloud
    Particle.publish("Feeding complete");
}

