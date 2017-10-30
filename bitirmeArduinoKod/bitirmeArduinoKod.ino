#include <SoftwareSerial.h>


const int rxpini = 2; // Alici pini
const int txpini = 3; // Gonderici pini

SoftwareSerial bluetooth(rxpini, txpini);

#include <TimeLib.h>
#include <Time.h>

#include <LiquidCrystal.h>
#include <MQ135.h>
#include <dht11.h>


#define TOPRAKNEM A5
#define GAZSENSOR A1
#define ROLE3 11
#define ROLE4 A3
#define ROLE5 12
#define ROLE6 10
#define ROLE7 A2
dht11 DHT11;
MQ135 gazSensor = MQ135(GAZSENSOR);
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

float sicaklik;
float nem_hava;
float karbondioksit;
int nem_toprak;

int gunler;
int saatler;
int dakikalar;
int saniyeler;

//Digital PIN ==> LCD         -->  4,5,6,7,8,9
//                DHT11       -->  13
//           ***  ROLE4       -->  A3          ---- ISITICI
//                ROLE6       -->  10          ---- SOGUTUCU
//           ***  ROLE7       -->  A2 -->role8 de         ---- NEMLENDIRICI
//                ROLE3       -->  11-->role2 de          ---- HAVALANDIRMA
//                ROLE5       -->  12          ---- SULAMA
//
//
//Analog PIN ==>  MQ135       -->  A1
//                TOPRAK_NEM  -->  A5



//const int Buzzer = A4;
//const int songLength = 18;

//char notes[] = "cdfda ag cdfdg gf "; // a space represents a rest
//int beats[] = {1,1,1,1,1,1,4,4,2,1,1,1,1,1,1,4,4,2};


//int tempo = 150;  // Speed of tempo


void setup()
{
  //pinMode(Buzzer, OUTPUT);
  pinMode(rxpini, INPUT);
  DHT11.attach(13);    // Arduino'daki Digital 13 PIN ---> DHT11 sensoru
  //Serial.begin(9600);
  bluetooth.begin(9600);
  //Serial.println("Seri Port Hazır ");
  bluetooth.println("Bluetooth Hazır …");

  //Serial.write("ssss");
  //byte myByte;
  //myByte = "asdf";
  //Serial.write(myByte) ;

  //digitalWrite(myByte, txpini);
  //bluetooth.write(txpini);

  digitalWrite(ROLE4, LOW);
  pinMode(ROLE4, OUTPUT);

  digitalWrite(ROLE6, LOW);
  pinMode(ROLE6, OUTPUT);

  digitalWrite(ROLE7, LOW);
  pinMode(ROLE7, OUTPUT);

  digitalWrite(ROLE3, LOW);
  pinMode(ROLE3, OUTPUT);

  digitalWrite(ROLE5, LOW);
  pinMode(ROLE5, OUTPUT);

  lcd.begin(16, 2);


}

