#include <iostream> // library that contain basic input/output functions
#include <fstream>  // library that contains file input/output functions
#include <cstring>
#include <cstdio>
#include <windows.h>
#include <math.h>
using namespace std;

bool file_exists(string filename);
int get_file_size(string filename);
bool validOsr(string fin);
bool makeMods(bool setMods[], char * argv[]);
int main(int argc, char * argv[]) {
  if (argc < 3) {
    cout << "Usage: osu!Remod.exe <input OSR file> <output OSR file> ( NF | EZ | NV | HD | HR | SD | DT | RX | HT | NC | FL | AUTO | SO | AP | PF | 1K | 2K | 3K | 4K | 5K | 6K | 7K | 8K | 9K | FI | RD | Cinema | TP | COOP )" << endl;
    return 0;
  }

  if (!validOsr(argv[1])) {
    return 0;
  }

  if (file_exists(argv[2])) {
    cout << "Warning: " << argv[2] << " already exists. Do you want to overwrite it? (y/n)\n";
    string resp;
    cin >> resp;
    if (resp == "y") {
      cout << argv[2] << " will be overwritten.\n";
    } else if (resp == "n") {
      return 0;
    } else {
      cout << "I didn't understand you.\n";
      return 0;
    }
  }
  int osrSize=get_file_size(argv[1]);
  int numberOfMods = 29;
  bool setMods[numberOfMods];
  for (int i = 0; i <= numberOfMods; i++) {
    setMods[i] = 0;
  }

  makeMods(setMods, argv);


  char * array = new char[get_file_size(argv[1])];
  int position = 0;
  ifstream fin(argv[1], ios_base:: in | ios_base::binary);
  if (fin.is_open()) {

    cout << "Reading file..." << endl;

    while (position < osrSize + 2) {
      fin.get(array[position]);
      position++;
    }
    int nameLen = array[0x28];

    int modByte[4] = {0,0,0,0};
    for (int i = 1; i <= numberOfMods; i++) {
      if (setMods[i]) {
        int j = ceil(i / 8);
        if(i%8==0){
            j=j-1;
        }
        modByte[j] = modByte[j] + pow(0x2, (i - 0x1 - 8 * j));
        if(setMods[8]){cout<<"rx should be enabled\n";}
      }
    }

    for (int i = 0; i <= 4; i++) {
      array[0x5E + nameLen + i] = modByte[i];
    }
    cout << "Data has been read. Now writing to output file:" << endl;

    ofstream out(argv[2], ios_base::out | ios_base::binary);
    cout << argv[2] << endl;
    if (!out) {
      cout << "Cannot open output file\n";
      return 1;
    }

    out.write((char * ) array, position - 2);
    out.close();
    cout << "Done!" << endl;

  }

  return 0;
}
int get_file_size(string filename) {
  FILE * p_file = NULL;
  p_file = fopen(filename.c_str(), "rb");
  fseek(p_file, 0, SEEK_END);
  int size = ftell(p_file);
  fclose(p_file);
  return size;
}
bool file_exists(string filename) {
  ifstream in (filename.c_str(), ios_base:: in | ios_base::binary);
  if ( in .is_open()) { in .close();
    return 1;
  } else {
    return 0;
  }

}
bool validOsr(string fin) {
  if (!file_exists(fin)) {
    cout << "Error: " << fin << " does not exist or I don't have read permission.\n";
    return 0;
  }
  cout << "Size of file: " << get_file_size(fin) << endl;
  if (get_file_size(fin) < 1) {
    cout << "There's no data here! What are you trying to do to me?!?" << endl;
    return 0;
  } else {
    if (get_file_size(fin) < 94) {
      cout << "That wasn't big enough to be an OSR file..." << endl;
      return 0;
    }
  }
  return 1;
}
bool makeMods(bool setMods[], char * argv[]){
      for (int i = 3; argv[i] != NULL; i++) {
    if (!strcmp(argv[i], "NF") || !strcmp(argv[i], "nf")) {
      setMods[1] = 1;
    } else if (!strcmp(argv[i], "EZ") || !strcmp(argv[i], "ez")) {
      setMods[2] = 1;
    } else if (!strcmp(argv[i], "NV") || !strcmp(argv[i], "nv")) {
      setMods[3] = 1;
    } else if (!strcmp(argv[i], "HD") || !strcmp(argv[i], "hd")) {
      setMods[4] = 1;
    } else if (!strcmp(argv[i], "HR") || !strcmp(argv[i], "hr")) {
      setMods[5] = 1;
    } else if (!strcmp(argv[i], "SD") || !strcmp(argv[i], "sd")) {
      setMods[6] = 1;
    } else if (!strcmp(argv[i], "DT") || !strcmp(argv[i], "dt")) {
      setMods[7] = 1;
    } else if (!strcmp(argv[i], "RX") || !strcmp(argv[i], "rx")) {
      setMods[8] = 1;
    } else if (!strcmp(argv[i], "HT") || !strcmp(argv[i], "ht")) {
      setMods[9] = 1;
    } else if (!strcmp(argv[i], "NC") || !strcmp(argv[i], "nc")) {
      setMods[10] = 1;
    } else if (!strcmp(argv[i], "FL") || !strcmp(argv[i], "fl")) {
      setMods[11] = 1;
    } else if (!strcmp(argv[i], "AUTO") || !strcmp(argv[i], "auto")) {
      setMods[12] = 1;
    } else if (!strcmp(argv[i], "SO") || !strcmp(argv[i], "so")) {
      setMods[13] = 1;
    } else if (!strcmp(argv[i], "AP") || !strcmp(argv[i], "ap")) {
      setMods[14] = 1;
    } else if (!strcmp(argv[i], "PF") || !strcmp(argv[i], "pf")) {
      setMods[15] = 1;
    } else if (!strcmp(argv[i], "4K") || !strcmp(argv[i], "4k")) {
      setMods[16] = 1;
    } else if (!strcmp(argv[i], "5K") || !strcmp(argv[i], "5k")) {
      setMods[17] = 1;
    } else if (!strcmp(argv[i], "6K") || !strcmp(argv[i], "6k")) {
      setMods[18] = 1;
    } else if (!strcmp(argv[i], "7K") || !strcmp(argv[i], "7k")) {
      setMods[19] = 1;
    } else if (!strcmp(argv[i], "8K") || !strcmp(argv[i], "8k")) {
      setMods[20] = 1;
    } else if (!strcmp(argv[i], "FI") || !strcmp(argv[i], "fi")) {
      setMods[21] = 1;
    } else if (!strcmp(argv[i], "RD") || !strcmp(argv[i], "rd")) {
      setMods[22] = 1;
    } else if (!strcmp(argv[i], "Cinema") || !strcmp(argv[i], "cinema")) {
      setMods[23] = 1;
    } else if (!strcmp(argv[i], "TP") || !strcmp(argv[i], "tp")) {
      setMods[24] = 1;
    } else if (!strcmp(argv[i], "9K") || !strcmp(argv[i], "9k")) {
      setMods[25] = 1;
    } else if (!strcmp(argv[i], "COOP") || !strcmp(argv[i], "coop")) {
      setMods[26] = 1;
    } else if (!strcmp(argv[i], "1K") || !strcmp(argv[i], "1k")) {
      setMods[27] = 1;
    } else if (!strcmp(argv[i], "3K") || !strcmp(argv[i], "3k")) {
      setMods[28] = 1;
    } else if (!strcmp(argv[i], "2K") || !strcmp(argv[i], "2k")) {
      setMods[29] = 1;
    }
  }
  return setMods;
}
