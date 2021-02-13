const Publisher = require('./publisher')
var pub = new Publisher('127.0.0.1',8080);


pub.connect().then(() => {
    
})