#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <random>

#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <numeric>
using namespace std;

void Hashing(string code, vector<char>& codeHashed){
    char simbolis; // naudojama laikyti reiksmei kuri bus priskirta "codeHashed".
    long int simbolioASCII;
    long int numeriukasRaides, numeriukasLokacijos;
    long int ilgioMaisymas = 1;
    long int praeitasSimbolis = 1;
    long int simboliuSuma = 1;
    vector<char> codeToVector(code.begin(), code.end());

    for (int i = 0; i < code.size(); i++){
        simbolioASCII = (int)codeToVector[i];
        if(simbolioASCII > 91) ilgioMaisymas += 3;
        simboliuSuma += (int)codeToVector[i];
    }

    for (int i = 0; i < code.size(); i++){
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
}

void Generavimas(){
    ofstream outputFile("25000_4.txt");

    srand(static_cast<unsigned>(time(nullptr)));

    const int symbolsPerWord = 1000;
    const int numWords = 25000;

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
        Hashing(code, codeHashed);
        string codeHashedString(codeHashed.begin(), codeHashed.end());
        for (int j = 0; j < 64; j++) codeHashed[j] = '0';
        codesHashed.push_back(codeHashedString);
    }
    open_f.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << eiluciuKiekis << " uztruko: " << fixed << setprecision(10) << diff.count() << " sek." << endl;
    }

void SkaitymasDeterministiskumas (vector<string> codesHashed, vector<char> codeHashed, string code, string df, int& pasikartojimai) {
    bool buvoPasikartojimas;
    ifstream open_f(df);
    while (open_f){ 
      if (!open_f.eof()) { // skaito iki kol baigiasi failas
        getline(open_f, code);
        for (int i = 0; i < 64; i++) codeHashed[i] = '0';
        Hashing(code, codeHashed);
        string codeHashedString(codeHashed.begin(), codeHashed.end());
        for(int i = 0; i < codesHashed.size(); i++){
            if(codesHashed[i] == codeHashedString){
                pasikartojimai++;
                buvoPasikartojimas = true;
                cout << i << ". " << code << " " << codeHashedString << endl; // jei ivyktu pasikartojimas
            } 
        }
        if(!buvoPasikartojimas) codesHashed.push_back(codeHashedString);
        buvoPasikartojimas = false;
        if(codesHashed.size() % 250 == 0) cout << codesHashed.size()/250 << "%" << endl; // labai juokingas loading algoritmas ISTRINTI!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        }
      else break;
    }
    open_f.close();
}


string GenerateRandomString(int length) {
    string randomString;
    static const char charset[] =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    int charsetSize = sizeof(charset) - 1;

    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < length; ++i) {
        std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<int> dist(1, 1000);
        int randomNumber = dist(rng);
        randomString += charset[randomNumber % charsetSize];
    }

    return randomString;
}

unsigned int calculateBitDifference(const string& str1, const string& str2) {
    vector<char> codeHashed1(64, '0');
    vector<char> codeHashed2(64, '0');

    Hashing(str1, codeHashed1);
    Hashing(str2, codeHashed2);

    int diffCount = 0;
    for (int i = 0; i < 64; ++i) {
        if (codeHashed1[i] != codeHashed2[i]) {
            diffCount++;
        }
    }
    return diffCount;
}

unsigned int calculateHexDifference(const string& str1, const string& str2) {
    vector<char> codeHashed1(64, '0');
    vector<char> codeHashed2(64, '0');

    Hashing(str1, codeHashed1);
    Hashing(str2, codeHashed2);

    // Calculate the percentage difference between the two hashes
    int diffCount = 0;
    for (int i = 0; i < 64; ++i) {
        if (codeHashed1[i] != codeHashed2[i]) {
            diffCount++;
        }
    }
    return (static_cast<double>(diffCount) / 64.0) * 100.0;
}

