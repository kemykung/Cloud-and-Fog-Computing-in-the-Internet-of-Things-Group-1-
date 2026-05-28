# 💊 Smart Pill Box

### IoT Medication Reminder & Remote Monitoring System

An ESP32-based smart medication box designed to support medication reminders, lid-opening detection, cloud data upload, dashboard visualization, and caregiver-side monitoring.

<p align="center">
  <b>ESP32 ｜ DS3231 RTC ｜ Reed Switch ｜ ThingSpeak ｜ GitHub Pages ｜ Figma App ｜ Wix Website</b>
</p>

---

## 🔗 Project Links

| Item                    | Link                                                                                   |
| ----------------------- | -------------------------------------------------------------------------------------- |
| 🌐 Project Website      | https://xoxowendy61.wixsite.com/my-site                                                |
| 📊 Live Dashboard       | https://kemykung.github.io/Cloud-and-Fog-Computing-in-the-Internet-of-Things-Group-1-/ |
| 🧑‍💻 GitHub Repository | https://github.com/kemykung/Cloud-and-Fog-Computing-in-the-Internet-of-Things-Group-1- |
| 📱 App Prototype        | Please add the Figma prototype link here                                               |

---

## 📌 Project Overview

The **Smart Pill Box** is an IoT-based medication reminder system designed to improve medication adherence.

The system uses an **ESP32** as the main controller, a **DS3231 RTC module** for medication scheduling, a **reed switch** for lid-opening detection, and **LED/buzzer reminders** for real-time alerts.

After each medication event, the ESP32 uploads the medication record to **ThingSpeak** through Wi-Fi. The web dashboard then visualizes medication completion rate, response delay, daily intake, and recent medication behavior.

In addition to the hardware prototype, this project also includes:

* 🌐 **Wix Website** — project introduction and demonstration
* 📊 **GitHub Pages Dashboard** — medication data visualization
* 📱 **Figma App Prototype** — mobile interface for users and caregivers
* 🧑‍💻 **GitHub Repository** — source code and technical documentation

---

## 💡 Motivation

Medication non-adherence is a common issue, especially for elderly users or users who need to take multiple medications every day.

Traditional pillboxes and alarm-based reminders still have several limitations:

| Problem                      | Description                                              |
| ---------------------------- | -------------------------------------------------------- |
| ⏰ Forgetting medication      | Users may forget to take medicine on time                |
| 🔁 Repeated dosage           | Users may accidentally take the same medicine again      |
| 👨‍👩‍👧 Lack of remote care | Family members cannot remotely confirm medication status |
| 📝 No medication records     | Traditional pillboxes do not store usage history         |
| 📉 Hard to track behavior    | Long-term adherence is difficult to analyze without data |

Therefore, this project aims to build a **low-cost IoT medication reminder system** that not only reminds users, but also records medication behavior and supports remote monitoring.

---

## ✅ Proposed Solution

The Smart Pill Box integrates **hardware sensing**, **local decision-making**, **cloud data storage**, and **user-side visualization**.

Main functions include:

* ⏱️ Scheduled medication reminder using **DS3231 RTC**
* 🔔 LED and buzzer alerts when medication time arrives
* 📦 Lid-opening detection using **reed switch + magnet**
* ⚙️ Local event processing on **ESP32**
* ☁️ Medication record upload to **ThingSpeak**
* 📊 Dashboard for adherence monitoring
* 📱 App prototype for user-side and caregiver-side medication management
* 🌐 Wix website for project introduction and demonstration

---

## 🧩 System Architecture

> 🖼️ **Image to add:** `assets/system_architecture.png`
> Suggested content: ESP32 → ThingSpeak → GitHub Pages Dashboard / Figma App / Caregiver Monitoring.

The system is divided into four layers:

```text
Hardware Layer
ESP32 + RTC + Reed Switch + LED + Buzzer
        ↓
Edge / Fog Layer
Local reminder control and medication event processing
        ↓
Cloud Layer
ThingSpeak data upload and storage
        ↓
Application Layer
Dashboard, App Prototype, Wix Website
```

### 1. 📦 Hardware Layer

| Component            | Purpose                                    |
| -------------------- | ------------------------------------------ |
| ESP32                | Main controller and Wi-Fi communication    |
| DS3231 RTC           | Tracks real-time medication schedule       |
| Reed Switch + Magnet | Detects whether the pill box lid is opened |
| LED                  | Provides visual medication reminder        |
| Buzzer               | Provides audio medication reminder         |
| Pill Box             | Physical medication container              |

### 2. ⚙️ Edge / Fog Layer

