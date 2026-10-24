#include <stdio.h>

struct Vehicle {
    char name[30];
    int vehicleNo;
    char colour[15];
};



int LinearSearch(struct Vehicle a[], int n, int elem){ 
    int i;
    for(i = 0; i < n; i++){
        if(a[i].vehicleNo == elem){
            return i;
        }
    }
    return -1;
}

int SentinelSearch(struct Vehicle a[], int n, int elem){
    struct Vehicle last = a[n-1];
    a[n-1].vehicleNo = elem;

    int i = 0;
    while(a[i].vehicleNo != elem){
        i++;
    }

    a[n-1] = last;

    if(i < n-1 || a[i].vehicleNo == elem){
        return i;
    }
    else{
        return -1;
    }
}

int BinarySearch(struct Vehicle a[], int n, int elem){
    int low = 0, high = n-1, mid;

    while(low <= high){
        mid = (low + high)/2;

        if(a[mid].vehicleNo == elem){
            return mid;
        }
        else if(a[mid].vehicleNo < elem){
            low = mid + 1;
        }
        else{
            high = mid - 1;
        }
    }
    return -1;
} 

// ================== Sorting Methods ==================

void BubbleSort(struct Vehicle a[], int n){
    int i, j, flag;
    struct Vehicle temp;

    for(i = 0; i < n; i++){
        for(j = 0; j < n-i-1; j++){
            if(a[j].vehicleNo > a[j+1].vehicleNo){
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}

void SelectionSort(struct Vehicle a[], int n){
    int i, j, min_idx;
    struct Vehicle temp;

    for(i = 0; i < n; i++){
        min_idx = i;
        for(j = i+1; j < n; j++){
            if(a[j].vehicleNo < a[min_idx].vehicleNo){
                min_idx = j;
            }
        }
        temp = a[min_idx];
        a[min_idx] = a[i];
        a[i] = temp;
    }
}

void InsertionSort(struct Vehicle a[], int n){
    int i, j;
    struct Vehicle key;

    for(i = 1; i < n; i++){
        key = a[i];
        j = i - 1;
        while(j >= 0 && a[j].vehicleNo > key.vehicleNo){
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = key;
    }
}

void ShellSort(struct Vehicle a[], int n){
    int i,j,gap;
    struct Vehicle key;

    for(gap = n/2;gap >0;gap = gap/2){ //loop should be goverened by gap size
        for(i = gap;i<n;i++){
            key = a[i];
            j = i - gap;
            while(j >= 0 && a[j].vehicleNo > key.vehicleNo){
                a[j + gap] = a[j];
                j = j - gap;  // Offest by gap and not 1 
            }
            a[j + gap] = key;
        }
    }
}

void merge(struct Vehicle array[], struct Vehicle Left[], struct Vehicle Right[], int n){   
    int Lsize = n / 2, Rsize = n - Lsize;
    int i = 0, l = 0, r = 0;

    while(l < Lsize && r < Rsize){
        if(Left[l].vehicleNo < Right[r].vehicleNo){   
            array[i] = Left[l];
            l++;
        }
        else{
            array[i] = Right[r];
            r++;
        }
        i++;
    }
    while (l < Lsize){
        array[i] = Left[l];
        l++;
        i++;
    }
    while (r < Rsize){
        array[i] = Right[r];
        r++;
        i++;
    }
}

void MergeSort(struct Vehicle a[], int n){
    int i, mid;
    if(n <= 1) return;
    mid = n / 2;

    struct Vehicle Left[mid], Right[n - mid];   

    for(i = 0; i < mid; i++) Left[i] = a[i];              
    for(i = 0; i < n - mid; i++) Right[i] = a[mid + i];

    MergeSort(Left, mid);        
    MergeSort(Right, n - mid);
    merge(a, Left, Right, n);
}

int BucketSort(struct Vehicle a[], int n){         
    int i, j, max = 0;                           
    for(i=0;i < n;i++){
        if(a[i].vehicleNo > max){                  
            max = a[i].vehicleNo;
        }
    }

    struct Vehicle bucket[max + 1];                
    int filled[max + 1];                            
    for(i=0;i <= max;i++) filled[i] = 0;

    for(i=0;i < n;i++){
        bucket[a[i].vehicleNo] = a[i];              
        filled[a[i].vehicleNo] = 1;
    }

    int k = 0;
    for(j=0;j <= max;j++){
        if(filled[j]){                             
            a[k] = bucket[j];
            k += 1;
        }
    }

    return 0;
}

int RadixSort(struct Vehicle a[],int n){          

    int i,j,max = 0;
    int digits,pass;

    for(i=0;i < n;i++){
        if(a[i].vehicleNo > max){                   
            max = a[i].vehicleNo;
        }
    }
    
    digits = 0;
    int max_copy = max; 
    while(max_copy != 0){
        max_copy = max_copy/10;
        digits = digits + 1;
    }

    int count[10],current;

    pass = 1;
    int place = 1;
    while(pass <= digits){
        for(i=0;i < 10;i++){
            count[i] = 0;
        }
        
        struct Vehicle bucket[10][n];                

        for(i=0;i < n;i++){
            current = (a[i].vehicleNo / place) % 10;  
            bucket[current][count[current]] = a[i];   
            count[current] += 1;
        }

        int k = 0;
        for(i=0;i < 10;i++){
            for(j=0;j < count[i];j++){
                a[k] = bucket[i][j];
                k += 1;
            }
        }

        place *= 10;
        pass += 1;
    }

    return 0;
} 



void printInventory(struct Vehicle a[], int n){
    printf("\n%s %s %s\n", "Name", "VehicleNo", "Colour");
    for(int i = 0; i < n; i++){
        printf("%s %d %s\n", a[i].name, a[i].vehicleNo, a[i].colour);
    }
}

// ========== MAIN ==========

int main(){
    struct Vehicle preset[30] = {
    {"MaseratiLevante",20, "Orange"},
    {"BentleyFlying",  5, "Silver"},
    {"AudiRS7",        24, "Grey"},
    {"LexusLS",        9, "Red"},
    {"RollsPhantom",   30, "White"},
    {"JaguarFPace",    28, "Yellow"},
    {"BMWX7",          12, "Black"},
    {"PorscheTaycan",  25, "Blue"},
    {"AstonRapide",    11, "White"},
    {"MercedesAMG",    23, "White"},
    {"RangeRover",     4, "Black"},
    {"BMW7Series",     1, "Red"},
    {"LexusRX",        27, "Silver"},
    {"AudiA8",         3, "White"},
    {"BentleyBentayga",16, "White"},
    {"MercedesSClass", 2, "Blue"},
    {"PorschePanamera",15, "Red"},
    {"AudiQ8",         14, "Grey"},
    {"RollsCullinan",  17, "Silver"},
    {"JaguarFType",    18, "Blue"},
    {"AstonDBX",       21, "Green"},
    {"MaseratiQP",     10, "Blue"},
    {"BentleyContinental", 29, "Red"},
    {"RollsGhost",     6, "Grey"},
    {"LexusLC",        19, "Black"},
    {"BMWi7",          22, "Red"},
    {"JaguarXJ",       8, "Orange"},
    {"RangeVelar",     26, "Black"},
    {"MercedesGLS",    13, "Yellow"},
    {"PorscheCayenne", 7, "Green"}
    };

    struct Vehicle inventory[30];
    int n, choice1, choice, key, dataChoice, found;

    printf("Choose dataset option:\n");
    printf("1. Use preset dataset (30 vehicles)\n");
    printf("2. Enter your own data\n");
    printf("Enter choice: ");
    scanf("%d", &dataChoice);

    if(dataChoice == 1){
        for(int i = 0; i < 30; i++){
            inventory[i] = preset[i];
        }
        n = 30;
        printf("\nPreset dataset loaded.\n");
        printInventory(inventory, n);
    }
    else{
        printf("Enter number of vehicles (max 30): ");
        scanf("%d", &n);

        for(int i = 0; i < n; i++){
            printf("\nVehicle %d\n", i+1);
            printf("Name: ");
            scanf("%s", inventory[i].name);
            printf("Vehicle No (integer): ");
            scanf("%d", &inventory[i].vehicleNo);
            printf("Colour: ");
            scanf("%s", inventory[i].colour);
        }
    }

    printf("\nWhat would you like to do?\n");
    printf("1. Search\n2. Sort\n");
    printf("Enter choice: ");
    scanf("%d", &choice1);

    switch(choice1){
        case 1:
            printf("\nEnter vehicle number to search: ");
            scanf("%d", &key);

            printf("\nChoose search method:\n");
            printf("1. Linear Search\n2. Sentinel Search\n3. Binary Search\n");
            printf("Enter choice: ");
            scanf("%d", &choice);

            if(choice == 3){
                BubbleSort(inventory, n);   // required for binary search
            }

            switch(choice){
                case 1:
                    found = LinearSearch(inventory, n, key);
                    if(found == -1)
                        printf("Not found in the dataset\n");
                    else
                        printf("Found: %s | %d | %s (at position %d)\n",
                            inventory[found].name, inventory[found].vehicleNo, inventory[found].colour, found+1);
                    break;
                case 2:
                    found = SentinelSearch(inventory, n, key);
                    if(found == -1)
                        printf("Not foudn in dataset");
                    else
                        printf("Found: %s | %d | %s (at position %d)\n",
                            inventory[found].name, inventory[found].vehicleNo, inventory[found].colour, found+1);
                    break;
                case 3:
                    found = BinarySearch(inventory, n, key);
                    if(found == -1)
                        printf("Not found in dataset");
                    else
                        printf("Found: %s | %d | %s (at position %d)\n",
                            inventory[found].name, inventory[found].vehicleNo, inventory[found].colour, found+1);
                    break;
                default:
                    printf("Invalid choice\n");
            }
            break;

        case 2:
            printf("\nChoose sorting method:\n");
            printf("1. Bubble Sort\n2.Selection Sort\n3.Insertion Sort\n4.Shell Sort\n5.Merge Sort\n6.Bucket Sort\n7.Radix Sort\n");  
            printf("Enter choice: ");
            scanf("%d", &choice);

            switch(choice){
                case 1:
                    BubbleSort(inventory, n);
                    printf("\nSorted by vehicle number:\n");
                    printInventory(inventory, n);
                    break;
                case 2:
                    SelectionSort(inventory, n);
                    printf("\nSorted by vehicle number:\n");
                    printInventory(inventory, n);
                    break;
                case 3:
                    InsertionSort(inventory, n);
                    printf("\nSorted by vehicle number:\n");
                    printInventory(inventory, n);
                    break;
                case 4:                                         
                    ShellSort(inventory, n);
                    printf("\nSorted by vehicle number:\n");
                    printInventory(inventory, n);
                    break;
                case 5:                                          
                    MergeSort(inventory, n);
                    printf("\nSorted by vehicle number:\n");
                    printInventory(inventory, n);
                    break;
                case 6:                                          
                    BucketSort(inventory, n);
                    printf("\nSorted by vehicle number:\n");
                    printInventory(inventory, n);
                    break;
                case 7:                                          
                    RadixSort(inventory, n);
                    printf("\nSorted by vehicle number:\n");
                    printInventory(inventory, n);
                    break;
                default:
                    printf("Invalid choice\n");
            }
            break;

        default:
            printf("Invalid choice\n");
    }

    return 0;
}