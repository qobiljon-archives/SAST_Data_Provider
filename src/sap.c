#include <glib.h>
#include <sap.h>
#include <device/power.h>
#include <sast_lib.h>
#include "helloaccessory.h"

#define SAST_ASPID "/sample/hello"
#define SAST_CHANNELID 104

struct priv {
	sap_agent_h agent;
	sap_socket_h socket;
	sap_peer_agent_h peer_agent;
};

static gboolean agent_created = FALSE;

static struct priv priv_data = { 0 };

static void on_service_connection_terminated(sap_peer_agent_h peer_agent, sap_socket_h socket, sap_service_connection_terminated_reason_e result, void *user_data) {
	switch (result) {
	case SAP_CONNECTION_TERMINATED_REASON_PEER_DISCONNECTED:
		dlog_print(DLOG_INFO, TAG, "disconnected because peer lost");
		break;

	case SAP_CONNECTION_TERMINATED_REASON_DEVICE_DETACHED:
		dlog_print(DLOG_INFO, TAG, "disconnected because device is detached");
		break;

	case SAP_CONNECTION_TERMINATED_REASON_UNKNOWN:
		dlog_print(DLOG_INFO, TAG, "disconnected because of unknown reason");
		break;
	}

	update_ui("Connection terminated");

	sap_socket_destroy(priv_data.socket);
	priv_data.socket = NULL;

	dlog_print(DLOG_INFO, TAG, "status:%d", result);
}

