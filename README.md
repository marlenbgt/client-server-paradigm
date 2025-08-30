# Programmierübung Rechnernetze SS 25 - Client/Server Paradigma
Programmieren Sie einen stark vereinfachten Dateiserver und einen dazu passenden Client.
Der Server soll Zugriff auf ein Verzeichnis mit mehreren (kleinen) Textdateien haben. Mittels
Anfragen soll er das Auflisten der Dateien im Verzeichnis sowie die Rückgabe eines
Dateiinhaltes ermöglichen.
Der Client soll als Konsolenanwendung das Verbinden zum Server, Absetzen der
Anfragen/Befehle sowie die Ausgabe der Antworten ermöglichen.
Folgende Befehle sollen unterstützt werden:
LIST Dateiauflistung: Rückgabe aller Dateinamen im Verzeichnis
GET <Dateiname> Anfordern der Textdatei <Dateiname> im Verzeichnis
QUIT Schließen der Verbindung
Zusätzliche Anforderungen:
1. TCP muss als Transportprotokoll eingesetzt werden.
2. Der Client soll mehrere Befehle absetzen können und die Verbindung soll
aufrechterhalten werden.
3. Der Server soll Anfragen von mehreren Clients parallel verarbeiten können.
4. Fehler (z.B. Datei nicht vorhanden, Server nicht erreichbar) sollen von Server und
Client abgefangen und behandelt werden (Ausgabe von Fehlermeldung).
Hinweise:
Client und Server können auf demselben Gerät laufen und über Ports oberhalb von
50000 kommunizieren