#include "fsm.hpp"


//Implementasi dari fungsi millis()
//Mengembalikan waktu saat ini dalam milidetik sejak program dimulai
uint32_t millis(){
    using namespace std::chrono;
    static auto start = steady_clock::now();
    auto now = steady_clock::now();
    return duration_cast<milliseconds>(now - start).count();
}

//Fungsi untuk mengubah SystemState menjadi string
//Digunakan untuk mencetak nama state dalam fungsi printStatus() dan printStateHistory()
string stateToString(SystemState state){
    switch (state){
        case SystemState::INIT : return "INIT";
        case SystemState::IDLE : return "IDLE";
        case SystemState::MOVEMENT : return "MOVEMENT";
        case SystemState::SHOOTING : return "SHOOTING";
        case SystemState::CALCULATION : return "CALCULATION";
        case SystemState::ERROR : return "ERROR";
        case SystemState::STOPPED : return "STOPPED";
        default : return "UNKNOWN";
    }
}

//Implementasi dari konstruktor FSM default
//Menginisialisasi currentState, lastHeartbeat, errorCount, delay, moveCount = 0,
//dan menginisialisasi vektor stateHistory kosong
FSM::FSM(){
    currentState = SystemState::INIT;
    lastHeartbeat = 0;
    delay = 0;
    errorCount = 0;
    moveCount = 0;
    stateHistory = {};
}

//Implementasi dari konstruktor FSM dengan parameter delay
//Menginisialisasi currentState, lastHeartbeat, errorCount, moveCount = 0,
//delay (punya class) =  delay (parameter),
//dan menginisialisasi vektor stateHistory kosong
FSM::FSM(uint32_t delay){
    currentState = SystemState::INIT;
    lastHeartbeat = 0;
    this->delay = delay;
    errorCount = 0;
    moveCount = 0;
    stateHistory = {};
}

//Implementasi dari destruktor FSM
//Menghapus semua elemen dari vektor stateHistory
//Catatan: C++ akan secara otomatis menghapus vektor ketika objek FSM dihancurkan
FSM::~FSM(){
    stateHistory.clear();
}

//Implementasi dari fungsi getCurrentState
//Mengembalikan currentState dari FSM
SystemState FSM::getCurrentState() const{
    return currentState;
}

//Implementasi dari fungsi transitionToState(SystemState newState)
//Meng update currentState ke newState
//dan mengupdate lastHeartbeat ke waktu saat ini dalam milidetik
void FSM::transitionToState(SystemState newState){
    currentState = newState;
    lastHeartbeat = millis();
}

//Implementasi dari fungsi setDelay(uint32_t delay)
//Mengatur delay dari FSM ke nilai yang diberikan parameter
void FSM::setDelay(uint32_t delay) {
    this->delay = delay; 
}

//Implementasi dari fungsi getDelay(uint32_t &delay) const
//Mengambil nilai delay dari FSM dan menyimpannya ke variabel yang diberikan sebagai parameter
void FSM::getDelay(uint32_t &delay) const{
    delay = this->delay;
}

//Implementasi dari fungsi setErrorCount(int count)
//Mengatur errorCount dari FSM ke nilai yang diberikan parameter
void FSM::setErrorCount(int count){
    errorCount = count;
}

//Implementasi dari fungsi getErrorCount() const
//Mengembalikan nilai errorCount dari FSM
int FSM::getErrorCount() const{
    return errorCount;
}

//Implementasi dari fungsi setMoveCount(int count)
//Mengatur moveCount dari FSM ke nilai yang diberikan parameter
void FSM::setMoveCount(int count){
    moveCount = count;
}

//Implementasi dari fungsi getMoveCount() const
//Mengembalikan nilai moveCount dari FSM
int FSM::getMoveCount() const{
    return moveCount;
}

//Implementasi dari fungsi addStateToHistory(SystemState state, uint32_t time)
//Menambahkan pasangan state dan waktu ke vektor stateHistory
void FSM::addStateToHistory(SystemState state, uint32_t time){
    stateHistory.push_back({state, time});
}

//Implementasi dari fungsi getStateHistory() const
//Mengembalikan salinan dari vektor stateHistory
vector<pair<SystemState, uint32_t>> FSM::getStateHistory() const{
    return stateHistory;
}

//Implementasi dari fungsi getLastHeartbeat() const
//Mengembalikan nilai lastHeartbeat dari FSM
uint32_t FSM::getLastHeartbeat() const{
    return lastHeartbeat;
}

//Implementasi dari fungsi setLastHeartbeat(uint32_t heartbeat)
//Mengatur nilai lastHeartbeat dari FSM ke nilai yang diberikan parameter
void FSM::setLastHeartbeat(uint32_t heartbeat){
    lastHeartbeat = heartbeat;
}

//Implementasi dari fungsi start()
//Memulai FSM dengan menjalankan loop sampai currentState menjadi STOPPED
//Loop ini memeriksa currentState setiap 1000 milidetik, dan memanggil fungsi update() 
void FSM::start(){
    while (currentState != SystemState::STOPPED){
        uint32_t currentTime = millis();

        if (currentTime - lastHeartbeat >= delay){
            update();
        }
    }
}


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
void FSM::update(){
    switch (currentState) {
        case SystemState::INIT:
            performInit();
            break;
        case SystemState::IDLE:
            performProcess();
            break; 
        case SystemState::MOVEMENT:
            performMovement();
            break;
        case SystemState::SHOOTING:
            performShooting();
            break;
        case SystemState::CALCULATION:
            performCalculation();
            break;
        case SystemState::ERROR:
            performErrorHandling();
            break;
        case SystemState::STOPPED:
            shutdown();
            break;
    }
    // Update last heartbeat time
    lastHeartbeat = millis();
    // Add current state and time to history vector
    addStateToHistory(currentState, lastHeartbeat);
}


//Implementasi dari fungsi printStatus()
//Mencetak status saat ini dari FSM, termasuk currentState, lastHeartbeat, delay, dan errorCount
void FSM::printStatus(){
    cout << "=========FSM Status=========" << endl;
    cout << "Current State  : " << stateToString(currentState) << endl;
    cout << "Last Heartbeat : " << lastHeartbeat << " ms" << endl;
    cout << "Delay          : " << delay << " ms" << endl;
    cout << "Error Count    : " << errorCount << endl;
    cout << "===========================" << endl;
}

//Implementasi dari fungsi printStateHistory()
//Mencetak riwayat state dari FSM, menunjukkan setiap state dan waktu saat state tersebut dari vektor stateHistory
void FSM::printStateHistory(){
    cout << "=========State History=========" << endl;
    for (const auto &entry : stateHistory){
        SystemState state = entry.fitst;
        uint32_t time = entry.second;
        cout << stateToString(state) << "at " << time << " ms" << endl;
    }
    cout << "===============================" << endl;
}
