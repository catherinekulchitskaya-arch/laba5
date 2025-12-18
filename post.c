#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "postrussia.h"

#define FILENAME "postal_database.txt"

void print_menu() {
    printf("\nПОЧТА РОССИИ - СИСТЕМА УЧЕТА ОТПРАВЛЕНИЙ\n");
    printf("1. Показать все отправления\n");
    printf("2. Добавить новое отправление\n");
    printf("3. Удалить отправление по трек-номеру\n");
    printf("4. Редактировать отправление\n");
    printf("5. Поиск по трек-номеру\n");
    printf("6. Поиск по статусу\n");
    printf("7. Поиск по отправителю\n");
    printf("8. Поиск по получателю\n");
    printf("9. Сохранить изменения в файл\n");
    printf("10. Загрузить данные из файла\n");
    printf("11. Статистика\n");
    printf("0. Выход\n");
    printf("\nВыберите действие: ");
}

void search_by_tracking_number(Node* head) {
    char track[TRACKING_LEN];
    printf("\nВведите трек-номер для поиска: ");
    scanf(" %[^\n]", track);
    
    Node* found = find_by_tracking_number(head, track);
    if (found != NULL) {
        printf("\nНАЙДЕННАЯ ЗАПИСЬ\n");
        print_item(found->data);
    } else {
        printf("Отправление с трек-номером '%s' не найдено.\n", track);
    }
}

void search_by_status_menu(Node* head) {
    char status[STATUS_LEN];
    printf("\nВведите статус для поиска (На обработке/В пути/Доставлено): ");
    scanf(" %[^\n]", status);
    
    Node* results = find_by_status(head, status);
    if (results != NULL) {
        free_list(&results);
    }
}

void search_by_sender_menu(Node* head) {
    char sender[NAME_LEN];
    printf("\nВведите ФИО или часть имени отправителя: ");
    scanf(" %[^\n]", sender);
    
    Node* results = find_by_sender(head, sender);
    if (results != NULL) {
        free_list(&results);
    }
}

void search_by_recipient_menu(Node* head) {
    char recipient[NAME_LEN];
    printf("\nВведите ФИО или часть имени получателя: ");
    scanf(" %[^\n]", recipient);
    
    Node* results = find_by_recipient(head, recipient);
    if (results != NULL) {
        free_list(&results);
    }
}

void edit_item_menu(Node* head) {
    char track[TRACKING_LEN];
    printf("\nВведите трек-номер отправления для редактирования: ");
    scanf(" %[^\n]", track);
    
    Node* found = find_by_tracking_number(head, track);
    if (found != NULL) {
        edit_item_interactive(&found->data);
        printf("\nЗапись успешно обновлена.\n");
    } else {
        printf("\nОтправление с трек-номером '%s' не найдено.\n", track);
    }
}

void show_statistics(Node* head) {
    if (head == NULL) {
        printf("\nБаза данных пуста.\n");
        return;
    }
    
    int total = list_size(head);
    int in_processing = 0, in_transit = 0, delivered = 0;
    float total_weight = 0, total_cost = 0;
    
    Node* current = head;
    while (current != NULL) {
        total_weight += current->data.weight;
        total_cost += current->data.cost;
        
        if (strstr(current->data.status, "На обработке") != NULL) in_processing++;
        else if (strstr(current->data.status, "В пути") != NULL) in_transit++;
        else if (strstr(current->data.status, "Доставлено") != NULL) delivered++;
        
        current = current->next;
    }
    
    printf("\nСТАТИСТИКА\n");
    printf("Всего отправлений: %d\n", total);
    printf("На обработке: %d (%.1f%%)\n", in_processing, 
           total > 0 ? (float)in_processing/total*100 : 0);
    printf("В пути: %d (%.1f%%)\n", in_transit, 
           total > 0 ? (float)in_transit/total*100 : 0);
    printf("Доставлено: %d (%.1f%%)\n", delivered, 
           total > 0 ? (float)delivered/total*100 : 0);
    printf("Общий вес: %.2f кг\n", total_weight);
    printf("Общая стоимость: %.2f руб\n", total_cost);
    printf("Средний вес: %.2f кг\n", total > 0 ? total_weight/total : 0);
    printf("Средняя стоимость: %.2f руб\n", total > 0 ? total_cost/total : 0);
}
int main() {
    Node* head = NULL;
    int choice;
    char track[TRACKING_LEN];
    
    printf("\nЗАГРУЗКА ДАННЫХ\n");
    head = load_from_file(FILENAME);
    
    do {
        print_menu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: 
                print_list(head);
                break;
                
            case 2: 
                {
                    PostalItem new_item = create_item_interactive();
                    add_to_list(&head, new_item);
                }
                break;
                
            case 3: 
                printf("Введите трек-номер для удаления: ");
                scanf(" %[^\n]", track);
                if (delete_from_list(&head, track)) {
                    printf("Удаление выполнено.\n");
                }
                break;
                
            case 4: 
                edit_item_menu(head);
                break;
                
            case 5: 
                search_by_tracking_number(head);
                break;
                
            case 6: 
                search_by_status_menu(head);
                break;
                
            case 7: 
                search_by_sender_menu(head);
                break;
                
            case 8: 
                search_by_recipient_menu(head);
                break;
                
            case 9: 
                save_to_file(head, FILENAME);
                break;
               
            case 10: 
                free_list(&head);
                head = load_from_file(FILENAME);
                break;
                
            case 11: 
                show_statistics(head);
                break;
                
            case 0: 
                printf("\nСохранение данных перед выходом\n");
                save_to_file(head, FILENAME);
                printf("Очистка памяти\n");
                free_list(&head);
                printf("Программа завершена\n");
                break;
                
            default:
                printf("Неверный выбор! Попробуйте снова.\n");
        }
        
    } while (choice != 0);
    
    return 0;
}