void loop()
{
  /*
    digitalWrite(ROLE4,LOW);
    pinMode(ROLE4, OUTPUT);

    digitalWrite(ROLE6,LOW);
    pinMode(ROLE6, OUTPUT);

    digitalWrite(ROLE7,LOW);
    pinMode(ROLE7, OUTPUT);

    digitalWrite(ROLE3,LOW);
    pinMode(ROLE3, OUTPUT);

    digitalWrite(ROLE5,LOW);
    pinMode(ROLE5, OUTPUT);*/

  /*
    digitalWrite(ROLE7,LOW);
    pinMode(ROLE7, OUTPUT);
    digitalWrite(ROLE7,HIGH);
    delay(2000);
    digitalWrite(ROLE7,LOW);

    digitalWrite(ROLE6,LOW);
    pinMode(ROLE6, OUTPUT);
    digitalWrite(ROLE6,HIGH);
    delay(2000);
    digitalWrite(ROLE6,LOW);

    digitalWrite(ROLE5,LOW);
    pinMode(ROLE5, OUTPUT);
    digitalWrite(ROLE5,HIGH);
    delay(2000);
    digitalWrite(ROLE5,LOW);

    digitalWrite(ROLE4,LOW);
    pinMode(ROLE4, OUTPUT);
    digitalWrite(ROLE4,HIGH);
    delay(2000);
    digitalWrite(ROLE4,LOW);

    digitalWrite(ROLE3,LOW);
    pinMode(ROLE3, OUTPUT);
    digitalWrite(ROLE3,HIGH);
    delay(2000);
    digitalWrite(ROLE3,LOW);
  */



  /**
    int i, duration;

    for (i = 0; i < songLength; i++) // step through the song arrays
    {
      duration = beats[i] * tempo;  // length of note/rest in ms

      if (notes[i] == ' ')          // is this a rest?
      {
        delay(duration);            // then pause for a moment
      }
      else                          // otherwise, play the note
      {
        tone(Buzzer, frequency(notes[i]), duration);
        delay(duration);            // wait for tone to finish
      }
      delay(tempo/10);              // brief pause between notes
    }
  */

  /*digitalWrite(ROLE3,HIGH);
    delay(2000);
    digitalWrite(ROLE3,LOW);*/

  /*digitalWrite(ROLE4,HIGH);
    delay(2000);
    digitalWrite(ROLE4,LOW);*/

  /*digitalWrite(ROLE5,HIGH);
    delay(2000);
    digitalWrite(ROLE5,LOW); */

  /*digitalWrite(ROLE6,HIGH);
    delay(2000);
    digitalWrite(ROLE6,LOW);*/

  /*digitalWrite(ROLE7,HIGH);
    delay(2000);
    digitalWrite(ROLE7,LOW);*/

  if (bluetooth.available()) // Bluetooth ta bilgi varsa bilgileri seri porta yaz. (GONDER)
  {
    char c = (char)bluetooth.read(); // Bilgileri oku c’ ye ata.
    //Serial.write(c);

    //  Serial.println("Dunya");


 // }
  //if (Serial.available()) // Seri portta bilgi varsa bilgileri Bluetooth ‘a yaz. (AL)
 // {
    //char c = (char)Serial.read(); // Bilgileri oku c’ ye ata .

    if (c == '0') {

      digitalWrite(ROLE4, HIGH);
      bluetooth.println("Isitici Acildi.");
    }
    if (c == '1') {
      digitalWrite(ROLE4, LOW);
      bluetooth.println("Isitici Kapandi.");

    }


    if (c == '2') {
      // Serial.println("yazdik bisiler.");
      //Serial.write("lannnn");
      //bluetooth.print("merhaba");
      digitalWrite(ROLE6, HIGH);
      bluetooth.println("Sogutucu Acildi.");
    }
    if (c == '3') {
      digitalWrite(ROLE6, LOW);
      bluetooth.println("Sogutucu Kapandi.");
    }



    if (c == '4') {
      digitalWrite(ROLE5, HIGH);
      bluetooth.println("Sulama Acildi.");
    }
    if (c == '5') {
      digitalWrite(ROLE5, LOW);
      bluetooth.println("Sulama Kapandi.");
    }


    if (c == '6') {
      digitalWrite(ROLE3, HIGH);
      bluetooth.println("Havalandirma Acildi.");
    }
    if (c == '7') {
      digitalWrite(ROLE3, LOW);
      bluetooth.println("Havalandirma Kapandi.");
    }


    if (c == '8') {
      digitalWrite(ROLE7, HIGH);
      bluetooth.println("Nemlendirme Acildi.");
    }
    if (c == '9') {
      digitalWrite(ROLE7, LOW);
      bluetooth.println("Nemlendirme Kapandi.");
    }

    if (c == 'S') {

      while (true) {
       
          zamanHesapla();
          sensorlerdenVeriOku();

          if (dakikalar == 0) { //if(gunler<18)
            miselOnGelisme();//16-18 gunde miseller kompostu sarar.                               // 0-17 gunler
          }
          if (dakikalar == 1) { //if(gunler>17 && gunler<34)
            ortuTopragiEvresi();//ortu topragi serilmesinden sonra 15-17 gunde mantarlar gozukur. // 18-33 gunler
          }
          if (dakikalar == 2) { //if(gunler>33)
            urunDonemi();//ortu topragi serilmesinden 20-25 gün sonra hasat yapilmaya baslanir.   // 33-43 gunler
          }
        
      }

    }
    if (c == 'D') {

      digitalWrite(ROLE4, LOW);
      digitalWrite(ROLE6, LOW);
      digitalWrite(ROLE5, LOW);
      digitalWrite(ROLE3, LOW);
      digitalWrite(ROLE7, LOW);
    }


   // c = (char)Serial.read(); // Bilgileri oku c’ ye ata .

 int chk = DHT11.read();
  //Serial.print("DH11 Sensor: ");
  // switch (chk)
  // {
  //   case 0:  Serial.println("OK"); break;
  //  case -1: Serial.println("Checksum error"); break;
  //  case -2: Serial.println("Time out error"); break;
  //   default: Serial.println("Unknown error"); break;
  // }

  nem_hava = DHT11.humidity;
  sicaklik = DHT11.temperature;
  karbondioksit = gazSensor.getPPM();
  int nem_toprak_ara_deger = analogRead(TOPRAKNEM);
  nem_toprak = map(nem_toprak_ara_deger, 0, 1023, 0, 100);

  if (c == 'a') {  
        bluetooth.println(sicaklik);
                 }
                 
  if (c == 'b') {  
        bluetooth.println(nem_hava);
                 }
                 
  if (c == 'c') {  
        bluetooth.println(karbondioksit);                
                }

  if (c == 'd') {  
        bluetooth.println(nem_toprak);                
                }
/*bluetooth.print("Sicaklik:  ");
bluetooth.println(sicaklik);
bluetooth.print("Hava Nemi:  ");
bluetooth.println(nem_hava);
bluetooth.print("Karbondioksit:  ");
bluetooth.println(karbondioksit);
bluetooth.print("Toprak Nemi:  ");
bluetooth.println(nem_toprak);*/

   // bluetooth.write(c);

  }


}

