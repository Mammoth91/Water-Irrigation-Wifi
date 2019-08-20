In this project, you will be making a wifi controlled two channel irrigation system. It is used with an app that sends requests to the NodeMCU which controls the relays that turn on the valves.

As the first step to this project, make sure you have an irrigation system installed by professionals or by yourself. Mine is a two channel one, meaning one valve for the front yard, another for the backyard. You can add more valves as you wish by altering the hardware and software.

You can watch my video on youtube for a demonstration.(video link)

Step Two:
Buy Materials
Materials List:
1x NodeMCU
2x Relay Module
1x Alot of wires
1x Power Supply(With output voltage of the valves. Mine is 24V)
1x Irrigation System(With two channels or more)
1x 5V power supply(For ModeMCU)

Step Three:
Install Software
Software:
Arduino IDE(With NodeMCU board and libraries added)
WaterIrrigation.aia(Mit App Inventor File)

Step Four:
Enter Your wifi SSID and password in the code. Then Upload It.

Step Five:
Open Mit App Inventor and upload the project file. Change the IP address of my NodeMCU to the address of your NodeMCU. Make sure to change the NodeMCU's Ip address to a static one. You can find it in the DHCP section of your router configuration page.

Step Six:
Compile the app and install it on your phone.

Step Seven:
Connect the NodeMCU along with the relays to the power supplies, then to the valves.

You should now be able to control the watering with the app on your phone once everything is powered.
Be sure to check the watering laws of your place before using it!
