const { pbkdf2 } = require('crypto');
const Publisher = require('./publisher')
var pub = new Publisher('127.0.0.1',8080);


pub.connect().then(() => {
    console.log('Connected to the server successfully.')
}).catch(err => {
    console.error(err)
})
