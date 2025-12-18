#ifndef POST_H
#define POST_H

#define TRACKING_LEN 20
#define NAME_LEN 100
#define EMAIL_LEN 100
#define ADDRESS_LEN 200
#define STATUS_LEN 50
#define DATE_LEN 11
#define PHONE_LEN 20

typedef struct {
    char tracking_number[TRACKING_LEN];    
    char sender[NAME_LEN];                 
    char recipient[NAME_LEN];              
    char sender_phone[PHONE_LEN];          
    char recipient_phone[PHONE_LEN];       
    char sender_email[EMAIL_LEN];          
    char recipient_email[EMAIL_LEN];       
    char sender_address[ADDRESS_LEN];      
    char recipient_address[ADDRESS_LEN];   
    char status[STATUS_LEN];               
    char date[DATE_LEN];                   
    float weight;                          
    float cost;                            
} PostalItem;

typedef struct Node {
    PostalItem data;
    struct Node* next;
} Node;

Node* create_node(PostalItem item);
void add_to_list(Node** head, PostalItem item);
int delete_from_list(Node** head, const char* tracking_number);
void print_list(Node* head);
void free_list(Node** head);
int list_size(Node* head);

Node* find_by_tracking_number(Node* head, const char* tracking_number);
Node* find_by_status(Node* head, const char* status);

void save_to_file(Node* head, const char* filename);
Node* load_from_file(const char* filename);

PostalItem create_item_interactive();
void edit_item_interactive(PostalItem* item);
void print_item(PostalItem item);

Node* find_by_sender(Node* head, const char* sender_name);
Node* find_by_recipient(Node* head, const char* recipient_name);

#endif