void zamanHesapla() {

  long simdikiZaman = millis();

  long gun = 86400000; // 86400000 milisaniye gunde
  long saat = 3600000; // 3600000 milisaniye saatte
  long dakika = 60000; // 60000 milisaniye dakikada
  long saniye =  1000; // 1000 milisaniye saniyede

  gunler = simdikiZaman / gun ;                                 //gunlerin sayisi
  saatler = (simdikiZaman % gun) / saat;                        //saat hesabi
  dakikalar = ((simdikiZaman % gun) % saat) / dakika ;          //dakika hesabi
  saniyeler = (((simdikiZaman % gun) % saat) % dakika) / saniye;//saniye hesabi

  // Ekrana zamani bastirmak
  // Serial.print(gunler,DEC);
  EkranaRakamBastir(saatler);
  EkranaRakamBastir(dakikalar);
  EkranaRakamBastir(saniyeler);
  // Serial.println();



}

void EkranaRakamBastir(byte rakamlar) {

  // kolonlari ve sifirlari da bastirir
  // Serial.print(":");
  // if(rakamlar < 10)
  // Serial.print('0');
  // Serial.print(rakamlar,DEC);
}
void sensorlerdenVeriOku() {

  // Serial.println("\n");
  int chk = DHT11.read();
  //Serial.print("DH11 Sensor: ");
  // switch (chk)
  // {
  //   case 0:  Serial.println("OK"); break;
  //  case -1: Serial.println("Checksum error"); break;
  //  case -2: Serial.println("Time out error"); break;
  //   default: Serial.println("Unknown error"); break;
  // }

  nem_hava = DHT11.humidity;
  // Serial.print("Nem (%): ");
  // Serial.println(nem_hava);
  //Serial.println((float)DHT11.humidity, DEC);

  sicaklik = DHT11.temperature;
  // Serial.print("Sicaklik (°C): ");
  // Serial.println(sicaklik);
  //Serial.println((float)DHT11.temperature, DEC);

  karbondioksit = gazSensor.getPPM();
  // Serial.print("CO2 ppm : ");
  // Serial.println(karbondioksit);

  int nem_toprak_ara_deger = analogRead(TOPRAKNEM);
  nem_toprak = map(nem_toprak_ara_deger, 0, 1023, 0, 100);
  // Serial.print("Toprak Nem: ");
  // Serial.println(nem_toprak);


  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Sicaklik: ");
  lcd.print(sicaklik);
  lcd.setCursor(0, 1);
  lcd.print("Hava nemi: ");
  lcd.print(nem_hava);
  delay(2000);
  lcd.clear();
  delay(250);
  lcd.setCursor(0, 0);
  lcd.print("CO2 ppm: ");
  lcd.print(karbondioksit);
  lcd.setCursor(0, 1);
  lcd.print("Toprak nemi: ");
  lcd.print(nem_toprak);
  delay(2000);
  lcd.clear();
  delay(250);


}
void miselOnGelisme() {


  // Serial.println("Misel On Gelisme Evresi ");
  // Serial.println("1. dakikanin icerisinde");

  if (sicaklik < 20) {
    //  Serial.println("Sicaklik Kritik Seviye Dusuk");
    //  Serial.println("Isitici Devrede ...");
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Sicaklik Dusuk ");
    lcd.setCursor(0, 1);
    lcd.print("Isitici Devrede... ");
    delay(2000);

    digitalWrite(ROLE4, HIGH);
    delay(2000);
    digitalWrite(ROLE4, LOW);

    lcd.clear();
    delay(250);
  }
  if (sicaklik > 19 && sicaklik < 25) {
    //  Serial.println("Sicaklik Normal");
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Sicaklik Normal ");
    lcd.setCursor(0, 1);
    lcd.print(sicaklik);
    lcd.print(" ^C");
    delay(2000);
    lcd.clear();
    delay(250);
  }
  if (sicaklik > 24) {
    //  Serial.println("Sicaklik Kritik Seviye Yuksek");
    //  Serial.println("Sogutucu Devrede ...");
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Sicaklik Yuksek ");
    lcd.setCursor(0, 1);
    lcd.print("Sogutucu Devrede... ");
    delay(2000);
    digitalWrite(ROLE6, HIGH);
    delay(2000);
    digitalWrite(ROLE6, LOW);

    lcd.clear();
    delay(250);
  }
  if (nem_hava < 80) {
    //  Serial.println("Havanin Nemi Kritik Seviye Dusuk");
    //  Serial.println("Nemlendirme Sistemi Devrede ...");
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Hava Nemi Dusuk ");
    lcd.setCursor(0, 1);
    lcd.print("Nemlendirme Devrede... ");
    delay(2000);
    digitalWrite(ROLE7, HIGH);
    delay(2000);
    digitalWrite(ROLE7, LOW);
    lcd.clear();
    delay(250);
  }
  if (nem_hava < 91 && nem_hava > 79) {
    // Serial.println("Havanin Nemi Normal");
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Hava Nemi Normal ");
    lcd.setCursor(0, 1);
    lcd.print(nem_hava);
    delay(2000);
    lcd.clear();
    delay(250);

  }
  if (nem_hava > 90) {
    //  Serial.println("Havanin Nemi Kritik Seviye Yuksek");
    // Serial.println("Havalandirma Sistemi Devrede ...");
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Hava Nemi Yuksek ");
    lcd.setCursor(0, 1);
    lcd.print("Havalandirma Devrede... ");
    delay(2000);
    digitalWrite(ROLE3, HIGH);
    delay(2000);
    digitalWrite(ROLE3, LOW);
    lcd.clear();
    delay(250);
  }

  if (nem_toprak < 100) {
    // Serial.println("Toprak Nemi Kritik Seviye Dusuk");
    // Serial.println("Sulama Sistemi Devrede ...");
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Toprak Nemi Dusuk ");
    lcd.setCursor(0, 1);
    lcd.print("Sulama Devrede... ");
    delay(2000);
    digitalWrite(ROLE5, HIGH);
    delay(2000);
    digitalWrite(ROLE5, LOW);
    lcd.clear();
    delay(250);
  }


  //Misel on gelisme devresinde oda sicakligi 20-24 oC,
  //Bu donemde oda sicakligi 27-28 oC’yi kesinlikle gecmemelidir.
  //hava nemi % 80-90 arasinda tutulmalidir.
  //% 90’in uzerinde ise bir cok hastaliklarin gelismesi icin uygun bir ortam olusturur
  //Ancak bu asamada yuksek karbondioksit orani istedigimiz icin
  //hic taze havaya (oksijen) gereksinim yoktur
  //Yukarida belirtilen kosullar yerine getirildiginde 16-18 gunde miseller kompostun her tarafini sarar.



}
void ortuTopragiEvresi() {


  // Serial.println("Ortu Topragi Evresi ");
  // Serial.println("2. dakikananin icerisinde");

  if (sicaklik < 18) {
    //  Serial.println("Sicaklik Kritik Seviye Dusuk");
    //  Serial.println("Isitici Devrede ...");
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Sicaklik Dusuk ");
    lcd.setCursor(0, 1);
    lcd.print("Isitici Devrede... ");
    delay(2000);
    digitalWrite(ROLE4, HIGH);
    delay(2000);
    digitalWrite(ROLE4, LOW);
    lcd.clear();
    delay(250);
  }
  if (sicaklik > 17 && sicaklik < 21) {
    //  Serial.println("Sicaklik Normal");
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Sicaklik Normal ");
    lcd.setCursor(0, 1);
    lcd.print(sicaklik);
    lcd.print(" ^C");
    delay(2000);
    lcd.clear();
    delay(250);
  }
  if (sicaklik > 20) {
    //  Serial.println("Sicaklik Kritik Seviye Yuksek");
    //  Serial.println("Sogutucu Devrede ...");
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Sicaklik Yuksek ");
    lcd.setCursor(0, 1);
    lcd.print("Sogutucu Devrede... ");
    delay(2000);
    digitalWrite(ROLE6, HIGH);
    delay(2000);
    digitalWrite(ROLE6, LOW);
    lcd.clear();
    delay(250);
  }
  if (nem_hava < 80) {
    //  Serial.println("Havanin Nemi Kritik Seviye Dusuk");
    // Serial.println("Nemlendirme Sistemi Devrede ...");
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Hava Nemi Dusuk ");
    lcd.setCursor(0, 1);
    lcd.print("Nemlendirme Devrede... ");
    delay(2000);
    digitalWrite(ROLE7, HIGH);
    delay(2000);
    digitalWrite(ROLE7, LOW);
    lcd.clear();
    delay(250);
  }
  if (nem_hava < 86 && nem_hava > 79) {
    //   Serial.println("Havanin Nemi Normal");
  }
  if (nem_hava > 85) {
    //   Serial.println("Havanin Nemi Kritik Seviye Yuksek");
    //   Serial.println("Havalandirma Sistemi Devrede ...");
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Hava Nemi Yuksek ");
    lcd.setCursor(0, 1);
    lcd.print("Havalandirma Devrede... ");
    delay(2000);
    digitalWrite(ROLE3, HIGH);
    delay(2000);
    digitalWrite(ROLE3, LOW);
    lcd.clear();
    delay(250);
  }
  if (nem_toprak < 100) {
    //   Serial.println("Toprak Nemi Kritik Seviye Dusuk");
    //   Serial.println("Sulama Sistemi Devrede ...");
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Toprak Nemi Dusuk ");
    lcd.setCursor(0, 1);
    lcd.print("Sulama Devrede... ");
    delay(2000);
    digitalWrite(ROLE5, HIGH);
    delay(2000);
    digitalWrite(ROLE5, LOW);
    lcd.clear();
    delay(250);
  }


  //ortu topragi serme asamasında toprak nemi % 70-75 neme sahip olmalidir.
  //ortu topragi ortuldukten sonra oda sicakligi ilk bir hafta icerisinde yavas yavas
  //18-20 oC’ye dusurulmeli ve ilk mantarciklar gorulunceye kadar (ortu topraginin son haftasina kadar) bu sekilde devam etmelidir.
  //Bu donemde topragin nemi ise % 80-85 civarinda tutulmalidir.
  //Yukarida sayilan kosullar yerine getirildiğinde toprak ortulmesinden itibaren
  //15-17 gun sonra mantarlar toprak uzerinde gorulmeye baslar ve
  //20-25 gun sonra hasat olgunluguna erisirler.

}

