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
    //   var text = "";

    var newMood = {

        mood_id: "O" + makeid(7),
        current_mood: x.elements[3].value, 
        desired_mood: x.elements[5].value
        // order_status: x.elements[1].value,
        // delivery_id: "D" + makeid(7),
        // delivery: {
        //     delivery_name: x.elements[3].value,
        //     delivery_address: x.elements[4].value,
        //     delivery_coordinates: x.elements[5].value
        // },
        // restaurant: {
        //     restaurant_id: x.elements[6].value,
        //     restaurant_name: x.elements[7].value,
        //     restaurant_coordinates: x.elements[8].value
        // },
        // order_items: x.elements[9].value,
        // order_total: x.elements[10].value,
        // order_currency: x.elements[11].value,
        // order_placed: x.elements[12].value
    };

    document.getElementById("mood").innerHTML = JSON.stringify(newMood);
    // document.getElementById("status").innerHTML = newOrder.order_status;
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

function updateTable(payload) {
    var tr;
    tr = $('<tr/>');
    tr.append("<td>" + json[0].mood_id + "</td>");
    tr.append("<td>" + json[1].current_mood + "</td>");
    tr.append("<td>" + json[4].desired_mood + "</td>");
    $('table').append(tr);
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