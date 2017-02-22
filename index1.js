
var macAddress = "00:06:66:7C:8A:55";
var Speed = 100;


function onLoad(){
    
	document.addEventListener("deviceready", onDeviceReady, false);
    
    document.getElementById("F").addEventListener("touchstart", Forward, false);
    document.getElementById("F").addEventListener("touchend", Stop, false);
    
    document.getElementById("B").addEventListener("touchstart", Back, false);
    document.getElementById("B").addEventListener("touchend", Stop, false);
    
    document.getElementById("L").addEventListener("touchstart", Left, false);
    document.getElementById("L").addEventListener("touchend", Stop, false);
    
    document.getElementById("R").addEventListener("touchstart", Right, false);
    document.getElementById("R").addEventListener("touchend", Stop, false);
    
	document.getElementById("incSpeed").addEventListener("touchstart", incSpeed, false);
    document.getElementById("incSpeed").addEventListener("touchend", Stop, false);
	
	document.getElementById("decSpeed").addEventListener("touchstart", decSpeed, false);
    document.getElementById("decSpeed").addEventListener("touchend", Stop, false);
	
}

//Control Functions


function Stop() {
	document.getElementById("showMsg").innerHTML = "stop";
    bluetoothSerial.write("s");
}

function Forward () {
    document.getElementById("showMsg").innerHTML = "forward";
	bluetoothSerial.write("f");
	
}

function Back() {
    document.getElementById("showMsg").innerHTML = "back";
	bluetoothSerial.write("b");
}

function Left() {
    document.getElementById("showMsg").innerHTML = "left";
	bluetoothSerial.write("l");
	
}

function Right() {
	document.getElementById("showMsg").innerHTML = "right";
    bluetoothSerial.write("r");
}



function incSpeed() {
	document.getElementById("showMsg").innerHTML = "inc";
	Speed+=25;
	if(Speed > 250) {
    Speed = 250;
  }
	document.getElementById("currentSpeed").innerHTML = Speed;
	bluetoothSerial.write("i");
	
}

function decSpeed() {
	document.getElementById("showMsg").innerHTML = "dec";
	Speed-=25;
	 if(Speed < 25) {
    Speed = 25;
	 }
	document.getElementById("currentSpeed").innerHTML = Speed;
	bluetoothSerial.write("d");
}


function onDeviceReady(){
	bluetoothSerial.connect(macAddress, onConnect, onDisconnect);
}

/* I onConnect kaldes bluetoothSerial.subscribe, der kaldes når data modtages
 * data skal sendes med et slut tegn i dette eksempel er det \n, der indgår i
 * Arduino-kommandoen println()
 */
function onConnect() {
    bluetoothSerial.subscribe("\n", onMessage, subscribeFailed);
    document.getElementByID("statusDiv").innerHTML="Connected to " + macAddress + ".";        		
}

/*
 * Data vises i "fraArduino"
 */
function onMessage(data) {
    document.getElementById("fraArduino").innerHTML =""+ data;       
}

/*
 * bluetoothSerial.write sender data af formen 
 * ArrayBuffer, string, array of integers, or a Uint8Array.
 * I dette eksempel sendes en streng 
 */
function sendToArduino(data) {
        bluetoothSerial.write(data);
}


function onDisconnect() {
        alert("Disconnected");
        statusDiv.innerHTML="Disconnected.";
}

function subscribeFailed() {
        alert("subscribe failed");
}
	