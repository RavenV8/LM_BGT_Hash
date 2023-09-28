#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
using namespace std;

void Hashing(string code, vector<char>& codeHashed){
    char simbolis; // naudojama laikyti reiksmiai kuri bus priskirta "codeHashed".
    int simbolioASCII, numeriukasRaides, numeriukasLokacijos;
    int ilgioMaisymas = 1;
    int praeitasSimbolis = 1;
    int simboliuSuma = 0;
    
    // cikle apskaiciuojami "ilgioMaisymas" ir "simboliuSuma" kintamieji, kurie bus naudojami hashavimui
    for (int i = 0; i < code.size(); i++){
        vector<char> codeToVector(code.begin(), code.end());
        simbolioASCII = (int)codeToVector[i];
        if(simbolioASCII > 91) ilgioMaisymas += 3;
        simboliuSuma += (int)codeToVector[i];
    }

    for (int i = 0; i < code.size(); i++){
        
        vector<char> codeToVector(code.begin(), code.end());

        simbolioASCII = (int)codeToVector[i]; // randa kiekvieno "code" simbolio ASCII.

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
        numeriukasLokacijos = ((simbolioASCII*(i+1)+ilgioMaisymas + praeitasSimbolis)+ simboliuSuma) % 64;
        codeHashed[numeriukasLokacijos] = simbolis; // priskiriamas simbolis i jam priklausancia vieta.

        // papildomai dar vienas hasavimas jog daugiau simboliu butu pakeista.
        numeriukasRaides = ((ilgioMaisymas + praeitasSimbolis) + simboliuSuma) % 16;
        numeriukasLokacijos = ((ilgioMaisymas + praeitasSimbolis)+ simboliuSuma) % 64; 
        codeHashed[numeriukasLokacijos] = simbolis;

        // papildomai dar vienas hasavimas jog daugiau simboliu butu pakeista.
        numeriukasRaides = (i + simboliuSuma + ilgioMaisymas) % 16;
        numeriukasLokacijos = (i + simboliuSuma + ilgioMaisymas) % 64; 
        codeHashed[numeriukasLokacijos] = simbolis;

        praeitasSimbolis = simbolioASCII; // naudojamas hashavimui.
    }
}

void Generavimas(){
    // ofstream outputFile("1111symbol(1.1).txt");

    // srand(static_cast<unsigned>(time(nullptr)));

    // for (int i = 0; i < 100000; ++i) {
    //     char randomChar = 'A' + rand() % 52; 
    //     outputFile << randomChar;
    // }
    // outputFile.close();

    ofstream outputFile("100000.txt");

    srand(static_cast<unsigned>(time(nullptr)));

    const int symbolsPerWord = 10;
    const int numWords = 100000;

    for (int i = 0; i < numWords; ++i) {
        for (int j = 0; j < symbolsPerWord; ++j) {
            char randomChar = 'A' + rand() % 52;
            outputFile << randomChar;
        }
        outputFile << '\n'; // Start a new line for the next word
    }

    outputFile.close();
}

void Skaitymas (vector<string>& codesHashed, vector<char> codeHashed, string code, string df) {

    ifstream open_f(df);
    while (open_f){ 
      if (!open_f.eof()) { // skaito iki kol baigiasi failas
        getline(open_f, code);
        for (int i = 0; i < 64; i++) codeHashed[i] = '0';
        // for (char symbols : hashLM) {codeHashed[symbols];}
        Hashing(code, codeHashed);
        string codeHashedString(codeHashed.begin(), codeHashed.end());
        codesHashed.push_back(codeHashedString);}
      else break;
    }
    open_f.close();
}

void SkaitymasTestavimui (vector<string> codesHashed, vector<char> codeHashed, string code, string df, int eiluciuKiekis) {
    auto start = std::chrono::high_resolution_clock::now(); auto st=start;

    ifstream open_f(df);
    for (int i = 0; i < eiluciuKiekis; i++){
        getline(open_f, code);
        for (int j = 0; j < 64; j++) codeHashed[j] = '0';
        Hashing(code, codeHashed);
        string codeHashedString(codeHashed.begin(), codeHashed.end());
        codesHashed.push_back(codeHashedString);
    }
    open_f.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << eiluciuKiekis << " uztruko: " << fixed << setprecision(10) << diff.count() << " sek." << endl;
    }

