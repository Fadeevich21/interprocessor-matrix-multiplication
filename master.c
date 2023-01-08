#include <stdio.h>
#include <stdlib.h>     // exit()
#include <sys/ipc.h>    // ftok()
#include <sys/msg.h>    // msgget(), msgctl()
#include <errno.h>      // errno
#include "libs/array/array.h"
#include "libs/matrix/matrix.h"
#include "libs/color_print/color_print.h"
#include "libs/messages_to_console/messages_to_console.h"
#include "libs/message/message.h"

SizeRow read_size_row() {
    printf("Введите число строк: ");
    SizeRow size_row;
    scanf("%lu", &size_row);

    return size_row;
}

SizeColumn read_size_column() {
    printf("Введите число столбцов: ");
    SizeColumn size_column;
    scanf("%lu", &size_column);

    return size_column;
}

#define COLOR_MASTER COLOR_YELLOW

#define PRINT_MASTER(format, args...)\
    PRINT_MESSAGE("MASTER", COLOR_MASTER, format "\n", ##args)

int main() {
    PRINT_DBG("Start program");

    const char* path = "/media/fadey/Fadey/Code/Code/C/Projects/OS/lab_03/tmp";
    int id = 'a';
    key_t key = ftok(path, id);
    if (key == -1) {
        PRINT_ERROR("ftok");
        exit(errno);
    }

    int handle = msgget(key, IPC_CREAT | IPC_EXCL | 0644);
    if (handle == -1) {
        PRINT_ERROR("msgget");
        exit(errno);
    }
    PRINT_DBG("Мастер открыл очередь сообщений!");

    puts("Ввод данных первой матрицы:");
    SizeRow size_row = read_size_row();
    SizeColumn size_column = read_size_column();
    Matrix matrix1 = create_matrix(size_row, size_column);
    printf("Введите числа матрицы размерностью %luX%lu:\n", matrix1.size_row, matrix1.size_column);
    read_matrix(&matrix1);

    puts("Ввод данных второй матрицы:");
    size_row = read_size_row();
    size_column = read_size_column();
    Matrix matrix2 = create_matrix(size_row, size_column);   
    printf("Введите числа матрицы размерностью %luX%lu:\n", matrix2.size_row, matrix2.size_column);
    read_matrix(&matrix2);

    if (matrix1.size_column == matrix2.size_row) {
        Matrix matrix_result = create_matrix(matrix1.size_row, matrix2.size_column);
        MasterToWorkerMsgInfo send_message;
        send_message.mType = 1;
        for (SizeRow index_row = 0; index_row < matrix_result.size_row; index_row++) {
            for (SizeColumn index_column = 0; index_column < matrix_result.size_column; index_column++) {
                send_message.info.index_row = index_row;
                send_message.info.index_column = index_column;
                send_message.info.row_array = create_array(matrix1.size_row);
                for (SizeData i = 0; i < send_message.info.row_array.size; i++)
                    send_message.info.row_array.data[i] = matrix1.data[send_message.info.index_row][i];
                send_message.info.column_array = get_array_column_matrix(matrix2, send_message.info.index_column);
                PRINT_MASTER("Send message");
                msgsnd(handle, &send_message, sizeof(MasterToWorkerActualInfo), 0);
            }
        }

        PRINT_MASTER("Получение сообщения");
        WorkerToMasterMsgInfo receive_message;
        size_t count_receive_elements = matrix_result.size_row *
                                        matrix_result.size_column;
        while (count_receive_elements != 0) {
            msgrcv(handle, &receive_message, sizeof(WorkerToMasterActualInfo), 2, 0);
            PRINT_MASTER("Я принял число от \"%s\": %d", receive_message.info.worker_name, receive_message.info.value);
            matrix_result.data[receive_message.info.index_row]
                            [receive_message.info.index_column] = 
                            receive_message.info.value;
            count_receive_elements--;
        }

        PRINT_DBG("Вывод умноженной матрицы:");
        print_matrix(matrix_result);

        delete_matrix(&matrix_result);
        PRINT_DBG("Всё прошло успешно!");
    } else {
        PRINT_ERROR("Матрицы невозможно умножить!");
    }

    delete_matrix(&matrix1);
    delete_matrix(&matrix2);
    
    if (msgctl(handle, IPC_RMID, NULL) == -1) {
        PRINT_ERROR("msgctl");
        exit(errno);
    }

    PRINT_MASTER("Я ухожу домой!");
    PRINT_DBG("Завершение программы...");

    return 0;
}