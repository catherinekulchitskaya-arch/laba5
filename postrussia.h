#ifndef POST_H
#define POST_H

typedef struct Parcel {
    char tracking_number[20];    
    char sender[100];           
    char recipient[100];        
    char sender_address[200];   
    char recipient_address[200]; 
    char status[50];           
    char date[20];              
    float weight;               
    float cost;                 
} Parcel;

void load_parcels(Parcel **parcels, int *count, const char *filename);
void save_parcels(Parcel *parcels, int count, const char *filename);
void print_parcels(Parcel *parcels, int count);
void add_parcel(Parcel **parcels, int *count);
void delete_parcel(Parcel **parcels, int *count);
void edit_parcel(Parcel *parcels, int count);
void search_parcels(Parcel *parcels, int count);

#endif
