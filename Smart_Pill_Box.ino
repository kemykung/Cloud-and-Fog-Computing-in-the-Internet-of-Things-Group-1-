#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Preferences.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS3231 rtc;
Preferences prefs;

const int hallPin = 4;
const int buzzerPin = 33;

const char* ssid     = "我是小Phone今年9歲";
const char* password = "0905820085";
const char* thingspeakServer = "http://api.thingspeak.com/update";
const char* apiKey = "53U1G6PDGN1X5SXW";

const int buzzerVolume = 128;

const int BOX_OPEN_STATE = LOW;

// === 鬧鐘時間 ===
const int MORNING_HOUR = 14, MORNING_MIN = 52;
const int NOON_HOUR    = 12, NOON_MIN    = 2;
const int EVENING_HOUR = 18, EVENING_MIN = 10;

const long TIMEOUT_SEC = 300;

// === 狀態變數 ===
int currentSlot = 0;
DateTime buzzerStartTime;
bool alarmTriggered = false;
bool dataSent = false;

// === 今日紀錄 ===
int lastTriggerDay = -1;
bool morningDone = false;
bool noonDone = false;
bool eveningDone = false;

int morningResult = -1;
int noonResult = -1;
int eveningResult = -1;

long morningDelay = 0;
long noonDelay = 0;
long eveningDelay = 0;

// === 過去 7 天歷史 ===
int last7Results[7][3];
long last7Delays[7][3];

void setup() {
  Serial.begin(115200);
  pinMode(hallPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Wire.begin(21, 22);

  lcd.init();
  lcd.backlight();
  lcd.clear();

  prefs.begin("medbox", false);
  loadHistoryFromPrefs();
  int savedDay = prefs.getInt("lastDay", -1);

  // WiFi
  lcd.print("Connecting WiFi");
  WiFi.begin(ssid, password);
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    attempts++;
  }
  lcd.clear();
  lcd.print(WiFi.status() == WL_CONNECTED ? "WiFi OK" : "WiFi FAIL");
  delay(1500);

  if (!rtc.begin()) {
    lcd.clear();
    lcd.print("RTC Error");
    while (1);
  }
  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  lastTriggerDay = savedDay;
  Serial.println("System ready");
}

void loop() {
  DateTime now = rtc.now();

  // === 午夜重置 ===
  if (now.day() != lastTriggerDay) {
    if (lastTriggerDay != -1) {
      shiftHistoryAndArchiveToday();
      saveHistoryToPrefs();
    }

    morningDone = false;
    noonDone = false;
    eveningDone = false;
    morningResult = -1;
    noonResult = -1;
    eveningResult = -1;
    morningDelay = 0;
    noonDelay = 0;
    eveningDelay = 0;
    lastTriggerDay = now.day();
    prefs.putInt("lastDay", lastTriggerDay);
  }

  // === 鬧鐘觸發 ===
  if (!alarmTriggered) {
    if (!morningDone && now.hour() == MORNING_HOUR && now.minute() == MORNING_MIN) {
      triggerAlarm(now, 1);
    } else if (!noonDone && now.hour() == NOON_HOUR && now.minute() == NOON_MIN) {
      triggerAlarm(now, 2);
    } else if (!eveningDone && now.hour() == EVENING_HOUR && now.minute() == EVENING_MIN) {
      triggerAlarm(now, 3);
    }
  }

  // === 蜂鳴中 ===
  if (alarmTriggered) {
    int hallState = digitalRead(hallPin);

    // 磁鐵離開 = 藥盒打開 → 停止蜂鳴
    if (hallState == BOX_OPEN_STATE && !dataSent) {
      long delay_sec = now.unixtime() - buzzerStartTime.unixtime();
      Serial.println(">>> OPENED slot " + String(currentSlot) + " delay " + String(delay_sec) + "s");

      ledcWrite(buzzerPin, 0);
      ledcDetach(buzzerPin);

      setSlotResult(currentSlot, 1, delay_sec);
      sendToThingSpeak(currentSlot, 1, delay_sec);
      markSlotDone(currentSlot);

      alarmTriggered = false;
      dataSent = true;
    }

    // 超時
    long elapsed = now.unixtime() - buzzerStartTime.unixtime();
    if (elapsed > TIMEOUT_SEC && !dataSent) {
      Serial.println(">>> TIMEOUT slot " + String(currentSlot));

      ledcWrite(buzzerPin, 0);
      ledcDetach(buzzerPin);

      setSlotResult(currentSlot, 0, TIMEOUT_SEC);
      sendToThingSpeak(currentSlot, 0, TIMEOUT_SEC);
      markSlotDone(currentSlot);

      alarmTriggered = false;
      dataSent = true;
    }
  }

  updateLCD(now);
  delay(500);
}

