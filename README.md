# Angabe zu Assignment 2

## Lernziel
Funktionen, Parameterübergabe, Pointer, Arrays, Strings, ASCII

## Aufgabenstellung

Erstellen Sie ein Programm, welches eine modifizierte Version der [Playfair-Chiffre](https://de.wikipedia.org/wiki/Playfair) implementiert. Nach Eingabe eines Schlüssels (A-Z und Leerzeichen, max. 25 Zeichen) kann das Programm eine Zeichenfolge (A-Z und Leerzeichen, maximal 50 Zeichen) ver- und entschlüsseln.

### Vorbereitung (=Bereinigung) des Schlüssels

Ein gültiger Schlüssel darf nur die Buchstaben A-Z (Groß-/Kleinschreibung egal, mindestens 1 Buchstabe) und Leerzeichen enthalten und maximal 25 Zeichen (inklusive Leerzeichen) lang sein. Für die Anwendung des Schlüssels muss dieser zuerst bereinigt werden. Dieser Vorgang besteht aus den folgenden Schritten:

* Leerzeichen werden entfernt.
* Alle Zeichen werden in Großbuchstaben umgewandelt.
* W wird mit V ersetzt.
* Bei mehrfach vorkommenden Buchstaben wird nur das erste Vorkommen des Buchstabens behalten. Alle weiteren Vorkommen des Buchstabens werden entfernt.

---
**Beispiel:**
```
Wir programmieren -> VIRPOGAMEN
```

---

### Erstellen des Playfair-Quadrats

Das 5x5 Playfair Quadrat wird beginnend von oben links (Index 0) befüllt. Dabei werden zuerst alle Felder mit geraden Indizes und erst danach alle Felder mit ungeraden Indizes befüllt. 
Die Befüllung erfolgt zuerst mit dem bereinigten Schlüssel, anschließend werden alle noch nicht verwendeten Buchstaben des Alphabets eingefügt.

Beispiel: siehe [Programmablauf](#programmablauf)


### Verschlüsselung

Ein gültiger Klartext (=der zu verschlüsselnde Text) darf nur die Buchstaben A-Z (Groß-/Kleinschreibung egal, mindestens ein Buchstabe) und Leerzeichen enthalten und maximal 50 Zeichen (inklusive Leerzeichen) lang sein.

Der Klartext wird wie folgt vorbereitet:

* Leerzeichen werden entfernt.
* Alle Zeichen werden in Großbuchstaben umgewandelt.
* W wird mit V ersetzt.

Anschließend wird der Klartext zu Bigrammen verarbeitet. Ein Bigramm ist ein Buchstabenpaar, das heißt, dass z. B. der vorbereitete Klartext SPITZE in die Bigramme SP, IT, und ZE umgewandelt wird. Bei dieser Umwandlung gelten folgende Regeln in dieser Reihenfolge:

* Kommen zwei gleiche Zeichen in einem Bigramm vor, wird der Buchstabe X zwischen die Buchstaben eingefügt (z.B. DO PP EL T  -> DO PX PE LT). Achtung, die maximale Länge von 50 Zeichen gilt auch für die Bigramme! Das heißt, wenn die Bigramme wegen eingefügten `'X'` auf eine Gesamtlänge von mehr als 50 Zeichen wachsen, dann ist der Klartext auch ungültig.
* Hat der Text jetzt eine ungerade Anzahl an Buchstaben, wird das letzte Bigramm mit X aufgefüllt (z.B. ESP -> ES PX oder BETT -> BE TX T -> BE TX TX).

Der Ablauf der Verschlüsselung erfolgt mit den folgenden drei Regeln der Playfair-Chiffre:

1. Befinden sich beide Buchstaben in derselben Zeile des Playfair-Quadrats, werden diese jeweils mit ihrem *rechten* Nachbarbuchstaben im Quadrat ersetzt. Falls sich ein Buchstabe am rechten Rand des Quadrats befindet, wird dieser mit dem Buchstaben am linken Rand derselben Zeile des Quadrats ersetzt.
2. Befinden sich beide Buchstaben in derselben Spalte des Playfair-Quadrats, werden diese jeweils mit ihrem *unteren* Nachbarbuchstaben im Quadrat ersetzt. Falls sich ein Buchstabe am unteren Rand des Quadrats befindet, wird dieser mit dem Buchstaben am oberen Rand derselben Spalte ersetzt.
3.  Befinden sich die Buchstaben in unterschiedlichen Zeilen und Spalten des Playfair-Quadrats, wird der jeweilige Buchstabe mit dem Buchstaben in derselben Zeile, aber der Spalte des anderen Buchstabens ersetzt (die zwei Buchstaben bilden ein Rechteck im Playfair-Quadrat und werden mit den jeweiligen Ecken ersetzt).

*Anmerkung:* Der Fall, dass der Klartext ein XX enthält oder auf XX aufgefüllt wird, muss bei der Verschlüsselung nicht beachtet werden.

Beispiel: siehe [Programmablauf](#programmablauf)

### Entschlüsselung

Ein gültiger Ciphertext (=verschlüsselter Text) darf nur die Buchstaben A-Z (Groß-/Kleinschreibung egal, mindestens 2 Buchstaben) und Leerzeichen enthalten und maximal 50 Zeichen (inklusive Leerzeichen) lang sein. Die Anzahl der Buchstaben des Ciphertexts muss außerdem eine gerade Zahl sein und der Text darf weder den Buchstaben W, noch Bigramme mit zwei gleichen Buchstaben enthalten.

Für die Entschlüsselung wird der Ciphertext wie folgt vorbereitet:

* Leerzeichen werden entfernt.
* Alle Zeichen werden in Großbuchstaben umgewandelt.

Der Ablauf der Entschlüsselung erfolgt umgekehrt zur Verschlüsselung mit folgenden Regeln:

1. Befinden sich beide Buchstaben in derselben Zeile des Playfair-Quadrats, werden diese jeweils mit ihrem *linken* Nachbarbuchstaben im Quadrat ersetzt. Falls sich ein Buchstabe am linken Rand des Quadrats befindet, wird dieser mit dem Buchstaben am rechten Rand derselben Zeile des Quadrats ersetzt.
2. Befinden sich beide Buchstaben in derselben Spalte des Playfair-Quadrats, werden diese jeweils mit ihrem *oberen* Nachbarbuchstaben im Quadrat ersetzt. Falls sich ein Buchstabe am oberen Rand des Quadrats befindet, wird dieser mit dem Buchstaben am unteren Rand derselben Spalte ersetzt.
3.  Befinden sich die Buchstaben in unterschiedlichen Zeilen und Spalten, erfolgt die Entschlüsselung gleich wie bei der Verschlüsselung (Regel 3).

Beispiel: siehe [Programmablauf](#programmablauf)

## Programmablauf:

Nach Programmstart soll direkt die Aufforderung zur Eingabe des Schlüssels angezeigt werden:

```
Bitte Schlüssel eingeben: <key>
```

Wobei `<key>` mit der Benutzereingabe gefolgt von Enter ersetzt wird (ohne eckige Klammern).
Wurde ein ungültiger Schlüssel eingeben, wird die letzte Abfrage wiederholt.
Wurde ein gültiger Schlüssel eingegeben, wird der [bereinigte Schlüssel](#vorbereitung-bereinigung-des-schlüssels) gefolgt vom Playfair Quadrat ausgegeben.

Beispiel mit Schlüssel ` Hallo  Welt `:
```
Ausgewählter Schlüssel: HALOVET

Playfair Quadrat:
H J A K L
M O N V P
E Q T R B
S C U D X
F Y G Z I
```

Anschließend wird die/der Benutzer*in mit folgender Ausgabe gefragt, ob sie/er einen Text ver- oder entschlüsseln oder das Programm beenden will.
``` 

Wählen Sie bitte eine Option:
1 - Verschlüsseln
2 - Entschlüsseln
0 - Programm beenden
  
<Wert>
```
 
In dieser Ausgabe entspricht `<Wert>` der Benutzereingabe.
Falls `<Wert>` den Wert 0 hat, wird das Programm mit dem Rückgabewert 0 beendet.
Wurde ein ungültiger Wert eingeben (also weder `0` noch `1` oder `2`), wird die letzte Abfrage wiederholt.

Falls 1 oder 2 gewählt wurde, wird der Text mit dem Ablauf im Folgenden ver- oder entschlüsselt.
Anschließend wird die obige Abfrage der Optionen wiederholt, bis die/der Benutzer*in das Programm beendet.

### Verschlüsselung

Wird ein Klartext verschlüsselt, erfolgt zuerst die Abfrage des Texts:
```
Klartext: <text>
```
Dabei entspricht `<text>` der Benutzereingabe.
Wurde ein ungültiger Text eingeben, wird die letzte Abfrage wiederholt.

Anschließend wird der Text wie oben beschrieben vorbereitet, verschlüsselt und in folgendem Format ausgegeben:

Beispiel mit Klartext `Programmieren macht Spass` mit Schlüssel von oben (HALOVET)
```
Vorbereiteter Klartext: PR OG RA MX MI ER EN MA CH TS PA SX SX
Ciphertext: VB NY TK PS PF QB TM NH SJ EU NL CS CS
```

### Entschlüsselung
Wird ein Cipher-Text entschlüsselt, erfolgt zuerst die Abfrage des Texts:
```
Ciphertext: <text>
```
Dabei entspricht `<text>` der Benutzereingabe.
Wurde ein ungültiger Text eingeben, wird die letzte Abfrage wiederholt.

Anschließend wird der Text wie oben beschrieben vorbereitet, entschlüsselt und in folgendem Format ausgegeben:

Beispiel mit Ciphertext `vbnytkpspfqbtmnhsjeunlcscs` mit Schlüssel von oben (`HALOVET`)
```
Vorbereiteter Ciphertext: VB NY TK PS PF QB TM NH SJ EU NL CS CS
Klartext: PR OG RA MX MI ER EN MA CH TS PA SX SX 
```

### Beispiel
```
Bitte Schlüssel eingeben: Hallo  Welt
Ausgewählter Schlüssel: HALOVET

Playfair Quadrat:
H J A K L
M O N V P
E Q T R B
S C U D X
F Y G Z I

Wählen Sie bitte eine Option:
1 - Verschlüsseln
2 - Entschlüsseln
0 - Programm beenden

1
Klartext: Programmieren macht Spass
Vorbereiteter Klartext: PR OG RA MX MI ER EN MA CH TS PA SX SX
Ciphertext: VB NY TK PS PF QB TM NH SJ EU NL CS CS

Wählen Sie bitte eine Option:
1 - Verschlüsseln
2 - Entschlüsseln
0 - Programm beenden

2
Ciphertext: vbnytkpspfqbtmnhsjeunlcscs
Vorbereiteter Ciphertext: VB NY TK PS PF QB TM NH SJ EU NL CS CS
Klartext: PR OG RA MX MI ER EN MA CH TS PA SX SX

Wählen Sie bitte eine Option:
1 - Verschlüsseln
2 - Entschlüsseln
0 - Programm beenden

0
```

## Framework

Ein Framework, welches die Erstellung des Playfair-Quadrats übernimmt, wird in [framework.h](./framework.h) zur Verfügung gestellt.
Die Funktion `generatePlayfairSquare` des Frameworks kann dazu verwendet werden, den Schlüssel abzufragen, zu bereinigen und anschließend das Playfair-Quadrat auszugeben. Der Funktion `generatePlayfairSquare` wird der Parameter `square` übergeben, der das Playfair-Quadrat darstellt.

Damit die `generatePlayfairSquare` korrekt funktioniert, müssen folgende drei Funktionen in der Datei `a2.c` implementiert werden:

* `int stringLength(char *text)`: Gibt die Länge des nullterminierten Strings `text` als int zurück. (Länge des Strings ohne den Nullterminator \0)
* `void toUpper(char *text)`: Konvertiert alle Buchstaben des Strings `text` zu Großbuchstaben.
* `void replaceLetters(char *text, char original, char new_char)`: Ersetzt alle Vorkommen des Zeichens `original` im String `text` mit dem Zeichen `new_char`.

*Anmerkung:* Strings, die länger als SIZE_BUFFER sind, werden vom TestSystem NICHT getestet. 

## Spezifikation

* Es dürfen **keine Funktionen im Zusammenhang mit dynamischem Speichermanagement** verwendet werden (malloc).
* Außerdem **nicht erlaubte Bibliotheken**: <string.h> und <stdlib.h>
* Keine zusätzlichen Ausgaben
* Alle Ausgaben erfolgen auf stdout
* Keinerlei Ausgaben auf stderr
* Abgabe bis *spätestens*: 05.12.2020 23:59 (in Österreich gültige Zeit)
* Abgabe: a2.c


## Bewertung
Das Assignment wird [wie im TeachCenter beschrieben](https://tc.tugraz.at/main/mod/page/view.php?id=55761) bewertet. Machen Sie sich auch mit dem [Beurteilungsschema](https://tc.tugraz.at/main/mod/page/view.php?id=55602) für die Übungen vertraut, insbesondere mit den Regeln zu Plagiaten!

---
**ACHTUNG!**

Damit die Abgabe als ernsthafter Versuch gewertet wird, muss das abgegebene Programm
mindestens 5 Test Cases bestehen!

---



