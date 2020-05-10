const robot = require("robotjs");
const SerialPort = require('serialport')
port = new SerialPort('/dev/tty.usbmodem142101', {
  baudRate: 9600
});

port.on('data', async function (data) {
  console.log('Data', data.toString('utf8'))
  await new Promise(resolve => setTimeout(resolve, 1100));
  robot.keyTap("space");
});


