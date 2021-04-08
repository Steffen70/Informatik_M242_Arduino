#include <SoftwareSerial.h>

// SoftwareSerial Objekt das zur verbindung mit dem seriellen Display benötigt wird
SoftwareSerial mySerial(0, 1);

// Gemorste Zeichenkette die mit der Evaluate Methode zu einem Buchstaben gewandelt wird
char *letter;
// Startpositon im Letter Array
int letterPosition = 0;
// Länge des letter Arrays
int letterLength = sizeof(letter) / sizeof(letter[0]);
// Text der auf dem Display angezeigt wird
char *plainText;
// Länge des plainText Arrays
int plainTextLength = sizeof(plainText) / sizeof(plainText[0]);

int newKeyCount[] = { // Pins der LEDs die dem Benutzer anzeigen ob der nächste Impuls noch zum angefangen Buchstaben gehört oder zum nächste gewertet werden.
    4,
    5,
    6,
    7,
    8};
// Länge des newKeyCount Arrays
int newKeyCountSize = sizeof(newKeyCount) / sizeof(newKeyCount[0]);
int lengthCount[] = { // Pins der LEDs die dem Benutzer anzeigen ob der Impuls als kurzes oder langes Morsesignal gewertet wird 
    9,
    10,
    11,
    12,
    13};
// Länge des lengthCount Arrays
int lengthCountSize = sizeof(lengthCount) / sizeof(lengthCount[0]);
// Startpositon im lengthCount Array
int length = 0;
// Startpositon im newKeyCount Array
int newKey = newKeyCountSize;

void setup()
{ // Startet die Komunikation mit dem seriellen Display, teilt dem Arduino mit das die Pins der LEDs Outputs sind und der Pin des Morseknopfs ein Input.
    mySerial.begin(9600);
    pinMode(2, INPUT);

    for (int i = 0; i < newKeyCountSize; i++)
    {
        pinMode(newKeyCount[i], OUTPUT);
        digitalWrite(newKeyCount[i], HIGH);
    }

    for (int i = 0; i < lengthCountSize; i++)
    {
        pinMode(lengthCount[i], OUTPUT);
    }
}

void loop()
{
    if (digitalRead(2)) // Ist der Morseknopf gedrückt
    { // Wenn der Morseknopf gedrückt ist
        if (newKey < newKeyCountSize)
            AllNewKeyOn();
        if (length <= lengthCountSize)
        {
            digitalWrite(lengthCount[length], HIGH);
            length++;
        }
    }
    else 
    { // Wenn er nicht gedrückt ist
        if (length > 0)
        {
            if (length > 3) 
            { // Langer Impuls
                letter[letterPosition] = '-';
                letterPosition++;
            }
            else 
            { // Kurzer Impuls
                letter[letterPosition] = '.';
                letterPosition++;
            }
            // Position im lengthCount Array auf 0
            length = 0;
            // Alle lengthCount LEDs aus
            for (int i = 0; i < lengthCountSize; i++)
            {
                digitalWrite(lengthCount[i], LOW);
            }
        }
        if (newKey != 0)
        { // Wenn noch LEDs des newKey Arrays brennen
            // Position minus 1
            newKey--;
            // nächstes LED aus
            digitalWrite(newKeyCount[newKey], LOW);
        }
        else
        {
            Evaluate(); // Letztes Zeichen Evaluate.
            memset(letter, 0, letterLength);
            // plainTextLength plus 1
            plainTextLength++;
            // setzt letterPosition zurück
            letterPosition = 0;
            // Die Letzten Zeichen auf dem Display anzeigen
            Display(); 
        }
    }
    // lässt den Benutzer die geschwindikeit des Programmes regulieren um die Eingabe zu erleichtern
    delay(analogRead(A0) / 4 + 50);
}

void AllNewKeyOn()
{// Zündet alle LEDs die dem Benutzer mitteilen wie langer er noch Zeit hat um am angefangen Buchstaben weiter zu morsen und wann der nächste Impuls schon zum nächsten Buchstaben zählt.
    newKey = newKeyCountSize;
    for (int i = 0; i < newKeyCountSize; i++)
    {
        digitalWrite(newKeyCount[i], HIGH);
    }
}

