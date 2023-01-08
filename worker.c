#include <stdlib.h>     // exit()
#include <sys/ipc.h>    // ftok()
#include <sys/msg.h>    // msgget(), msgctl()
#include <errno.h>      // errno
#include <string.h>     // strcpy()
#include "libs/color_print/color_print.h"
#include "libs/messages_to_console/messages_to_console.h"
#include "libs/message/message.h"
#include "libs/array/array.h"

#define COLOR_WORKER COLOR_GREEN

#define PRINT_WORKER(format, args...)\
    PRINT_MESSAGE("WORKER", COLOR_WORKER, format "\n", ##args)

int main(int args, char* argv[]) {
    if (args != 2) {
        PRINT_ERROR("Введите имя рабочего!");
        exit(1);
    }

    char* worker_name = argv[1];
    const char* path = "/media/fadey/Fadey/Code/Code/C/Projects/OS/lab_03/tmp";
    int id = 'a';
    key_t key = ftok(path, id);
    if (key == -1) {
        PRINT_ERROR("ftok");
        exit(errno);
    }

    PRINT_DBG("Рабочий создан! Ждём мастера...");
    int handle;
    while ((handle = msgget(key, IPC_EXCL | 0644)) == -1) {
        ;
    }
    PRINT_DBG("Рабочий нашёл мастера!");
    PRINT_WORKER("Лааадно, за работу!");

    while (1) {
        MasterToWorkerMsgInfo receive_message;
        PRINT_WORKER("Получение сообщения");
        msgrcv(handle, &receive_message, sizeof(MasterToWorkerActualInfo), 1, 0);
        if (errno == EIDRM) {
            PRINT_DBG("Очередь сообщений удалена!");
            break;
        }

        WorkerToMasterMsgInfo send_message;
        send_message.mType = 2;
        strcpy(send_message.info.worker_name, worker_name);
        send_message.info.index_row = receive_message.info.index_row;
        send_message.info.index_column = receive_message.info.index_column;
        Array array = multiplication_arrays(receive_message.info.row_array,
                                            receive_message.info.column_array);
        send_message.info.value = 0;
        for (SizeData i = 0; i < array.size; i++) {
            send_message.info.value += array.data[i];
        } 

        PRINT_WORKER("Отправка сообщения");
        msgsnd(handle, &send_message, sizeof(WorkerToMasterActualInfo), 0);
    }

    PRINT_DBG("Всё прошло успешно!");
    PRINT_WORKER("Я заканчиваю смену!");

    return 0;
}