The ESP32 performs local decision-making before uploading data to the cloud.

Main tasks include:

* Checking whether the current time matches the medication schedule
* Activating LED and buzzer reminders
* Detecting lid-opening events
* Determining medication status: **Taken** or **Missed**
* Calculating response delay
* Uploading structured medication records to ThingSpeak

This design allows the device to respond immediately even before cloud visualization is updated.

### 3. ☁️ Cloud Layer

ThingSpeak is used as the cloud data platform.

| Field   | Meaning                    | Value Example                                              |
| ------- | -------------------------- | ---------------------------------------------------------- |
| Field 1 | Medication result          | `1 = Taken`, `0 = Missed`                                  |
| Field 2 | Daily completed dose count | `0–3`                                                      |
| Field 3 | Response delay             | Seconds                                                    |
| Field 4 | Medication time slot       | `1 = Morning`, `2 = Afternoon`, `3 = Evening`, `4 = Night` |

### 4. 📱 Application Layer

| Interface                 | Role                                          |
| ------------------------- | --------------------------------------------- |
| 🌐 Wix Website            | Project landing page and product introduction |
| 📊 GitHub Pages Dashboard | Medication data visualization                 |
| 📱 Figma App Prototype    | User-side medication management interface     |
| 🧑‍💻 GitHub Repository   | Technical documentation and source code       |

---

## 🔄 System Workflow

> 🖼️ **Image to add:** `assets/demo_flow.png`
> Suggested content: medication reminder → lid opening → ThingSpeak upload → dashboard update.

```text
1. RTC checks medication time
        ↓
2. ESP32 activates LED and buzzer
        ↓
3. User opens the pill box
        ↓
4. Reed switch detects lid opening
        ↓
5. ESP32 records Taken / Missed
        ↓
6. Data is uploaded to ThingSpeak
        ↓
7. Dashboard visualizes medication behavior
        ↓
8. App prototype presents user and caregiver interaction
```

### Event Logic

| Status      | Condition                                                       |
| ----------- | --------------------------------------------------------------- |
| ✅ Taken     | User opens the pill box within the expected time window         |
| ❌ Missed    | User does not open the pill box within the expected time window |
| 🟡 Delayed  | User opens the pill box later than expected                     |
| 🔵 Upcoming | Medication time has not arrived yet                             |

---

## 📦 Hardware Design

> 🖼️ **Image to add:** `assets/circuit_diagram.png`
> Suggested content: ESP32 connected to DS3231 RTC, reed switch, LED, and buzzer.

### Hardware Components

| No. |               Component | Quantity | Purpose                          |
| --- | ----------------------: | -------: | -------------------------------- |
| 1   | ESP32 Development Board |        1 | Main controller and Wi-Fi upload |
| 2   |      Reed Switch Module |        1 | Lid-opening detection            |
| 3   |                  Magnet |        1 | Works with reed switch           |
| 4   |              RTC DS3231 |        1 | Real-time medication schedule    |
| 5   |                  Buzzer |        1 | Audio reminder                   |
| 6   |                     LED |      1–2 | Visual reminder                  |
| 7   |              Breadboard |        1 | Prototype wiring                 |
| 8   |            Jumper Wires |    1 set | Circuit connection               |
| 9   |                Pill Box |        1 | Medication storage               |
| 10  |               USB Cable |        1 | Power and programming            |

### Suggested Pin Configuration

| Component          | ESP32 Pin | Description                         |
| ------------------ | --------- | ----------------------------------- |
| Reed Switch Signal | GPIO 27   | Detects lid state                   |
| LED                | GPIO 26   | Medication reminder indicator       |
| Buzzer             | GPIO 25   | Audio reminder                      |
| DS3231 SDA         | GPIO 21   | I2C data                            |
| DS3231 SCL         | GPIO 22   | I2C clock                           |
| DS3231 VCC         | 3.3V / 5V | Depends on RTC module specification |
| DS3231 GND         | GND       | Common ground required              |

---

## 🛠️ Hardware Prototype

> 🖼️ **Image to add:** `assets/prototype_photo.jpg`
> Suggested content: real photo of the smart pill box, ESP32 board, wiring, reed switch, LED, and buzzer.

The prototype uses a **reed switch and magnet** to detect whether the pill box lid has been opened.

When the scheduled medication time arrives, the ESP32 activates the LED and buzzer. If the user opens the pill box, the system records the medication as taken and uploads the event to ThingSpeak.

---

## ☁️ Cloud Data Upload

The ESP32 uploads medication records to ThingSpeak through HTTP requests.

Each medication event includes:

