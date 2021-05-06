/*
Copyright (c) 2013-2019 Ubidots.
Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:
The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Developed and maintained by Jose Garcia and Cristian Arrieta for IoT Services
Inc
@jotathebest at github: https://github.com/jotathebest
@crisap94 at github: https://github.com/crisap94
*/

#ifndef _UbiTcp_H_
#define _UbiTcp_H_

#define TINY_GSM_MODEM_SIM900
#define TINY_GSM_USE_GPRS true

#include <SoftwareSerial.h>

#include "UbiProtocol.h"

#define RX 7
#define TX 8
#define BAUDRATE 19200
#define SIM900_POWER_UP_PIN 9

class UbiTCP : public UbiProtocol {
 private:
  bool _debug = false;
  long long _timer = 0;
  char replybuffer[MAX_SERIAL_BUFFER_SIZE];
  unsigned long _timerToSync = millis();
  bool isConnectedToServer = false;
  bool isJoinedToNetwork = false;
  bool isNetworkRegistered = false;
  bool isInitiatedModule = false;
  bool isPoweredOn = false;
  bool isSimInserted = false;

  SoftwareSerial *Sim900;

  UbiServer _server;
  const char *_user_agent;
  UbiToken _token;
  UbiApn _apn;
  UbiApn _apnUser;
  UbiApn _apnPass;

  int _port;

  bool _isPoweredOn();
  bool _isSimCardInserted();
  bool _initGPRS();
  bool _waitingForNetwork();
  bool _isNetworkRegistered();
  bool _isJoinedToNetwork();
  bool _hasConnectivity();
  bool _isConnectedToServer();
  void _powerUpDown();
  float _parseTCPAnswer(const char *request_type);

  void sendCommand(const char *command, uint16_t timeout = 3000);
  bool sendCommandToServer(const char *payload, uint16_t timeout = 5000);
  bool sendCommand(const char *command, const char *reply, uint16_t timeout = 600);

  uint16_t _endpointLength(const char *device_label, const char *variable_label);

  bool _preConnectionChecks();

 public:
  UbiTCP(UbiToken token, UbiServer server, const int port, const char *user_agent, UbiApn apn, UbiApn apnUser,
         UbiApn apnPass);

  bool sendData(const char *device_label, const char *device_name, char *payload);

  float get(const char *device_label, const char *variable_label);

  void setDebug(bool debug);

  bool serverConnected();

  ~UbiTCP();
};

#endif
