// Create a client instance, we create a random id so the broker will allow multiple sessions
client = new Paho.MQTT.Client("broker.mqttdashboard.com", 8000, "clientId" + makeid(3));

// set callback handlers
client.onConnectionLost = onConnectionLost;
client.onMessageArrived = onMessageArrived;

// connect the client
client.connect({
    onSuccess: onConnect
});

function sendMood() {
    var x = document.getElementById("frm1");

    var newMood = {

        mood_id: "O" + makeid(7),
        current_mood: x.elements[1].value, 
        desired_mood: x.elements[5].value
    };

    document.getElementById("mood").innerHTML = JSON.stringify(newMood);
    onSubmit(JSON.stringify(newMood));
}

// called when the client connects
function onSubmit(payload) {
    // Once a connection has been made, make a subscription and send a message.
    console.log("onSubmit");
    client.subscribe("james_turrell");
    message = new Paho.MQTT.Message(payload);
    message.destinationName = "james_turrell";
    client.send(message);
}

// called when the client connects
function onConnect() {
    // Once a connection has been made report.
    console.log("Connected");
}

// called when the client loses its connection
function onConnectionLost(responseObject) {
    if (responseObject.errorCode !== 0) {
        console.log("onConnectionLost: " + responseObject.errorMessage);
    }
}

// called when a message arrives
function onMessageArrived(message) {
    console.log("onMessageArrived:" + message.payloadString);
}

// called to generate the IDs
function makeid(length) {
    var result = '';
    var characters = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';
    var charactersLength = characters.length;
    for (var i = 0; i < length; i++) {
        result += characters.charAt(Math.floor(Math.random() * charactersLength));
    }
    return result;
}