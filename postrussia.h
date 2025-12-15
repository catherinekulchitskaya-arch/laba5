#ifndef POST_H
#define POST_H
#define NAME_LEN 100

typedef struct {
    char tracking_number;    
    char sender;           
    char recipient;
    char sender_number;
    char recipient_number;
    char sender_email;
    char recipient_email;
    char sender_address;   
    char recipient_address; 
    char status;           
    char date;              
    float weight;               
    float cost;                 
} PostalItem;

typedef struct Node {
    PostalItem data;
    struct Node* next;
} Node;

Node* create_node(PostalItem item);
void add_to_list(Node** head, PostalItem item);
void delete_from_list(Node** head, char tracking_number );
Node* find_by_id(Node* head, char tracking_number);
Node* find_by_status(Node* head, const char* status);
void print_list(Node* head);
void free_list(Node** head);
int list_size(Node* head);

void save_to_file(Node* head, const char* filename);
Node* load_from_file(const char* filename);

PostalItem create_item();
void edit_item(PostalItem* item);
void print_item(PostalItem item);


#endif