// TODO receives data from smartphone
static void on_data_recieved(sap_socket_h socket, unsigned short int channel_id, unsigned int payload_length, void *buffer, void *user_data) {
	// TODO print on a pop-up dialog
	dlog_print(DLOG_INFO, TAG, "VAL %d", (int) *(unsigned char*) buffer);

	short sample_interval = *((unsigned char*) buffer + 1) | ((*((unsigned char*) buffer + 2) << 8) & 0xff00);
	short sample_duration = *((unsigned char*) buffer + 3) | ((*((unsigned char*) buffer + 4) << 8) & 0xff00);

	switch (*(unsigned char*) buffer) {
	case SENS_ACCELEROMETER:
		update_ui("ACCELEROMETER REQUESTED");
		if (sensor_listeners[SENS_ACCELEROMETER] == NULL)
			sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 1, (void*) &MSG_RES_FAIL);
		else {
			sample_counters[SENS_ACCELEROMETER] = 0;
			SAMPLE_CNT_MAX[SENS_ACCELEROMETER] = sample_duration;
			sensor_listener_set_interval(sensor_listeners[SENS_ACCELEROMETER], sample_interval);
			sensor_listener_start(sensor_listeners[SENS_ACCELEROMETER]);
		}
		break;
	case SENS_GRAVITY:
		update_ui("GRAVITY REQUESTED");
		if (sensor_listeners[SENS_GRAVITY] == NULL)
			sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 1, (void*) &MSG_RES_FAIL);
		else {
			sample_counters[SENS_GRAVITY] = 0;
			SAMPLE_CNT_MAX[SENS_GRAVITY] = sample_duration;
			sensor_listener_set_interval(sensor_listeners[SENS_GRAVITY], sample_interval);
			sensor_listener_start(sensor_listeners[SENS_GRAVITY]);
		}
		break;
	case SENS_LINEAR_ACCELERATION:
		update_ui("LINEAR_ACCELERATION REQUESTED");
		if (sensor_listeners[SENS_LINEAR_ACCELERATION] == NULL)
			sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 1, (void*) &MSG_RES_FAIL);
		else {
			sample_counters[SENS_LINEAR_ACCELERATION] = 0;
			SAMPLE_CNT_MAX[SENS_LINEAR_ACCELERATION] = sample_duration;
			sensor_listener_set_interval(sensor_listeners[SENS_LINEAR_ACCELERATION], sample_interval);
			sensor_listener_start(sensor_listeners[SENS_LINEAR_ACCELERATION]);
		}
		break;
	case SENS_MAGNETIC:
		update_ui("MAGNETIC REQUESTED");
		if (sensor_listeners[SENS_MAGNETIC] == NULL)
			sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 1, (void*) &MSG_RES_FAIL);
		else {
			sample_counters[SENS_MAGNETIC] = 0;
			SAMPLE_CNT_MAX[SENS_MAGNETIC] = sample_duration;
			sensor_listener_set_interval(sensor_listeners[SENS_MAGNETIC], sample_interval);
			sensor_listener_start(sensor_listeners[SENS_MAGNETIC]);
		}
		break;
	case SENS_ROTATION_VECTOR:
		update_ui("ROTATION_VECTOR REQUESTED");
		if (sensor_listeners[SENS_ROTATION_VECTOR] == NULL)
			sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 1, (void*) &MSG_RES_FAIL);
		else {
			sample_counters[SENS_ROTATION_VECTOR] = 0;
			SAMPLE_CNT_MAX[SENS_ROTATION_VECTOR] = sample_duration;
			sensor_listener_set_interval(sensor_listeners[SENS_ROTATION_VECTOR], sample_interval);
			sensor_listener_start(sensor_listeners[SENS_ROTATION_VECTOR]);
		}
		break;
	case SENS_ORIENTATION:
		update_ui("ORIENTATION REQUESTED");
		if (sensor_listeners[SENS_ORIENTATION] == NULL)
			sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 1, (void*) &MSG_RES_FAIL);
		else {
			sample_counters[SENS_ORIENTATION] = 0;
			SAMPLE_CNT_MAX[SENS_ORIENTATION] = sample_duration;
			sensor_listener_set_interval(sensor_listeners[SENS_ORIENTATION], sample_interval);
			sensor_listener_start(sensor_listeners[SENS_ORIENTATION]);
		}
		break;
	case SENS_GYROSCOPE:
		update_ui("GYROSCOPE REQUESTED");
		if (sensor_listeners[SENS_GYROSCOPE] == NULL)
			sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 1, (void*) &MSG_RES_FAIL);
		else {
			sample_counters[SENS_GYROSCOPE] = 0;
			SAMPLE_CNT_MAX[SENS_GYROSCOPE] = sample_duration;
			sensor_listener_set_interval(sensor_listeners[SENS_GYROSCOPE], sample_interval);
			sensor_listener_start(sensor_listeners[SENS_GYROSCOPE]);
		}
		break;
	case SENS_LIGHT:
		update_ui("LIGHT REQUESTED");
		if (sensor_listeners[SENS_LIGHT] == NULL)
			sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 1, (void*) &MSG_RES_FAIL);
		else {
			sample_counters[SENS_LIGHT] = 0;
			SAMPLE_CNT_MAX[SENS_LIGHT] = sample_duration;
			sensor_listener_set_interval(sensor_listeners[SENS_LIGHT], sample_interval);
			sensor_listener_start(sensor_listeners[SENS_LIGHT]);
		}
		break;
	case SENS_PROXIMITY:
		update_ui("PROXIMITY REQUESTED");
		if (sensor_listeners[SENS_PROXIMITY] == NULL)
			sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 1, (void*) &MSG_RES_FAIL);
		else {
			sample_counters[SENS_PROXIMITY] = 0;
			SAMPLE_CNT_MAX[SENS_PROXIMITY] = sample_duration;
			sensor_listener_set_interval(sensor_listeners[SENS_PROXIMITY], sample_interval);
			sensor_listener_start(sensor_listeners[SENS_PROXIMITY]);
		}
		break;
	case SENS_PRESSURE:
		update_ui("PRESSURE REQUESTED");
		if (sensor_listeners[SENS_PRESSURE] == NULL)
			sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 1, (void*) &MSG_RES_FAIL);
		else {
			sample_counters[SENS_PRESSURE] = 0;
			SAMPLE_CNT_MAX[SENS_PRESSURE] = sample_duration;
			sensor_listener_set_interval(sensor_listeners[SENS_PRESSURE], sample_interval);
			sensor_listener_start(sensor_listeners[SENS_PRESSURE]);
		}
		break;
	case SENS_ULTRAVIOLET:
		update_ui("ULTRAVIOLET REQUESTED");
		if (sensor_listeners[SENS_ULTRAVIOLET] == NULL)
			sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 1, (void*) &MSG_RES_FAIL);
		else {
			sample_counters[SENS_ULTRAVIOLET] = 0;
			SAMPLE_CNT_MAX[SENS_ULTRAVIOLET] = sample_duration;
			sensor_listener_set_interval(sensor_listeners[SENS_ULTRAVIOLET], sample_interval);
			sensor_listener_start(sensor_listeners[SENS_ULTRAVIOLET]);
		}
		break;
	case SENS_TEMPERATURE:
		update_ui("TEMPERATURE REQUESTED");
		if (sensor_listeners[SENS_TEMPERATURE] == NULL)
			sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 1, (void*) &MSG_RES_FAIL);
		else {
			sample_counters[SENS_TEMPERATURE] = 0;
			SAMPLE_CNT_MAX[SENS_TEMPERATURE] = sample_duration;
			sensor_listener_set_interval(sensor_listeners[SENS_TEMPERATURE], sample_interval);
			sensor_listener_start(sensor_listeners[SENS_TEMPERATURE]);
		}
		break;
	case SENS_HUMIDITY:
		update_ui("HUMIDITY REQUESTED");
		if (sensor_listeners[SENS_HUMIDITY] == NULL)
			sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 1, (void*) &MSG_RES_FAIL);
		else {
			sample_counters[SENS_HUMIDITY] = 0;
			SAMPLE_CNT_MAX[SENS_HUMIDITY] = sample_duration;
			sensor_listener_set_interval(sensor_listeners[SENS_HUMIDITY], sample_interval);
			sensor_listener_start(sensor_listeners[SENS_HUMIDITY]);
		}
		break;
	case SENS_HRM:
		update_ui("HRM REQUESTED");
		if (sensor_listeners[SENS_HRM] == NULL)
			sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 1, (void*) &MSG_RES_FAIL);
		else {
			sample_counters[SENS_HRM] = 0;
			SAMPLE_CNT_MAX[SENS_HRM] = sample_duration;
			sensor_listener_set_interval(sensor_listeners[SENS_HRM], sample_interval);
			sensor_listener_start(sensor_listeners[SENS_HRM]);
		}
		break;
	case SENS_HRM_LED_GREEN:
		update_ui("HRM_LED_GREEN REQUESTED");
		if (sensor_listeners[SENS_HRM_LED_GREEN] == NULL)
			sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 1, (void*) &MSG_RES_FAIL);
		else {
			sample_counters[SENS_HRM_LED_GREEN] = 0;
			SAMPLE_CNT_MAX[SENS_HRM_LED_GREEN] = sample_duration;
			sensor_listener_set_interval(sensor_listeners[SENS_HRM_LED_GREEN], sample_interval);
			sensor_listener_start(sensor_listeners[SENS_HRM_LED_GREEN]);
		}
		break;
	case SENS_HRM_LED_IR:
		update_ui("HRM_LED_IR REQUESTED");
		if (sensor_listeners[SENS_HRM_LED_IR] == NULL)
			sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 1, (void*) &MSG_RES_FAIL);
		else {
			sample_counters[SENS_HRM_LED_IR] = 0;
			SAMPLE_CNT_MAX[SENS_HRM_LED_IR] = sample_duration;
			sensor_listener_set_interval(sensor_listeners[SENS_HRM_LED_IR], sample_interval);
			sensor_listener_start(sensor_listeners[SENS_HRM_LED_IR]);
		}
		break;
	case SENS_HRM_LED_RED:
		update_ui("HRM_LED_RED REQUESTED");
		if (sensor_listeners[SENS_HRM_LED_RED] == NULL)
			sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 1, (void*) &MSG_RES_FAIL);
		else {
			sample_counters[SENS_HRM_LED_RED] = 0;
			SAMPLE_CNT_MAX[SENS_HRM_LED_RED] = sample_duration;
			sensor_listener_set_interval(sensor_listeners[SENS_HRM_LED_RED], sample_interval);
			sensor_listener_start(sensor_listeners[SENS_HRM_LED_RED]);
		}
		break;
	case SENS_GYROSCOPE_UNCALIBRATED:
		update_ui("GYROSCOPE_UNCALIBRATED REQUESTED");
		if (sensor_listeners[SENS_GYROSCOPE_UNCALIBRATED] == NULL)
			sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 1, (void*) &MSG_RES_FAIL);
		else {
			sample_counters[SENS_GYROSCOPE_UNCALIBRATED] = 0;
			SAMPLE_CNT_MAX[SENS_GYROSCOPE_UNCALIBRATED] = sample_duration;
			sensor_listener_set_interval(sensor_listeners[SENS_GYROSCOPE_UNCALIBRATED], sample_interval);
			sensor_listener_start(sensor_listeners[SENS_GYROSCOPE_UNCALIBRATED]);
		}
		break;
	case SENS_GEOMAGNETIC_UNCALIBRATED:
		update_ui("GEOMAGNETIC_UNCALIBRATED REQUESTED");
		if (sensor_listeners[SENS_GEOMAGNETIC_UNCALIBRATED] == NULL)
			sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 1, (void*) &MSG_RES_FAIL);
		else {
			sample_counters[SENS_GEOMAGNETIC_UNCALIBRATED] = 0;
			SAMPLE_CNT_MAX[SENS_GEOMAGNETIC_UNCALIBRATED] = sample_duration;
			sensor_listener_set_interval(sensor_listeners[SENS_GEOMAGNETIC_UNCALIBRATED], sample_interval);
			sensor_listener_start(sensor_listeners[SENS_GEOMAGNETIC_UNCALIBRATED]);
		}
		break;
	case SENS_GYROSCOPE_ROTATION_VECTOR:
		update_ui("GYROSCOPE_ROTATION_VECTOR REQUESTED");
		if (sensor_listeners[SENS_GYROSCOPE_ROTATION_VECTOR] == NULL)
			sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 1, (void*) &MSG_RES_FAIL);
		else {
			sample_counters[SENS_GYROSCOPE_ROTATION_VECTOR] = 0;
			SAMPLE_CNT_MAX[SENS_GYROSCOPE_ROTATION_VECTOR] = sample_duration;
			sensor_listener_set_interval(sensor_listeners[SENS_GYROSCOPE_ROTATION_VECTOR], sample_interval);
			sensor_listener_start(sensor_listeners[SENS_GYROSCOPE_ROTATION_VECTOR]);
		}
		break;
	case SENS_GEOMAGNETIC_ROTATION_VECTOR:
		update_ui("GEOMAGNETIC_ROTATION_VECTOR REQUESTED");
		if (sensor_listeners[SENS_GEOMAGNETIC_ROTATION_VECTOR] == NULL)
			sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 1, (void*) &MSG_RES_FAIL);
		else {
			sample_counters[SENS_GEOMAGNETIC_ROTATION_VECTOR] = 0;
			SAMPLE_CNT_MAX[SENS_GEOMAGNETIC_ROTATION_VECTOR] = sample_duration;
			sensor_listener_set_interval(sensor_listeners[SENS_GEOMAGNETIC_ROTATION_VECTOR], sample_interval);
			sensor_listener_start(sensor_listeners[SENS_GEOMAGNETIC_ROTATION_VECTOR]);
		}
		break;
	case SENS_SIGNIFICANT_MOTION:
		update_ui("SIGNIFICANT_MOTION REQUESTED");
		if (sensor_listeners[SENS_SIGNIFICANT_MOTION] == NULL)
			sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 1, (void*) &MSG_RES_FAIL);
		else {
			sample_counters[SENS_SIGNIFICANT_MOTION] = 0;
			SAMPLE_CNT_MAX[SENS_SIGNIFICANT_MOTION] = sample_duration;
			sensor_listener_set_interval(sensor_listeners[SENS_SIGNIFICANT_MOTION], sample_interval);
			sensor_listener_start(sensor_listeners[SENS_SIGNIFICANT_MOTION]);
		}
		break;
	case SENS_HUMAN_PEDOMETER:
		update_ui("HUMAN_PEDOMETER REQUESTED");
		if (sensor_listeners[SENS_HUMAN_PEDOMETER] == NULL)
			sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 1, (void*) &MSG_RES_FAIL);
		else {
			sample_counters[SENS_HUMAN_PEDOMETER] = 0;
			SAMPLE_CNT_MAX[SENS_HUMAN_PEDOMETER] = sample_duration;
			sensor_listener_set_interval(sensor_listeners[SENS_HUMAN_PEDOMETER], sample_interval);
			sensor_listener_start(sensor_listeners[SENS_HUMAN_PEDOMETER]);
		}
		break;
	case SENS_HUMAN_SLEEP_MONITOR:
		update_ui("HUMAN_SLEEP_MONITOR REQUESTED");
		if (sensor_listeners[SENS_HUMAN_SLEEP_MONITOR] == NULL)
			sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 1, (void*) &MSG_RES_FAIL);
		else {
			sample_counters[SENS_HUMAN_SLEEP_MONITOR] = 0;
			SAMPLE_CNT_MAX[SENS_HUMAN_SLEEP_MONITOR] = sample_duration;
			sensor_listener_set_interval(sensor_listeners[SENS_HUMAN_SLEEP_MONITOR], sample_interval);
			sensor_listener_start(sensor_listeners[SENS_HUMAN_SLEEP_MONITOR]);
		}
		break;
	case SENS_HUMAN_SLEEP_DETECTOR:
		update_ui("HUMAN_SLEEP_DETECTOR REQUESTED");
		if (sensor_listeners[SENS_HUMAN_SLEEP_DETECTOR] == NULL)
			sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 1, (void*) &MSG_RES_FAIL);
		else {
			sample_counters[SENS_HUMAN_SLEEP_DETECTOR] = 0;
			SAMPLE_CNT_MAX[SENS_HUMAN_SLEEP_DETECTOR] = sample_duration;
			sensor_listener_set_interval(sensor_listeners[SENS_HUMAN_SLEEP_DETECTOR], sample_interval);
			sensor_listener_start(sensor_listeners[SENS_HUMAN_SLEEP_DETECTOR]);
		}
		break;
	case SENS_HUMAN_STRESS_MONITOR:
		update_ui("HUMAN_STRESS_MONITOR REQUESTED");
		if (sensor_listeners[SENS_HUMAN_STRESS_MONITOR] == NULL)
			sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 1, (void*) &MSG_RES_FAIL);
		else {
			sample_counters[SENS_HUMAN_STRESS_MONITOR] = 0;
			SAMPLE_CNT_MAX[SENS_HUMAN_STRESS_MONITOR] = sample_duration;
			sensor_listener_set_interval(sensor_listeners[SENS_HUMAN_STRESS_MONITOR], sample_interval);
			sensor_listener_start(sensor_listeners[SENS_HUMAN_STRESS_MONITOR]);
		}
		break;
	default:
		break;
	}
}

