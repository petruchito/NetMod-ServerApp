/*
 * Copyright (c) 2001-2003, Adam Dunkels.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This file is part of the uIP TCP/IP stack.
 *
 * $Id: uipopt.h,v 1.1 2007/01/04 11:06:41 adamdunkels Exp $
 *
 */

/* Modifications 2020 Michael Nielson
 * Adapted for STM8S005 processor, ENC28J60 Ethernet Controller,
 * Web_Relay_Con V2.0 HW-584, and compilation with Cosmic tool set.
 * Author: Michael Nielson
 * Email: nielsonm.projects@gmail.com
 *
 * This declaration applies to modifications made by Michael Nielson
 * and in no way changes the Adam Dunkels declaration above.
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful, but
 WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 General Public License for more details.

 See GNU General Public License at <http://www.gnu.org/licenses/>.
 
 Copyright 2020 Michael Nielson
*/



/**
 * Configuration options for uIP
 *
 * uIP is configured using the per-project configuration file uipopt.h.
 * This file contains all compile-time options for uIP and should be
 * tweaked to match each specific project.
 */

#ifndef __UIPOPT_H__
#define __UIPOPT_H__

#ifndef UIP_LITTLE_ENDIAN
#define UIP_LITTLE_ENDIAN  3412
#endif /* UIP_LITTLE_ENDIAN */
#ifndef UIP_BIG_ENDIAN
#define UIP_BIG_ENDIAN     1234
#endif /* UIP_BIG_ENDIAN */

#include "uip_types.h"
#include "Enc28j60.h"
#include "uip_TcpAppHub.h"


/*------------------------------------------------------------------------------*/
// IP configuration options
/*------------------------------------------------------------------------------*/
 
// The IP TTL (time to live) of IP packets sent by uIP.
// This should normally not be changed.
#define UIP_TTL         64


/*------------------------------------------------------------------------------*/
// TCP configuration options
/*------------------------------------------------------------------------------*/

// The maximum number of simultaneously open TCP connections. Since the TCP
// connections are statically allocated, turning this configuration knob down
// results in less RAM used. Each TCP connection requires approximately 30 bytes
// of memory.
//
// Comment MN: Experiment shows actual RAM consumption per connection to be 40
// bytes.
#define UIP_CONNS       6


// The maximum number of simultaneously listening TCP ports. Each listening TCP
// port requires 2 bytes of memory.
//
// Comment MN: Experiment shows the 2 bytes of RAM estimate to be correct.
#define UIP_LISTENPORTS 5


// The initial retransmission timeout counted in timer pulses.
// This should not be changed.
#define UIP_RTO         3


// The maximum number of times a segment should be retransmitted before the
// connection should be aborted.
// This should not be changed.
#define UIP_MAXRTX      8


// The maximum number of times a SYN segment should be retransmitted before a
// connection request should be deemed to have been unsuccessful.
// This should not need to be changed.
#define UIP_MAXSYNRTX      5


// The TCP maximum segment size. This is should not be to set to more than
// UIP_BUFSIZE - UIP_LLH_LEN - UIP_TCPIP_HLEN.
#define UIP_TCP_MSS     (UIP_BUFSIZE - UIP_LLH_LEN - UIP_TCPIP_HLEN)


// The size of the advertised receiver's window. Should be set low (i.e., to the
// size of the uip_buf buffer) if the application is slow to process incoming
// data, or high (32768 bytes) if the application processes data quickly.
#define UIP_RECEIVE_WINDOW UIP_TCP_MSS


// How long a connection should stay in the TIME_WAIT state. This configiration
// option has no real implication, and it should be left untouched.
#define UIP_TIME_WAIT_TIMEOUT 120


/*------------------------------------------------------------------------------*/
// ARP configuration options
/*------------------------------------------------------------------------------*/

// The size of the ARP table. This option should be set to a larger value if
// this uIP node will have many connections from the local network.
#define UIP_ARPTAB_SIZE 8


// The maxium age of ARP table entries measured in 10ths of seconds. A
// UIP_ARP_MAXAGE of 120 corresponds to 20 minutes (BSD default).
#define UIP_ARP_MAXAGE 120


/*------------------------------------------------------------------------------*/
// General configuration options
/*------------------------------------------------------------------------------*/

// The size of the uIP packet buffer. The uIP packet buffer should not be smaller
// than 60 bytes, and does not need to be larger than 1500 bytes. Lower size
// results in lower TCP throughput, larger size results in higher TCP throughput.
#define UIP_BUFSIZE     ENC28J60_MAXFRAME


// Determines if statistics support should be compiled in. The statistics are
// useful for debugging and to show the user. If you are modifying the project
// and need more program space eliminating the statistics pages and processes will
// free up considerable space.
#define UIP_STATISTICS  1


// The link level header length. This is the offset into the uip_buf where the IP
// header can be found. For Ethernet, this should be set to 14. For SLIP, this
// should be set to 0.
#define UIP_LLH_LEN     14


// CPU architecture configuration. The CPU architecture configuration is where
// the endianess of the CPU on which uIP is to be run is specified. Most CPUs
// today are little endian, and the most notable exception are the Motorolas
// which are big endian. The BYTE_ORDER macro should be changed to reflect the
// CPU architecture on which uIP is to be run. This option can be either
// BIG_ENDIAN (Motorola byte order) or LITTLE_ENDIAN (Intel byte order).
#define UIP_BYTE_ORDER     UIP_BIG_ENDIAN


/*------------------------------------------------------------------------------*/
/**
 * Application specific compile controls
 *
 * Controls whether the options for code compile. For instance:
 *  - Controls with/without Help web pages
 *  - Control number of relay outputs / sense inputs
 *      16 relay outputs (no inputs)
 *        OR
 *      8 relay outputs and 8 sense inputs
 *        OR
 *      16 sense inputs
 */


// Determines if help support should be compiled in. If you are modifying the
// project and need more program space eliminating the help pages and processes
// will free up considerable space.
#define HELP_SUPPORT  1


// Determines how many GPIO pins are relay control outputs and how many are
// sense inputs. Due to flash space limitations this can't be a run time option.
// It must be a build time option.
// 1 = 16 relay outputs
// 2 = 8 relay outputs / 8 sense inputs
// 3 = 16 sense inputs
#define GPIO_SUPPORT  1


/*------------------------------------------------------------------------------*/
/**
 * Appication specific configurations
 *
 * An uIP application is implemented using a single application function that is
 * called by uIP whenever a TCP/IP event occurs. The name of this function must
 * be registered with uIP at compile time using the UIP_APPCALL definition.
 *
 * uIP applications can store the application state within the uip_conn
 * structure by specifying the type of the application structure by typedef:ing
 * the type uip_tcp_appstate_t.
 *
 * The file containing the definitions must be included in the uipopt.h file.
 *
 * The following example illustrates how this can look.
 \code

void httpd_appcall(void);
#define UIP_APPCALL     httpd_appcall

struct httpd_state {
  uint8_t state;
  uint16_t count;
  char *dataptr;
  char *script;
};
typedef struct httpd_state uip_tcp_appstate_t
 \endcode
 */


/**
 * \var #define UIP_APPCALL
 *
 * The name of the application function that uIP should call in
 * response to TCP/IP events.
 *
 */


/**
 * \var typedef uip_tcp_appstate_t
 *
 * The type of the application state that is to be stored in the
 * uip_conn structure. This usually is typedef:ed to a struct holding
 * application state information.
 */

#endif /* __UIPOPT_H__ */