void SkaitymasDeterministiskumas (vector<string>& codesHashed, vector<char> codeHashed, string code, string df, int& pasikartojimai) {
    bool buvoPasikartojimas;
    ifstream open_f(df);
    while (open_f){ 
      if (!open_f.eof()) { // skaito iki kol baigiasi failas
        getline(open_f, code);
        for (int i = 0; i < 64; i++) codeHashed[i] = '0';
        // for (char symbols : hashLM) {codeHashed[symbols];}
        Hashing(code, codeHashed);
        string codeHashedString(codeHashed.begin(), codeHashed.end());
        for(int i = 0; i < codesHashed.size(); i++){
            if(codesHashed[i] == codeHashedString){
                pasikartojimai++;
                buvoPasikartojimas = true;
            } 
        }
        if(!pasikartojimai) codesHashed.push_back(codeHashedString);
        else pasikartojimai = false;
        }
      else break;
    }
    open_f.close();
}

int main(){
    string code;
    vector<char> codeHashed;
    vector<string> codesHashed;
    for (int i = 0; i < 64; i++) codeHashed.push_back('0');

    char a; // naudojamas paimti duomenis apie vartotojo pasirinkima del nuskaitymo
    string failoPavadinimas;
    bool pasirinkimas; // naudojamas su char a pasirinkimui while cikle
    do
    {
        if((a!='3' && a!='2' && a!='1' && a!='0')){ // 1 arba 0
            cout << "Spauskite 3 testuoti determiniskuma, 2 jeigu norite testuoti konstitucija, 1 jeigu norite, kad nuskaitytu is failo arba 0 jeigu norite vesti duomenis: ";
            cin>>a;
            pasirinkimas = false; // nustatomas default
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }
        else pasirinkimas = true;
    }while(!pasirinkimas);

    if (a==((int)'3')){
        int pasikartojimai = 0;
        failoPavadinimas = '100000.txt';
        SkaitymasDeterministiskumas(codesHashed, codeHashed, code, failoPavadinimas, pasikartojimai);
        cout << "Buvo " << pasikartojimai << " pasikartojimu";
    }
    else if(a==((int)'2')){
        SkaitymasTestavimui(codesHashed, codeHashed, code, failoPavadinimas, 2);
        SkaitymasTestavimui(codesHashed, codeHashed, code, failoPavadinimas, 4);
        SkaitymasTestavimui(codesHashed, codeHashed, code, failoPavadinimas, 8);
        SkaitymasTestavimui(codesHashed, codeHashed, code, failoPavadinimas, 16);
        SkaitymasTestavimui(codesHashed, codeHashed, code, failoPavadinimas, 32);
        SkaitymasTestavimui(codesHashed, codeHashed, code, failoPavadinimas, 64);
        SkaitymasTestavimui(codesHashed, codeHashed, code, failoPavadinimas, 128);
        SkaitymasTestavimui(codesHashed, codeHashed, code, failoPavadinimas, 256);
        SkaitymasTestavimui(codesHashed, codeHashed, code, failoPavadinimas, 512);
        SkaitymasTestavimui(codesHashed, codeHashed, code, failoPavadinimas, 788);
    }
    else if(a==((int)'1')){
        char b;
        pasirinkimas = false;
        do
        {
            if((b!='1' && b!='0')){ // 1 arba 0
            cout << "Spauskite 1 jeigu norite, kad butu file sugeneruoti, jeigu nenorite spauskite 0: ";
            cin>>b;
            pasirinkimas = false; // nustatomas default
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            }
            else pasirinkimas = true;
        }while(!pasirinkimas);
        if(b==((int)'1')) Generavimas();

        cout<<"Iveskite failo pavadinima: "; cin>>failoPavadinimas;
        Skaitymas(codesHashed, codeHashed, code, failoPavadinimas);
        cout << endl << endl << endl;
        for (int i = 0; i < codesHashed.size(); i++) {
            //std::cout << answer[i] << " index: " << i << endl;
            std::cout << i+1 << ". " << codesHashed[i] << endl;
        }
    }
    else{
        cout << "Iveskite koda: ";
        cin >> code;
        Hashing(code, codeHashed);

        cout << endl << endl << endl;
        for (int i = 0; i < codeHashed.size(); i++) {
            //std::cout << answer[i] << " index: " << i << endl;
            std::cout << codeHashed[i];
        }
    }
    return 0;
}