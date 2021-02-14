const Publisher = require('./publisher')
const Subscriber = require('./subscriber')
const readline = require('readline')

var rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

var pub = new Publisher('127.0.0.1',8080);

function publish() {
    rl.question('What to publish?', async data => {
        await pub.publish({
            dataType: 'Binary',
            data: Buffer.from(data)
        })

        publish()
    })
}
 function test() {
    pub.connect().then((response) => {
        var sub = new Subscriber('127.0.0.1', 8080)
        
        sub.listen(pub.id, data => {
            console.log('Published data is: ', data.toString('ascii'))
        }).then(() => {
            publish()
        })
    }).catch(err => {
        console.log(err)
    })
}

test()