//khusus esp32
// kita perlu akun www.cryptocompare.com, dan dapatkan API key dan apiURL https://developers.coindesk.com/documentation/legacy/Price/SingleSymbolPriceEndpoint 
//https://developers.coindesk.com/documentation/legacy/Price/SingleSymbolPriceEndpoint kunjungi tu web. buat dapat apiURL bisa dicustom juga
// jangan lupa install semua library. semuanya ada kok 
// kenapa pakai ArduinoJson karena bentuk data dari si www.cryptocompare.com adalah json, perlu di manipulasi supaya terstruktur

#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>

// === WiFi credentials ===
const char* ssid = "KHUSUS CLOUD";
const char* password = "aKAganteng06";

// === CryptoCompare API Key & Endpoint ===
const char* apiKey = "gantii dengan api kalian";
const char* apiURL = "https://min-api.cryptocompare.com/data/price?fsym=BTC&tsyms=IDR,USD,JPY,EUR";

// === LCD I2C ===
LiquidCrystal_PCF8574 lcd(0x26);  // Ganti dengan address I2C jika tidak sama

// === Web Server ===
AsyncWebServer server(80);

// === Harga koin ===
String btcPriceIDR = "Loading...";
String btcPriceUSD = "Loading...";
String btcPriceJPY = "Loading...";
String btcPriceEUR = "Loading...";

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);  // LCD 16x2
  lcd.setBacklight(1); // Nyalakan backlight
  lcd.setCursor(0, 0);
  lcd.print("Connecting WiFi");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connected");

  // Jalankan fetch data sebagai task background
  xTaskCreatePinnedToCore(fetchCryptoData, "GetPrices", 4096, NULL, 1, NULL, 1);

  // Endpoint Web UI
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", htmlPage().c_str());
  });

  // Endpoint JSON
  server.on("/data", HTTP_GET, [](AsyncWebServerRequest *request){
    String json = "{\"BTC_IDR\":\"" + btcPriceIDR + "\",\"BTC_USD\":\"" + btcPriceUSD + "\",\"BTC_JPY\":\"" + btcPriceJPY + "\",\"BTC_EUR\":\"" + btcPriceEUR + "\"}";
    request->send(200, "application/json", json);
  });

  server.begin();
}

// === Fungsi untuk ambil data harga crypto secara berkala ===
void fetchCryptoData(void * parameter) {
  for(;;) {
    if(WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(apiURL);
      http.addHeader("authorization", "Apikey " + String(apiKey));

      int httpCode = http.GET();
      if(httpCode > 0) {
        String payload = http.getString();
        Serial.println(payload);

        // Parse JSON
        DynamicJsonDocument doc(512);
        DeserializationError err = deserializeJson(doc, payload);
        if (!err) {
          btcPriceIDR = String(doc["IDR"].as<float>(), 2);
          btcPriceUSD = String(doc["USD"].as<float>(), 2);
          btcPriceJPY = String(doc["JPY"].as<float>(), 2);
          btcPriceEUR = String(doc["EUR"].as<float>(), 2);

          // Tampilkan ke LCD
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("BTC IDR: " + btcPriceIDR);
          lcd.setCursor(0, 1);
          lcd.print("USD: " + btcPriceUSD);
        }
      } else {
        Serial.printf("HTTP Error: %d\n", httpCode);
      }
      http.end();
    }

    delay(10000); // Refresh tiap 10 detik
  }
}

// === Halaman Web UI ===
String htmlPage() {
  return R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
      <title>Crypto Prices</title>
      <meta name="viewport" content="width=device-width, initial-scale=1" />
      <style>
        body { font-family: Arial; background: #111; color: #fff; text-align: center; padding: 30px; }
        h1 { color: #0f0; }
        .price-box {
          display: inline-block;
          margin: 20px;
          padding: 20px;
          background: #222;
          border-radius: 10px;
          box-shadow: 0 0 10px #0f0;
        }
        .price-box h2 { margin: 10px 0; font-size: 28px; }
        .price { font-size: 24px; color: #0f0; }
      </style>
    </head>
    <body>
      <h1>💹 Realtime Crypto Prices</h1>
      <div class="price-box">
        <h2>BTC</h2>
        <div class="price" id="btc_idr">Loading...</div>
        <div class="price" id="btc_usd">Loading...</div>
        <div class="price" id="btc_jpy">Loading...</div>
        <div class="price" id="btc_eur">Loading...</div>
      </div>
      <script>
        async function fetchPrices() {
          try {
            const res = await fetch('/data');
            const data = await res.json();
            document.getElementById('btc_idr').textContent = 'IDR: Rp' + data.BTC_IDR;
            document.getElementById('btc_usd').textContent = 'USD: $' + data.BTC_USD;
            document.getElementById('btc_jpy').textContent = 'JPY: ¥' + data.BTC_JPY;
            document.getElementById('btc_eur').textContent = 'EUR: €' + data.BTC_EUR;
          } catch (e) {
            console.error(e);
          }
        }
        setInterval(fetchPrices, 5000);
        fetchPrices();
      </script>
    </body>
    </html>
  )rawliteral";  // <-- PENUTUP RAW STRING LITERAL YANG BENAR
}

// === Tambahkan fungsi loop() kosong untuk ESP32 ===
void loop() {
  // Fungsi loop() kosong, diperlukan agar ESP32 dapat berjalan normal.
}
