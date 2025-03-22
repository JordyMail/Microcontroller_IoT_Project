# Keypad Input with Arduino

## Deskripsi
Kode ini digunakan untuk membaca input dari keypad 4x4 menggunakan Arduino dan menampilkan hasilnya melalui Serial Monitor.

## Peralatan yang Dibutuhkan
- Arduino (Uno, Mega, atau lainnya yang kompatibel)
- Keypad 4x4
- Kabel jumper

## Library yang Digunakan
Kode ini menggunakan library `Keypad.h`, yang harus diinstal terlebih dahulu. Jika belum terinstal, Anda dapat menambahkannya melalui Library Manager di Arduino IDE.

## Penjelasan Kode
1. **Deklarasi Keypad**
   ```cpp
   #include<Keypad.h>
   ```
   Library `Keypad.h` digunakan untuk mengelola input dari keypad.

2. **Mendefinisikan Layout Keypad**
   ```cpp
   char keys[4][4] = {
     {'1', '2', '3', 'A'},
     {'4', '5', '6', 'B'},
     {'7', '8', '9', 'C'},
     {'*', '0', '#', 'D'}
   };
   ```
   Array dua dimensi `keys` mendefinisikan karakter yang dikaitkan dengan setiap tombol pada keypad.

3. **Menentukan Pin Baris dan Kolom**
   ```cpp
   byte rowPins[] = {4, 5, 6, 7};
   byte colPins[] = {8, 9, 10, 11};
   ```
   `rowPins` dan `colPins` menentukan koneksi pin Arduino ke baris dan kolom pada keypad.

4. **Inisialisasi Keypad**
   ```cpp
   Keypad myKey = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);
   ```
   `makeKeymap(keys)` digunakan untuk menghubungkan array tombol dengan objek keypad.

5. **Inisialisasi Serial Monitor**
   ```cpp
   void setup()
   {
     Serial.begin(9600);
   }
   ```
   `Serial.begin(9600);` digunakan untuk menginisialisasi komunikasi serial dengan baud rate 9600.

6. **Loop untuk Membaca Input Keypad**
   ```cpp
   void loop()
   {
     char inputKey = myKey.getKey();
     if (inputKey) {
       Serial.println(inputKey);
     }
   }
   ```
   - `myKey.getKey()` digunakan untuk membaca tombol yang ditekan.
   - Jika ada tombol yang ditekan, karakter tersebut akan ditampilkan di Serial Monitor.

## Cara Menggunakan
1. Sambungkan keypad ke Arduino sesuai dengan konfigurasi pin dalam kode.
2. Unggah kode ke Arduino menggunakan Arduino IDE.
3. Buka Serial Monitor (Ctrl + Shift + M di Arduino IDE).
4. Tekan tombol pada keypad, dan hasilnya akan ditampilkan di Serial Monitor.

## Output yang Diharapkan
Jika pengguna menekan tombol "1" pada keypad, Serial Monitor akan menampilkan:
```
1
```
Begitu pula dengan tombol lainnya sesuai dengan mapping yang telah dibuat.

## Catatan
- Pastikan koneksi kabel ke keypad sesuai dengan pin yang ditentukan dalam kode.
- Jika keypad tidak merespons, periksa apakah library `Keypad.h` telah terinstal dengan benar di Arduino IDE.

## Image

WOKWI LINK: [https://wokwi.com/projects/420296768401395713]


![image](https://github.com/user-attachments/assets/7b99109a-c66c-4e53-8082-da70a569e59c)
