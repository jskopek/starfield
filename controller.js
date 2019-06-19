const SerialPort = require('serialport')
const Readline = require('@serialport/parser-readline')
const path = '/dev/ttyS3'
const baudRate = 9600;
const port = new SerialPort(path, { baudRate: baudRate });

const parser = new Readline();
port.pipe(parser);

parser.on('data', line => console.log(`> ${line}`))
port.write('ROBOT POWER ON\n')

setInterval(() => {
    let choices = "abc";
    let choice = choices[parseInt(choices.length * Math.random())]
    port.write(choice, (err) => {
        if(err) { console.log(`error sending data through port baudRate: ${baudRate} command: ${choices}`); }
        console.log(`sent sequence: ${choice}`);
    });
}, 100);
//> ROBOT ONLINE
