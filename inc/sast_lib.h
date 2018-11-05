#ifndef SAST_LIB_H_
#define SAST_LIB_H_

#include <sensor.h>

// SENSOR DATA TYPES
#define SUPP_SENSORS_COUNT 26
#define SENS_ACCELEROMETER 0x00
#define SENS_GRAVITY 0x01
#define SENS_LINEAR_ACCELERATION 0x02
#define SENS_MAGNETIC 0x03
#define SENS_ROTATION_VECTOR 0x04
#define SENS_ORIENTATION 0x05
#define SENS_GYROSCOPE 0x06
#define SENS_LIGHT 0x07
#define SENS_PROXIMITY 0x08
#define SENS_PRESSURE 0x09
#define SENS_ULTRAVIOLET 0x0A
#define SENS_TEMPERATURE 0x0B
#define SENS_HUMIDITY 0x0C
#define SENS_HRM 0x0D
#define SENS_HRM_LED_GREEN 0x0E
#define SENS_HRM_LED_IR 0x0F
#define SENS_HRM_LED_RED 0x10
#define SENS_GYROSCOPE_UNCALIBRATED 0x11
#define SENS_GEOMAGNETIC_UNCALIBRATED 0x12
#define SENS_GYROSCOPE_ROTATION_VECTOR 0x13
#define SENS_GEOMAGNETIC_ROTATION_VECTOR 0x14
#define SENS_SIGNIFICANT_MOTION 0x15
#define SENS_HUMAN_PEDOMETER 0x16
#define SENS_HUMAN_SLEEP_MONITOR 0x17
#define SENS_HUMAN_SLEEP_DETECTOR 0x18
#define SENS_HUMAN_STRESS_MONITOR 0x19

// SAMPLING DURATION
#define DUR_SHORT 0x01
#define DUR_MEDIUM 0x02
#define DUR_LONG 0x03

// SAMPLING FREQUENCY
#define FREQ_LOW 0x01
#define FREQ_MEDIUM 0x02
#define FREQ_HIGH 0x03

// MESSAGING CONSTANTS
#define MSG_RES_OK 0x01
const static unsigned char MSG_RES_FAIL = 0x02;

// VARIABLES
static sensor_listener_h sensor_listeners[SUPP_SENSORS_COUNT];
static short sample_counters[SUPP_SENSORS_COUNT];
static short SAMPLE_CNT_MAX[SUPP_SENSORS_COUNT];

// FUNCTIONS
void sensors_callback(sensor_h, sensor_event_s *, void *);
static sensor_listener_h set_sensor_listener(sensor_h, unsigned int, void *);
void setup_sensor_callbacks();

#endif