static void on_service_connection_requested(sap_peer_agent_h peer_agent, sap_socket_h socket, sap_service_connection_result_e result, void *user_data) {
	priv_data.socket = socket;
	priv_data.peer_agent = peer_agent;

	sap_peer_agent_set_service_connection_terminated_cb(priv_data.peer_agent, on_service_connection_terminated, user_data);

	sap_socket_set_data_received_cb(socket, on_data_recieved, peer_agent);

	sap_peer_agent_accept_service_connection(peer_agent);

	update_ui("Connection Established");
}

static void on_agent_initialized(sap_agent_h agent, sap_agent_initialized_result_e result, void *user_data) {
	switch (result) {
	case SAP_AGENT_INITIALIZED_RESULT_SUCCESS:
		dlog_print(DLOG_INFO, TAG, "agent is initialized");

		sap_agent_set_service_connection_requested_cb(agent, on_service_connection_requested, NULL);

		priv_data.agent = agent;
		agent_created = true;

		setup_sensor_callbacks();

		break;

	case SAP_AGENT_INITIALIZED_RESULT_DUPLICATED:
		dlog_print(DLOG_INFO, TAG, "duplicate registration");
		break;

	case SAP_AGENT_INITIALIZED_RESULT_INVALID_ARGUMENTS:
		dlog_print(DLOG_INFO, TAG, "invalid arguments");
		break;

	case SAP_AGENT_INITIALIZED_RESULT_INTERNAL_ERROR:
		dlog_print(DLOG_INFO, TAG, "internal sap error");
		break;

	default:
		dlog_print(DLOG_INFO, TAG, "unknown status (%d)", result);
		break;
	}

	dlog_print(DLOG_INFO, TAG, "agent initialized callback is over");
}

static void on_device_status_changed(sap_device_status_e status, sap_transport_type_e transport_type, void *user_data) {
	switch (transport_type) {
	case SAP_TRANSPORT_TYPE_BT:
		dlog_print(DLOG_INFO, TAG, "connectivity type(%d): bt", transport_type);
		break;

	case SAP_TRANSPORT_TYPE_BLE:
		dlog_print(DLOG_INFO, TAG, "connectivity type(%d): ble", transport_type);
		break;

	case SAP_TRANSPORT_TYPE_TCP:
		dlog_print(DLOG_INFO, TAG, "connectivity type(%d): tcp/ip", transport_type);
		break;

	case SAP_TRANSPORT_TYPE_USB:
		dlog_print(DLOG_INFO, TAG, "connectivity type(%d): usb", transport_type);
		break;

	case SAP_TRANSPORT_TYPE_MOBILE:
		dlog_print(DLOG_INFO, TAG, "connectivity type(%d): mobile", transport_type);
		break;

	default:
		dlog_print(DLOG_INFO, TAG, "unknown connectivity type (%d)", transport_type);
		break;
	}

	switch (status) {
	case SAP_DEVICE_STATUS_DETACHED:

		if (priv_data.peer_agent) {
			sap_socket_destroy(priv_data.socket);
			priv_data.socket = NULL;
			sap_peer_agent_destroy(priv_data.peer_agent);
			priv_data.peer_agent = NULL;

		}

		break;

	case SAP_DEVICE_STATUS_ATTACHED:
		break;

	default:
		dlog_print(DLOG_INFO, TAG, "unknown status (%d)", status);
		break;
	}
}

