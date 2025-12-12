int main() {
    Parcel *parcels = NULL;
    int count = 0;
    const char *filename = "parcels.txt";
    
    load_parcels(&parcels, &count, filename);
    
    while (1) {
        printf("\nПочта России: Система отслеживания\n");
        printf("1. Просмотреть все отправления\n");
        printf("2. Добавить новое отправление\n");
        printf("3. Отредактировать отправление\n");
        printf("4. Удалить отправление\n");
        printf("5. Поиск по номеру\n");
        printf("6. Выход\n");
        
        int choice;
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: print_parcels(parcels, count); break;
            case 2: add_parcel(&parcels, &count); break;
            case 3: edit_parcel(parcels, count); break;
            case 4: delete_parcel(&parcels, &count); break;
            case 5: search_parcels(parcels, count); break;
            case 6: 
                save_parcels(parcels, count, filename);
                free(parcels);
                return 0;
            default: printf("Неверный выбор\n");
        }
    }
    return 0;
}
