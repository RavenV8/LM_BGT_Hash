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
