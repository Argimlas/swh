---
title: "Instruction Bar Terminals"
date: 2023-07-22T11:43:11+02:00
draft: false
---

This post features the instruction for my bar terminals.

## Introducition

With this instruction I will show you how to build yourself(bar-) terminals, that use radio signals to send each other predefined messages.

The terminal allows you to select a message and send it to a selected ohter terminal and displays recieved messages on an oled. If a message is recieved a LED turns on to indicate a recieved message.

The messages are send via a radio signal and the terminals are implemented as a really simplified mesh-network so each terminal recieves the message and if the message is not meant for the terminal it forwards the message. This also allows to bridge longer distances than the radio signal can reach.

## Everything you need

For 3 bar-terminals you need the following:

### Parts
 - 3 x HC-12 radio module: [Amazon](https://www.amazon.de/dp/B07C92ZRS8?psc=1&ref=ppx_yo2ov_dt_b_product_details)
 - 3 x Arduino nano: [Amazon](https://www.amazon.de/-/en/AZDelivery-AZ-Nano-board-Atmega328-including/dp/B078SBBST6/ref=sr_1_3?crid=274FHDIZFJWDZ&keywords=arduino+nano+azdelivery&qid=1690021059&sprefix=arduino+nano+a%2Caps%2C81&sr=8-3)
 - 3 x 128x64 oled: [Amazon](https://www.amazon.de/-/en/dp/B074N9VLZX/ref=twister_B07ZQNB1HL?_encoding=UTF8&psc=1)
 - 3 x EC12 rotary encoder: [Amazon](https://www.amazon.de/dp/B08728PS6N?psc=1&ref=ppx_yo2ov_dt_b_product_details)
 - 3 x Red LEDs (5mm)
 - 3 x 100 µF Capacitor
 - 3 x 220 Ω Resistor (for LED - pulldown) 
 - 9 x 10 kΩ Resistor (for Rotary encoder - pulldown)

### Hardware
 - filament for your 3D-printer
 - Solder (and if needed Flux)
 - Wires
 - shrink tubing
 - hot-glue-sticks
 - 3 x breadboards like those: [Amazon](https://www.amazon.de/-/en/AZDelivery-AZ-Nano-board-Atmega328-including/dp/B078SBBST6/ref=sr_1_3?crid=274FHDIZFJWDZ&keywords=arduino+nano+azdelivery&qid=1690021059&sprefix=arduino+nano+a%2Caps%2C81&sr=8-3)
 - 3 x 9V Battery

### Tools

 - 3D Printer
 - Soldering Station/Iron
 - If needed: helping hands for soldering or a vise as misused helping hands :D
 - Hot-glue-gun
 - Wire stripper
 - Pliers
 - Saw (Handsaw, Bandsaw or similar)

## Soldering

In the following image you can see how everything is supposed to be wired up.
I **always** used 70mm long wires for soldering.

| ![img1](terminal_fritzing.png) |
| :-: |
| *soldering diagram* |

1. Because the space is limited you need to cut the breadboards to the desired size of 18x11 holes.

2. To connect more holes I used a short wire and soldered it to each hole and the pin of the arduino.

   | ![img2](breadboard.JPG) | ![img3](5v-gnd-line.JPG) |
   | :-: | :-: |
   | *cutted breadboard with connection of holes* | *5V and gnd line from top* |

3. As you can see I only soldered the pins of the arduino, that I needed.
   On the left picture on the left hand side you can see the gnd and 5V line from the bottom. 
   The next step would be to connect the gnd-arduino-pin with the gnd line and the 5V pin with the 5V line.
   | ![img4](gnd-line.JPG) | ![img5](5V-line.JPG) |
   | :-: | :-: |
   | *gnd connection* | *5V-connection* |

4. VIN and gnd-wire for the external power source
   | ![img5](5V-line.JPG) |
   | :-: |
   | *blue: VIN-wire, black: gnd-wire* |

5. Next you should solder the radio-module.
   1. Solder the 100 µF Capacitor onto the module. :warning: be carefull so that the white side of the capacitor is connected to the gnd pin of the radio-module
   
   2. Now solder all 4 wires to the radio-module.

   3. In the last step you solder the wires from the radio module to your breadboard, start with gnd then 5V and then the two data wires.
      | ![img6](hc-12.JPG) |
      | :-: |
      | *radio-module with capacitor* |

6. After the radio module continue with soldering the oled-screen.
   Again, first solder the wires to the screen and then to the breadboard.
   On the breadboard start with gnd, then 5V, then the data wires.

7. Now the LED follows.
   First solder the 220 Ω Resistor onto the short leg (cutted side) of the LED.
   This side also goes onto your gnd line on the breadboard.
   After that solder the other leg of the LED onto the data pin.

8. Next is the rotary encoder:
   1. First solder all the wires onto the rotary encoder and then the two gnd wires onto the gnd-line on the breadboard.
   
   2. After that, solder the three 10 kΩ Resistors onto the 5V-line and then onto the three data pins.
      To prevent short circuits use shrink tubing around the resistors and only leave a small part of the wire unprotected.
      | ![img7](10k-resistors.JPG) |
      | :-: |
      | *10 kΩ Resistors with shrink tubing* |

   3. To finish solder the data wires onto the breadboard.
   
9.  Congratulations you finished soldering everything!
   It should look somewhat like this:

   | ![img8](soldering-left.JPG) | ![img9](soldering-front.JPG) | ![img10](soldering-right.JPG) |
   | :-: | :-: | :-: |
   | *left* | *front* | *right* |

## 3D-printing

Now you need to print the housing of the Termial.
It consists of two parts, the box and the cover.

The measurements of my box are for a specific cash register we use at our uni-partys, if you want to fit the terminal into your cash register you probably have to take the measurements yourself and design your own box.

For printing you dont need support structure!

### box

### cover

//druckdateien

## Assembly

## Code

## Finished!

//zip

### license

https://creativecommons.org/licenses/?lang=de