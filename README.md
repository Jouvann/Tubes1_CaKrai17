# Tubes1_CaKrai17

Jadi Implementasi Fungsi" file header fsm.hpp dibuat di file fsm.cpp
Terus dijalankan melalui file main.cpp
Akhirnya ada Makefile buat menjalankan semua file diatas jadi file executable

Cara Menjalankan Program:
make = membangun file objek header, implementasi, dan main file (.o) yang disatukan jadi file 'fsm_test'
./fsm_test = menjalankan file 'fsm_test' untuk menguji program
make clean = menghapus semua file yang ber ekstensi .o dari directory

Sebenernya masih ada beberapa cout yang looping 2 kali sewaktu dipanggil fungsinya, dan aku tidak mengerti kenapa itu bisa terjadi. Tapi oh well, kayanya sudah works 95%, jadi okelah.

Jujur bingung menjelaskan implementasi yang dimaksud harus jelasin pake bahasa indonesia step by step tiap fungsi kah???
Anyway dibawah ringkasan komentar saya pada pengerjaan implementasi file fsm.cpp

//Implementasi dari fungsi millis()
//Mengembalikan waktu saat ini dalam milidetik sejak program dimulai
uint32_t millis() {}

//Fungsi untuk mengubah SystemState menjadi string
//Digunakan untuk mencetak nama state dalam fungsi printStatus() dan printStateHistory()
string stateToString(SystemState state) {}

//Implementasi dari konstruktor FSM default
//Menginisialisasi currentState, lastHeartbeat, errorCount, delay, moveCount = 0,
//dan menginisialisasi vektor stateHistory kosong
FSM::FSM() {}

//Implementasi dari konstruktor FSM dengan parameter delay
//Menginisialisasi currentState, lastHeartbeat, errorCount, moveCount = 0,
//delay (punya class) =  delay (parameter),
//dan menginisialisasi vektor stateHistory kosong
FSM::FSM(uint32_t delay) {}

//Implementasi dari destruktor FSM
//Menghapus semua elemen dari vektor stateHistory
//Catatan: C++ akan secara otomatis menghapus vektor ketika objek FSM dihancurkan
FSM::~FSM() {}

//Implementasi dari fungsi getCurrentState
//Mengembalikan currentState dari FSM
SystemState FSM::getCurrentState() const {}

//Implementasi dari fungsi transitionToState(SystemState newState)
//Meng update currentState ke newState
//dan mengupdate lastHeartbeat ke waktu saat ini dalam milidetik
void FSM::transitionToState(SystemState newState) {}

//Implementasi dari fungsi setDelay(uint32_t delay)
//Mengatur delay dari FSM ke nilai yang diberikan parameter
void FSM::setDelay(uint32_t delay) {}

//Implementasi dari fungsi getDelay(uint32_t &delay) const
//Mengambil nilai delay dari FSM dan menyimpannya ke variabel yang diberikan sebagai parameter
void FSM::getDelay(uint32_t &delay) const{}

//Implementasi dari fungsi setErrorCount(int count)
//Mengatur errorCount dari FSM ke nilai yang diberikan parameter
void FSM::setErrorCount(int count){}

//Implementasi dari fungsi getErrorCount() const
//Mengembalikan nilai errorCount dari FSM
int FSM::getErrorCount() const{}

//Implementasi dari fungsi setMoveCount(int count)
//Mengatur moveCount dari FSM ke nilai yang diberikan parameter
void FSM::setMoveCount(int count){}

//Implementasi dari fungsi getMoveCount() const
//Mengembalikan nilai moveCount dari FSM
int FSM::getMoveCount() const{}

//Implementasi dari fungsi addStateToHistory(SystemState state, uint32_t time)
//Menambahkan pasangan state dan waktu ke vektor stateHistory
void FSM::addStateToHistory(SystemState state, uint32_t time){}

//Implementasi dari fungsi getStateHistory() const
//Mengembalikan salinan dari vektor stateHistory
vector<pair<SystemState, uint32_t>> FSM::getStateHistory() const{}

//Implementasi dari fungsi getLastHeartbeat() const
//Mengembalikan nilai lastHeartbeat dari FSM
uint32_t FSM::getLastHeartbeat() const{}