| ThingSpeak Field | Data Name      | Description                           | Example                                                    |
| ---------------- | -------------- | ------------------------------------- | ---------------------------------------------------------- |
| Field 1          | Result         | Whether the medication was completed  | `1 = Taken`, `0 = Missed`                                  |
| Field 2          | Today Score    | Number of completed doses today       | `0–3`                                                      |
| Field 3          | Response Delay | Time between reminder and lid opening | `35` seconds                                               |
| Field 4          | Time Slot      | Medication time period                | `1 = Morning`, `2 = Afternoon`, `3 = Evening`, `4 = Night` |

Example upload format:

```text
https://api.thingspeak.com/update?api_key=YOUR_WRITE_API_KEY&field1=1&field2=1&field3=35&field4=1
```

This means:

| Field  | Value | Meaning                                       |
| ------ | ----: | --------------------------------------------- |
| field1 |     1 | Medication was taken                          |
| field2 |     1 | One dose completed today                      |
| field3 |    35 | User opened the box 35 seconds after reminder |
| field4 |     1 | Morning medication slot                       |

---

## 📊 Dashboard Design

> 🖼️ **Image to add:** `assets/dashboard_screenshot.png`
> Suggested content: screenshot of the GitHub Pages dashboard.

The dashboard is used to visualize medication data retrieved from ThingSpeak.

Main dashboard metrics include:

| Metric                   | Meaning                                                                  |
| ------------------------ | ------------------------------------------------------------------------ |
| 📈 7-Day Completion Rate | Completed doses / scheduled doses within the latest 7 days               |
| 💊 7-Day Doses Taken     | Number of `Taken` medication events within the latest 7 days             |
| ⏱️ Avg Response Time     | Average delay between reminder time and lid opening                      |
| ⭐ Adherence Score        | Overall medication behavior score based on completion and response delay |
| 🧾 Recent Records        | Latest medication events grouped by time slot and status                 |

The dashboard helps convert raw IoT sensor data into clear medication behavior indicators.

---

## 📱 Mobile App Prototype

> 🖼️ **Image to add:** `assets/app_prototype.png`
> Suggested content: exported screenshot of the Figma app prototype.

The mobile app prototype is designed as the user-side interface of the Smart Pill Box system.

It demonstrates how users and caregivers can interact with the medication reminder system in a real-life scenario.

### App Pages

| Page                   | Function                                                       |
| ---------------------- | -------------------------------------------------------------- |
| 🔐 Login               | Account sign-in and user identity setup                        |
| 🏠 Home                | Today’s schedule, next dose, weekly adherence                  |
| 🔔 Reminder            | Medication reminder, dose information, Taken / Snooze action   |
| 📅 Medication Schedule | Daily medication list by time slot                             |
| ➕ Add Medicine         | Add medicine name, dosage, frequency, reminder time, and notes |
| 🕘 History             | View medication records: Taken, Missed, Delayed, Upcoming      |
| 👥 Caregiver           | Manage caregivers and send missed-dose alerts                  |
| ⚙️ Profile & Settings  | Reminder preferences, device connection, language, privacy     |

The app prototype connects the IoT system with actual user scenarios. ESP32 and ThingSpeak handle data collection and cloud storage, while the app presents medication status in a clear and user-friendly way.

---

## 🌐 Website Design

> 🖼️ **Image to add:** `assets/wix_website_screenshot.png`
> Suggested content: screenshot of the Wix project website.

The Wix website works as the project landing page.

It introduces:

* 💡 Project motivation
* 💊 Smart pill box features
* 🔄 IoT system workflow
* 🎬 Demo video
* 🧑‍💻 GitHub repository
* 👥 Team members

The website helps viewers quickly understand what the project is, why it is needed, and how the system works.

---

## 🗂️ Repository Structure

```text
Cloud-and-Fog-Computing-in-the-Internet-of-Things-Group-1-
│
├── README.md
├── index.html
│
├── arduino/
│   └── smart_pill_box.ino
│
├── docs/
│   ├── HARDWARE_SETUP_GUIDE.md
│   ├── SOFTWARE_SETUP_GUIDE.md
│   ├── SYSTEM_WORKFLOW.md
│   ├── WEB_AND_APP_INTERFACE.md
│   ├── USER_GUIDE.md
│   └── TEAM_AND_PROGRESS.md
│
├── assets/
│   ├── system_architecture.png
│   ├── circuit_diagram.png
│   ├── prototype_photo.jpg
│   ├── dashboard_screenshot.png
│   ├── app_prototype.png
│   ├── wix_website_screenshot.png
│   ├── thingspeak_channel.png
│   └── demo_flow.png
│
└── data/
    └── sample_thingspeak_data.csv
```