gboolean agent_initialize() {
	int result = 0;

	do {
		result = sap_agent_initialize(priv_data.agent, SAST_ASPID, SAP_AGENT_ROLE_PROVIDER, on_agent_initialized, NULL);

		dlog_print(DLOG_INFO, TAG, "SAP >>> getRegisteredServiceAgent() >>> %d", result);
	} while (result != SAP_RESULT_SUCCESS);

	return true;
}

void initialize_sap() {
	sap_agent_h agent = NULL;

	sap_agent_create(&agent);

	if (agent == NULL)
		dlog_print(DLOG_ERROR, TAG, "ERROR in creating agent");
	else
		dlog_print(DLOG_INFO, TAG, "SUCCESSFULLY create sap agent");

	priv_data.agent = agent;

	sap_set_device_status_changed_cb(on_device_status_changed, NULL);

	agent_initialize();
}

// TODO sensor callback for any sensor
void sensors_callback(sensor_h sensor, sensor_event_s *event, void *user_data) {
	sensor_type_e type;
	sensor_get_type(sensor, &type);

	unsigned char buf[64] = { MSG_RES_OK, SENS_ACCELEROMETER };
	switch (type) {
	case SENSOR_ACCELEROMETER: {
		unsigned long long timestamp = event->timestamp;
		int accuracy = event->accuracy;

		float x = event->values[0];
		float y = event->values[1];
		float z = event->values[2];

		memcpy(buf + 2, (unsigned char*) (&timestamp), 8);
		memcpy(buf + 10, (unsigned char*) (&accuracy), 4);
		memcpy(buf + 14, (unsigned char*) (&x), 4);
		memcpy(buf + 18, (unsigned char*) (&y), 4);
		memcpy(buf + 22, (unsigned char*) (&z), 4);

		sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 26, buf);
		sample_counters[SENS_ACCELEROMETER]++;
		if (sample_counters[SENS_ACCELEROMETER] == SAMPLE_CNT_MAX[SENS_ACCELEROMETER])
			sensor_listener_stop(sensor_listeners[SENS_ACCELEROMETER]);
	}
		break;
	case SENSOR_GRAVITY: {
		unsigned long long timestamp = event->timestamp;
		int accuracy = event->accuracy;

		float x = event->values[0];
		float y = event->values[1];
		float z = event->values[2];

		memcpy(buf + 2, (unsigned char*) (&timestamp), 8);
		memcpy(buf + 10, (unsigned char*) (&accuracy), 4);
		memcpy(buf + 14, (unsigned char*) (&x), 4);
		memcpy(buf + 18, (unsigned char*) (&y), 4);
		memcpy(buf + 22, (unsigned char*) (&z), 4);

		sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 26, buf);
		sample_counters[SENS_GRAVITY]++;
		if (sample_counters[SENS_GRAVITY] == SAMPLE_CNT_MAX[SENS_GRAVITY])
			sensor_listener_stop(sensor_listeners[SENS_GRAVITY]);
	}
		break;
	case SENSOR_LINEAR_ACCELERATION: {
		unsigned long long timestamp = event->timestamp;
		int accuracy = event->accuracy;

		float x = event->values[0];
		float y = event->values[1];
		float z = event->values[2];

		memcpy(buf + 2, (unsigned char*) (&timestamp), 8);
		memcpy(buf + 10, (unsigned char*) (&accuracy), 4);
		memcpy(buf + 14, (unsigned char*) (&x), 4);
		memcpy(buf + 18, (unsigned char*) (&y), 4);
		memcpy(buf + 22, (unsigned char*) (&z), 4);

		sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 26, buf);
		sample_counters[SENS_LINEAR_ACCELERATION]++;
		if (sample_counters[SENS_LINEAR_ACCELERATION] == SAMPLE_CNT_MAX[SENS_LINEAR_ACCELERATION])
			sensor_listener_stop(sensor_listeners[SENS_LINEAR_ACCELERATION]);
	}
		break;
	case SENSOR_MAGNETIC: {
		unsigned long long timestamp = event->timestamp;
		int accuracy = event->accuracy;

		float x = event->values[0];
		float y = event->values[1];
		float z = event->values[2];

		memcpy(buf + 2, (unsigned char*) (&timestamp), 8);
		memcpy(buf + 10, (unsigned char*) (&accuracy), 4);
		memcpy(buf + 14, (unsigned char*) (&x), 4);
		memcpy(buf + 18, (unsigned char*) (&y), 4);
		memcpy(buf + 22, (unsigned char*) (&z), 4);

		sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 26, buf);
		sample_counters[SENS_MAGNETIC]++;
		if (sample_counters[SENS_MAGNETIC] == SAMPLE_CNT_MAX[SENS_MAGNETIC])
			sensor_listener_stop(sensor_listeners[SENS_MAGNETIC]);
	}
		break;
	case SENSOR_ROTATION_VECTOR: {
		unsigned long long timestamp = event->timestamp;
		int accuracy = event->accuracy;

		float x = event->values[0];
		float y = event->values[1];
		float z = event->values[2];
		float w = event->values[3];

		memcpy(buf + 2, (unsigned char*) (&timestamp), 8);
		memcpy(buf + 10, (unsigned char*) (&accuracy), 4);
		memcpy(buf + 14, (unsigned char*) (&x), 4);
		memcpy(buf + 18, (unsigned char*) (&y), 4);
		memcpy(buf + 22, (unsigned char*) (&z), 4);
		memcpy(buf + 26, (unsigned char*) (&w), 4);

		sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 30, buf);
		sample_counters[SENS_ROTATION_VECTOR]++;
		if (sample_counters[SENS_ROTATION_VECTOR] == SAMPLE_CNT_MAX[SENS_ROTATION_VECTOR])
			sensor_listener_stop(sensor_listeners[SENS_ROTATION_VECTOR]);
	}
		break;
	case SENSOR_ORIENTATION: {
		unsigned long long timestamp = event->timestamp;
		int accuracy = event->accuracy;

		float azimuth = event->values[0];
		float pitch = event->values[1];
		float roll = event->values[2];

		memcpy(buf + 2, (unsigned char*) (&timestamp), 8);
		memcpy(buf + 10, (unsigned char*) (&accuracy), 4);
		memcpy(buf + 14, (unsigned char*) (&azimuth), 4);
		memcpy(buf + 18, (unsigned char*) (&pitch), 4);
		memcpy(buf + 22, (unsigned char*) (&roll), 4);

		sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 26, buf);
		sample_counters[SENS_ORIENTATION]++;
		if (sample_counters[SENS_ORIENTATION] == SAMPLE_CNT_MAX[SENS_ORIENTATION])
			sensor_listener_stop(sensor_listeners[SENS_ORIENTATION]);
	}
		break;
	case SENSOR_GYROSCOPE: {
		unsigned long long timestamp = event->timestamp;
		int accuracy = event->accuracy;

		float x = event->values[0];
		float y = event->values[1];
		float z = event->values[2];

		memcpy(buf + 2, (unsigned char*) (&timestamp), 8);
		memcpy(buf + 10, (unsigned char*) (&accuracy), 4);
		memcpy(buf + 14, (unsigned char*) (&x), 4);
		memcpy(buf + 18, (unsigned char*) (&y), 4);
		memcpy(buf + 22, (unsigned char*) (&z), 4);

		sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 26, buf);
		sample_counters[SENS_GYROSCOPE]++;
		if (sample_counters[SENS_GYROSCOPE] == SAMPLE_CNT_MAX[SENS_GYROSCOPE])
			sensor_listener_stop(sensor_listeners[SENS_GYROSCOPE]);
	}
		break;
	case SENSOR_LIGHT: {
		unsigned long long timestamp = event->timestamp;
		int accuracy = event->accuracy;

		int level = event->values[0];

		memcpy(buf + 2, (unsigned char*) (&timestamp), 8);
		memcpy(buf + 10, (unsigned char*) (&accuracy), 4);
		memcpy(buf + 14, (unsigned char*) (&level), 4);

		sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 18, buf);
		sample_counters[SENS_LIGHT]++;
		if (sample_counters[SENS_LIGHT] == SAMPLE_CNT_MAX[SENS_LIGHT])
			sensor_listener_stop(sensor_listeners[SENS_LIGHT]);
	}
		break;
	case SENSOR_PROXIMITY: {
		unsigned long long timestamp = event->timestamp;
		int accuracy = event->accuracy;

		float proximity = event->values[0];

		memcpy(buf + 2, (unsigned char*) (&timestamp), 8);
		memcpy(buf + 10, (unsigned char*) (&accuracy), 4);
		memcpy(buf + 14, (unsigned char*) (&proximity), 4);

		sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 18, buf);
		sample_counters[SENS_PROXIMITY]++;
		if (sample_counters[SENS_PROXIMITY] == SAMPLE_CNT_MAX[SENS_PROXIMITY])
			sensor_listener_stop(sensor_listeners[SENS_PROXIMITY]);
	}
		break;
	case SENSOR_PRESSURE: {
		unsigned long long timestamp = event->timestamp;
		int accuracy = event->accuracy;

		float pressure = event->values[0];

		memcpy(buf + 2, (unsigned char*) (&timestamp), 8);
		memcpy(buf + 10, (unsigned char*) (&accuracy), 4);
		memcpy(buf + 14, (unsigned char*) (&pressure), 4);

		sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 18, buf);
		sample_counters[SENS_PRESSURE]++;
		if (sample_counters[SENS_PRESSURE] == SAMPLE_CNT_MAX[SENS_PRESSURE])
			sensor_listener_stop(sensor_listeners[SENS_PRESSURE]);
	}
		break;
	case SENSOR_ULTRAVIOLET: {
		unsigned long long timestamp = event->timestamp;
		int accuracy = event->accuracy;

		float uv_index = event->values[0];

		memcpy(buf + 2, (unsigned char*) (&timestamp), 8);
		memcpy(buf + 10, (unsigned char*) (&accuracy), 4);
		memcpy(buf + 14, (unsigned char*) (&uv_index), 4);

		sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 18, buf);
		sample_counters[SENS_ULTRAVIOLET]++;
		if (sample_counters[SENS_ULTRAVIOLET] == SAMPLE_CNT_MAX[SENS_ULTRAVIOLET])
			sensor_listener_stop(sensor_listeners[SENS_ULTRAVIOLET]);
	}
		break;
	case SENSOR_TEMPERATURE: {
		unsigned long long timestamp = event->timestamp;
		int accuracy = event->accuracy;

		float temperature = event->values[0];

		memcpy(buf + 2, (unsigned char*) (&timestamp), 8);
		memcpy(buf + 10, (unsigned char*) (&accuracy), 4);
		memcpy(buf + 14, (unsigned char*) (&temperature), 4);

		sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 18, buf);
		sample_counters[SENS_TEMPERATURE]++;
		if (sample_counters[SENS_TEMPERATURE] == SAMPLE_CNT_MAX[SENS_TEMPERATURE])
			sensor_listener_stop(sensor_listeners[SENS_TEMPERATURE]);
	}
		break;
	case SENSOR_HUMIDITY: {
		unsigned long long timestamp = event->timestamp;
		int accuracy = event->accuracy;

		float humidity = event->values[0];

		memcpy(buf + 2, (unsigned char*) (&timestamp), 8);
		memcpy(buf + 10, (unsigned char*) (&accuracy), 4);
		memcpy(buf + 14, (unsigned char*) (&humidity), 4);

		sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 18, buf);
		sample_counters[SENS_HUMIDITY]++;
		if (sample_counters[SENS_HUMIDITY] == SAMPLE_CNT_MAX[SENS_HUMIDITY])
			sensor_listener_stop(sensor_listeners[SENS_HUMIDITY]);
	}
		break;
	case SENSOR_HRM: {
		unsigned long long timestamp = event->timestamp;
		int accuracy = event->accuracy;

		int beats_per_minute = (int) event->values;

		memcpy(buf + 2, (unsigned char*) (&timestamp), 8);
		memcpy(buf + 10, (unsigned char*) (&accuracy), 4);
		memcpy(buf + 14, (unsigned char*) (&beats_per_minute), 4);

		sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 18, buf);
		sample_counters[SENS_HRM]++;
		if (sample_counters[SENS_HRM] == SAMPLE_CNT_MAX[SENS_HRM])
			sensor_listener_stop(sensor_listeners[SENS_HRM]);
	}
		break;
	case SENSOR_HRM_LED_GREEN: {
		unsigned long long timestamp = event->timestamp;
		int accuracy = event->accuracy;

		int hrm_green_light_value = (int) event->values[0];

		memcpy(buf + 2, (unsigned char*) (&timestamp), 8);
		memcpy(buf + 10, (unsigned char*) (&accuracy), 4);
		memcpy(buf + 14, (unsigned char*) (&hrm_green_light_value), 4);

		sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 18, buf);
		sample_counters[SENS_HRM_LED_GREEN]++;
		if (sample_counters[SENS_HRM_LED_GREEN] == SAMPLE_CNT_MAX[SENS_HRM_LED_GREEN])
			sensor_listener_stop(sensor_listeners[SENS_HRM_LED_GREEN]);
	}
		break;
	case SENSOR_HRM_LED_IR: {
		unsigned long long timestamp = event->timestamp;
		int accuracy = event->accuracy;

		int hrm_ir_light_value = (int) event->values[0];

		memcpy(buf + 2, (unsigned char*) (&timestamp), 8);
		memcpy(buf + 10, (unsigned char*) (&accuracy), 4);
		memcpy(buf + 14, (unsigned char*) (&hrm_ir_light_value), 4);

		sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 18, buf);
		sample_counters[SENS_HRM_LED_IR]++;
		if (sample_counters[SENS_HRM_LED_IR] == SAMPLE_CNT_MAX[SENS_HRM_LED_IR])
			sensor_listener_stop(sensor_listeners[SENS_HRM_LED_IR]);
	}
		break;
	case SENSOR_HRM_LED_RED: {
		unsigned long long timestamp = event->timestamp;
		int accuracy = event->accuracy;

		int hrm_red_light_value = (int) event->values[0];

		memcpy(buf + 2, (unsigned char*) (&timestamp), 8);
		memcpy(buf + 10, (unsigned char*) (&accuracy), 4);
		memcpy(buf + 14, (unsigned char*) (&hrm_red_light_value), 4);

		sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 18, buf);
		sample_counters[SENS_HRM_LED_RED]++;
		if (sample_counters[SENS_HRM_LED_RED] == SAMPLE_CNT_MAX[SENS_HRM_LED_RED])
			sensor_listener_stop(sensor_listeners[SENS_HRM_LED_RED]);
	}
		break;
	case SENSOR_GYROSCOPE_UNCALIBRATED: {
		unsigned long long timestamp = event->timestamp;
		int accuracy = event->accuracy;

		float x = event->values[0];
		float y = event->values[1];
		float z = event->values[2];
		float x_drift = event->values[3];
		float y_drift = event->values[4];
		float z_drift = event->values[5];

		memcpy(buf + 2, (unsigned char*) (&timestamp), 8);
		memcpy(buf + 10, (unsigned char*) (&accuracy), 4);
		memcpy(buf + 14, (unsigned char*) (&x), 4);
		memcpy(buf + 18, (unsigned char*) (&y), 4);
		memcpy(buf + 22, (unsigned char*) (&z), 4);
		memcpy(buf + 26, (unsigned char*) (&x_drift), 4);
		memcpy(buf + 30, (unsigned char*) (&y_drift), 4);
		memcpy(buf + 34, (unsigned char*) (&z_drift), 4);

		sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 38, buf);
		sample_counters[SENS_GYROSCOPE_UNCALIBRATED]++;
		if (sample_counters[SENS_GYROSCOPE_UNCALIBRATED] == SAMPLE_CNT_MAX[SENS_GYROSCOPE_UNCALIBRATED])
			sensor_listener_stop(sensor_listeners[SENS_GYROSCOPE_UNCALIBRATED]);
	}
		break;
	case SENSOR_GEOMAGNETIC_UNCALIBRATED: {
		unsigned long long timestamp = event->timestamp;
		int accuracy = event->accuracy;

		float x = event->values[0];
		float y = event->values[1];
		float z = event->values[2];
		float x_bias = event->values[3];
		float y_bias = event->values[4];
		float z_bias = event->values[5];

		memcpy(buf + 2, (unsigned char*) (&timestamp), 8);
		memcpy(buf + 10, (unsigned char*) (&accuracy), 4);
		memcpy(buf + 14, (unsigned char*) (&x), 4);
		memcpy(buf + 18, (unsigned char*) (&y), 4);
		memcpy(buf + 22, (unsigned char*) (&z), 4);
		memcpy(buf + 26, (unsigned char*) (&x_bias), 4);
		memcpy(buf + 30, (unsigned char*) (&y_bias), 4);
		memcpy(buf + 34, (unsigned char*) (&z_bias), 4);

		sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 38, buf);
		sample_counters[SENS_GEOMAGNETIC_UNCALIBRATED]++;
		if (sample_counters[SENS_GEOMAGNETIC_UNCALIBRATED] == SAMPLE_CNT_MAX[SENS_GEOMAGNETIC_UNCALIBRATED])
			sensor_listener_stop(sensor_listeners[SENS_GEOMAGNETIC_UNCALIBRATED]);
	}
		break;
	case SENSOR_GYROSCOPE_ROTATION_VECTOR: {
		unsigned long long timestamp = event->timestamp;
		int accuracy = event->accuracy;

		float x = event->values[0];
		float y = event->values[1];
		float z = event->values[2];
		float w = event->values[3];

		memcpy(buf + 2, (unsigned char*) (&timestamp), 8);
		memcpy(buf + 10, (unsigned char*) (&accuracy), 4);
		memcpy(buf + 14, (unsigned char*) (&x), 4);
		memcpy(buf + 18, (unsigned char*) (&y), 4);
		memcpy(buf + 22, (unsigned char*) (&z), 4);
		memcpy(buf + 26, (unsigned char*) (&w), 4);

		sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 30, buf);
		sample_counters[SENS_GYROSCOPE_ROTATION_VECTOR]++;
		if (sample_counters[SENS_GYROSCOPE_ROTATION_VECTOR] == SAMPLE_CNT_MAX[SENS_GYROSCOPE_ROTATION_VECTOR])
			sensor_listener_stop(sensor_listeners[SENS_GYROSCOPE_ROTATION_VECTOR]);
	}
		break;
	case SENSOR_GEOMAGNETIC_ROTATION_VECTOR: {
		unsigned long long timestamp = event->timestamp;
		int accuracy = event->accuracy;

		float x = event->values[0];
		float y = event->values[1];
		float z = event->values[2];
		float w = event->values[3];

		memcpy(buf + 2, (unsigned char*) (&timestamp), 8);
		memcpy(buf + 10, (unsigned char*) (&accuracy), 4);
		memcpy(buf + 14, (unsigned char*) (&x), 4);
		memcpy(buf + 18, (unsigned char*) (&y), 4);
		memcpy(buf + 22, (unsigned char*) (&z), 4);
		memcpy(buf + 26, (unsigned char*) (&w), 4);

		sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 30, buf);
		sample_counters[SENS_GEOMAGNETIC_ROTATION_VECTOR]++;
		if (sample_counters[SENS_GEOMAGNETIC_ROTATION_VECTOR] == SAMPLE_CNT_MAX[SENS_GEOMAGNETIC_ROTATION_VECTOR])
			sensor_listener_stop(sensor_listeners[SENS_GEOMAGNETIC_ROTATION_VECTOR]);
	}
		break;
	case SENSOR_SIGNIFICANT_MOTION: {
		unsigned long long timestamp = event->timestamp;
		int accuracy = event->accuracy;

		float significant_motion_detected = event->values[0];

		memcpy(buf + 2, (unsigned char*) (&timestamp), 8);
		memcpy(buf + 10, (unsigned char*) (&accuracy), 4);
		memcpy(buf + 14, (unsigned char*) (&significant_motion_detected), 4);

		sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 18, buf);
		sample_counters[SENS_SIGNIFICANT_MOTION]++;
		if (sample_counters[SENS_SIGNIFICANT_MOTION] == SAMPLE_CNT_MAX[SENS_SIGNIFICANT_MOTION])
			sensor_listener_stop(sensor_listeners[SENS_SIGNIFICANT_MOTION]);
	}
		break;
	case SENSOR_HUMAN_PEDOMETER: {
		unsigned long long timestamp = event->timestamp;
		int accuracy = event->accuracy;

		int number_of_steps = (int) event->values[0];
		int number_of_walking_steps = (int) event->values[1];
		int number_of_running_steps = (int) event->values[2];
		int moving_distance = (int) event->values[3];
		int calories_burned = (int) event->values[4];
		int last_speed = (int) event->values[5];
		int last_stepping_frequency = (int) event->values[6];
		int last_pedestrian_state = (int) event->values[7];

		memcpy(buf + 2, (unsigned char*) (&timestamp), 8);
		memcpy(buf + 10, (unsigned char*) (&accuracy), 4);
		memcpy(buf + 14, (unsigned char*) (&number_of_steps), 4);
		memcpy(buf + 18, (unsigned char*) (&number_of_walking_steps), 4);
		memcpy(buf + 22, (unsigned char*) (&number_of_running_steps), 4);
		memcpy(buf + 26, (unsigned char*) (&moving_distance), 4);
		memcpy(buf + 26, (unsigned char*) (&calories_burned), 4);
		memcpy(buf + 26, (unsigned char*) (&last_speed), 4);
		memcpy(buf + 26, (unsigned char*) (&last_stepping_frequency), 4);
		memcpy(buf + 26, (unsigned char*) (&last_pedestrian_state), 4);

		sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 30, buf);
		sample_counters[SENS_HUMAN_PEDOMETER]++;
		if (sample_counters[SENS_HUMAN_PEDOMETER] == SAMPLE_CNT_MAX[SENS_HUMAN_PEDOMETER])
			sensor_listener_stop(sensor_listeners[SENS_HUMAN_PEDOMETER]);
	}
		break;
	case SENSOR_HUMAN_SLEEP_MONITOR: {
		unsigned long long timestamp = event->timestamp;
		int accuracy = event->accuracy;

		int user_sleep_state = (int) event->values[0];

		memcpy(buf + 2, (unsigned char*) (&timestamp), 8);
		memcpy(buf + 10, (unsigned char*) (&accuracy), 4);
		memcpy(buf + 14, (unsigned char*) (&user_sleep_state), 4);

		sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 18, buf);
		sample_counters[SENS_HUMAN_SLEEP_MONITOR]++;
		if (sample_counters[SENS_HUMAN_SLEEP_MONITOR] == SAMPLE_CNT_MAX[SENS_HUMAN_SLEEP_MONITOR])
			sensor_listener_stop(sensor_listeners[SENS_HUMAN_SLEEP_MONITOR]);
	}
		break;
	case SENSOR_HUMAN_SLEEP_DETECTOR:
		break;
	case SENSOR_HUMAN_STRESS_MONITOR:
		break;
	default:
		buf[0] = MSG_RES_FAIL;
		sap_socket_send_data(priv_data.socket, SAST_CHANNELID, 1, buf);
		break;
	}
}

