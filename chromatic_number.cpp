#include <iostream>
#include <stdio.h>
using namespace std;

class Queue {
private:
   int max;
   int *queue;
   int write = 0;
   int read = 0;

public:
   Queue() { queue = nullptr; }
   Queue(int max) : max(max) { queue = (int *)malloc(max * sizeof(max)); }

   bool enqueue(int item) {
      if ((write + 1) % max == read)
         return false;
      queue[write] = item;
      write = (write + 1) % max;
      return true;
   }

   bool dequeue(int &item) {
      if (write == read)
         return false;
      item = queue[read];
      read = (read + 1) % max;
      return true;
   }

   int count() {
      if (write >= read)
         return (write - read);
      else
         return (write - read + max);
   }
};

class Vrh {
private:
   char *susjedi;
   int stupanj;

public:
   Vrh() : susjedi(nullptr), stupanj(0) {}
   void initialize(int n) { susjedi = (char *)malloc(n * sizeof(char)); }
   void increment() { stupanj++; }
   void storeElement(int index, int element) { susjedi[index] = element; }
   int getElement(int index) { return (int)susjedi[index]; }
   int getStupanj() { return stupanj; };
   char *getSusjedi() { return susjedi; }
};

int kromatskiBroj(Vrh v[], int brojVrhova) {
   int maxBoja = 0;
   bool van;

   int boje[brojVrhova];

   for (int i = 0; i < brojVrhova; i++)
      boje[i] = 0;

   for (int i = 0; i < brojVrhova; i++) { // uzmi točku
      Vrh vrh = v[i];
      for (int j = 1; j <= brojVrhova; j++) { // boja
         van = false;
         for (int k = 0; k < brojVrhova; k++) { // susjed
            if (k != i) {
               if (vrh.getSusjedi()[k] == 1) {
                  if (boje[k] == j) {
                     van = true;
                     break;
                  }
               }
            }
         }
         if (van)
            continue;
         boje[i] = j;
         if (maxBoja < j)
            maxBoja = j;
         break;
      }
   }
   return maxBoja;
}

int main(void) {
   int n, broj;
   string filename;

   cout << "Unesite ime datoteke: ";
   getline(cin, filename);
   FILE *ulaz = fopen(filename.c_str(), "r");
   fscanf(ulaz, "%d", &n);
   Vrh vrhovi[n];
   for (int i = 0; i < n; i++) {
      vrhovi[i].initialize(n);
   }
   for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
         fscanf(ulaz, "%d", &broj);
         vrhovi[i].storeElement(j, broj);
         if (broj == 1)
            vrhovi[i].increment();
      }
   }
   fclose(ulaz);

   for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
         cout << vrhovi[i].getElement(j) << " ";
      }
      cout << "  " << vrhovi[i].getStupanj() << endl;
   }
   cout << "Kromatski broj grafa je " << kromatskiBroj(vrhovi, n);

   return 0;
}