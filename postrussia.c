#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "postrussia.h"

Node* create_node(PostalItem item) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }
    new_node->data = item;
    new_node->next = NULL;
    return new_node;
}

void add_to_list(Node** head, PostalItem item) {
    Node* new_node = create_node(item);
    if (new_node == NULL) return;
    
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    printf("\nЭлемент успешно добавлен!\n");
}

int delete_from_list(Node** head, const char* tracking_number) {
    if (*head == NULL) {
        printf("Список пуст!\n");
        return 0;
    }
    
    Node* current = *head;
    Node* prev = NULL;
    
    while (current != NULL) {
        if (strcmp(current->data.tracking_number, tracking_number) == 0) {
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Элемент с трек-номером %s удален.\n", tracking_number);
            return 1;
        }
        prev = current;
        current = current->next;
    }
    
    printf("Элемент с трек-номером %s не найден.\n", tracking_number);
    return 0;
}

void print_list(Node* head) {
    if (head == NULL) {
        printf("База данных пуста.\n");
        return;
    }
    
    printf("СПИСОК ПОЧТОВЫХ ОТПРАВЛЕНИЙ \n");
    Node* current = head;
    int count = 1;
    
    while (current != NULL) {
        printf("Запись №%d \n", count++);
        print_item(current->data);
        current = current->next;
    }
    printf("Всего записей: %d \n", count-1);
}

