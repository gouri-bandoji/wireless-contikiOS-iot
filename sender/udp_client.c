#include "contiki.h"
#include "contiki-net.h"
#include "sys/etimer.h"
#include "dev/light-sensor.h"
#include <stdio.h>
#include <string.h>
#define UDP_CLIENT_PORT 8765
#define UDP_SERVER_PORT 5678
#define SEND_INTERVAL (10 * CLOCK_SECOND) // Send data every 10 seconds
static struct simple_udp_connection udp_conn;
static struct etimer send_timer;
PROCESS(udp_client_process, "UDP Client (Light Sensor Node)");
AUTOSTART_PROCESSES(&udp_client_process);
PROCESS_THREAD(udp_client_process, ev, data) {
 static char msg[50];
 static uip_ipaddr_t server_ipaddr;
PROCESS_BEGIN();

 // Activate the light sensor properly
 SENSORS_ACTIVATE(light_sensor);
 light_sensor.configure(SENSORS_ACTIVE, 1);
 // Set up UDP connection
 simple_udp_register(&udp_conn, UDP_CLIENT_PORT, NULL, UDP_SERVER_PORT,
NULL);
 // Set receiver's (Mote 2) IPv6 address (change if needed)
 uip_ip6addr(&server_ipaddr, 0xfe80,0,0,0,0x0212,0x7401,0x0001,0x0001);
 // Start periodic timer for automatic sending
 etimer_set(&send_timer, SEND_INTERVAL);
 while (1) {
 PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&send_timer));
 // Read light sensor value
 int light_level = light_sensor.value(LIGHT_SENSOR_TOTAL_SOLAR);
 // Format and send message
 snprintf(msg, sizeof(msg), "Light Level: %d", light_level);
 simple_udp_sendto(&udp_conn, msg, strlen(msg), &server_ipaddr);
 printf("Sent: %s\n", msg);
// Reset the timer for next transmission
 etimer_reset(&send_timer);
 }
 PROCESS_END();
}
