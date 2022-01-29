const WebSocket = require("ws");
const Net = require('net');
const { Socket } = require("dgram");

require("crypto");
//import WebSocket, {WebSocketServer} from "ws";
require("dotenv").config({path: `./../.env` });

const HOST = process.env.HOST
const PORT = process.env.PORT

const Clients = new Array();//for storing the clients with an ID
const ClientNames = new Map();//for storing the clients with a name

//const wss = new WebSocket.Server({port: PORT });
const server = new Net.Server(function(connection)
{
    //connection.setKeepAlive(50000);
    //connection.setTimeout(40000);
});
//console.log("Server is listening on port " + PORT);

/*wss.RegisterClient = (ws, name)=>{
    
}

wss.on('connection', (ws)=>{
    Clients.push(ws);

    console.log("A new client has connected");
    
})
*/

server.listen(PORT, HOST, function ()
{ console.log("Server is running on " + HOST + ":" + PORT)})



server.on('connection', function (sock)  
{ 
    console.log("A new client connected!");
    sock.setKeepAlive(true, 500);

    Clients.push(sock);



    sock.on('data', function(chunk){

        const msg = chunk.toString();
        const firstChar = msg.charAt(0);

        if(firstChar == '/')
        {
            ReadCommand(msg, sock);
        } else{
            SendMessage(msg, sock);
        }
    });

    sock.on('error', function(err) {
        const usr = ClientNames.get(sock);

        console.log(`{${usr}} ${err}`);
     });

     sock.on('close', function() //close is called when the connection truely ends
     {
        LeaveServer(sock);
     })
    
    sock.on('end', function() //end is called whenever the socket connection is closed through client via propper protocol NOTE: This does not end the connection
    {
        console.log("Terminating connection safely...");
    })

    sock.on('timeout', function()
    {
        console.log("timeout called");

        if(sock.destroyed)
        {
            console.log("left from timeout");
            LeaveServer(sock);
        }
    })
})

function SendMessage(msg, client)
{

    const clientName = ClientNames.get(client);
    let recieverMsg = `${clientName}: ${msg}`;

    console.log(recieverMsg);


    Clients.forEach(elm => {
        if(elm != client)
        {
            elm.write(recieverMsg);
        }
        else {
            elm.write("You: " + msg);
        }
    })

}

function RegisterNewUser(client, usrname)
{
    ClientNames.set(client, usrname.toString());
    let userJoinedMessage = usrname + " has joined the server!";
    let hack = "";
    let hack2 = hack.concat(userJoinedMessage);
    console.log(hack2);

    Clients.forEach(elm => {

        const cli = ClientNames.get(elm);

        if(cli != "")
        {
            if(cli != usrname)
            {
                elm.write(hack2);
            }        
            else 
            {
                elm.write("You have joined the server!");
            }
        }
    })
}

function LeaveServer(client)
{
    const usr = ClientNames.get(client);
    console.log(usr + " has left the server");

    const elementFinder = (element) => element == client;
    index = Clients.findIndex(elementFinder);
    Clients.splice(index, index);
    ClientNames.delete(client);

    client.end();
    client.destroy();
}

function ReadCommand(msg, client)
{
    const command = msg.charAt(1);
    const cmdCheck = msg.charAt(2);

    if(cmdCheck == " ")
    {
        const args = msg.substring(3);

        switch(command)
        {
            case 'u': 
                console.log("new username");
                RegisterNewUser(client, args.toString());
                break;
            default:
                console.log("invalid command recieved");
                client.write('Invalid command entered.');
                break;
        }
    }
    else 
    {
        console.log("invaldi command sent");
        client.write('Please format commands like /{command char} [args].')
    }
}