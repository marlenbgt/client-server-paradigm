# Programmeringsövning Datornätverk - Client/Server Paradigm
### Kör på Windows (MSYS2 Mingw64)
```
gcc server.c -o server.exe -lws2_32
```
```
gcc client.c -o client.exe -lws2_32
```
### Kör sedan 
```
./server.exe
```
```
./client.exe
```
### Uppgift
Programmera en mycket förenklad filserver och en motsvarande klient. Servern ska ha tillgång till en katalog som innehåller flera textfiler. Med hjälp av förfrågningar bör den möjliggöra listning av filer i katalogen och retur av filinnehållet. Klienten, som en konsolapplikation, bör tillåta anslutning till servern, skicka förfrågningar/kommandon och utmatning av svar. Följande kommandon bör stödjas:
LIST Fillista,
GET <filnam>,
QUIT.
#### Ytterligare krav
- TCP måste användas som transportprotokoll
- klienten måste kunna skicka flera kommandon och anslutningen måste upprätthållas
- servern måste kunna bearbeta förfrågningar från flera klienter parallellt
- fel (t.ex. fil saknas, servern kan inte nås) måste fångas upp och hanteras av både servern och klienten (visa ett felmeddelande)
#### Anmärkningar
Klienten och servern kan köras på samma enhet och kommunicera via portar över 50000.