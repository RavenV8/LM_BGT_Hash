#### Programos naudojimas:
* Paleidimas: g++ -O2 LM_blockchain.cpp -o v01 && ./v01
* Norint daryti testus su sukurtai failais (naudoti 2 ir 3 funkciją), reikia išsikelti txt files iš foulderio "Testai"

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
1. 1symbol(1).txt, Hash - 0000000030000000000000000000000000000000000000e00000000000008000
2. 1symbol(2).txt, Hash - 0000000000e0000000000000000b0000000000000a0000000000000000000000
#### Du failai sudaryti iš daugiau nei 1000 atsitiktinai sugeneruotų simbolių:
1. 1111symbol(1.1).txt, Hash - cdef0f23456712aa2e72a2a4d6f8285cde5092b3d6f88a3e537392ee96fe14c1
2. 1111symbol(1.2).txt, Hash - cdef0f23456712aa2e72a2a4d6f8285cde5092b3d6f88a3e537392ee96fe14c1
#### Du failai sudaryti iš daugiau nei 1000 simbolių, bet skiriasi vienu nuo kito tik vienu simboliu:
1. 1111symbol(2.1).txt, Hash - cdef0f23456712aa2e72a2a4d6f8285cde5092b3d6f88a3e537392ee96fe14c1
2. 1111symbol(2.2).txt, Hash - 01234b6787abcde6597092b9d6f81a3c5e7096b4d9f5193c557092b6d0f51f3a
#### Tuščias failas:
1. 0symbol.txt, Hash - 0000000000000000000000000000000000000000000000000000000000000000
#### Efektyvumas
<img width="963" alt="Screenshot 2023-10-05 at 14 52 33" src="https://github.com/RavenV8/LM_BGT_Hash/assets/55328476/09c0da5d-d61b-48ff-a1e1-18b3a96ffe34">


#### Testuojama su 100,000 atsitiktinių simbolių:
Kolizijų skaicius su
* 25,000 porų, kurių ilgis - 10 simbolių: 0
* 25,000 porų, kurių ilgis - 100 simbolių: 0
* 25,000 porų, kurių ilgis - 500 simbolių: 0
* 25,000 porų, kurių ilgis - 1000 simbolių: 3

#### 100,000 atsitiktinių simbolių eilučių porų, skiriančių tik vienu simboliu "skirtingumas" bit'ų ir hex lygyje: 
Bit-level Difference Statistics:
- Minimum Difference: 0%
- Maximum Difference: 64%
- Average Difference: 55.86%

Hex-level Difference Statistics:
- Minimum Difference: 0%
- Maximum Difference: 100%
- Average Difference: 86.78%

#### Išvados
* Hashavimas vykstas sąlyginai greitai.
* Atkūrimas praktiškai neįmanomas.
* Algoritmas yra deterministinis.
* Tenkina lavinos efektą.
* Trūkumas - Galimos kolizijos, bet praktikoje mažai pasitaikančios (su 1000 simbolių ilgio 25000 stringais galimybė - 0,03%)
* Trūkumas - tik nuo 22 simboliu visos 64 vietos pasikeičia. Hashavime yra trys lygiai, reiktų iš viso 64, kad jau nuo vieno simbolio viskas keistųsi.
