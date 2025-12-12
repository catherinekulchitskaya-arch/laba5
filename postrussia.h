#ifndef POST_H
#define POST_H

typedef struct Parcel {
    char tracking_number[20];    // Номер отслеживания
    char sender[100];           // Отправитель
    char recipient[100];        // Получатель
    char sender_address[200];   // Адрес отправителя
    char recipient_address[200]; // Адрес получателя
    char status[50];            // Статус отправления
    char date[20];              // Дата отправления
    float weight;               // Вес (кг)
    float cost;                 // Стоимость
} Parcel;

// Прототипы функций
void load_parcels(Parcel **parcels, int *count, const char *filename);
void save_parcels(Parcel *parcels, int count, const char *filename);
void print_parcels(Parcel *parcels, int count);
void add_parcel(Parcel **parcels, int *count);
void delete_parcel(Parcel **parcels, int *count);
void edit_parcel(Parcel *parcels, int count);
void search_parcels(Parcel *parcels, int count);

#endif
