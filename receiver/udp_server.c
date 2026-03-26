#include "contiki.h"
#include "contiki-net.h"
#include "dev/button-sensor.h"
#include "dev/leds.h"
#include <stdio.h>
#include <string.h>
#define UDP_CLIENT_PORT 8765
#define UDP_SERVER_PORT 5678
static struct simple_udp_connection udp_conn;
PROCESS(udp_server_process, "UDP Server (Receiver Mote)");
AUTOSTART_PROCESSES(&udp_server_process);
// Callback function to handle incoming UDP packets
static void udp_rx_callback(struct simple_udp_connection *c,
 const uip_ipaddr_t *sender_addr,
 uint16_t sender_port,
 const uip_ipaddr_t *receiver_addr,
uint16_t receiver_port,
 const uint8_t *data,
 uint16_t datalen) {
 char msg[50];

 // Ensure proper string formatting and extract the light intensity value
 snprintf(msg, sizeof(msg), "%.*s", datalen, (const char *)data);
 // Process only messages that start with "Light Level: "
 if (strncmp(msg, "Light Level: ", 13) == 0) {
 int light_level = atoi(msg + 13); // Extract the light intensity value from the message
 // Print the received light intensity value (for debugging)
 printf("Received Light Level: %d\n\r", light_level);
 // Adjust the LED based on the light intensity
 if (light_level < 70) {
 leds_off(LEDS_RED); // High light intensity -> Red LED ON
 leds_off(LEDS_GREEN); // Ensure other LEDs are OFF
 leds_on(LEDS_BLUE);
 } else if (light_level >= 70 && light_level < 400) {
 leds_on(LEDS_GREEN); // Medium light intensity -> Green LED ON
 leds_off(LEDS_RED); // Ensure other LEDs are OFF
 leds_off(LEDS_BLUE);
 } else {
 leds_off(LEDS_BLUE); // Low light intensity -> Blue LED ON
 leds_on(LEDS_RED); // Ensure other LEDs are OFF
 leds_off(LEDS_GREEN);
 }
}
}
PROCESS_THREAD(udp_server_process, ev, data) {
 PROCESS_BEGIN();

 // Activate the button sensor
 SENSORS_ACTIVATE(button_sensor);

 // Register the UDP connection to receive data
 simple_udp_register(&udp_conn, UDP_SERVER_PORT, NULL, UDP_CLIENT_PORT,
udp_rx_callback);

 // Indicate that the server is started
 printf("UDP Server started. Waiting for button press...\n");
 while (1) {
 // Wait for the button press event
 PROCESS_WAIT_EVENT_UNTIL(ev == sensors_event && data == &button_sensor);

 // Once the button is pressed, indicate that we're waiting for light intensity data
 printf("Button pressed, waiting for light intensity data...\n");
 // Wait until the next button press (the loop will restart after each press)
 }
 PROCESS_END();
}
