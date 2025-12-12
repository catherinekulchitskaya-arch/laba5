#include "post.h"

void load_parcels(Parcel **parcels, int *count, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        *count = 0;
        return;
    }
    
    fscanf(file, "%d", count);
    *parcels = (Parcel *)malloc(*count * sizeof(Parcel));
    
    for (int i = 0; i < *count; i++) {
        fscanf(file, "%s %s %s %s %s %s %s %f %f",
               (*parcels)[i].tracking_number,
               (*parcels)[i].sender,
               (*parcels)[i].recipient,
               (*parcels)[i].sender_address,
               (*parcels)[i].recipient_address,
               (*parcels)[i].status,
               (*parcels)[i].date,
               &(*parcels)[i].weight,
               &(*parcels)[i].cost);
    }
    fclose(file);
}


