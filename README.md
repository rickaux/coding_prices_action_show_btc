Berikut adalah isi lengkap `README.md` yang bisa kamu gunakan di GitHub untuk proyek `coding_prices_action_show_btc.ino`. File ini menjelaskan deskripsi, penjelasan fungsi, cara installasi library, setup board ESP32, dan cara upload. Sudah disertakan credit ke author GitHub kamu.

---

````markdown
# 💸 coding_prices_action_show_btc.ino

Menampilkan harga **Bitcoin (BTC)** secara real-time menggunakan ESP32 dan LCD I2C. Data harga ditarik dari API online dan ditampilkan melalui layar LCD. Sistem ini juga menyediakan WebServer lokal yang menampilkan harga terkini melalui browser.

## ✨ Fitur

- Menampilkan harga Bitcoin secara real-time dari API.
- Output pada LCD I2C 16x2 (melalui I2C interface).
- WebServer lokal berbasis ESP32 untuk tampilkan harga via browser.
- Dapat digunakan untuk monitoring harga kripto di rumah.

---

## 📷 Tampilan

- **LCD**: Menampilkan teks seperti `BTC: $67235`
- **Browser**: Menampilkan halaman web dengan harga terbaru

---

## 📦 Library yang Digunakan

Berikut adalah library yang perlu di-install agar proyek ini bisa dikompilasi:

```cpp
#include <WiFi.h>                      // Untuk koneksi WiFi di ESP32
#include <Wire.h>                      // Untuk komunikasi I2C (LCD)
#include <LiquidCrystal_PCF8574.h>     // Library LCD I2C berbasis PCF8574
#include <HTTPClient.h>                // Untuk mengambil data dari API
#include <ArduinoJson.h>               // Untuk parsing JSON dari API
#include <ESPAsyncWebServer.h>         // WebServer asinkron untuk ESP32
#include <AsyncTCP.h>                  // Pendukung ESPAsyncWebServer
````

### Cara Install Library

1. Buka **Arduino IDE**
2. Pergi ke **Sketch > Include Library > Manage Libraries...**
3. Cari dan install berikut:

   * `LiquidCrystal_PCF8574` by Matthias Hertel
   * `ArduinoJson` by Benoit Blanchon
   * `ESPAsyncWebServer` by me-no-dev
   * `AsyncTCP` by me-no-dev (khusus ESP32)
4. Library `WiFi.h`, `Wire.h`, dan `HTTPClient.h` sudah bawaan board ESP32.

---

## ⚙️ Instalasi Board ESP32

1. Buka **Arduino IDE**
2. Buka **File > Preferences**
3. Di kolom **Additional Board Manager URLs**, tambahkan URL berikut:

```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```

4. Klik OK.
5. Buka **Tools > Board > Boards Manager**
6. Cari `esp32` lalu klik **Install** dari Espressif Systems.

---

## 🧠 Cara Upload ke ESP32

1. Hubungkan ESP32 ke PC lewat kabel USB.
2. Buka file `coding_prices_action_show_btc.ino` di Arduino IDE.
3. Pilih board: **Tools > Board > ESP32 Dev Module**
4. Pilih port: **Tools > Port > COMx**
5. Klik tombol **Upload (→)**

---

## 🌐 Setup WiFi

WiFi dan password biasanya di-define di bagian atas kode:

```cpp
const char* ssid = "NAMA_WIFI";
const char* password = "PASSWORD_WIFI";
```

Ganti sesuai jaringan WiFi kamu.

---

## 🧪 API Provider

Harga BTC diambil dari API kripto seperti:

```txt
https://api.coindesk.com/v1/bpi/currentprice/BTC.json
```

Atau bisa diganti dengan API lain sesuai kebutuhan, pastikan format JSON dikenali oleh ArduinoJson.

---

## ✍️ Author

Made with ❤️ by [Rickaux](https://github.com/rickaux)

---

## ⚠️ Catatan Tambahan

* Pastikan koneksi internet tersedia saat ESP32 pertama menyala.
* Pastikan API tidak membutuhkan token atau authentication jika ingin langsung bekerja.

```

---

Jika kamu butuh juga versi `coding_prices_action_show_btc.ino` lengkap atau ingin file `README.md` langsung jadi dalam format siap upload ke GitHub, tinggal beri tahu saja.
```
