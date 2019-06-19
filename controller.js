const SerialPort = require('serialport')
const Readline = require('@serialport/parser-readline')
const path = '/dev/ttyS3'
const baudRate = 9600;
const port = new SerialPort(path, { baudRate: baudRate });

const parser = new Readline();
port.pipe(parser);

parser.on('data', line => console.log(`received data > ${line}`))
port.write('ROBOT POWER ON\n')

setInterval(() => {
    let lightSequence = [];
    for(var pixelNum = 0; pixelNum < 2; pixelNum++) {
        let red = parseInt(255 * Math.random());
        let green = parseInt(255 * Math.random());
        let blue = parseInt(255 * Math.random());
        lightSequence.push([red, green, blue]);
    }

    let lightSequenceString = lightSequence.map(rgbArray => rgbArray.join(',')).join(';')

    let command = `<${lightSequenceString}>`
    port.write(command, (err) => {
        if(err) { console.log(`error sending data through port baudRate: ${baudRate} command: ${choices}`); }
        console.log(`sent command: ${command}`);
    });
}, 1000);
//> ROBOT ONLINE
