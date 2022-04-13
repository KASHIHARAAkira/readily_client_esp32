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

#include "Arduino.h"
#include "ReadilyClient.h"
#include <WiFiClientSecure.h>

ReadilyClient::ReadilyClient(int timeout)
{
  _timeout = timeout;
};

// Verify CA of TLS/SSL
int ReadilyClient::verifyCA()
{  
  client.setCACert(_root_ca);

  if (!client.connect(_server, 443)) {
    return -1;
  } else {
    return 0;
  }
};

String ReadilyClient::getTime() {
  client.println("GET https://api.readily.online/time HTTP/1.0");
  client.println("Host: api.readily.online");
  client.println("Connection: close");
  client.println();

  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      // Serial.println("headers received");
      break;
    }
  }
  // if there are incoming bytes available
  // from the server, read them and print them:
  int lineNum = 0;
  String resultLine;
  while (client.available()) {
    resultLine = client.readStringUntil('\r');
    lineNum++;
  }
  return resultLine;
  client.stop();
};

String ReadilyClient::refreshToken(String refreshToken) {
  const char* path = "https://api.readily.online/refresh_token";
  const String json = "{\"refresh_token\": \"" + refreshToken + "\"}";

  Serial.print("requesting URL:");
  Serial.println(path);

  client.println("POST https://api.readily.online/refresh_token HTTP/1.0");
  client.println("Host: api.readily.online");
  client.println("Content-Type: application/json");
  client.println("Content-Length:" + String(json.length()));
  client.println();
  client.println(json);
  client.println();

  Serial.println("request sent");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      // Serial.println("headers received");
      break;
    }
  }

  int lineNum = 0;
  String resultLine;
  while (client.available()) {
    resultLine = client.readStringUntil('\r');
    lineNum++;
    // char c = client.read();
    // Serial.write(c);
  }

  return resultLine;
  client.stop();
}

String ReadilyClient::uploadData(String accessToken, String chartId, float payload[], int sizePayload) {
  const String path = "https://api.readily.online/upload?chartId=" + chartId;
  String arrayData = "[[";
  //make data
  for (int i = 0; i < sizePayload - 1; i++) {
    arrayData += String(payload[i]);
    arrayData += ",";
  }
  arrayData += String(payload[sizePayload - 1]);
  arrayData += "]]";
  const String json = "{\"access_token\": \"" + accessToken + "\", \"data\": " + arrayData + "}";

  client.println("POST " + path + " HTTP/1.0");
  client.println("Host: api.readily.online");
  client.println("Content-Type: application/json");
  client.println("Content-Length:" + String(json.length()));
  client.println();
  client.println(json);
  client.println();

  Serial.println("request sent");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      // Serial.println("headers received");
      break;
    }
  }

  int lineNum = 0;
  String resultLine;
  while (client.available()) {
    resultLine = client.readStringUntil('\r');
    lineNum++;
    // char c = client.read();
    // Serial.write(c);
  }
  return resultLine;
  client.stop();
}