// TODO sets individual listener to sensor
static sensor_listener_h set_sensor_listener(sensor_h sensor, unsigned int interval_ms, void *data) {
	sensor_listener_h listener;
	sensor_create_listener(sensor, &listener);
	sensor_listener_set_option(listener, SENSOR_OPTION_ALWAYS_ON);
	sensor_listener_set_attribute_int(listener, SENSOR_ATTRIBUTE_PAUSE_POLICY, SENSOR_PAUSE_NONE);
	sensor_listener_set_event_cb(listener, interval_ms, sensors_callback, data);
	return listener;
}

// TODO sensor callbacks are set
void setup_sensor_callbacks() {
	dlog_print(DLOG_INFO, TAG, "Setting up sensor callbacks");
	device_power_request_lock(POWER_LOCK_CPU, 0);

	bool supported = false;
	sensor_h sensor;
	sensor_is_supported(SENSOR_ACCELEROMETER, &supported);
	if (supported) {
		sensor_get_default_sensor(SENSOR_ACCELEROMETER, &sensor);
		sensor_listeners[SENS_ACCELEROMETER] = set_sensor_listener(sensor, 100, NULL);
		update_ui("ACCELEROMETER IS NOT NULL");
	} else {
		sensor_listeners[SENS_ACCELEROMETER] = NULL;
		update_ui("ERROR OCCURRED");
	}
	sensor_is_supported(SENSOR_GRAVITY, &supported);
	if (supported) {
		sensor_get_default_sensor(SENSOR_GRAVITY, &sensor);
		sensor_listeners[SENS_GRAVITY] = set_sensor_listener(sensor, 100, NULL);
	} else
		sensor_listeners[SENS_GRAVITY] = NULL;
	sensor_is_supported(SENSOR_LINEAR_ACCELERATION, &supported);
	if (supported) {
		sensor_get_default_sensor(SENSOR_LINEAR_ACCELERATION, &sensor);
		sensor_listeners[SENS_LINEAR_ACCELERATION] = set_sensor_listener(sensor, 100, NULL);
	} else
		sensor_listeners[SENS_LINEAR_ACCELERATION] = NULL;
	sensor_is_supported(SENSOR_MAGNETIC, &supported);
	if (supported) {
		sensor_get_default_sensor(SENSOR_MAGNETIC, &sensor);
		sensor_listeners[SENS_MAGNETIC] = set_sensor_listener(sensor, 100, NULL);
	} else
		sensor_listeners[SENS_MAGNETIC] = NULL;
	sensor_is_supported(SENSOR_ROTATION_VECTOR, &supported);
	if (supported) {
		sensor_get_default_sensor(SENSOR_ROTATION_VECTOR, &sensor);
		sensor_listeners[SENS_ROTATION_VECTOR] = set_sensor_listener(sensor, 100, NULL);
	} else
		sensor_listeners[SENS_ROTATION_VECTOR] = NULL;
	sensor_is_supported(SENSOR_ORIENTATION, &supported);
	if (supported) {
		sensor_get_default_sensor(SENSOR_ORIENTATION, &sensor);
		sensor_listeners[SENS_ORIENTATION] = set_sensor_listener(sensor, 100, NULL);
	} else
		sensor_listeners[SENS_ORIENTATION] = NULL;
	sensor_is_supported(SENSOR_GYROSCOPE, &supported);
	if (supported) {
		sensor_get_default_sensor(SENSOR_GYROSCOPE, &sensor);
		sensor_listeners[SENS_GYROSCOPE] = set_sensor_listener(sensor, 100, NULL);
	} else
		sensor_listeners[SENS_GYROSCOPE] = NULL;
	sensor_is_supported(SENSOR_LIGHT, &supported);
	if (supported) {
		sensor_get_default_sensor(SENSOR_LIGHT, &sensor);
		sensor_listeners[SENS_LIGHT] = set_sensor_listener(sensor, 100, NULL);
	} else
		sensor_listeners[SENS_LIGHT] = NULL;
	sensor_is_supported(SENSOR_PROXIMITY, &supported);
	if (supported) {
		sensor_get_default_sensor(SENSOR_PROXIMITY, &sensor);
		sensor_listeners[SENS_PROXIMITY] = set_sensor_listener(sensor, 100, NULL);
	} else
		sensor_listeners[SENS_PROXIMITY] = NULL;
	sensor_is_supported(SENSOR_PRESSURE, &supported);
	if (supported) {
		sensor_get_default_sensor(SENSOR_PRESSURE, &sensor);
		sensor_listeners[SENS_PRESSURE] = set_sensor_listener(sensor, 100, NULL);
	} else
		sensor_listeners[SENS_PRESSURE] = NULL;
	sensor_is_supported(SENSOR_ULTRAVIOLET, &supported);
	if (supported) {
		sensor_get_default_sensor(SENSOR_ULTRAVIOLET, &sensor);
		sensor_listeners[SENS_ULTRAVIOLET] = set_sensor_listener(sensor, 100, NULL);
	} else
		sensor_listeners[SENS_ULTRAVIOLET] = NULL;
	sensor_is_supported(SENSOR_TEMPERATURE, &supported);
	if (supported) {
		sensor_get_default_sensor(SENSOR_TEMPERATURE, &sensor);
		sensor_listeners[SENS_TEMPERATURE] = set_sensor_listener(sensor, 100, NULL);
	} else
		sensor_listeners[SENS_TEMPERATURE] = NULL;
	sensor_is_supported(SENSOR_HUMIDITY, &supported);
	if (supported) {
		sensor_get_default_sensor(SENSOR_HUMIDITY, &sensor);
		sensor_listeners[SENS_HUMIDITY] = set_sensor_listener(sensor, 100, NULL);
	} else
		sensor_listeners[SENS_HUMIDITY] = NULL;
	sensor_is_supported(SENSOR_HRM, &supported);
	if (supported) {
		sensor_get_default_sensor(SENSOR_HRM, &sensor);
		sensor_listeners[SENS_HRM] = set_sensor_listener(sensor, 100, NULL);
	} else
		sensor_listeners[SENS_HRM] = NULL;
	sensor_is_supported(SENSOR_HRM_LED_GREEN, &supported);
	if (supported) {
		sensor_get_default_sensor(SENSOR_HRM_LED_GREEN, &sensor);
		sensor_listeners[SENS_HRM_LED_GREEN] = set_sensor_listener(sensor, 100, NULL);
	} else
		sensor_listeners[SENS_HRM_LED_GREEN] = NULL;
	sensor_is_supported(SENSOR_HRM_LED_IR, &supported);
	if (supported) {
		sensor_get_default_sensor(SENSOR_HRM_LED_IR, &sensor);
		sensor_listeners[SENS_HRM_LED_IR] = set_sensor_listener(sensor, 100, NULL);
	} else
		sensor_listeners[SENS_HRM_LED_IR] = NULL;
	sensor_is_supported(SENSOR_HRM_LED_RED, &supported);
	if (supported) {
		sensor_get_default_sensor(SENSOR_HRM_LED_RED, &sensor);
		sensor_listeners[SENS_HRM_LED_RED] = set_sensor_listener(sensor, 100, NULL);
	} else
		sensor_listeners[SENS_HRM_LED_RED] = NULL;
	sensor_is_supported(SENSOR_GYROSCOPE_UNCALIBRATED, &supported);
	if (supported) {
		sensor_get_default_sensor(SENSOR_GYROSCOPE_UNCALIBRATED, &sensor);
		sensor_listeners[SENS_GYROSCOPE_UNCALIBRATED] = set_sensor_listener(sensor, 100, NULL);
	} else
		sensor_listeners[SENS_GYROSCOPE_UNCALIBRATED] = NULL;
	sensor_is_supported(SENSOR_GEOMAGNETIC_UNCALIBRATED, &supported);
	if (supported) {
		sensor_get_default_sensor(SENSOR_GEOMAGNETIC_UNCALIBRATED, &sensor);
		sensor_listeners[SENS_GEOMAGNETIC_UNCALIBRATED] = set_sensor_listener(sensor, 100, NULL);
	} else
		sensor_listeners[SENS_GEOMAGNETIC_UNCALIBRATED] = NULL;
	sensor_is_supported(SENSOR_GYROSCOPE_ROTATION_VECTOR, &supported);
	if (supported) {
		sensor_get_default_sensor(SENSOR_GYROSCOPE_ROTATION_VECTOR, &sensor);
		sensor_listeners[SENS_GYROSCOPE_ROTATION_VECTOR] = set_sensor_listener(sensor, 100, NULL);
	} else
		sensor_listeners[SENS_GYROSCOPE_ROTATION_VECTOR] = NULL;
	sensor_is_supported(SENSOR_GEOMAGNETIC_ROTATION_VECTOR, &supported);
	if (supported) {
		sensor_get_default_sensor(SENSOR_GEOMAGNETIC_ROTATION_VECTOR, &sensor);
		sensor_listeners[SENS_GEOMAGNETIC_ROTATION_VECTOR] = set_sensor_listener(sensor, 100, NULL);
	} else
		sensor_listeners[SENS_GEOMAGNETIC_ROTATION_VECTOR] = NULL;
	sensor_is_supported(SENSOR_SIGNIFICANT_MOTION, &supported);
	if (supported) {
		sensor_get_default_sensor(SENSOR_SIGNIFICANT_MOTION, &sensor);
		sensor_listeners[SENS_SIGNIFICANT_MOTION] = set_sensor_listener(sensor, 100, NULL);
	} else
		sensor_listeners[SENS_SIGNIFICANT_MOTION] = NULL;
	sensor_is_supported(SENSOR_HUMAN_PEDOMETER, &supported);
	if (supported) {
		sensor_get_default_sensor(SENSOR_HUMAN_PEDOMETER, &sensor);
		sensor_listeners[SENS_HUMAN_PEDOMETER] = set_sensor_listener(sensor, 100, NULL);
	} else
		sensor_listeners[SENS_HUMAN_PEDOMETER] = NULL;
	sensor_is_supported(SENSOR_HUMAN_SLEEP_MONITOR, &supported);
	if (supported) {
		sensor_get_default_sensor(SENSOR_HUMAN_SLEEP_MONITOR, &sensor);
		sensor_listeners[SENS_HUMAN_SLEEP_MONITOR] = set_sensor_listener(sensor, 100, NULL);
	} else
		sensor_listeners[SENS_HUMAN_SLEEP_MONITOR] = NULL;
	sensor_is_supported(SENSOR_HUMAN_SLEEP_DETECTOR, &supported);
	if (supported) {
		sensor_get_default_sensor(SENSOR_HUMAN_SLEEP_DETECTOR, &sensor);
		sensor_listeners[SENS_HUMAN_SLEEP_DETECTOR] = set_sensor_listener(sensor, 100, NULL);
	} else
		sensor_listeners[SENS_HUMAN_SLEEP_DETECTOR] = NULL;
	sensor_is_supported(SENSOR_HUMAN_STRESS_MONITOR, &supported);
	if (supported) {
		sensor_get_default_sensor(SENSOR_HUMAN_STRESS_MONITOR, &sensor);
		sensor_listeners[SENS_HUMAN_STRESS_MONITOR] = set_sensor_listener(sensor, 100, NULL);
	} else
		sensor_listeners[SENS_HUMAN_STRESS_MONITOR] = NULL;

	/*if (supported) {
	 if (sensor_listeners[SENS_ACCELEROMETER] == nullptr) {

	 } else {
	 sensor_listener_start(sensor_listeners[SENS_ACCELEROMETER]);
	 }
	 } else {
	 unsigned char res[] = { MSG_RES_FAIL };
	 sap_socket_send_data(priv_data.socket, HELLO_ACC_CHANNELID, 1, res);
	 }
	 sensor_h sensor;
	 sensor_get_default_sensor(SENSOR_ACCELEROMETER, &sensor);
	 sensor_listener_h listener;
	 sensor_create_listener(sensor, &listener);
	 sensor_listener_set_event_cb(listener, 100, sensors_callback,
	 NULL);
	 sensor_listeners[SENS_ACCELEROMETER] = listener;
	 sensor_listener_start(listener);*/
}