void urunDonemi() {

  //  Serial.println("Urun Donemi Evresi ");
  //  Serial.println("3. dakikanin icerisinde");

  if (sicaklik < 15) {
    //  Serial.println("Sicaklik Kritik Seviye Dusuk");
    //   Serial.println("Isitici Devrede ...");
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Sicaklik Dusuk ");
    lcd.setCursor(0, 1);
    lcd.print("Isitici Devrede... ");
    delay(2000);
    digitalWrite(ROLE4, HIGH);
    delay(2000);
    digitalWrite(ROLE4, LOW);
    lcd.clear();
    delay(250);
  }
  if (sicaklik > 14 && sicaklik < 18) {
    //  Serial.println("Sicaklik Normal");
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Sicaklik Normal ");
    lcd.setCursor(0, 1);
    lcd.print(sicaklik);
    lcd.print(" ^C");
    delay(2000);
    lcd.clear();
    delay(250);
  }
  if (sicaklik > 17) {
    //   Serial.println("Sicaklik Kritik Seviye Yuksek");
    //  Serial.println("Sogutucu Devrede ...");
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Sicaklik Yuksek ");
    lcd.setCursor(0, 1);
    lcd.print("Sogutucu Devrede... ");
    delay(2000);
    digitalWrite(ROLE6, HIGH);
    delay(2000);
    digitalWrite(ROLE6, LOW);
    lcd.clear();
    delay(250);
  }
  if (nem_hava < 80) {
    //   Serial.println("Havanin Nemi Kritik Seviye Dusuk");
    //   Serial.println("Nemlendirme Sistemi Devrede ...");
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Hava Nemi Dusuk ");
    lcd.setCursor(0, 1);
    lcd.print("Nemlendirme Devrede... ");
    delay(2000);
    digitalWrite(ROLE7, HIGH);
    delay(2000);
    digitalWrite(ROLE7, LOW);
    lcd.clear();
    delay(250);
  }
  if (nem_hava < 86 && nem_hava > 79) {
    //   Serial.println("Havanin Nemi Normal");
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Hava Nemi Normal ");
    lcd.setCursor(0, 1);
    lcd.print(nem_hava);
    delay(2000);
    lcd.clear();
    delay(250);
  }
  if (nem_hava > 85) {
    //    Serial.println("Havanin Nemi Kritik Seviye Yuksek");
    //   Serial.println("Havalandirma Sistemi Devrede ...");
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Hava Nemi Yuksek ");
    lcd.setCursor(0, 1);
    lcd.print("Havalandirma Devrede... ");
    delay(2000);
    digitalWrite(ROLE3, HIGH);
    delay(2000);
    digitalWrite(ROLE3, LOW);
    lcd.clear();
    delay(250);
  }

  if (nem_toprak < 100) {
    //    Serial.println("Toprak Nemi Kritik Seviye Dusuk");
    //    Serial.println("Sulama Sistemi Devrede ...");
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Toprak Nemi Dusuk ");
    lcd.setCursor(0, 1);
    lcd.print("Sulama Devrede... ");
    delay(2000);
    digitalWrite(ROLE5, HIGH);
    delay(2000);
    digitalWrite(ROLE5, LOW);
    lcd.clear();
    delay(250);
  }
  //15-17 gun sonra mantarlar toprak uzerinde gorulmeye baslar ve
  //Mantarlar goruldukten sonra oda sicakligi 15-17 oC civarında olmalidir.
  //mantarciklar gorulmeye basladiktan sonra havalandirmaya baslanmali ve icerideki karbondioksiti dısarı atmalidir.
  //ortu topragi serildikten 20-25 gün sonra hasat yapilmaya baslanir.
  //3.5-4 cm cap buyukluğu alan mantarlar hasat edilirler
  //Hasat doneminde oda sicakliği 15-17 oC arasinda tutulmalidir.
  //Nemin % 70-80 arasinda olmasi uygundur.

}

int frequency(char note)
{
  int i;
  const int numNotes = 8;      // number of notes we're storing
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int frequencies[] = {262, 294, 330, 349, 392, 440, 494, 523};

  for (i = 0; i < numNotes; i++)
  {
    if (names[i] == note)
    {
      return (frequencies[i]);
    }
  }
  return (0);
}




