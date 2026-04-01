# Smart Medication Box
### Smart Medication Reminder System Based on ESP32 and Reed Switch

---

## 📌 Project Overview
This project develops an IoT-based smart medication box designed to improve medication adherence.  
By integrating a reed switch sensor, RTC module, and ESP32, the system can provide scheduled reminders and detect whether the pill box has been opened.

---

## 🎯 Problem Statement
Medication non-adherence is a common issue, especially among elderly patients.

Current solutions such as alarms or mobile apps:
- Only provide reminders  
- Cannot verify if medication is actually taken  

👉 Therefore, a system with **sensing capability** is required.

---

## 💡 Proposed Solution
We propose a smart medication box that:

- Uses a **reed switch sensor** to detect lid opening  
- Provides **real-time alerts** using LED and buzzer  
- Uses **ESP32** for control and processing  
- Integrates an **RTC module** for scheduled reminders  

---

## ⚙️ System Features

- ⏰ Scheduled medication reminder  
- 🔔 Buzzer alert  
- 💡 LED notification  
- 📦 Lid-opening detection (Reed Switch)  
- ✅ Automatic stop alert after detection  
- 📊 Basic medication behavior monitoring  

---

## 🏗️ System Architecture

### IoT Layer
- ESP32  
- Reed Switch  
- RTC Module  
- LED & Buzzer  

### Fog Layer
- Local processing on ESP32  
- Real-time decision making  

### Cloud Layer (Future Work)
- Data storage  
- Remote monitoring  

---

## 🔄 System Workflow

1. RTC tracks current time  
2. At scheduled time → system triggers alert  
3. User opens the pill box  
4. Reed switch detects lid opening  
5. System confirms medication action  
6. Alert stops and event is recorded  

---

## 🔧 Hardware Components

- ESP32  
- Reed Switch Module  
- Magnet  
- RTC DS3231  
- LED  
- Buzzer  
- Breadboard  
- Jumper wires  
- Pill box  

---

## 💰 Bill of Materials (BOM)

| Item | Component | Quantity | Cost (NTD) |
|------|----------|----------|------------|
| 1 | ESP32 | 1 | 150 |
| 2 | Reed Switch | 1 | 20 |
| 3 | Magnet | 1 | 10 |
| 4 | RTC DS3231 | 1 | 80 |
| 5 | Buzzer | 1 | 20 |
| 6 | LED | 2 | 10 |
| 7 | Breadboard | 1 | 50 |
| 8 | Jumper wires | 1 set | 50 |
| 9 | Pill box | 1 | 100 |
| 10 | USB cable | 1 | 50 |

**Total Cost: ~540 NTD**

---

## 📅 Gantt Chart (Project Timeline)

| Week | Task |
|------|------|
| Week 1 | Topic brainstorming |
| Week 2 | Problem definition |
| Week 3 | System design |
| Week 4 | Proposal & BOM |
| Week 5 | Component purchase |
| Week 6 | ESP32 & RTC testing |
| Week 7 | Reed switch testing |
| Week 8 | Alert system integration |
| Week 9 | Hardware assembly |
| Week 10 | System integration |
| Week 11 | GitHub documentation |
| Week 12 | Final presentation |

---

## 👥 Team Members & Roles

### Member A – Project Manager
- Project planning and scheduling  
- Manage GitHub repository  
- Prepare Gantt chart  

### Member B – Hardware Engineer
- ESP32 wiring  
- Reed switch installation  
- Hardware assembly  

### Member C – Software Engineer
- ESP32 programming  
- RTC and sensor logic  
- Alert control  

### Member D – System Architect
- IoT system design  
- Data flow and workflow  
- Architecture design  

### Member E – Documentation
- Proposal writing  
- GitHub documentation  
- Meeting records  

---

## 📈 Development Progress

- Week 1: Brainstorming ideas  
- Week 2: Topic selection (Smart Medication Box)  
- Week 3: System architecture design  
- Week 4: Proposal and BOM preparation  

---

## 📝 Meeting Records

### Meeting 1
- Topic: Project brainstorming  
- Decision: Choose smart medication box  

### Meeting 2
- Topic: Hardware selection  
- Decision: Use ESP32 and reed switch  

---

## 🚀 Future Work

- Cloud database integration  
- Mobile app / LINE notification  
- Weight sensor for pill detection  
- AI-based behavior prediction  

---

## 📌 Conclusion

This project presents a low-cost IoT-based smart medication box with sensing capability.  
By integrating a reed switch sensor, the system can detect user behavior and improve medication adherence.

---