// === 觸發鬧鐘（修正：attach 只做一次）===
void triggerAlarm(DateTime now, int slot) {
  currentSlot = slot;
  buzzerStartTime = now;
  alarmTriggered = true;
  dataSent = false;

  ledcAttachChannel(buzzerPin, 1000, 8, 0);
  ledcWrite(buzzerPin, buzzerVolume);

  String name = (slot == 1) ? "MORNING" : (slot == 2) ? "NOON" : "EVENING";
  Serial.println(">>> ALARM: " + name);
}

// === 設定結果 ===
void setSlotResult(int slot, int result, long delay_sec) {
  if (slot == 1) { morningResult = result; morningDelay = delay_sec; }
  else if (slot == 2) { noonResult = result; noonDelay = delay_sec; }
  else if (slot == 3) { eveningResult = result; eveningDelay = delay_sec; }
}

void markSlotDone(int slot) {
  if (slot == 1) morningDone = true;
  else if (slot == 2) noonDone = true;
  else if (slot == 3) eveningDone = true;
}

// === 歷史陣列操作 ===
void shiftHistoryAndArchiveToday() {
  for (int i = 0; i < 6; i++) {
    for (int s = 0; s < 3; s++) {
      last7Results[i][s] = last7Results[i + 1][s];
      last7Delays[i][s] = last7Delays[i + 1][s];
    }
  }
  last7Results[6][0] = morningResult;
  last7Results[6][1] = noonResult;
  last7Results[6][2] = eveningResult;
  last7Delays[6][0] = morningDelay;
  last7Delays[6][1] = noonDelay;
  last7Delays[6][2] = eveningDelay;
}

// === 週統計計算 ===
float calculateWeeklyRate() {
  int total = 0, taken = 0;
  for (int i = 0; i < 6; i++) {
    for (int s = 0; s < 3; s++) {
      if (last7Results[i][s] != -1) {
        total++;
        if (last7Results[i][s] == 1) taken++;
      }
    }
  }
  if (morningResult != -1) { total++; if (morningResult == 1) taken++; }
  if (noonResult != -1)    { total++; if (noonResult == 1)    taken++; }
  if (eveningResult != -1) { total++; if (eveningResult == 1) taken++; }
  if (total == 0) return 0.0;
  return (taken * 100.0) / total;
}

float calculateWeeklyAvgDelay() {
  long totalD = 0;
  int count = 0;
  for (int i = 0; i < 6; i++) {
    for (int s = 0; s < 3; s++) {
      if (last7Results[i][s] == 1) { totalD += last7Delays[i][s]; count++; }
    }
  }
  if (morningResult == 1) { totalD += morningDelay; count++; }
  if (noonResult == 1)    { totalD += noonDelay;    count++; }
  if (eveningResult == 1) { totalD += eveningDelay; count++; }
  if (count == 0) return 0.0;
  return (float)totalD / count;
}

int calculateWeeklyTaken() {
  int count = 0;
  for (int i = 0; i < 6; i++) {
    for (int s = 0; s < 3; s++) {
      if (last7Results[i][s] == 1) count++;
    }
  }
  if (morningResult == 1) count++;
  if (noonResult == 1)    count++;
  if (eveningResult == 1) count++;
  return count;
}

int getTodayScore() {
  int count = 0;
  if (morningResult == 1) count++;
  if (noonResult == 1)    count++;
  if (eveningResult == 1) count++;
  return count;
}

int calculateAdherenceScore() {
  float rate = calculateWeeklyRate();
  float avgDelay = calculateWeeklyAvgDelay();
  int delayScore = 30;
  if (avgDelay > 60) {
    delayScore = max(0, 30 - (int)((avgDelay - 60) / 10));
  }
  return constrain((int)(rate * 0.7) + delayScore, 0, 100);
}

