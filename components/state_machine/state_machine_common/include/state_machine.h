/*
 * state_mashine.h
 *
 *  Created on: Feb 17, 2024
 *      Author: vlasi
 */

#ifndef INCLUDE_SIMPLEOBJECTLIB_STATE_MACHINE_STATE_MACHINE_H_
#define INCLUDE_SIMPLEOBJECTLIB_STATE_MACHINE_STATE_MACHINE_H_

#include "esp_event.h"
#include "arrayList.h"
#include "threadable.h"

// *.h часть:
//---------------------------------------------------------------------------------------
// Укорачиваем место хранения времени и экономим память:
// переопределение интервалов до 65535 мсек
typedef unsigned long long int KaTime;

#define kaMillis() ((KaTime)esp_timer_get_time())

// Выделенные коды состояний для всех типов конечных автоматов тут:
// автомат "выключен":
#define KA_STATE_OFF -1
// нет нового состояния перехода (не изменять!)
#define KA_STATE_NO  -2

// ****************** 2. Автоматы времени, управляемые таблицей состояний(переходов) ***************** //

// Все действия автомата определяются интервалами между ними - разного рода "мигалки".
// Порядок: сначала вызывается команда, а потом(!) выдерживается указанная в строке пауза до указанной строки
//   "Выполнить текущую команду и ждать этот интервал до заданной строки"
// Нумерация состояний с 0
// Слушатель входного потока - тут встроен и занят только ожиданием завершения таймаута.
// Исполнитель команды возвращает bool - откуда брать новое состояние {stateOk|stateNo}

//typedef struct _ka_time_ctrl KaTimeControl;

// Функции - исполнители действий автоматов времени (моргалок)
// Получает структуру своего КА на всякий случай..
// Возвращает bool, выбор следующей строки по результату из колонки: nextOk или nextNo
//typedef int (*KaTimeCommand)();

// Преобразователь указателей к типу "команда автомата времени"
//#define ptrKaTimeCommand() ((KaTimeCommand)())

//This class represents the state of the state machine with a timeout.
//It stores
//	a pointer to an `object` of type `Type`,
//	a pointer to the object method `action,
//  `timeout`,
//  state: `stateOk` and `stateNo`.

template<typename Type>
class StepTimeStateMachine {

public:
	Type *object;
	int (Type::*action)(); // команда (метод) для исполнения действий состояния
	KaTime timeout; // временной интервал до(!) следующего состояния (мсек)
	int stateOk; // успешно: номер следующей команды в таблице состояний КА
	int stateNo; // ошибка: номер следующей команды в таблице состояний КА

	StepTimeStateMachine() :
			object(nullptr), action(nullptr), timeout(0), stateOk(0), stateNo(0) {

	}
	;

	StepTimeStateMachine(Type *_object, int (Type::*_action)(), KaTime _timeout,
			int _stateOk, int _stateNo) :
			object(_object), action(_action), timeout(_timeout), stateOk(
					_stateOk), stateNo(_stateNo) {
	}
	;

};

template<typename Type> class TimeStateMachine: public Threadable {

private:

	volatile bool run = false;
	TaskHandle_t handle_task_run = nullptr;

	// Принудительное изменение шага: и сразу исполняет его команду.
	void run_state(int _toStep) {

		if (table != nullptr) { // table exist

			int res = 1;                   // ??? нет команды - значит "всё ок".

			started_at = kaMillis(); // start time

			const StepTimeStateMachine<Type> &currentStep = table->get(_toStep);

			//if (_action) {

			timeout = currentStep.timeout;
			res = (currentStep.object->*currentStep.action)();
			nextState = (res == 1 ? currentStep.stateOk : currentStep.stateNo); // select next state
			//}

		}

	}
	;

public:

	TimeStateMachine() {
		this->table = nullptr;
		this->started_at = 0;      // Start time
		this->timeout = 0;         // Timeout before next step
		this->nextState = 0;      	// Next step number
	}
	;
	TimeStateMachine(
			esp_util::ArrayList<StepTimeStateMachine<Type>> *newTable) {
		this->table = newTable;
		this->started_at = 0;      // Start time
		this->timeout = 0;         // Timeout before next step
		this->nextState = 0;      	// Next step number

	}
	;

	~TimeStateMachine() {
		if (handle_task_run != nullptr) {
			vTaskDelete(handle_task_run);
		}

	}

	void setTable(esp_util::ArrayList<StepTimeStateMachine<Type>> *newTable) {
		this->table = newTable;
	}

	bool is_runing() {
		return run;
	}

	// В loop(): исполнение шага, если прошел интервал с предыдущего (его помним)
	//   Если таблица не задана - ничего не выполняет (отключение автомата)
	//   Если в таблице нет команды (==0) производит задержку до следующего выполнения, ничего не вызывает
	//   Время исполнения текущей команды входит в интервал ожидания следующей!
	void loop() {

		KaTime skippedTime = kaMillis() - started_at; // time counter

		//if ((nextState != KA_STATE_OFF) && (skippedTime >= timeout)) {
		if (skippedTime >= timeout) {
			run_state(nextState);
		}

	}
	;

	void runLoop() {

		while (true) {
			vTaskDelay(pdMS_TO_TICKS(50));
			loop();
		}

	}

	void start() {

		task_param = new TaskParams();

		task_param->task_name = "StateMachine_Blink";
		task_param->task_stack_size = 4096;
		task_param->method = [this]() {
			this->runLoop();
		};

		Threadable::run_task();
	}
	;
	void stop() {

		Threadable::stop_task();

	}
	;

	esp_util::ArrayList<StepTimeStateMachine<Type>> *table; // Table of states

	KaTime started_at = 0;      // Start time
	KaTime timeout = 0;         // Timeout before next step
	int nextState = 0;      	// Next step number

};

#endif /* INCLUDE_SIMPLEOBJECTLIB_STATE_MACHINE_STATE_MACHINE_H_ */
