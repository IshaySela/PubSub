const ClientType = require('./protocol').ClientType
const net = require('net')

class Subscriber {
    get port() { return this._port; }
    get remoteIp() { return this._remoteIp; }
    get id() { return this._id; }

    /**
     * @param { string } remoteIp The address of the server. 
     * @param { number } port 
     */
    constructor(remoteIp, port) {
        this._remoteIp = remoteIp;
        this._port = port;
        this._socket = undefined
        this._id = undefined
    }

    /**
     * Subscribe to the endpoint and listen for data.
     * @param { string } endpointId The id of the endpoint to subscribe to.
     * @param { (data: Buffer) => void } callback The callback will be called when data is recived.
     * @returns { Promise<void> } A promise that indicates success or failure.
     */

    listen(endpointId, callback) {
        return new Promise((resolve, reject) => {
            var headers = {
                ClientType: ClientType.Subscriber,
                Id: endpointId
            }
        
            this.socket = net.createConnection(this.port, this.remoteIp)
            
            this.socket.on('connect', (had_error) => {
                this.socket.write(JSON.stringify(headers))
                this.socket.write('\r\n\r\n')
                
                this.socket.on('data', data => {
                    if(!this._doneHandshake)
                    {
                        this._id = JSON.parse(data.toString('ascii')).Id
                        this._doneHandshake = true;
                    }
                    
                    this.socket.on('data', data => {
                        callback(data)
                    })

                    resolve()
                })
    
            })
        })
    }
}

module.exports = Subscriber