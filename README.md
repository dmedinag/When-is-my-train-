# Traintimes

This repository encompasses a fun couple of days during the Make-A-Thon: a hackathon involving not only software but also hardware. My team and I worked on a small 8-digit display that would display two configurable times: the train of the next train home and the time it would take you to commute by car.

The components of the project were fairly simple:
- A device controller, to be run in an arduino-compatible micro controller with WiFi connection (we used something like [this](https://www.adafruit.com/product/3213))
- The display, in our case the a 8-digit 7-segment (`MAX72XX`)
- A node.js server, running in the cloud, providing the display with the data to be displayed (hosted in GCP)

Feel free to look around the code. It is provided with no guarantee whatsoever, use at your own risk!