//Implementasi dari fungsi setLastHeartbeat(uint32_t heartbeat)
//Mengatur nilai lastHeartbeat dari FSM ke nilai yang diberikan parameter
void FSM::setLastHeartbeat(uint32_t heartbeat){}

//Implementasi dari fungsi start()
//Memulai FSM dengan menjalankan loop sampai currentState menjadi STOPPED
//Loop ini memeriksa currentState setiap 1000 milidetik, dan memanggil fungsi update() 
void FSM::start(){}


//Implementasi dari fungsi update()
//Memeriksa currentState dan memanggil fungsi yang sesuai berdasarkan state tersebut
// - Jika currentState adalah INIT, panggil performInit()
// - Jika currentState adalah IDLE, panggil performProcess()
// - Jika currentState adalah MOVEMENT, panggil performMovement()
// - Jika currentState adalah SHOOTING, panggil performShooting()
// - Jika currentState adalah CALCULATION, panggil performCalculation()
// - Jika currentState adalah ERROR, panggil performErrorHandling()
// - Jika currentState adalah STOPPED, panggil shutdown()
//Setelah memanggil fungsi yang sesuai, update lastHeartbeat dengan waktu saat ini dalam milidetik
//Dan tambahkan pasangan currentState dan lastHeartbeat ke vektor stateHistory
void FSM::update(){}


//Implementasi dari fungsi printStatus()
//Mencetak status saat ini dari FSM, termasuk currentState, lastHeartbeat, delay, dan errorCount
void FSM::printStatus(){}

//Implementasi dari fungsi printStateHistory()
//Mencetak riwayat state dari FSM, menunjukkan setiap state dan waktu saat state tersebut dari vektor stateHistory
void FSM::printStateHistory(){}

//Implementasi dari fungsi performInit()
//Mengatur currentState ke IDLE, mengatur delay jadi 1000ms dan mengatur lastHeartbeat ke waktu saat ini dalam milidetik.
// Mencetak "Initializing system..." dan memanggil printStatus() untuk menampilkan status awal FSM.
void FSM::performInit(){}


//Implementasi dari fungsi performProcess()
//Fungsi ini dipanggil ketika FSM berada dalam state IDLE.
//Fungsi ini menampilkan menu untuk memilih aksi yang dapat dilakukan:
// - Menampilkan status dan riwayat state (IDLE)
// - Melakukan pergerakan (MOVEMENT)
// - Melakukan penembakan (SHOOTING)
// - Melakukan perhitungan (CALCULATION)
//Pengguna diminta untuk memilih aksi dengan memasukkan angka sesuai pilihan.
void FSM::performProcess(){}


//Implementasi dari fungsi performMovement()
//Fungsi ini dipanggil ketika FSM berada dalam state MOVEMENT.
//Jika sudah melakukan 3 pergerakan, FSM akan beralih ke state SHOOTING.
//Jika belum, FSM akan kembali ke state IDLE.
void FSM::performMovement(){}

//Implementasi dari fungsi performShooting()
//Fungsi ini dipanggil ketika FSM berada dalam state SHOOTING.
//Mencetak "Shooting...", mengatur moveCount ke 0, dan beralih ke state IDLE.
//Juga mengupdate lastHeartbeat ke waktu saat ini dalam milidetik.
void FSM::performShooting(){}

//Implementasi dari fungsi performCalculation()
//Fungsi ini dipanggil ketika FSM berada dalam state CALCULATION.
//Mencetak "Performing calculation..."
//Jika moveCount adalah 0, FSM akan beralih ke state ERROR.
//Jika moveCount lebih dari 0, FSM akan kembali ke state IDLE.
void FSM::performCalculation(){}

 
//Implementasi dari fungsi performErrorHandling()
//Fungsi ini dipanggil ketika FSM berada dalam state ERROR.
// Mencetak "Error occurred, performing error handling..."
//Menginkrementasi errorCount, jika errorCount melebihi 3, FSM akan beralih ke state STOPPED.
//Jika tidak, FSM akan kembali ke state IDLE.
void FSM::performErrorHandling(){}

//Implementasi dari fungsi shutdown()
//Fungsi ini dipanggil ketika FSM berada dalam state STOPPED.
// Mencetak "System stopped, shutting down..." dan menghapus semua elemen dari vektor stateHistory.
void FSM::shutdown(){}