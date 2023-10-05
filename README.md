
## Hashing pseudo kodas
<pre>
    char simbolis; // naudojama laikyti reiksmei kuri bus priskirta "codeHashed".
    long int simbolioASCII;
    long int numeriukasRaides, numeriukasLokacijos;
    long int ilgioMaisymas = 1;
    long int praeitasSimbolis = 1;
    long int simboliuSuma = 1;
    
    for (int i = 0; i < code.size(); i++){
        vector<char> codeToVector(code.begin(), code.end());
        simbolioASCII = (int)codeToVector[i];
        if(simbolioASCII > 91) ilgioMaisymas += 3;
        simboliuSuma += (int)codeToVector[i];
    }

    for (int i = 0; i < code.size(); i++){
        
        vector<char> codeToVector(code.begin(), code.end());

        simbolioASCII = (int)codeToVector[i]; // randa kiekvieno "code" simbolio ASCII.
        if(simbolioASCII < 0) simbolioASCII *= -1; // paprasciausias sutvarkymas del non ASCII characters.
        // suskaiciuojama kokia reiksme bus priskirta pagal hex koduote. 
        // '*(i+1)' skirta, jog tie patys simboliai neuzimtu tu paciu vietu.
        // saknies liekana is 16, nes sudaryta is hex.
        numeriukasRaides = ((simbolioASCII*(i+1)+ilgioMaisymas + praeitasSimbolis)+ simboliuSuma) % 16;
        
        // naudojama paversti 10-15 skaicius i a-f raides.
        // 0-9 skaiciai paverciami i string tipo.
        if (numeriukasRaides >= 10 && numeriukasRaides <= 15) {
        simbolis = 'a' + (numeriukasRaides - 10);
        } else {simbolis = '0' + numeriukasRaides;}
       
        // panasus principas kaip simbolio rinkime.
        // tik is saknies liekanos is 16 pakeiciama i 64.
        numeriukasLokacijos = ((simbolioASCII*(i+1)+ilgioMaisymas + praeitasSimbolis)* simboliuSuma * 5) % 64;
        codeHashed[numeriukasLokacijos] = simbolis; // priskiriamas simbolis i jam priklausancia vieta.

        // papildomai dar vienas hasavimas jog daugiau simboliu butu pakeista.
        praeitasSimbolis = numeriukasRaides;
        numeriukasRaides = ((ilgioMaisymas + 5) * (simboliuSuma % 5) + praeitasSimbolis) % 16;
        numeriukasLokacijos = ((ilgioMaisymas + 7) * (simboliuSuma * 3 % 3) + praeitasSimbolis) % 64; 

        if (numeriukasRaides >= 10 && numeriukasRaides <= 15) {
        simbolis = 'a' + (numeriukasRaides - 10);
        } else {simbolis = '0' + numeriukasRaides;}
        codeHashed[numeriukasLokacijos] = simbolis;

        // papildomai dar vienas hasavimas jog daugiau simboliu butu pakeista.
        praeitasSimbolis = numeriukasRaides;
        numeriukasRaides = (i * 3 + simboliuSuma + ilgioMaisymas * praeitasSimbolis) % 16;
        numeriukasLokacijos = (i * 8 + simboliuSuma + ilgioMaisymas * praeitasSimbolis) % 64; 
        if (numeriukasRaides >= 10 && numeriukasRaides <= 15) {
        simbolis = 'a' + (numeriukasRaides - 10);
        } else {simbolis = '0' + numeriukasRaides;}
        codeHashed[numeriukasLokacijos] = simbolis;

        praeitasSimbolis = simbolioASCII; // naudojamas hashavimui
    }

    Deklaruojami (kaip long int): simbolis, simbolioASCII, numeriukasRaides.
    Deklaruojami(kaip long int) ir priskiriama default reikšmė vientas: ilgioMaisymas, praeitasSimbolis, simboliuSuma.
    Naudojamas long int, nes vėliau skaičiuojant kartais tarpinaiai skaičiai perkopia int reikšmes.

    Konvertuojame stringą į simbolių vektorių ir išsaugojame kaip "codeToVector".
          
    Vyksta ciklas nuo 0 iki duoto stringo ilgio{
      Priskireme "codeToVector[i]" ASCII reikšmę kintamajam "simbolioASCII".
      Jei "simbolioASCII" daugiau už 91 tada padidiname "ilgioMaisymas" trimis.
      Padidiname "simboliuSuma" "codeToVector[i]" ASCII reikšme.
    }

    Vyksta ciklas nuo 0 iki duoto stringo ilgio{    
      Priskireme "codeToVector[i]" ASCII reikšmę kintamajam "simbolioASCII".  
      Jei "simbolioASCII" mažesnis nei 0, padauginkite jį iš -1 (apsisaugome nuo non ASCII simbolių).

          
      Nustatome "numeriukasRaides" kaip ((simbolioASCII * (i + 1) + ilgioMaisymas + praeitasSimbolis) + simboliuSuma) modulis 16.
  
      Jei numeriukasRaides yra didesnis arba lygus 10 ir mažesnis arba lygus 15:
          Priskirkite simboliui 'a' + (numeriukasRaides - 10).
      Kitu atveju:
          Priskirkite simboliui '0' + numeriukasRaides.
  
      Nustatome "numeriukasLokacijos" kaip ((simbolioASCII * (i + 1) + ilgioMaisymas + praeitasSimbolis) * simboliuSuma * 5) modulis 64.
      Priskirkite simbolių "codeHashed" vektoriui "numeriukasLokacijos" lokacijoje.

      ----------------------------------------------------------------------------------------------------
          
      Nustatykime "praeitasSimbolis" kaip "numeriukasRaides".
      Nustatome "numeriukasRaides"  kaip ((ilgioMaisymas + 5) * (simboliuSuma % 5) + praeitasSimbolis) modulis 16.
      Nustatome "numeriukasLokacijos"  kaip ((ilgioMaisymas + 7) * (simboliuSuma * 3 % 3) + praeitasSimbolis) modulis 64.
  
      Jei numeriukasRaides yra didesnis arba lygus 10 ir mažesnis arba lygus 15:
          Priskirkite simboliui 'a' + (numeriukasRaides - 10).
      Kitu atveju:
          Priskirkite simboliui '0' + numeriukasRaides.
  
      Priskirkite simbolių "codeHashed" vektoriui "numeriukasLokacijos" lokacijoje.

      ----------------------------------------------------------------------------------------------------

      Nustatykime "praeitasSimbolis" kaip "numeriukasRaides".
      Nustatome "numeriukasRaides"  kaip (i * 3 + simboliuSuma + ilgioMaisymas * praeitasSimbolis) modulis 16.
      Nustatome "numeriukasLokacijos"  kaip ((i * 8 + simboliuSuma + ilgioMaisymas * praeitasSimbolis) modulis 64.
  
      Jei numeriukasRaides yra didesnis arba lygus 10 ir mažesnis arba lygus 15:
          Priskirkite simboliui 'a' + (numeriukasRaides - 10).
      Kitu atveju:
          Priskirkite simboliui '0' + numeriukasRaides.
  
      Priskirkite simbolių "codeHashed" vektoriui "numeriukasLokacijos" lokacijoje.
  
      Nustatykime "praeitasSimbolis" kaip "simbolioASCII". 
    }
</pre>

## Eksperimentinė analizė:

#### Du failai sudaryti tik iš vieno, tačiau skirtingo, simbolio:
1. 1symbol(1).txt, Hash - 0000000700000000000000000000000000000770000000000000000000000000
2. 1symbol(2).txt, Hash - 0000000009000000000000000000000000000099000000000000000000000000
#### Du failai sudaryti iš daugiau nei 1000 atsitiktinai sugeneruotų simbolių:
1. 1111symbol(1.1).txt, Hash - 65dd45658a8bcd1fd923866ee3a000efd5d3e516868dcc6101cddc64c9933d52
2. 1111symbol(1.2).txt, Hash - 65dd45658a8bcd1fd923866ee3a000efd5d3e516868dcc6101cddc64c9933d52
#### Du failai sudaryti iš daugiau nei 1000 simbolių, bet skiriasi vienu nuo kito tik vienu simboliu:
1. 1111symbol(2.1).txt, Hash - 65dd45658a8bcd1fd923866ee3a000efd5d3e516868dcc6101cddc64c9933d52
2. 1111symbol(2.2), Hash - 0b2e3535a993ede9aa93196600a2f32aa123257589aeca6f0533bb07dddbca2a
#### Tuščias failas:
1. empty.txt, Hash - 0000000000000000000000000000000000000000000000000000000000000000
#### Efektyvumas
<img width="571" alt="Screenshot 2023-09-28 at 23 41 35" src="https://github.com/RavenV8/LM_BGT_Hash/assets/55328476/39f2561c-d110-457e-9c11-38e4f0e41857">

#### Testuojama su 100,000 atsitiktinių simbolių:
Kolizijų skaicius su
* 25,000 porų, kurių ilgis - 10 simbolių: 0
* 25,000 porų, kurių ilgis - 100 simbolių: 0
* 25,000 porų, kurių ilgis - 500 simbolių: 0
* 25,000 porų, kurių ilgis - 1000 simbolių: 3
