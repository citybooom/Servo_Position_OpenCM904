/*******************************************************************************
 * Copyright 2016 ROBOTIS CO., LTD.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *******************************************************************************/

/* Authors: Taehun Lim (Darby) */
#define DEVICE_NAME "1" //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#include <DynamixelWorkbench.h>

#include <ros.h>
#include <std_msgs/Int16MultiArray.h>

#define BAUDRATE  1000000
//#define DXL_ID    3

DynamixelWorkbench dxl_wb;


ros::NodeHandle  nh;

void messageCb( const std_msgs::Int16MultiArray& msg) 
{
    dxl_wb.goalPosition(0, msg.data[0]);
    dxl_wb.goalPosition(1, msg.data[1]);
    dxl_wb.goalPosition(2, msg.data[2]);
    dxl_wb.goalPosition(3, msg.data[3]);
}

ros::Subscriber<std_msgs::Int16MultiArray> sub("ServoPoseSerial", messageCb );

void setup() 
{
    Serial.begin(57600);
    while(!Serial); // If this line is activated, you need to open Serial Terminal.

    dxl_wb.begin(DEVICE_NAME, BAUDRATE);
    dxl_wb.ping(0);
    dxl_wb.jointMode(0);
    dxl_wb.ping(1);
    dxl_wb.jointMode(1);
    dxl_wb.ping(2);
    dxl_wb.jointMode(2);
    dxl_wb.ping(3);
    dxl_wb.jointMode(3);

    nh.initNode();
    nh.subscribe(sub);
}

void loop() 
{
    nh.spinOnce();
}
