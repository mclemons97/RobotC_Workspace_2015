/************************************************************************/
/*                                                                      */
/* Program Name: PSP-Nx-lib.h                                      			*/
/* ===========================                                          */
/*                                                                      */
/* Copyright (c) 2008 by mindsensors.com                                */
/* Email: info (<at>) mindsensors (<dot>) com                           */
/*                                                                      */
/* This program is free software. You can redistribute it and/or modify */
/* it under the terms of the GNU General Public License as published by */
/* the Free Software Foundation; version 3 of the License.              */
/* Read the license at: http://www.gnu.org/licenses/gpl.txt             */
/*                                                                      */
/************************************************************************/

/*
 * History
 * ------------------------------------------------
 * Author     Date      Comments
 * Deepak     04/08/09  Initial Authoring.
 * Morgan     04/16/14  changed filetype to ".h" as there was no entrypoint to the program...
 * Morgan			04/17/14  changed "msg[0]"  to  "&msg[0]"  at lines (86, 136).
 * Morgan			04/18/14	Commments added to warn users to take precautionary measures that may help prevent incident.
 */

 /*
 * NOTES
 * ------------------------------------------------
 * Author     Date      NOTE
 * Morgan			04/17/14  Take care when using this API it returns reverse logic for currstates.
 *											if a currState is false it will read as true. keep this in mind when developing logic.
 * 											Failure to do so, resulting in operator error could incur possible damage to
 *											system, preson, and property!
 */


/*
  bits as follows:
   b1:   a b c d x r_j_b l_j_b x
   b2:   square cross circle triang R1 L1 R2 L2
*/
typedef struct {
  char   b1;  //raw byte read from PSP-Nx
  char   b2;  //raw byte read from PSP-Nx

  // computed button states
  char   l1;
  char   l2;
  char   r1;
  char   r2;
  char   a;
  char   b;
  char   c;
  char   d;
  char   triang;
  char   square;
  char   circle;
  char   cross;
  char   l_j_b;  // joystick button state
  char   r_j_b;  // joystick button state

  int   l_j_x;   // analog value of joystick scaled from 0 to 100
  int   l_j_y;   // analog value of joystick scaled from 0 to 100
  int   r_j_x;   // analog value of joystick scaled from 0 to 100
  int   r_j_y;   // analog value of joystick scaled from 0 to 100
} psp;

void PSP_SendCommand(tSensors port, byte i2cAddr, byte  command)
{
        byte msg[5];

        // Build the I2C message
        msg[0] = 3;
        msg[1] = i2cAddr;
        msg[2] = 0x41;
        msg[3] = command;

        // Wait for I2C bus to be ready
        while (nI2CStatus[port] == STAT_COMM_PENDING);// ignore "*Warning*:';' found following 'while' statement. Is this intentional?"
        // when the I2C bus is ready, send the message you built
        sendI2CMsg(port, &msg[0], 0);
        while (nI2CStatus[port] == STAT_COMM_PENDING);// ignore "*Warning*:';' found following 'while' statement. Is this intentional?"
}

void PSP_ReadButtonState(tSensors port, byte i2cAddr, psp & currState)
{
  byte msg[5];
  unsigned byte replyMsg[7];
  byte b0, b1;

  msg[0] = 2;
  msg[1] = i2cAddr;
  msg[2] = 0x42;

  currState.b1 = 0;
  currState.b2 = 0;
  currState.l1 = 0;
  currState.l2 = 0;
  currState.r1 = 0;
  currState.r2 = 0;
  currState.a = 0;
  currState.b = 0;
  currState.c = 0;
  currState.d = 0;
  currState.triang = 0;
  currState.square = 0;
  currState.circle = 0;
  currState.cross = 0;
  currState.l_j_b = 0;
  currState.r_j_b = 0;
  currState.l_j_x = 0;
  currState.l_j_y = 0;
  currState.r_j_x = 0;
  currState.r_j_y = 0;

  while (nI2CStatus[port] == STAT_COMM_PENDING)
    {
      // Wait for I2C bus to be ready
    }
  // when the I2C bus is ready, send the message you built
  sendI2CMsg (port, &msg[0], 6);
  while (nI2CStatus[port] == STAT_COMM_PENDING)
    {
      // Wait for I2C bus to be ready
    }
  // read back the response from I2C
  readI2CReply (port, &replyMsg[0], 6);

        b0 = replyMsg[0]&0xff;
        b1 = replyMsg[1]&0xff;

        currState.b1        = b0;
        currState.b2        = b1;

        currState.l_j_b     = (b0 >> 1) & 0x01;
        currState.r_j_b     = (b0 >> 2) & 0x01;

        currState.d         = (b0 >> 4) & 0x01;
        currState.c         = (b0 >> 5) & 0x01;
        currState.b         = (b0 >> 6) & 0x01;
        currState.a         = (b0 >> 7) & 0x01;

        currState.l2        = (b1     ) & 0x01;
        currState.r2        = (b1 >> 1) & 0x01;
        currState.l1        = (b1 >> 2) & 0x01;
        currState.r1        = (b1 >> 3) & 0x01;
        currState.triang    = (b1 >> 4) & 0x01;
        currState.circle    = (b1 >> 5) & 0x01;
        currState.cross     = (b1 >> 6) & 0x01;
        currState.square    = (b1 >> 7) & 0x01;

        currState.l_j_x = (((replyMsg[2]&0xff) - 128) * 100)/128;
        currState.l_j_y = (((replyMsg[3]&0xff) - 128) * 100)/128;
        currState.r_j_x = (((replyMsg[4]&0xff) - 128) * 100)/128;
        currState.r_j_y = (((replyMsg[5]&0xff) - 128) * 100)/128;

}
