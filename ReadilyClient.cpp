/**
  MIT License

  Copyright (c) 2022 Akira Kashihara

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

/*Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.*/

#include "Arduino.h"
#include "ReadilyClient.h"

ReadilyClient::ReadilyClient(int timeout)
{
  _timeout = timeout;
};

// Verify CA of TLS/SSL
int ReadilyClient::verifyCA()
{  
  client.setCACert(_root_ca);
  return 0;

  if (!client.connect(_server, 443)) {
    return -1;
  } else {
    return 0;
  }
};

int ReadilyClient::getTime() {
  client.println("GET https://api.readily.online/time HTTP/1.0");
  // client.println("Host: api.readily.online");
  // client.println("Connection: close");
  // client.println();

  // while (client.connected()) {
  //   String line = client.readStringUntil('\n');
  //   if (line == "\r") {
  //     Serial.println("headers received");
  //     break;
  //   }
  // }
  // // if there are incoming bytes available
  // // from the server, read them and print them:
  // while (client.available()) {
  //   char c = client.read();
  //   Serial.write(c);
  // }

  // client.stop();
}

// Morse::Morse(int pin){
//   pinMode(pin, OUTPUT);
//   _pin = pin;}

// void Morse::dot(){
//   digitalWrite(_pin, HIGH);
//   delay(250);
//   digitalWrite(_pin, LOW);
//   delay(250);  }

// void Morse::dash(){
//   digitalWrite(_pin, HIGH);
//   delay(1000);
//   digitalWrite(_pin, LOW);
//   delay(250);}