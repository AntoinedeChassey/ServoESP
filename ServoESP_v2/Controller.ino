/********** Controller functions **********/

void send_MQTTmsg(String msg) {
  Serial << "Sending message to MQTT broker: " << msg << endl;
  // send id to the MQTT topic
  mqtt_payload = strToChar(msg);
  client.publish(mqtt_topic, mqtt_payload, retained);
}

void servo(int angle) {
  /*
    int pos = 90;
    if (angle > 90) {
    for (pos; pos <= angle; pos += 1) {
     Serial << pos << endl;
     myservo.write(pos);
     delay(15);
    }
    }

    if (angle < 90) {
    for (pos; pos >= angle; pos -= 1) {
     Serial << pos << endl;
     myservo.write(pos);
     delay(15);
    }
    }
  */
  myservo.write(angle);
  //myservo.write(90);      // reset servo to mid rang


  /*
    for (pos = angle; pos <= 180; pos += 10) {            // goes from 0 degrees to 180 degrees // in steps of 1 degree
    Serial << pos << endl;
    myservo.write(pos);                         // tell servo to go to position in variable 'pos'
    delay(15);                                  // waits 15ms for the servo to reach the position
    }

    Serial << endl;
    for (pos = 180; pos >= angle; pos -= 10) {        // goes from 180 degrees to 0 degrees
    Serial << pos << endl;
    myservo.write(pos);                         // tell servo to go to position in variable 'pos'
    delay(15);                                  // waits 15ms for the servo to reach the position
    }
  */
}

