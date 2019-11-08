const SerialPort = require('serialport')
const Readline = require('@serialport/parser-readline')
const path = '/dev/ttyS3'
const baudRate = 9600;
const port = new SerialPort(path, { baudRate: baudRate });

const parser = new Readline();
port.pipe(parser);

parser.on('data', line => console.log(`received data > ${line}`))
port.write('READER POWER ON\n')
