$.ajaxSetup({timeout:100});
<!--funzione che permetta la progettazione di pagine web interattive tramite chiamate asincrone-->
var latch = false;

function readUrlAV (form) {
    TextVar = form.inputbox.value;
	VideoVar = "http://"+TextVar+":8080/video";
	AudioVar = "http://"+TextVar+":8080/audio.opus";
	document.getElementById("video").setAttribute('data', VideoVar);
	document.getElementById("audio").setAttribute('data', AudioVar);
}
function testarArduino (form) {
    TextVar = myform2.inputbox.value;
	ArduinoVar = "http://" + TextVar + ":80";
	$.get( ArduinoVar, { "cm3": 7000 })	;
	{Connection: close};
}

document.onkeydown = checkKeyDown;
document.onkeyup = checkKeyUp;

function checkKeyDown(e) {

    e = e || window.event;

    if (e.keyCode == '38') {
        // via avanti
		if (latch == false) {
			TextVar = myform2.inputbox.value;
			ArduinoVar = "http://" + TextVar + ":80";
			$.get( ArduinoVar, { "cm1": 1000 })	;
			{Connection: close};
			latch = true;
		}
    }
    else if (e.keyCode == '40') {
        // vai indietro
		if (latch == false) {
			TextVar = myform2.inputbox.value;
			ArduinoVar = "http://" + TextVar + ":80";
			$.get( ArduinoVar, { "cm2": 1000 })	;
			{Connection: close};
			latch = true;
		}
    }
    else if (e.keyCode == '37') {
       // vai a sinistra
	   if (latch == false) {
			TextVar = myform2.inputbox.value;
			ArduinoVar = "http://" + TextVar + ":80";
			$.get( ArduinoVar, { "cm3": 1000 })	;
			{Connection: close};
			latch = true;
		}

	}
    else if (e.keyCode == '39') {
       // vai a destra
	   if (latch == false) {
			TextVar = myform2.inputbox.value;
			ArduinoVar = "http://" + TextVar + ":80";
			$.get( ArduinoVar, { "cm4": 1000 })	;
			{Connection: close};
			latch = true;
		}
	}
}

function checkKeyUp(e) {
    e = e || window.event;

    if ((e.keyCode == '38')||(e.keyCode == '40')||(e.keyCode == '37')||(e.keyCode == '39')) {
        // mantieni lo stato
		setTimeout(doNothing, 200);
    }
}

function doNothing(){
	TextVar = myform2.inputbox.value;
		ArduinoVar = "http://" + TextVar + ":80";
		$.get( ArduinoVar, { "cm5": 1000 })	;
		{Connection: close};
		latch = false;
}