// === 上傳到 ThingSpeak ===
void sendToThingSpeak(int slot, int result, long delay_seconds) {
  if (WiFi.status() != WL_CONNECTED) return;

  HTTPClient http;
  String url = String(thingspeakServer) + "?api_key=" + apiKey;

  url += "&field1=" + String(result);
  url += "&field2=" + String(getTodayScore());
  url += "&field3=" + String(delay_seconds);
  url += "&field4=" + String(slot);

  if (isLastSlotOfDay()) {
    url += "&field5=" + String(calculateWeeklyRate(), 1);
    url += "&field6=" + String(calculateWeeklyAvgDelay(), 1);
    url += "&field7=" + String(calculateWeeklyTaken());
    url += "&field8=" + String(calculateAdherenceScore());
  }

  Serial.println("Upload: " + url);
  http.begin(url);
  int code = http.GET();
  Serial.println("Response: " + http.getString());
  http.end();
}

// === 判斷是否為今天最後一個時段 ===
bool isLastSlotOfDay() {
  int doneCount = 0;
  if (morningDone || currentSlot == 1) doneCount++;
  if (noonDone || currentSlot == 2) doneCount++;
  if (eveningDone || currentSlot == 3) doneCount++;
  return doneCount >= 3;
}

// === Flash 讀寫 ===
void saveHistoryToPrefs() {
  for (int i = 0; i < 7; i++) {
    for (int s = 0; s < 3; s++) {
      String keyR = "r" + String(i) + String(s);
      String keyD = "d" + String(i) + String(s);
      prefs.putInt(keyR.c_str(), last7Results[i][s]);
      prefs.putLong(keyD.c_str(), last7Delays[i][s]);
    }
  }
}

void loadHistoryFromPrefs() {
  for (int i = 0; i < 7; i++) {
    for (int s = 0; s < 3; s++) {
      String keyR = "r" + String(i) + String(s);
      String keyD = "d" + String(i) + String(s);
      last7Results[i][s] = prefs.getInt(keyR.c_str(), -1);
      last7Delays[i][s] = prefs.getLong(keyD.c_str(), 0);
    }
  }
  Serial.println("History loaded");
}

// === 取得下次吃藥的剩餘秒數 ===
long getSecondsToNextAlarm(DateTime now) {
  long nowSec = (long)now.hour() * 3600 + now.minute() * 60 + now.second();

  long slots[3] = {
    (long)MORNING_HOUR * 3600 + MORNING_MIN * 60,
    (long)NOON_HOUR    * 3600 + NOON_MIN    * 60,
    (long)EVENING_HOUR * 3600 + EVENING_MIN * 60
  };
  bool done[3] = { morningDone, noonDone, eveningDone };

  for (int i = 0; i < 3; i++) {
    if (!done[i] && slots[i] > nowSec) {
      return slots[i] - nowSec;
    }
  }

  long secsLeftToday = 86400 - nowSec;
  return secsLeftToday + slots[0];
}

// === LCD 顯示 ===
void updateLCD(DateTime now) {
  lcd.clear();
  lcd.setCursor(0, 0);

  if (now.hour() < 10) lcd.print("0");
  lcd.print(now.hour()); lcd.print(":");
  if (now.minute() < 10) lcd.print("0");
  lcd.print(now.minute()); lcd.print(":");
  if (now.second() < 10) lcd.print("0");
  lcd.print(now.second());

  if (!alarmTriggered) {
    long remain = getSecondsToNextAlarm(now);
    int h = remain / 3600;
    int m = (remain % 3600) / 60;
    int s = remain % 60;

    lcd.setCursor(8, 0);
    if (h > 0) {
      lcd.print(" N");
      lcd.print(h);
      lcd.print("h");
      if (m < 10) lcd.print("0");
      lcd.print(m);
      lcd.print("m");
    } else {
      lcd.print(" N");
      if (m < 10) lcd.print("0");
      lcd.print(m);
      lcd.print(":");
      if (s < 10) lcd.print("0");
      lcd.print(s);
    }
  }

  lcd.setCursor(0, 1);
  if (alarmTriggered) {
    String name = (currentSlot == 1) ? "M " : (currentSlot == 2) ? "N " : "E ";
    lcd.print(name + "TAKE NOW!");
  } else {
    lcd.print("M:");
    lcd.print(morningResult == 1 ? "v " : morningResult == 0 ? "x " : "- ");
    lcd.print("N:");
    lcd.print(noonResult == 1 ? "v " : noonResult == 0 ? "x " : "- ");
    lcd.print("E:");
    lcd.print(eveningResult == 1 ? "v" : eveningResult == 0 ? "x" : "-");
  }
}