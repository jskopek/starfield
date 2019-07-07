const SerialPort = require('serialport')
const Readline = require('@serialport/parser-readline')

class LEDController {
    /* responsible for connecting to the LED controller and sending commands. Commands should be sent to an Arduino
     * via the serial port */
    init() {
        this.opened = false
        this.port = undefined;
        this.parser = undefined;
    }

    connect(path, baudRate) {
        this.path = path;
        this.baudRate = baudRate;

        this.port = new SerialPort(this.path, { baudRate: this.baudRate });
        this.parser = new Readline();
        this.port.pipe(this.parser);

        //this.parser.on('data', line => console.log(`received data > ${line}`))
        this.port.write('LED CONTROLLER ON\n')


        this.port.on('error', function(err) {
            console.log('Error: ', err.message)
        })
        this.port.on('open', function(err) {
            console.log('Port opened!')
            this.opened = true;
        })

    }
    send(ledArray) {
        /* send an array of [r,g,b] values to the LEDs */
        let ledArrayString = ledArray.map(rgbArray => rgbArray.join(',')).join(';');

        let command = `<${ledArrayString}>`
        
        if(this.opened) {
            this.port.write(command, (err) => {
                if(err) { console.log(`error sending data through port baudRate: ${this.baudRate} command: ${command}`); }
                console.log(`sent command: ${command}`);
            });
        } else {
            console.log(`not connected to LEDController; simulating command: ${command}`);
        }
    }
}

var controller = new LEDController();
controller.connect('/dev/ttyS3', 9600)

setInterval(() => {
    let lightSequence = [];
    for(var pixelNum = 0; pixelNum < 2; pixelNum++) {
        let red = parseInt(255 * Math.random());
        let green = parseInt(255 * Math.random());
        let blue = parseInt(255 * Math.random());
        lightSequence.push([red, green, blue]);
    }
    controller.send(lightSequence);
}, 1000);


