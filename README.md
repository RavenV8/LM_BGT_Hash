
## Hashing pseudo kodas
<pre>
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

      ----------------------------------------------------------------------------------------------------
          
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

      ----------------------------------------------------------------------------------------------------
  
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

#### 100,000 atsitiktinių simbolių eilučių porų, skiriančių tik vienu simboliu "skirtingumas" bit'ų ir hex lygyje: 
Bit-level Difference Statistics:
Minimum Difference: 0
Maximum Difference: 64
Average Difference: 55.8571

Hex-level Difference Statistics:
Minimum Difference: 0
Maximum Difference: 100
Average Difference: 86.779

#### Išvados
* Hashavimas vykstas sąlyginai greitai.
* Atkūrimas praktiškai neįmanomas.
* Algoritmas yra deterministinis.
* Tenkina lavinos efektą.
* Trūkumas - Galimos kolizijos, bet praktikoje mažai pasitaikančios (su 1000 simbolių ilgio 25000 stringais galimybė - 0,03%)
* Trūkumas - tik nuo 22 simboliu visos 64 vietos pasikeičia. Hashavime yra trys lygiai, reiktų iš viso 64, kad jau nuo vieno simbolio viskas keistųsi.