void Evaluate()
{ // Wandelt die Impulskette der letter Variabel zu Buchstaben um und fügt sie zur Zeichenkette plainText hinzu.
    if (letter == ".-")
    {
        plainText[plainTextLength] = 'A';
    }
    if (letter == "-...")
    {
        plainText[plainTextLength] = 'B';
    }
    if (letter == "-.-.")
    {
        plainText[plainTextLength] = 'C';
    }
    if (letter == "-..")
    {
        plainText[plainTextLength] = 'D';
    }
    if (letter == ".")
    {
        plainText[plainTextLength] = 'E';
    }
    if (letter == "..-.")
    {
        plainText[plainTextLength] = 'F';
    }
    if (letter == "--.")
    {
        plainText[plainTextLength] = 'G';
    }
    if (letter == "....")
    {
        plainText[plainTextLength] = 'H';
    }
    if (letter == "..")
    {
        plainText[plainTextLength] = 'I';
    }
    if (letter == ".---")
    {
        plainText[plainTextLength] = 'J';
    }
    if (letter == "-.-")
    {
        plainText[plainTextLength] = 'K';
    }
    if (letter == ".-..")
    {
        plainText[plainTextLength] = 'L';
    }
    if (letter == "--")
    {
        plainText[plainTextLength] = 'M';
    }
    if (letter == "-.")
    {
        plainText[plainTextLength] = 'N';
    }
    if (letter == "---")
    {
        plainText[plainTextLength] = 'O';
    }
    if (letter == ".--.")
    {
        plainText[plainTextLength] = 'P';
    }
    if (letter == "--.-")
    {
        plainText[plainTextLength] = 'Q';
    }
    if (letter == ".-.")
    {
        plainText[plainTextLength] = 'R';
    }
    if (letter == "...")
    {
        plainText[plainTextLength] = 'S';
    }
    if (letter == "-")
    {
        plainText[plainTextLength] = 'T';
    }
    if (letter == "..-")
    {
        plainText[plainTextLength] = 'U';
    }
    if (letter == "...-")
    {
        plainText[plainTextLength] = 'V';
    }
    if (letter == ".--")
    {
        plainText[plainTextLength] = 'W';
    }
    if (letter == "-..-")
    {
        plainText[plainTextLength] = 'X';
    }
    if (letter == "-.--")
    {
        plainText[plainTextLength] = 'Y';
    }
    if (letter == "--..")
    {
        plainText[plainTextLength] = 'Z';
    }
    if (letter == ".----")
    {
        plainText[plainTextLength] = '1';
    }
    if (letter == "..---")
    {
        plainText[plainTextLength] = '2';
    }
    if (letter == "...--")
    {
        plainText[plainTextLength] = '3';
    }
    if (letter == "....-")
    {
        plainText[plainTextLength] = '4';
    }
    if (letter == ".....")
    {
        plainText[plainTextLength] = '5';
    }
    if (letter == "-....")
    {
        plainText[plainTextLength] = '6';
    }
    if (letter == "--...")
    {
        plainText[plainTextLength] = '7';
    }
    if (letter == "---..")
    {
        plainText[plainTextLength] = '8';
    }
    if (letter == "----.")
    {
        plainText[plainTextLength] = '9';
    }
    if (letter == "-----")
    {
        plainText[plainTextLength] = '0';
    }
    if (letter == ".-.-.-")
    {
        plainText[plainTextLength] = '.';
    }
    if (letter == "--.--")
    {
        plainText[plainTextLength] = ',';
    }
    if (letter == "..--..")
    {
        plainText[plainTextLength] = '?';
    }
    if (letter == "---...")
    {
        plainText[plainTextLength] = ':';
    }
    if (letter == "-.-.-.")
    {
        plainText[plainTextLength] = ';';
    }
    if (letter == "-...-")
    {
        plainText[plainTextLength] = ' ';
    }
    if (letter == "-..-.")
    {
        plainText[plainTextLength] = '/';
    }
    if (letter == ".-..-.")
    {
        plainText[plainTextLength] = '"';
    }
}

void Display()
{ // Führt die Methode ClearDisplay aus und schreibt die Zeichen des plainText strings auf den Display
    ClearDisplay();

    mySerial.write(254); // Cursor zum Anfang der ersten Linie
    mySerial.write(128);
    mySerial.write(plainText);
}

void ClearDisplay()
{ // Löscht die Zeichen vom seriellen Display
    mySerial.write(254); // Cursor zum Anfang der ersten Linie
    mySerial.write(128);

    mySerial.write("                "); 
    mySerial.write("                ");
}
