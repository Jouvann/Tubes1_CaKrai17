#include "fsm.hpp"


//Implementasi dari fungsi millis()
//Mengembalikan waktu saat ini dalam milidetik sejak program dimulai
uint32_t millis(){
    using namespace std::chrono;
    static auto start = steady_clock::now();
    auto now = steady_clock::now();
    return duration_cast<milliseconds>(now - start).count();
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