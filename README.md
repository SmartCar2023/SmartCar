## Name
your droid tm. Arduino Robot source code

## Beschreibung
GitLab repo für your Droid tm. Arduino Roboter. Geschrieben in Arduino/c++.

Als Entwicklungsboard benutzen wir den Arduino Nano

Alle module im Abschnitt "Aufrufbare Funktionen" können frei verwendet werden.

Zunächst bitte die Pins am Codeanfang festlegen.

## FAQ

<details><summary>Arduino IDE hängt sich beim starten auf</summary>

Die neue Version der Arduino IDE (2.1.X) lädt beim ersten start weitere resourcendateinen aus dem Internet herunter. Wenn der Computer also keine aktive Internetverbindung hat, wird die IDE nie Starten. 

Um dies zu umgehen kann die Legacy IDE (1.8.X) von der [Arduino Webseite](https://www.arduino.cc/en/software) heruntergeladen werden. 

PS: VS Code ist ein wesentlich besserer code editor

</details>

<details><summary>Flashen funktioniert nicht (timeout oder zugriff verweigert)</summary>

Möglichkeit 1: Falsches Board oder falscher COM Port ist ausgewählt. Unter dem Reiter Werkzeug sind festzulegen:

-> Board : Arduino Nano

-> Prozessor : ATMega382P (Old Bootloader)

-> Port : Trian and error. Meistens der COM Port mit der größten Zahl


Es geht immer noch nicht?

Eventuell fehlt der USB to Serial Treiber. Nortmalerweise lädt sich Windows den Treiber automatisch über Windows Update herunter, wenn jedoch keine Internetverbindung besteht funktioniert das nicht.

Um dies unter Windows festzustellen einfach den Geräte Manager öffnen und gucken ob ein Gerät mit dem Namen "USB2.0-Serial" unter dem Punkt "Andere Geräte" erscheint. Zum testen kann der Arduino abgesteckt werden, dann einmal rechtsklick auf ein irgendein Gerät und einmal "Nach geänderter Hardware suchen" klicken. Ist das Gerät nun weg, handelt es sich um den Arduino und der Treiber fehlt.

Richtig wäre das der Arduino unter "Anschlüsse (COM & LPT)" auftaucht. Auch hier kann zum feststellen ob es der Arduino ist nach dem gleichen prinzip vorgegangen werden.

Ein funktionierender Treiber wäre z.B. der "CH343SER" Treiber von WCH. Einen Download davon findet ihr im Ordern "Arduino_Nano_Driver". 

Alternativ kann er [hier](https://www.wch.cn/downloads/category/67.html?feature=USB%E8%BD%AC%E4%B8%B2%E5%8F%A3&product_name=CH347) heruntergleaden werden

</details>

<details><summary>Flashen funktioniert nicht (not in sync error)</summary>

Sollte der Sketch erfolgreich kompilieren aber ihr bekommt beim Hochladen eures Programms diesen Fehler:

`avrdude: stk500_getsync() attempt 10 of 10: not in sync: resp=0xe0`

Dann liegt das an dem Bluetooth Modul. Dieses blockiert die Serielle verbindung und muss daher zum Hochladen des codes kurzzeitig entfernt werden. Nach dem Hochlanden kann das Modul wieder eingesteckt werden.

Auch während das Bluetooth Modul den Arduino steuert, ist der serielle Monitor zum debuggen verfügbar.

</details>

<details><summary>Flashen funktioniert nicht (can't open device error)</summary>

Sollte der Sketch erfolgreich kompilieren aber ihr bekommt beim Hochladen eures Programms diesen Fehler:

`avrdude: ser_open(): can't open device "\\.\COM1": Das System kann die angegebene Datei nicht finden.`

Wobei COM1 hier nur ein Beispiel für den COM Port ist, auf den ihr geflashed habt.

Dieser Fehler kann mehrere Gründe haben. Hier sind ein paar Ideen.

1. Der falsche COM Port ist ausgewählt

2. Das Kabel könnte defekt sein und sollte mit einem anderen Gerät getestet werden.

3. Der falsche Treiber ist installiert. Bitte nehmt den Treiber aus dem Ordner Arduino_Nano_Driver. Ihr müsst ihn entpacken und die .exe ausführen

</details>

## Emp­foh­lene Pinbelegung

**Motor:**
<details><summary>Click to expand</summary>

| Variabel | standard Pin | Beschreibung |
| ------ | ------ | ------ |
|     ML1 | 9   |    Gleichstrommotor Links - Am Motor contoller ist es "In 1"    |
|    ML2 | 5    |    Gleichstrommotor Links - Am Motor contoller ist es "In 2"     |
| MR1 | 10 | Gleichstrommotor Rechts - Am Motor contoller ist ess "in 3" |
| MR2 | 6 | Gleichstrommotor Rechts - Am Motor contoller ist es "in 4" |

Hier schonmal eine kleine Vorwarnung. Wenn das car z. B. beim Aufrufen der Funktion drive_forward rückwärts fährt oder sich dreht, dann müssen entweder die betroffenen Motoranschlüsse gedreht werden oder die Pinbelegung im code gedreht werden.

</details>

**Lichtschranke:**

<details><summary>Click to expand</summary>

| Variabel | standard Pin | Beschreibung |
| ------ | ------ | ------ |
|    LSR | 3    |   Lichtschranke rechtes Rad !!!ACHTUNG NACH BAUPLAN SIND LINKS UND RECHTS VERTAUSCHT!!!     |
|    LSL | 2    |   Lichtschranke linkes Rad !!!ACHTUNG NACH BAUPLAN SIND LINKS UND RECHTS VERTAUSCHT!!!     |
| LED_PIN | 4 | LED Pin der Gabellichtschrankenplatine |

Signal Links des Bauplanes ist eigentlich rechts und rechts ist eigentlich links, wenn die Platine wie in den Bauplänen ausgerichtet ist! Wenn wir davon ausgehen, dass das Lichtschrankenmodul so wie in den Bildern ausgerichtet ist, dann ist der obere datapin (3er Pinreihe, der oberste) für das rechte Rad zuständig und der untere data pin (3er Pinreihe, der untere pin) für das links Rad zuständig.

Gabellichtschranke und Überblick:

<p align="center">
  <img src=/pictures/Gabellichtschranke.png width="350" title="Gabellichtschranke">
  <img src=/pictures/Übersicht.png width="350" title="Übersicht">
</p>

</details>

**Servo motor:**

<details><summary>Click to expand</summary>

| Variabel | standard Pin | Beschreibung |
| ------ | ------ | ------ |
|   SERVO_PIN | 12     |    Pin that the Servo is on    |

</details>             

**Ultraschall entfernungsmesser:**

<details><summary>Click to expand</summary>

| Variabel | standard Pin | Beschreibung |
| ------ | ------ | ------ |
|    ultrasonic_power_pin | 11    |    plus pole of the ultrasonic sensor    |
|   ultrasonic_trigger_pin | 7     |   trigger pin of ultrasonic sensor     |
| ultrasonic_echo_pin | 8 | echo pin of ultrasonic sensor |

</details>     

## Variablen:

<details><summary>Servo</summary>

| Datatype | Variabel | Standard Wert | Beschreibung |
|------ | ------ | ------ | ------ |
| int |    servo_mittel_position | 135   |    Trial and error Wert zwischen 0 und 180 bei dem der Ultraschallsensor nach vorne zeigt    |


</details>

<details><summary>Motor Korrekturfaktoren</summary>

Dies sind Korrekturfaktoren damit das car geradeaus fährt.

Sie werden duch trial and error ermittelt. **Diese Faktore sind immer >= 1.** Bsp. bei Linkskurve faktor rechts leicht verkleinern, z. B. 0.9 und faktor rechts auf 1.00 belassen!

Es gibt zwei verschiedene korrekturtypen. Die beiden folgenden Werte werden durch das Trim() Script an die umdrehungen der Räder angepasst. Sie können also bei verwendung des Trim() scripts beim standard Wert belassen werden.


| Datatype | Variabel | Standard Wert |
| ------ | ------ | ------ |
| float |   faktor_motor_links     | 1.00 |
| float |   faktor_motor_rechts     | 1.00 |

Die folgenden beiden Faktoren werden **NACH** dem Trim() script aufgerechnet. Sie sind zu verändern, wenn das car auch nach dem Trim() script noch einen Drall hat. **Wenn das Trim() script nicht verwendet wird haben diesen beiden Werte keinen Einfluss!**

| Datatype | Variabel | Standard Wert |
| ------ | ------ | ------ |
| float |   motor_korrektur_faktor_links_after_trim | 1.00 |
| float |   motor_korrektur_faktor_rechts_after_trim | 1.00 |

</details>

<details><summary>Bluetooth Spezifische variablen</summary>

| Datatype | Variabel | Standard Wert | Beschreibung |
| ------ | ------ | ------ | ------ |
|    int    |    bl_speed_value    | 150 | Standard fahrgeschwindigkeit wenn diese nicht per app geändert wird. Wert zwischen 0-255 |

Diese beiden Werte stellen die restliche geschwindigkeit beim fahren der vorwärts-rechts und vorwärts-links funktionen dar. Sie werden via trial and error ermittelt. Desto geringer der Wert ist, desto kleiner wird der kurvenradius.

| Datatype | Variabel | Standard Wert |
| ------ | ------ | ------ |
|   float     |    curve_speed_links    | 0.65 |
|   float     |    curve_speed_right    | 0.65 |

</details>

## Aufrufbare Funktionen

<details><summary>drive_forward</summary>

Die Funktion _drive_forward_ akzeptiert zwei Parameter vom Typ int, die die Geschwindigkeit der linken und rechten Motoren angeben. Das Car fährt dann gerade aus. Diese Werte können 0-255 annehmen. Der Roboter wird so lange nach vorne fahren bis halt_motors() oder ein anderer drive aufruf getätigt wird.

| Funktionsname | Wert 1 | Wert 2 |
| ------ | ------ | ------ |
|    drive_forward    |   Motorgeschwindigkeit Links  | Motorgeschwindigkeit Rechts |

Ein Beispielaufruf wäre "drive_forward(200, 200);"

Die Funktion skaliert die Geschwindigkeit jedes Motors mit dem faktor_motor_links und faktor_motor_rechts und schreibt dann die PWM-Signale auf die entsprechenden Motor Pins.

</details>

<details><summary>drive_backward</summary>

Die Funktion _drive_backward_ akzeptiert zwei Parameter vom Typ int, die die Geschwindigkeit der linken und rechten Motoren angeben. Das Car fährt dann rückwärts. Diese Werte können 0-255 annehmen. Der Roboter wird so lange rückwärts fahren bis halt_motors() oder ein anderer drive aufruf getätigt wird.

| Funktionsname | Wert 1 | Wert 2 |
| ------ | ------ | ------ |
|    drive_backward    |   Motorgeschwindigkeit Links  | Motorgeschwindigkeit Rechts |

Ein Beispielaufruf wäre "drive_backward(200, 200);"

Die Funktion skaliert die Geschwindigkeit jedes Motors mit dem faktor_motor_links und faktor_motor_rechts und schreibt dann die PWM-Signale auf die entsprechenden Motor Pins.

</details>

<details><summary>drive_rotate_right</summary>

Die Funktion _drive_rotate_right_ akzeptiert einen Parameter vom Typ int, der die Geschwindigkeit des linken Motors angibt. Das Car dreht sich dann mit dem Durchmesser der beiden Räder. Dieser Wert kann 0-255 annehmen. Der Roboter wird sich so lange drehen bis halt_motors() oder ein anderer drive aufruf getätigt wird.

| Funktionsname | Wert 1 |
| ------ | ------ |
|    drive_rotate_right    |   Motorgeschwindigkeit Links  |

Ein Beispielaufruf wäre "drive_rotate_right(200);"

Die Funktion skaliert die Geschwindigkeit jedes Motors mit dem faktor_motor_links und schreibt dann das PWM-Signal auf den entsprechenden Motor Pin.

</details>

<details><summary>drive_rotate_left</summary>

Die Funktion _drive_rotate_left_ akzeptiert einen Parameter vom Typ int, der die Geschwindigkeit des rechten Motors angibt. Das Car dreht sich dann mit dem Durchmesser der beiden Räder. Dieser Wert kann 0-255 annehmen. Der Roboter wird sich so lange drehen bis halt_motors() oder ein anderer drive aufruf getätigt wird.

| Funktionsname | Wert 1 |
| ------ | ------ |
|    drive_rotate_left    |   Motorgeschwindigkeit rechts  |

Ein Beispielaufruf wäre "drive_rotate_left(200);"

Die Funktion skaliert die Geschwindigkeit jedes Motors mit dem faktor_motor_rechts und schreibt dann das PWM-Signal auf den entsprechenden Motor Pin.

</details>

<details><summary>halt_motors</summary>

Die Funktion _halt_motors_ stoppt alle Motoren und lässt das car zum stillstand kommen.

Ein Beispielaufruf wäre "halt_motors();"

</details>

<details><summary>trim</summary>

**Die Funktion wird im setup mit dem befehl "trim()" aufgerufen**

Die Trim funktion hat die Aufgabe leichte unterschiede zwischen den Motoren automatisch auszugleichen. Sie ist im setup loop einmalig auszuführen

Um dies zu erzielen, fährt das Car für insgesamt 2,8 Sekunden vier verschiedene Geschwindigkeiten für jeweils 700 Millisekunden und zählt dabei die umdrehungen der beiden Räder mit den Lichtschranken.

Aus der differenz wird ein Faktor errechnet, mit dem der faktor_motor_links und faktor_motor_rechts aktualisiert werden, um die drehzahl der beiden Motoren anzugleichen. Danach wird noch der motor_korrektur_faktor_links_after_trim und motor_korrektur_faktor_rechts_after_trim auf den angepassten Wert gerechnet.

Die Funktion erwartet das die drive funktionen zuvor definiert wurden und funktionieren. PinModes und variablen die das Script benötigt werden zu beginn der funktion automatisch definiert.

</details>

<details><summary>Servo_init</summary>

Die _Servo_init_ funktion initialisiert den Servo für weitere benutzung. Ohne diese funktion auszuführen, funktionen keine anderen servo funktionen.

Diese Funktion ist einmalig im Setup auszuführen.

Dabei wird nur der Befehl "Servo.attach(SERVO_PIN)" ausgeführt

</details>

<details><summary>servo_set_degree</summary>

Die _servo_set_degree_ Funktion stellt den Winkel des Servos ein.

| Datatype | Funktionsname | Wert 1 | Wertebereich |
| ------ | ------ | ------ | ------ |
|   int     |    servo_set_degree    | Servo Winkel | 0-180 |

Ein Beispielaufruf wäre "servo_set_degree(125);"

</details>

<details><summary>ultrasonic_sensor_init</summary>

Die _ultrasonic_sensor_init_ Funktion initialisiert den Ultraschall entfernungsmesser.

PinModes werden zu Anfang der Funktion definiert. Für die spätere Verwendung wird auch schonmal der Ultraschall Sensor per GPIO Pin mit Strom versorgt.

</details>

<details><summary>ultrasonic_sensor_read_distance_cm</summary>

Die funktion _ultrasonic_sensor_read_distance_cm_ liest die Distanz die der Ultraschallsensor erkennt aus und gibt diese via return wieder zurück.

| Funktionsname | return Datatype |
| ------ | ------ |
|    ultrasonic_sensor_read_distance_cm    |    float    |

Ein Anwendungsbeispiel wäre:

`gemesserner_abstand = ultrasonic_sensor_read_distance_cm();`

`Serial.print(gemesserner_abstand);`

`delay(1000);`

Dieser code liest den Ultraschallsensor jede Sekunde einmal aus und druckt die erkannte Distanz in cm in die serielle Konsole.

Um die Abstandmessung vom Ultraschallmodul zu erhalten muss der Sense Pin für 10 Nanosekunden eingeschaltet werden

Das Script schaltet den sense Pin vom Ultraschallsensor zunächst für 5 Nanosekunden aus, damit das nachflgende HIGH Signal klar ist. Danach wird der Pin für 10 Nanosekunden aktiviert und danach wieder deaktiviert.

Danach messen wir den mit der pulseIn Funktion die länge des Pulses den wir vom echo Pin des Ultraschallsensors zurückbekommen. Diese Länge speichern wir in einer long.

Um die dauer des Signals von Nanosekunden in cm zu bekommen, nehmen wir uns den Umrachnungsfaktor aus dem Datenblatt des Ultraschallsensors. Diesen Wert geben wir dann mit return wieder zurück.

</details>

## void setup() Tips

Wenn man irgendwas mit den Motoren machen möchte, müssen die Motorpins erstmal als output definiert werden. Dazu einfach folgenden code verwenden:

`pinMode(ML1, OUTPUT);`

`pinMode(ML2, OUTPUT);`

`pinMode(MR1, OUTPUT);`

`pinMode(MR2, OUTPUT);`

Für die Serielle ausgabe und für das Bluetooth modul muss die Serielle verbindung mit der Baudrate 9600 gestartet werden. Dazu den folgenden Befehl verwenden.

`Serial.begin(9600);`

Danach muss nach bedarf initialisiert werden. Für die trim() Funktion muss der Ultraschallsensor initialisiert sein. Dafür einfach folgenden befehl benutzen.

`ultrasonic_sensor_init();`

Trim kann ganz einfach Aufgerufen werden. Dazu einfach folgenden Befehl ausführen.

`trim();`

Danach kann bei bedarf noch der Servo initialisiert und in die Mittelposition gefahren werden.

`servo_init();`

`servo_set_degree(servo_mittel_position);`

## Bluetooth Tips

Wenn man mit dem Bluetooth Modul arbeiten will, sollte man einige Dinge beachten.

Zunächst einmal das sich das gleich erklärte alles auf die Android APP "Arduino Car" von ONE DAY OF CODE bezieht. Ich wählte diese App, da sie mit etwa 100.000 Downloads die meistheruntergeladene App zum Zeitpunkt des schreibens des codes war.

Die App sendet, nachdem eine Verbindung mit dem Bluetooth modul des cars hergestellt wurde, bei konopfdruck jeweils einen Buchstaben. Z. B. "F" um nach vorne zu Fahren.

Ferner kann man mit der App aber auch Servos oder die Geschwindigkeit des Cars steuern, da zwei slider mit einer frei einstellabren Reichweite zur verfügung stehen. Diese machen das handling der Nachricht etwas schwerer. Da wir jetzt z. B. "J120" und nicht mehr nur einen einzelnen Buchstaben bekommen.

Es gibt auch noch rastende Schalter, die solange aktiv sind, bis sie erneut gedrückt werden.

zu beginn des loops sollten wir zunächst nur fortfahren wenn eine Serielle verbindung zur verfügung steht. Das kann mit:

`Serial.available()`

überprüft werden. Der restliche code sollte also in eine if Schleife mit dieser bedingung.

Nun müssen wir vom seriellen Eingang lesen. Wenn man nur einen Buchstaben oder eine Zahl haben möchte und alles weitere in dieser Zeile nicht benötigt, kann man:

`char Serial_input = Serial.read()`

benutzen. Jedoch funktioniert diese Methode nicht mehr, wenn wir statements von mehr als einem char bekommen. Wie z. B. die Servo pos. anfragen. Deswegen verwenden wir den folgenden Befehl:

`String Serial_input = Serial.readStringUntil('\n');`

Hierbei lesen wir nicht mehr nur einen einzelnen char sondern eine ganze Zeile. das '\n' ist das neue Zeile Symbol. Für das nachfolgende handling benötigen wir jedoch nur den ersten Buchstaben. Weswegen wir den string jetzt erstmal nach dem ersten character abschneiden:

`String Serial_input_first_char_substring = Serial_input.substring(0, 1);`

jetzt wandeln wir den String noch in einen char um:

`char Serial_input_first_char = Serial_input_first_char_substring.charAt(0);`

und jetzt haben wir immer den ersten Buchstaben von jeder Zeile als char. Den vollen String kann man jedoch im späteren verlauf dieser loop iteration aufrufen.

Jetzt geben wir unseren ersten char and die switch funktion.

`switch (Serial_input_first_char) {...}`

in diese switch funktion können wir cases tun, die ausgeführt werden, wenn der char übereinstimmt. Z. B.

`switch (Serial_input_first_char) {`

`    case 'F':`

`        drive_forward(150, 150);`

`        break;`

In diesem Beispielcode sehen wir einen case Fall. Wenn der char = "F" ist, wird die funktion drive_forward ausgeführt. Nach dem auszuführenden code muss ein break; plaziert werden. Dies beendet die aktuelle loop Iteration, und die nächste Iteration beginnt.

Dieses switch statement kann man nun wie in meinem Beispielcode verwenden und somit die grundfunktionen wie vorwärts fahren und drehen ermöglichen.

Um z. B. die Servo position zu setzen, bei mir case 'K', bearbeiten wir den Serial_input string nochmal leicht anders.

`int J_value = Serial_input.substring(1).toInt();`

wir nehmen hier den Serial_input string, entfernen den ersten char und konvertieren den String danach in ein Integer. Diesen wert kann man dann z. B. verweden, um die Servo position zu setzen, indem der Wert an die funktion servo_set_degree gegeben wird.

`servo_set_degree(J_value);`

Die dritte sondersituation ist der Knopf, wo anderer code im loop ausgeführt werden soll, bis der gleiche Knopf nochmal betätigt wird.

Dafür benötigen wir einen while loop der solange ausführt bis unser key word zum aufhören erneut auftaucht. zunächst definieren wir eine variabel für unser stop word und setzen diese NICHT auf unseren sollbuchstaben sondern einfach irgendeinen anderen Buchstaben.

`char stop_exec = 'F';`

danach kommt die while schleife

`while (stop_exec != 'M') {`

` `
    
`    //Hier der code der dann im loop laufen soll!`

` `
    
`    stop_exec = Serial.read();`

`    if (stop_exec == 'M') {halt_motors();}`

`}`

Diese while Schleife läuft solange, bis stop_exec = 'M' ist. Die erste ausführung ist durch unser vorheriges Setzen der stop_exec Variabel gegeben. Danach können wir einfach unsere logic die im loop laufen soll in die while schleife schreiben. Am ende der while schleife lesen wir nochmal seriell den nächsten Buchstaben. Und sollten wir in der Schleife befehle benutzen die aufgehoben werden müssen, wie z. B. einen drive befehl, so schreibt man die aufhebung in das if statement am Ende.

Diese implementation hat jedoch ein Problem. Sie funktioniert nur, wenn der loop sich schnell wiederholt. Wenn Pausen verwende werden, kann es sein, das gesedete Buchstaben verloren gehen. Aber auch wenn der loop sich schnell wiederholt kann es Probleme geben wenn die steuerende Person zu viele befehle sendet. Z. B. indem der slider in der Smartphone app langsam hin und her gezogen wird.

In letzterem Fall kann man das gleiche wie oben anwenden und eine ReadStringUntil implementation machen. Im ersten Fall jedoch habe ich so auf die schnelle keine Lösung. Es gibt bestimmt einen Weg auch dieses Problem mit interrups zu Lösen.

Am ende der cases kann noch ein default statement stehen, dieses wird ausgeführt, wenn keine der chars mit der Varibel übereinstimmen. Ich habe in meinem Beispiel einfach einen break; in das default geschrieben.


## Verwendung

Einfach "src/main.ccp" z. B. per Arduino IDE auf den Arduino flashen. Via dem Seriellen Monitor können diverse Werte abgelesen werden. Z. B. die Korrekturfaktoren der Motoren

## Project status
WIP
