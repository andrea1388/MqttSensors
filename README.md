# MqttSensors
C++ classes for mqtt enabled sensors and actuators


Implementano i seguenti oggetti: sensore binario, attuatore binario (switch), sensore analogico.

Ogni sensore ha associato un topic mqtt ed ha la funzione publish per notificareil cambio di stato


classe BinarySensor
fornisce un valore di uscita (value) che può essere 0 o 1 a seconda del valore di ingresso
la lettura avviene nel metodo run al quale si fornisce l'ingresso (tipicamente il livello di un pin gpio). La classe fa il debouncing. Dopo un cambio di stato non legge più l'ingresso per un tempo debounceTime in ms
Se sono impostati i parametri  mqtt e mqttStateTopic ad ogni cambio di stato farà il publish con messaggio ON/OFF

classe Sensor
fornisce un valore di uscita (value) di tipo float a seconda del valore di ingresso
la lettura avviene nel metodo run al quale si fornisce l'ingresso (tipicamente il valore di un sensore es temperatura)
Se sono impostati i parametri  mqtt e mqttStateTopic ad ogni cambio di valore che si discosta più di un valore impostato e non prima di un certo tempo dall'ultima pubblicazione farà il publish con messaggio uguale al valore

classe Switch
rappresenta un attuatore ed è associato ad un pin di uscita. Il valore value dipende dall'ingresso che viene valutato dal metodo run(bool inputvalue). Ha due modalià di funzionamento: normale e toggle. Con la prima l'uscita è attiva se l'ingresso è attivo. Con la seconda l'uscita viene invertita ad ogni cambio dell'ingresso da 0 a 1. Non c'è il debouncing quindi conviene fornire come ingresso l'uscita di uno BinarySwitch. In modo normale si può impostare un duty cycle con i parametri tOn e tOff. Se sono impostati i parametri  mqtt e mqttStateTopic ad ogni cambio di stato farà il publish con messaggio ON/OFF


























































































