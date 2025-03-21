#include <BleKeyboard.h>

// Initialize BLE Keyboard with a custom device name, manufacturer name, and battery level
// Modify the first parameter to change the device name shown in Bluetooth settings
BleKeyboard bleKeyboard("Truck Button Box", "ESP32-S3", 100);

// ========== SPST TOGGLE SWITCHES ========== //
// These switches hold a key when in the ON position and release it when OFF
// Modify the pin numbers in spstPins[] to change the physical switch connections
// Modify the characters in spstKeys[] to change the keys they trigger
const int spstPins[8] = {14,13,12,11,10,9,46,3};
const char spstKeys[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'}; 

// ========== SPDT TOGGLE SWITCHES ========== //
// These switches send different keys when toggled left or right
// Modify pin numbers in spdtLeftPins[] and spdtRightPins[] to change switch wiring
// Modify characters in spdtLeftKeys[] and spdtRightKeys[] to change the triggered keys
const int spdtLeftPins[7] = {35, 46, 21, 19, 37, 39, 41};
const int spdtRightPins[7] = {36, 45, 47, 20, 38, 40, 42};
const char spdtLeftKeys[7] = {'I', 'J', 'K', 'L', 'M', 'N', 'O'};
const char spdtRightKeys[7] = {'P', 'Q', 'R', 'S', 'T', 'U', 'V'};

// ========== MOMENTARY BUTTONS ========== //
// These buttons send a keypress once when pressed and released
// Modify the pin numbers to change the button connections
// Modify the characters to change which key each button sends
const int ignitionPin = 2; // Ignition Button
const char ignitionKey = 'Y';

const int pushPullPins[2] = {15,16}; // Two Push-Pull Buttons
const char pushPullKeys[2] = {'Z', 'X'};

const int hazardPin = 1; // Hazard Button
const char hazardKey = 'H';

const int pushReleasePin = 29; // Push Release Button
const char pushReleaseKey = 'P';

const int ncNoButton = 7; // NC/NO Button
const char ncNoKey = 'N';

// Store previous states for momentary buttons to detect presses
bool prevIgnitionState = HIGH;
bool prevPushPullState[2] = {HIGH, HIGH};
bool prevHazardState = HIGH;
bool prevPushReleaseState = HIGH;
bool prevNcNoState = HIGH;

void setup() {
    Serial.begin(115200);
    Serial.println("Starting BLE work!");
    bleKeyboard.begin();

    // Configure switch and button pins as inputs with pull-up resistors
    for (int i = 0; i < 8; i++) pinMode(spstPins[i], INPUT_PULLUP);
    for (int i = 0; i < 7; i++) {
        pinMode(spdtLeftPins[i], INPUT_PULLUP);
        pinMode(spdtRightPins[i], INPUT_PULLUP);
    }

    pinMode(ignitionPin, INPUT_PULLUP);
    pinMode(pushPullPins[0], INPUT_PULLUP);
    pinMode(pushPullPins[1], INPUT_PULLUP);
    pinMode(hazardPin, INPUT_PULLUP);
    pinMode(pushReleasePin, INPUT_PULLUP);
    pinMode(ncNoButton, INPUT_PULLUP);
}

void loop() {
    if (!bleKeyboard.isConnected()) {
        Serial.println("Waiting for BLE connection...");
        delay(5000); // Wait before checking again
        return;
    }

    Serial.println("BLE Connected. Checking inputs...");

    // ========== HANDLE SPST TOGGLE SWITCHES ========== //
    // If the switch is ON (LOW signal), hold the key; otherwise, release it
    for (int i = 0; i < 8; i++) {
        if (digitalRead(spstPins[i]) == LOW) {
            bleKeyboard.press(spstKeys[i]);
        } else {
            bleKeyboard.release(spstKeys[i]);
        }
    }

    // ========== HANDLE SPDT TOGGLE SWITCHES ========== //
    // Send a different keypress based on switch position
    for (int i = 0; i < 7; i++) {
        bool leftState = digitalRead(spdtLeftPins[i]);
        bool rightState = digitalRead(spdtRightPins[i]);

        if (leftState == LOW) {
            bleKeyboard.press(spdtLeftKeys[i]);
            bleKeyboard.release(spdtRightKeys[i]);
        } else if (rightState == LOW) {
            bleKeyboard.press(spdtRightKeys[i]);
            bleKeyboard.release(spdtLeftKeys[i]);
        } else {
            bleKeyboard.release(spdtLeftKeys[i]);
            bleKeyboard.release(spdtRightKeys[i]);
        }
    }

    // ========== HANDLE MOMENTARY BUTTONS ========== //
    // Check button state changes and send keypresses when pressed
    if (digitalRead(ignitionPin) == LOW && prevIgnitionState == HIGH) {
        bleKeyboard.press(ignitionKey);
        delay(10);
        bleKeyboard.release(ignitionKey);
    }
    prevIgnitionState = digitalRead(ignitionPin);

    for (int i = 0; i < 2; i++) {
        if (digitalRead(pushPullPins[i]) == LOW && prevPushPullState[i] == HIGH) {
            bleKeyboard.press(pushPullKeys[i]);
            delay(10);
            bleKeyboard.release(pushPullKeys[i]);
        }
        prevPushPullState[i] = digitalRead(pushPullPins[i]);
    }

    if (digitalRead(hazardPin) == LOW && prevHazardState == HIGH) {
        bleKeyboard.press(hazardKey);
        delay(10);
        bleKeyboard.release(hazardKey);
    }
    prevHazardState = digitalRead(hazardPin);

    if (digitalRead(pushReleasePin) == LOW && prevPushReleaseState == HIGH) {
        bleKeyboard.press(pushReleaseKey);
        delay(10);
        bleKeyboard.release(pushReleaseKey);
    }
    prevPushReleaseState = digitalRead(pushReleasePin);

    if (digitalRead(ncNoButton) == LOW && prevNcNoState == HIGH) {
        bleKeyboard.press(ncNoKey);
        delay(10);
        bleKeyboard.release(ncNoKey);
    }
    prevNcNoState = digitalRead(ncNoButton);

    delay(20); // Small delay to reduce CPU load
}