---

## 👥 Team Members & Roles

| Member | Student ID | Role                                 | Responsibility                                                |
| ------ | ---------- | ------------------------------------ | ------------------------------------------------------------- |
| 鄭羽喬    | M11451023  | Project Coordination / Documentation | GitHub organization, project explanation, report integration  |
| 蕭詠蒨    | M11451033  | Website / Interface Design           | Wix website, visual presentation, app interface support       |
| 鄭矞心    | M11451016  | Hardware Integration                 | ESP32 wiring, reed switch, RTC, LED, buzzer testing           |
| 龔倢     | M11451018  | Cloud & Dashboard                    | ThingSpeak setup, dashboard data mapping, data upload testing |
| 劉芸廷    | M11451020  | Demo / Final Presentation            | Demo video, project flow explanation, presentation material   |

> Please adjust the role descriptions based on the actual team division before final submission.

---

## 📅 Development Progress

| Week    | Task                                 | Status                     |
| ------- | ------------------------------------ | -------------------------- |
| Week 1  | Topic brainstorming                  | ✅ Completed                |
| Week 2  | Problem definition                   | ✅ Completed                |
| Week 3  | System architecture design           | ✅ Completed                |
| Week 4  | Proposal and BOM preparation         | ✅ Completed                |
| Week 5  | Component preparation                | 🟡 Completed / In progress |
| Week 6  | ESP32 and RTC testing                | 🟡 In progress             |
| Week 7  | Reed switch and reminder testing     | 🟡 In progress             |
| Week 8  | ThingSpeak upload testing            | 🟡 In progress             |
| Week 9  | Dashboard integration                | 🟡 In progress             |
| Week 10 | App prototype and website refinement | 🟡 In progress             |
| Week 11 | GitHub documentation                 | 🟡 In progress             |
| Week 12 | Final demo and presentation          | 🔵 Planned                 |

---

## 🔍 Comparison With Existing Smart Pill Box Projects

Some existing smart pill box projects use ESP32, RTC modules, sensors, buzzers, LCD displays, and mobile platforms such as Blynk to provide medication reminders and app notifications.

Compared with these projects, our system focuses on integrating multiple layers of an IoT service:

| Aspect             | Existing Smart Pill Box Projects   | Our Project                                                 |
| ------------------ | ---------------------------------- | ----------------------------------------------------------- |
| Controller         | ESP32 / Arduino                    | ESP32                                                       |
| Time Scheduling    | RTC module                         | DS3231 RTC                                                  |
| Lid Detection      | Hall sensor / reed switch          | Reed switch + magnet                                        |
| Alert Method       | LED, buzzer, LCD, app notification | LED, buzzer, dashboard, app prototype                       |
| Cloud Platform     | Blynk or other IoT platforms       | ThingSpeak                                                  |
| Data Visualization | App-based display                  | GitHub Pages Dashboard                                      |
| Project Website    | Usually not included               | Wix project website                                         |
| Mobile UI          | Existing IoT app or simple app     | Figma app prototype                                         |
| Documentation      | Hardware and software guides       | GitHub README, dashboard, app, website, and system workflow |

Our project does not only focus on the hardware reminder function. It also presents a complete IoT flow from sensing and cloud upload to dashboard visualization and user-side interface design.

---

## 🚀 Future Work

Future improvements include:

* 🔗 Connect the physical prototype with real ThingSpeak data upload
* ⚖️ Improve medication detection accuracy with additional sensors, such as a weight sensor or multiple lid sensors
* 👥 Add caregiver notification through mobile app, email, or cloud trigger
* 📊 Improve dashboard design for long-term medication behavior analysis
* 📦 Extend the system to support multiple medication compartments
* 🔋 Add device connection status, battery status, and Wi-Fi status
* 🧪 Conduct usability testing with target users or caregivers
* 📱 Integrate the app prototype with real backend data in the future

---

## 🎯 Conclusion

This project presents a low-cost IoT-based Smart Pill Box system.

By combining **ESP32**, **RTC scheduling**, **reed switch detection**, **ThingSpeak cloud upload**, **dashboard visualization**, **Wix project website**, and **Figma app prototype design**, the system supports not only local medication reminders but also medication behavior monitoring and remote care scenarios.

The project demonstrates a complete IoT application flow from **device sensing** to **cloud data management** and **user-centered interface design**.
<img width="589" height="276" alt="image" src="https://github.com/user-attachments/assets/644ffa65-55e8-4813-8f58-9d451184f0e4" />
