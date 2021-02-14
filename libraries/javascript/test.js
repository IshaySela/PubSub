const Publisher = require('./publisher')
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

async function test() {
    var response = await pub.connect();
    console.log('Publishing on port ', response.id)
    publish()
}

test()