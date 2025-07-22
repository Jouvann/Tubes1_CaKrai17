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
        SystemState state = entry.first;
        uint32_t time = entry.second;
        cout << stateToString(state) << "at " << time << " ms" << endl;
    }
    cout << "===============================" << endl;
}

//Implementasi dari fungsi performInit()
//Mengatur currentState ke IDLE, mengatur delay jadi 1000ms dan mengatur lastHeartbeat ke waktu saat ini dalam milidetik.
// Mencetak "Initializing system..." dan memanggil printStatus() untuk menampilkan status awal FSM.
void FSM::performInit(){
    setDelay(1000); // Set default delay to 1000 ms
    transitionToState(SystemState::IDLE); // Transition to IDLE state

    cout << "Initializing system..." << endl;
    printStatus(); // Print the current status of the FSM
}


//Implementasi dari fungsi performProcess()
//Fungsi ini dipanggil ketika FSM berada dalam state IDLE.
//Fungsi ini menampilkan menu untuk memilih aksi yang dapat dilakukan:
// - Menampilkan status dan riwayat state (IDLE)
// - Melakukan pergerakan (MOVEMENT)
// - Melakukan penembakan (SHOOTING)
// - Melakukan perhitungan (CALCULATION)
//Pengguna diminta untuk memilih aksi dengan memasukkan angka sesuai pilihan.
void FSM::performProcess(){
    while (currentState == SystemState::IDLE){
        //Print Menu untuk memilih aksi
        cout << "============Menu============" << endl;
        cout << "Ready for commands. Choose an action:" << endl;
        cout << "1. IDLE - Display status and state history" << endl;
        cout << "2. MOVEMENT - Move the robot" << endl;
        cout << "3. SHOOTING - Shoor the robot" << endl;
        cout << "4. CALCULATION - Perform calculations" << endl;

        int choice;
        cin >> choice;
        cout << endl;

        //Pilih aksi berdasarkan input user
        switch (choice){
            case 1:
                cout << "Displaying status and state history..." << endl;
                cout << endl;
                printStatus();
                cout << endl;
                printStateHistory();
                break;
            case 2:
                cout << "Moving..." << endl;
                transitionToState(SystemState::MOVEMENT);
                break;
            case 3:
                cout << "Shooting..." << endl;
                transitionToState(SystemState::SHOOTING);
                break;
            case 4:
                cout << "Performing Calculation..." << endl;
                transitionToState(SystemState::CALCULATION);
                break;
            default: 
                cout << "Invalid choice. Staying In IDLE." << endl;
                break;; 
        }
    }
}


//Implementasi dari fungsi performMovement()
//Fungsi ini dipanggil ketika FSM berada dalam state MOVEMENT.
//Jika sudah melakukan 3 pergerakan, FSM akan beralih ke state SHOOTING.
//Jika belum, FSM akan kembali ke state IDLE.
void FSM::performMovement(){
    cout << "Moving..." << endl;
    moveCount++;

    if (moveCount >= 3){
        cout << "Move count reached 3, entering SHOOTING mode..." << endl;
        transitionToState(SystemState::SHOOTING);
    }
    else {
        cout << "Move count is " << moveCount << ", returning to IDLE state..." << endl;
        transitionToState(SystemState::IDLE);
    }
}

//Implementasi dari fungsi performShooting()
//Fungsi ini dipanggil ketika FSM berada dalam state SHOOTING.
//Mencetak "Shooting...", mengatur moveCount ke 0, dan beralih ke state IDLE.
//Juga mengupdate lastHeartbeat ke waktu saat ini dalam milidetik.
void FSM::performShooting(){
    cout << "Shooting..." << endl;
    moveCount = 0;
    transitionToState(SystemState::IDLE);
}

//Implementasi dari fungsi performCalculation()
//Fungsi ini dipanggil ketika FSM berada dalam state CALCULATION.
//Mencetak "Performing calculation..."
//Jika moveCount adalah 0, FSM akan beralih ke state ERROR.
//Jika moveCount lebih dari 0, FSM akan kembali ke state IDLE.
void FSM::performCalculation(){
    cout << "Performing calculation..." << endl;
    if (moveCount == 0){
        cout << "No movements performed, transitioning to ERROR state..." << endl;
        transitionToState(SystemState::ERROR);
    }
    else if (moveCount > 0){
        cout << "Movements performed, returning to IDLE state..." << endl;
        transitionToState(SystemState::IDLE);
    }
}

 
//Implementasi dari fungsi performErrorHandling()
//Fungsi ini dipanggil ketika FSM berada dalam state ERROR.
// Mencetak "Error occurred, performing error handling..."
//Menginkrementasi errorCount, jika errorCount melebihi 3, FSM akan beralih ke state STOPPED.
//Jika tidak, FSM akan kembali ke state IDLE.
void FSM::performErrorHandling(){
    cout << "Error occurred, performing error handling..." << endl;

    errorCount++;

    if (errorCount > 3) {
        cout << "Error count exceeded 3, transitioning to STOPPED state..." << endl;
        transitionToState(SystemState::STOPPED);
    }
    else {
        cout << "Error count is " << errorCount << ", returning to IDLE state..." << endl;
        transitionToState(SystemState::IDLE);
    }
}

