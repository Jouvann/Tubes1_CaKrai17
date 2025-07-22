# Tubes1_CaKrai17 - Simulasi Finite State Machine (FSM)

## 📌 Deskripsi Proyek

Proyek ini merupakan simulasi sistem **Finite State Machine (FSM)** berbasis C++ yang diimplementasikan menggunakan prinsip **Object-Oriented Programming (OOP)**.  
FSM ini mensimulasikan alur logika dari sebuah sistem robotik yang memiliki beberapa state seperti:

- `INIT`
- `IDLE`
- `MOVEMENT`
- `SHOOTING`
- `CALCULATION`
- `ERROR`
- `STOPPED`

---

## 🛠️ File & Struktur Proyek

```text
├── fsm.hpp         # Header file berisi deklarasi class FSM
├── fsm.cpp         # Implementasi fungsi-fungsi dari class FSM
├── main.cpp        # File utama untuk menjalankan FSM
├── Makefile        # Otomatisasi build
├── README.md       # Penjelasan proyek (file ini)
└── .gitignore      # Daftar file yang tidak dilacak git
```

---

## ▶️ Cara Menjalankan Program

### 1. Compile program:
```bash
make
```

### 2. Jalankan executable:
```bash
./fsm_test
```

### 3. Bersihkan file build (.o):
```bash
make clean
```

---

## ✨ Fitur Utama

- Transisi antar state berbasis waktu (heartbeat)
- Antarmuka terminal untuk input pengguna
- Pelacakan riwayat state dan waktu transisi
- Penanganan error otomatis dan shutdown saat kesalahan melebihi batas
- Desain modular dan terpisah antar file (`.hpp`, `.cpp`, `main.cpp`)

---

## 🔧 Ringkasan Implementasi

Implementasi dilakukan di file `fsm.cpp`, berdasarkan spesifikasi fungsi di `fsm.hpp`.  
Desain menggunakan prinsip OOP seperti:

- **Encapsulation**: semua atribut class disembunyikan dengan `private`
- **Constructor dan Destructor**: mengatur inisialisasi dan pembersihan objek
- **Modularisasi**: logika dibagi ke fungsi-fungsi terpisah sesuai state

Untuk setiap state, terdapat fungsi `performX()` masing-masing seperti:
- `performInit()`, `performProcess()`, `performMovement()`, dst.

Loop utama ada di `start()` dan `update()`, yang berjalan sampai state menjadi `STOPPED`.

> ⚠️ **Catatan**: Masih terdapat beberapa `cout` yang muncul dua kali saat program berjalan — kemungkinan karena duplikasi panggilan fungsi, tapi secara keseluruhan program berfungsi dengan baik.

---

## 📌 Contoh Output Terminal

```bash
Initializing system...
=========FSM Status=========
Current State  : IDLE
Last Heartbeat : 2000 ms
Delay          : 1000 ms
Error Count    : 0
===========================
============Menu============
Ready for commands. Choose an action:
1. IDLE - Display status and state history
2. MOVEMENT - Move the robot
3. SHOOTING - Shoot the robot
4. CALCULATION - Perform calculations
```

---

## 🧑‍💻 Author

- **Nama**: Jouvann  
- **Kru**: CaKrai17  
- **Topik**: Tugas Besar Milestone 1 - Implementasi FSM dengan C++ dan OOP

---

![Last Commit](https://img.shields.io/github/last-commit/Jouvann/Tubes1_CaKrai17)
