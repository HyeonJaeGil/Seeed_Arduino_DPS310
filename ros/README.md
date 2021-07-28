# Usage

## 1. Setup arduino, sensor library and rosserial library

https://github.com/Infineon/DPS310-Pressure-Sensor/releases
https://www.arduino.cc/en/Guide/Linux
http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup

## 2. get id of arduino and write rules file

https://www.clearpathrobotics.com/assets/guides/kinetic/ros/Udev%20Rules.html
https://www.clearpathrobotics.com/assets/guides/kinetic/ros/Driving%20Husky%20with%20ROSSerial.html


<pre><code>
# /etc/udev/rules.d/97-arduino.rules 
SUBSYSTEMS=="usb", ACTION=="add", ATTRS{idVendor}=="0403", ATTRS{idProduct}=="6001", MODE="0666", SYMLINK+="arduino_nano", GROUP="dialout"
</code></pre>

sudo udevadm control --reload-rules && sudo service udev restart && sudo udevadm trigger


## 3. rosrun rosserial_python serial_node.py /dev/arduino_nano



# Issue
- python version issue
https://answers.ros.org/question/362043/importerror-no-module-named-queue/

- How to calculate the altitude
https://www.mide.com/air-pressure-at-altitude-calculator
