const net = require('net')
const protocol = require('./protocol')

class Publisher {
    /**
     * The constructor for class Publisher. no logic is done here.
     * @param { string } remoteIp 
     * @param { number } port 
     */
    constructor(remoteIp, port) {
        this._remoteIp = remoteIp;
        this._port = port;
    }

    /**
     * Connect to the server and send the handshake data.
     * @returns { Promise<void> } A promise that indicates the status of handshake.
     */
    connect() {
        return new Promise((resolve, reject) => {
            this.socket = net.createConnection(this.port,this.remoteIp)
            
            this.socket.on('connect', () => {
                var headers = {
                    ClientType: protocol.ClientType.Publisher,
                    Encrypt: false
                }

                this.socket.write(JSON.stringify(headers));
                this.socket.write('\r\n\r\n')
                
                this.socket.on('data', data => {
                    // resolve the data to the user
                    resolve(JSON.parse(data.toString('ascii')))
                })

            });

        });
    }

    /**
     * Publish the request to all of the subscribers.
     * @param { PublishRequest } request 
     */
    publish(request) {
        var headers = {
            Length : request.data.length,
            DataType: request.dataType
        }

        this.socket.write(JSON.stringify(headers))
        this.socket.write('\r\n\r\n')
    }

    get remoteIp() { return this._remoteIp; }
    get port() { return this._port; }
}

module.exports = Publisher