void palyginimas(int numPairs) {
    vector<string> stringPairs;
    vector<unsigned int> bitDifferences;
    vector<unsigned int> hexDifferences;

    for (int i = 0; i < numPairs; i++) {
        // Generate random string pairs and store them in stringPairs vector
        //int number = rand() % 1000 + 1;
        //cout << i << ". " << number << endl;
        std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<int> dist(1, 1000);
        int randomNumber = dist(rng);
        stringPairs.push_back(GenerateRandomString(randomNumber));
        stringPairs.push_back(GenerateRandomString(randomNumber));
        cout << i << ". " << randomNumber << endl;

    }

    for (int i = 0; i < numPairs; i++) {
        unsigned int bitDiff = calculateBitDifference(stringPairs[2 * i], stringPairs[2 * i + 1]);
        unsigned int hexDiff = calculateHexDifference(stringPairs[2 * i], stringPairs[2 * i + 1]);

        bitDifferences.push_back(bitDiff);
        hexDifferences.push_back(hexDiff);
    }

    // Calculate and print statistics for bit-level difference
    unsigned int minBitDiff = *min_element(bitDifferences.begin(), bitDifferences.end());
    unsigned int maxBitDiff = *max_element(bitDifferences.begin(), bitDifferences.end());
    double avgBitDiff = accumulate(bitDifferences.begin(), bitDifferences.end(), 0.0) / numPairs;

    cout << "Bit-level Difference Statistics:" << endl;
    cout << "Minimum Difference: " << minBitDiff << endl;
    cout << "Maximum Difference: " << maxBitDiff << endl;
    cout << "Average Difference: " << avgBitDiff << endl << endl;

    // Calculate and print statistics for hex-level difference
    unsigned int minHexDiff = *min_element(hexDifferences.begin(), hexDifferences.end());
    unsigned int maxHexDiff = *max_element(hexDifferences.begin(), hexDifferences.end());
    double avgHexDiff = accumulate(hexDifferences.begin(), hexDifferences.end(), 0.0) / numPairs;

    cout << "Hex-level Difference Statistics:" << endl;
    cout << "Minimum Difference: " << minHexDiff << endl;
    cout << "Maximum Difference: " << maxHexDiff << endl;
    cout << "Average Difference: " << avgHexDiff << endl;
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
        if((a!='4' && a!='3' && a!='2' && a!='1' && a!='0')){ // 1 arba 0
            cout << "Spauskite 4 testuoti skirtinguma, 3 testuoti determiniskuma, 2 jeigu norite testuoti konstitucija, 1 jeigu norite, kad nuskaitytu is failo arba 0 jeigu norite vesti duomenis: ";
            cin>>a;
            pasirinkimas = false; // nustatomas default
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }
        else pasirinkimas = true;
    }while(!pasirinkimas);

    if (a==((int)'4')){
        cout << endl << endl << endl;
        int numPairsToGenerate = 100000; // Kiekis analizuojamu simboliu stringu
        palyginimas(numPairsToGenerate);
    }
    else if (a==((int)'3')){
        int pasikartojimai = 0;
        char c;
        do{
            if((c!='4' && c!='3' && c!='2' && c!='1')){ // 1 arba 0
                cout << "kuri testa atlikti 1, 2, 3, 4. Jeigu norite savo - 0 (loading bar gali klaidingai veikti): ";
                cin>>c;
                pasirinkimas = false; // nustatomas default
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            }
            else pasirinkimas = true;
        }while(!pasirinkimas);
        if (c==((int)'1')){
            failoPavadinimas = "25000_1.txt";
            SkaitymasDeterministiskumas(codesHashed, codeHashed, code, failoPavadinimas, pasikartojimai);
            cout << "Buvo " << pasikartojimai << " pasikartojimu";
        }
        else if (c==((int)'2')){
            failoPavadinimas = "25000_2.txt";
            SkaitymasDeterministiskumas(codesHashed, codeHashed, code, failoPavadinimas, pasikartojimai);
            cout << "Buvo " << pasikartojimai << " pasikartojimu";
        }
        else if (c==((int)'3')){
            failoPavadinimas = "25000_3.txt";
            SkaitymasDeterministiskumas(codesHashed, codeHashed, code, failoPavadinimas, pasikartojimai);
            cout << "Buvo " << pasikartojimai << " pasikartojimu";
        }
        else if (c==((int)'4')){
            failoPavadinimas = "25000_4.txt";
            SkaitymasDeterministiskumas(codesHashed, codeHashed, code, failoPavadinimas, pasikartojimai);
            cout << "Buvo " << pasikartojimai << " pasikartojimu";
        }
        else if (c==((int)'0')){
            cin >> failoPavadinimas;
            SkaitymasDeterministiskumas(codesHashed, codeHashed, code, failoPavadinimas, pasikartojimai);
            cout << "Buvo " << pasikartojimai << " pasikartojimu";
        }
    }
    else if(a==((int)'2')){ 
        failoPavadinimas = "konstitucija.txt";
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
            std::cout << i+1 << ". " << codesHashed[i] << endl;
        }
    }
    else{
        cout << "Iveskite koda: ";
        getline(cin, code);
        Hashing(code, codeHashed);

        cout << endl << endl << endl;
        for (int i = 0; i < codeHashed.size(); i++) {
            //std::cout << answer[i] << " index: " << i << endl;
            std::cout << codeHashed[i];
        }
    }
    return 0;
}