#ifndef UBX_CFG_H
#define UBX_CFG_H

//  Copyright (C) 2014-2017, SlashDevin
//
//  This file is part of NeoGPS
//
//  NeoGPS is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  NeoGPS is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with NeoGPS.  If not, see <http://www.gnu.org/licenses/>.

//--------------------------------------------------------------------
// Enable/disable the parsing of specific UBX messages.
//
// Configuring out a message prevents its fields from being parsed.
// However, the message type will still be recognized by /decode/ and
// stored in member /rx_msg/.  No valid flags would be available.

#define UBLOX_PARSE_SVINFO      // 30
#define UBLOX_PARSE_STATUS      // 03
#define UBLOX_PARSE_POSLLH      // 02
#define UBLOX_PARSE_DOP         // 04
#define UBLOX_PARSE_VELNED      // 12
#define UBLOX_PARSE_TIMEGPS     // 20
#define UBLOX_PARSE_TIMEUTC     // 21
//#define UBLOX_PARSE_CFGNAV5
//#define UBLOX_PARSE_MONVER
//#define UBLOX_PARSE_HNR_PVT

/* Mini GPS FW 7.03
UBX: 01 30
UBX: 01 03
UBX: 01 02
UBX: 01 04
UBX: 01 12
UBX: 01 21
*/

#if defined(UBLOX_PARSE_HNR_PVT)
  #define UBX_LAST_MSG_CLASS_IN_INTERVAL ublox::UBX_HNR
  #define UBX_LAST_MSG_ID_IN_INTERVAL    ublox::UBX_HNR_PVT
#else
  #define UBX_LAST_MSG_CLASS_IN_INTERVAL ublox::UBX_NAV
  #if defined(UBLOX_PARSE_TIMEUTC)
    #define UBX_LAST_MSG_ID_IN_INTERVAL  ublox::UBX_NAV_TIMEUTC
  #elif defined(UBLOX_PARSE_TIMEGPS)
    #define UBX_LAST_MSG_ID_IN_INTERVAL  ublox::UBX_NAV_TIMEGPS
  #elif defined(UBLOX_PARSE_VELNED)
    #define UBX_LAST_MSG_ID_IN_INTERVAL  ublox::UBX_NAV_VELNED
  #elif defined(UBLOX_PARSE_DOP)
    #define UBX_LAST_MSG_ID_IN_INTERVAL  ublox::UBX_NAV_DOP
  #elif defined(UBLOX_PARSE_POSLLH)
    #define UBX_LAST_MSG_ID_IN_INTERVAL  ublox::UBX_NAV_POSLLH
  #elif defined(UBLOX_PARSE_SVINFO)
    #define UBX_LAST_MSG_ID_IN_INTERVAL  ublox::UBX_NAV_SVINFO
  #else
    #define UBX_LAST_MSG_ID_IN_INTERVAL  ublox::UBX_NAV_STATUS
  #endif
#endif

#if defined(UBLOX_PARSE_DOP) & \
    ( !defined(GPS_FIX_HDOP) & \
      !defined(GPS_FIX_VDOP) & \
      !defined(GPS_FIX_PDOP) )
  #warning UBX DOP message is enabled, but all gps_fix DOP members are disabled.
#endif

//--------------------------------------------------------------------
// Identify the last UBX message in an update interval.
//    (There are two parts to a UBX message, the class and the ID.)
// For coherency, you must determine which UBX message is last!
// This section *should* pick the correct last UBX message for NEO-6M devices.
#if 0
#if defined(UBLOX_PARSE_HNR_PVT)
  #define UBX_LAST_MSG_CLASS_IN_INTERVAL ublox::UBX_HNR
  #define UBX_LAST_MSG_ID_IN_INTERVAL    ublox::UBX_HNR_PVT
#endif
#endif
#if 1
#define UBX_LAST_MSG_CLASS_IN_INTERVAL     ublox::UBX_NAV         // 01
  #if defined(UBLOX_PARSE_TIMEUTC)                                // M8 #7
    #define UBX_LAST_MSG_ID_IN_INTERVAL    ublox::UBX_NAV_TIMEUTC // 21
  #elif defined(UBLOX_PARSE_TIMEGPS)                              // M8 #6
    #define UBX_LAST_MSG_ID_IN_INTERVAL    ublox::UBX_NAV_TIMEGPS // 20
  #elif defined(UBLOX_PARSE_DOP)                                  // M8 #4
    #define UBX_LAST_MSG_ID_IN_INTERVAL    ublox::UBX_NAV_DOP     // 04
  #elif defined(UBLOX_PARSE_VELNED)                               // M8 #5
    #define UBX_LAST_MSG_ID_IN_INTERVAL    ublox::UBX_NAV_VELNED  // 12
  #elif defined(UBLOX_PARSE_POSLLH)                               // M8 #3
    #define UBX_LAST_MSG_ID_IN_INTERVAL    ublox::UBX_NAV_POSLLH  // 02
  #elif defined(UBLOX_PARSE_SVINFO)                               // M8 #1
    #define UBX_LAST_MSG_ID_IN_INTERVAL    ublox::UBX_NAV_SVINFO  // 30
  #else
    #define UBX_LAST_MSG_ID_IN_INTERVAL    ublox::UBX_NAV_STATUS  // 03
  #endif
#endif // If #0
#endif

/* UBLOX M8030-CT SW[ROM CORE 3.01 (107888)]HW[00080000]
UBX: C01 I30 SVINFO
UBX: C01 I03 NAVSTATUS
UBX: C01 I02 POSLLH
UBX: C01 I04 DOP
UBX: C01 I12 VELNED
UBX: C01 I20 TIMEGPS
UBX: C01 I21 TIMEUTC
*/
