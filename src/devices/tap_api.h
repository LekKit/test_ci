/*
tap_api.h - TAP Networking API
Copyright (C) 2021  LekKit <github.com/LekKit>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef RVVM_TAP_H
#define RVVM_TAP_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

// Maximum size for an Ethernet II header + payload
#define TAP_FRAME_SIZE 1514

typedef struct {
    // Network card specific context
    void* net_dev;
    // Feed received Ethernet frame to the NIC (Without CRC)
    bool (*feed_rx)(void* net_dev, const void* data, size_t size);
} tap_net_dev_t;

typedef struct tap_dev tap_dev_t;

// Open TAP interface, link to the NIC
tap_dev_t* tap_open(const tap_net_dev_t* net_dev);

// Send Ethernet frame (Without CRC)
bool       tap_send(tap_dev_t* tap, const void* data, size_t size);

// Set/get interface MAC address
bool       tap_get_mac(tap_dev_t* tap, uint8_t mac[6]);
bool       tap_set_mac(tap_dev_t* tap, const uint8_t mac[6]);

// Shut down the interface
void       tap_close(tap_dev_t* tap);

#endif