void free_list(Node** head) {
    Node* current = *head;
    Node* next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

int list_size(Node* head) {
    int count = 0;
    Node* current = head;
    
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

Node* find_by_tracking_number(Node* head, const char* tracking_number) {
    Node* current = head;
    
    while (current != NULL) {
        if (strcmp(current->data.tracking_number, tracking_number) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}


Node* find_by_status(Node* head, const char* status) {
    Node* current = head;
    Node* result = NULL;
    Node* temp;
    int found = 0;
    
    printf(" Результаты поиска по статусу '%s'\n", status);
    
    while (current != NULL) {
        if (strstr(current->data.status, status) != NULL) {
            printf("\n Найденная запись\n");
            print_item(current->data);
            found = 1;
            
            if (result == NULL) {
                temp = create_node(current->data);
                result = temp;
            } else {
                temp->next = create_node(current->data);
                temp = temp->next;
            }
        }
        current = current->next;
    }
    
    if (!found) {
        printf("Записи со статусом '%s' не найдены.\n", status);
    }
    
    return result; 
}

Node* find_by_sender(Node* head, const char* sender_name) {
    Node* current = head;
    Node* result = NULL;
    Node* temp;
    int found = 0;
    
    printf("Результаты поиска по отправителю '%s'\n", sender_name);
    
    while (current != NULL) {
        if (strstr(current->data.sender, sender_name) != NULL) {
            printf("\n Найденная запись \n");
            print_item(current->data);
            found = 1;
            
            if (result == NULL) {
                temp = create_node(current->data);
                result = temp;
            } else {
                temp->next = create_node(current->data);
                temp = temp->next;
            }
        }
        current = current->next;
    }
    
    if (!found) {
        printf("Записи от отправителя '%s' не найдены.\n", sender_name);
    }
    
    return result;
}


Node* find_by_recipient(Node* head, const char* recipient_name) {
    Node* current = head;
    Node* result = NULL;
    Node* temp;
    int found = 0;
    
    printf("Результаты поиска по получателю '%s' \n", recipient_name);
    
    while (current != NULL) {
        if (strstr(current->data.recipient, recipient_name) != NULL) {
            printf(" Найденная запись \n");
            print_item(current->data);
            found = 1;
            
            if (result == NULL) {
                temp = create_node(current->data);
                result = temp;
            } else {
                temp->next = create_node(current->data);
                temp = temp->next;
            }
        }
        current = current->next;
    }
    
    if (!found) {
        printf("Записи для получателя '%s' не найдены.\n", recipient_name);
    }
    
    return result;
}


void save_to_file(Node* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка открытия файла для записи!\n");
        return;
    }
    
    Node* current = head;
    int count = 0;
    
    while (current != NULL) {
        fprintf(file, "%s\n", current->data.tracking_number);
        fprintf(file, "%s\n", current->data.sender);
        fprintf(file, "%s\n", current->data.recipient);
        fprintf(file, "%s\n", current->data.sender_phone);
        fprintf(file, "%s\n", current->data.recipient_phone);
        fprintf(file, "%s\n", current->data.sender_email);
        fprintf(file, "%s\n", current->data.recipient_email);
        fprintf(file, "%s\n", current->data.sender_address);
        fprintf(file, "%s\n", current->data.recipient_address);
        fprintf(file, "%s\n", current->data.status);
        fprintf(file, "%s\n", current->data.date);
        fprintf(file, "%.2f\n", current->data.weight);
        fprintf(file, "%.2f\n", current->data.cost);
        fprintf(file, "---\n");
        
        current = current->next;
        count++;
    }
    
    fclose(file);
    printf("Данные сохранены в файл '%s'. Записей: %d\n", filename, count);
}


Node* load_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Файл '%s' не найден. Будет создана новая база данных.\n", filename);
        return NULL;
    }
    
    Node* head = NULL;
    PostalItem item;
    char separator[10];
    
    while (1) {
        if (fscanf(file, " %[^\n]", item.tracking_number) != 1) break;
        fscanf(file, " %[^\n]", item.sender);
        fscanf(file, " %[^\n]", item.recipient);
        fscanf(file, " %[^\n]", item.sender_phone);
        fscanf(file, " %[^\n]", item.recipient_phone);
        fscanf(file, " %[^\n]", item.sender_email);
        fscanf(file, " %[^\n]", item.recipient_email);
        fscanf(file, " %[^\n]", item.sender_address);
        fscanf(file, " %[^\n]", item.recipient_address);
        fscanf(file, " %[^\n]", item.status);
        fscanf(file, " %[^\n]", item.date);
        fscanf(file, "%f", &item.weight);
        fscanf(file, "%f", &item.cost);
        fscanf(file, " %[^\n]", separator); 
        
        add_to_list(&head, item);
    }
    
    fclose(file);
    printf("Данные загружены из файла '%s'. Загружено записей: %d\n", 
           filename, list_size(head));
    return head;
}

PostalItem create_item_interactive() {
    PostalItem item;
    
    printf("СОЗДАНИЕ НОВОЙ ЗАПИСИ \n");
    
    printf("Трек-номер (например, RA123456789RU): ");
    scanf(" %[^\n]", item.tracking_number);
    
    printf("Отправитель (ФИО): ");
    scanf(" %[^\n]", item.sender);
    
    printf("Получатель (ФИО): ");
    scanf(" %[^\n]", item.recipient);
    
    printf("Телефон отправителя: ");
    scanf(" %[^\n]", item.sender_phone);
    
    printf("Телефон получателя: ");
    scanf(" %[^\n]", item.recipient_phone);
    
    printf("Email отправителя: ");
    scanf(" %[^\n]", item.sender_email);
    
    printf("Email получателя: ");
    scanf(" %[^\n]", item.recipient_email);
    
    printf("Адрес отправителя: ");
    scanf(" %[^\n]", item.sender_address);
    
    printf("Адрес получателя: ");
    scanf(" %[^\n]", item.recipient_address);
    
    printf("Статус (На обработке/В пути/Доставлено): ");
    scanf(" %[^\n]", item.status);
    
    printf("Дата отправки (ГГГГ-ММ-ДД): ");
    scanf(" %[^\n]", item.date);
    
    printf("Вес (кг): ");
    scanf("%f", &item.weight);
    
    printf("Стоимость (руб): ");
    scanf("%f", &item.cost);
    
    return item;
}


void edit_item_interactive(PostalItem* item) {
    int choice;
    char new_value[ADDRESS_LEN];
    float new_float;
    
    do {
        printf("РЕДАКТИРОВАНИЕ ЗАПИСИ \n");
        printf("Текущие данные:\n");
        print_item(*item);
        
        printf("Выберите поле для редактирования:\n");
        printf(" 1. Отправитель\n");
        printf(" 2. Получатель\n");
        printf(" 3. Телефон отправителя\n");
        printf(" 4. Телефон получателя\n");
        printf(" 5. Email отправителя\n");
        printf(" 6. Email получателя\n");
        printf(" 7. Адрес отправителя\n");
        printf(" 8. Адрес получателя\n");
        printf(" 9. Статус\n");
        printf("10. Дата отправки\n");
        printf("11. Вес\n");
        printf("12. Стоимость\n");
        printf(" 0. Завершить редактирование\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Новое ФИО отправителя: ");
                scanf(" %[^\n]", item->sender);
                break;
            case 2:
                printf("Новое ФИО получателя: ");
                scanf(" %[^\n]", item->recipient);
                break;
            case 3:
                printf("Новый телефон отправителя: ");
                scanf(" %[^\n]", item->sender_phone);
                break;
            case 4:
                printf("Новый телефон получателя: ");
                scanf(" %[^\n]", item->recipient_phone);
                break;
            case 5:
                printf("Новый email отправителя: ");
                scanf(" %[^\n]", item->sender_email);
                break;
            case 6:
                printf("Новый email получателя: ");
                scanf(" %[^\n]", item->recipient_email);
                break;
            case 7:
                printf("Новый адрес отправителя: ");
                scanf(" %[^\n]", item->sender_address);
                break;
            case 8:
                printf("Новый адрес получателя: ");
                scanf(" %[^\n]", item->recipient_address);
                break;
            case 9:
                printf("Новый статус: ");
                scanf(" %[^\n]", item->status);
                break;
            case 10:
                printf("Новая дата отправки (ГГГГ-ММ-ДД): ");
                scanf(" %[^\n]", item->date);
                break;
            case 11:
                printf("Новый вес (кг): ");
                scanf("%f", &item->weight);
                break;
            case 12:
                printf("Новая стоимость (руб): ");
                scanf("%f", &item->cost);
                break;
            case 0:
                printf("Редактирование завершено.\n");
                break;
            default:
                printf("Неверный выбор!\n");
        }
    } while (choice != 0);
}

void print_item(PostalItem item) {
    printf("Трек-номер: %s\n", item.tracking_number);
    printf("Отправитель: %s\n", item.sender);
    printf("Получатель: %s\n", item.recipient);
    printf("Телефон отправителя: %s\n", item.sender_phone);
    printf("Телефон получателя: %s\n", item.recipient_phone);
    printf("Email отправителя: %s\n", item.sender_email);
    printf("Email получателя: %s\n", item.recipient_email);
    printf("Адрес отправителя: %s\n", item.sender_address);
    printf("Адрес получателя: %s\n", item.recipient_address);
    printf("Статус: %s\n", item.status);
    printf("Дата отправки: %s\n", item.date);
    printf("Вес: %.2f кг\n", item.weight);
    printf("Стоимость: %.2f руб\n", item.cost);
}
