---
title: "Project Second Semester"
date: 2023-07-18T22:22:33+02:00
draft: false
---

## Project pitch

We started the second semester with a presentation about the pitch of the project we planned to tackle for the second semester.

The Problem I wanted to solve is communication between bars and finances at Uni-Partys.

Currently DECTs are used to communicate on uni-partys. DECTs are basically old button cellphones, which allow you to call someone, write messages and thats about it.
The main things you want to communicate to others (bars or finances in specific) is to ask for change, that you need helpers or a refill of clean glasses.

The Problem with talking over DECTs is that because of the music its hard to understand each other. 
The number of DECTs we have available is also limited, which results in only two persons per bar actually having a DECT.

So my idea was to create small bar-terminals which can be located in all the cashboxes behind bars at uni-partys to communicate between each other.

The terminals are supposed to:
 - be scaleable (as many terminals as you want per bar, as many bars as you want)
 - have predefined messages from which the user can select one and send it to a specific selected bar
 - have a button to send messages to finances
 - have a screen to show messages

The last problem is that the wifi-access-point can be overloaded due to the high amount of people (1500) on a small space.
Because of this I decided to use a 433mHz radio signal to communicate between the bars and implement everything as a mesh-network to bridge longer distances between bars.

## Timeline

From the Pitch till the presentation of our project at the ["Streiflicht"](https://www.uni-ulm.de/in/mi/streiflicht) at Ulm University we had 7 Weeks (17.05.23 - 05.07.23).

I set myself the following timeline and milestones:
 - First two weeks (17.05.23 - 29.05.23):
   
   Research on mesh-networks, radio-signals and radio-modules for arduino, because I barely had any knowledge about any of those topics.
 - As soon as my ordered parts would arrive my plan was to put everything together on a breadboard and start programming.
 - Milestone 1 till the 11.06.23:
   
   Have a working system on a breadboard
 - After that my plan was create a housing with the buttons and solder everything together.
 - Milestone 2 till the 25.06.23:
   
   First version of the project is finished and ready to be presented
 - Till the 05.07.23: 
   
   Improve small things if necesary

## First weeks untill the 12.06.23

Contrary to my timeline I spend more time into research about mesh networks and radio modules.
On top of that my order of the radio modules got lost as well, which set me back a little.

In my pitch I also got some tips for other ways to communicate between the terminals like using the already existing DECT-Network or LoRaWan, so I reserched about them as well and asked a lecturer for further information.

As soon as the two radio modules I orderd arrived, I tested both of them about generall usability and functionality as well as the range of the radio signal:
 - The NRF24L01-module:

   The older of the two modules need 7 pins to connect to an arduino, uses 2,4 GHz, the range is not that good, theres more documentation in the internet for this one

 - HC-12-moduel:

   Newer, needs only 4 pins to connect to an arduino, uses 433 MHz, range was better in my tests and it seemed more intuitive to use for me.

So I decided to use radio modules and choose the HC-12 module over the NRF24L01+PA+LNA-module.
The main reasons were longer range, fewer pins to connect, which would make soldering a lot easier later and that it seemed more intuitive to use for me.

I also ordered rotary encoders and oled-displays to use for the view and controll of my terminal.

Undortunately I did not reached the goal of my first milestone, because I just had decided for a radio module.

## 12.06. - 20.06

In this week I focused on the view and controll of my bar-terminal.

To show the user all the necesary Information i used a 128x64 pixel oled.
For manipulation of the oled like selecting a message, selecting a bar and sendig it to that bar I used a rotary encoder.

I researched a lot about menues with rotary encoders and which library to use to create a menue, but everything I could find surpassed my needs and was extremely complex for just a simple menue so I decided to implement a menue myself. A lot of librarys also nearly completely filled the ram of an arduino which was bad if you want to implement more stuffe besides the menue.

Im pretty proud of the result so I'm planning to put it on Instructables or a similar site so other people can use it as well.

I used the SSD1306Ascii-library made bei greiman which is pretty resourcefull and not overloaded.

## 20.06. - 26.06.

In this week I connected my radio modules with the oled and rotary encoder with my menue.

I basically reached Milestone 1 in this week because I had a finished prototype on a breadboard.

It was now possible to select a messages, a bar which is supposed to recieve the message and send the message. The other Terminal then was able to display the Message and from which bar it came.

When a message was send, every other terminal recieved it and decided based on the header, if the message was meant for itself or not.

If the message was meant for that terminal it displayed the message, otherwise the message got forwarded.

The header was build out of a string containing 3 numbers:
 - The first number indicated which message was send.
 - The second number indicated to which terminal the message was supposed to go.
 - The third number indicated from which terminal the message was send.












## Final Project

### Summary of my plan

### Functions

### Improvements