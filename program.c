#include <stdio.h>
#include <stdlib.h>
#include<string.h>

// Định nghĩa cấu trúc cho một nút trong danh sách liên kết đơn
struct Node {
    char licensePlate[30];
    char time[100];
    struct Node* next;
};

// Hàm khởi tạo danh sách liên kết đơn
struct Node* createList() {
    return NULL;
}

struct Node* insertNode(struct Node* head, char licensePlate[],char time[]) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->licensePlate, licensePlate);
    strcpy(newNode->time,time);
    newNode->next = head;
    return newNode;
}


// Hàm in ra danh sách biển số xe
void printList(struct Node* head) {
    struct Node* current = head;
    int h,m,s;
    while (current != NULL) {
        printf("%s\t", current->licensePlate);
        sscanf(current->time,"%d:%d:%d",&h,&m,&s);
        printf("%d:%d:%d",h,m,s);
        current = current->next;
    }
}
int findLicensePlate(struct Node* head, char licensePlate[]) {
    struct Node* current = head;
    for(int i = 0;current!=NULL;current = current->next,i++){
        if (strcmp(current->licensePlate, licensePlate) == 0) {
            return i ;
        }
    }
    return -1; // Không tìm thấy
}
int Count(struct Node* head){
    int count = 0;
    char str[]= "xxxx";
    struct Node* current = head;
    while(current !=NULL){
        if(strncmp(current->licensePlate,str,4)!=0){
        count++;}
        current = current->next;
    }
    return count;
}
void Delete(struct Node**head,char plate[]){
    struct Node*current = *head;
    struct Node*prev = NULL;

    while(current != NULL){
        if(strcmp(current->licensePlate,plate)==0){
            if (prev == NULL){
                *head = current->next; 
            }else {
                prev ->next = current ->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}
int Bill(struct Node*head, char plate[], char billtime[]){
    char str[]="xxxx";
    int bill = 0;
    int timebill,mbill,sbill;
    sscanf(billtime,"%d:%d:%d",&timebill,&mbill,&sbill);
    struct Node*current = head;
    char time[100];
    int hour,m,s;
    sscanf(current->time,"%d:%d:%d",&hour,&m,&s);
    while(current != NULL){
        if((strcmp(current->licensePlate,plate)==0) && (strncmp(current->licensePlate,str,4)!=0)){
            if((hour >=6 &&  hour < 18) && (timebill >=6 &&  timebill < 18)) bill = 3000;
            else if((!(hour >=6) && !(timebill >=6)) || (!(hour < 18) && !(timebill < 18))) bill = 5000;
            else if((hour >=6 &&  hour < 18) || (timebill >=6 &&  timebill < 18)) bill = 8000;
            else bill = 13000;
        }else if(strcmp(current->licensePlate,plate)==0){
            if((hour >=6 &&  hour < 18) && (timebill >=6 &&  timebill < 18)) bill = 1000; //p->timebill là giờ vào và timebill là giờ ra
            else if((!(hour >=6) && !(timebill >=6)) || (!(hour < 18) && !(timebill < 18))) bill = 2000;
            else if((!(hour >=6) && (timebill >=6 &&  timebill < 18)) || ((hour >=6 &&  hour < 18) && !(timebill < 18))) bill = 3000;
            else bill = 5000;
        }
        current = current->next;
    }
    return bill;
}
int BillAll(struct Node*head,char plate[],char billtime[]){
    struct Node*current = head;
    int timebill,mbill,sbill;
    sscanf(billtime,"%d:%d:%d",&timebill,&mbill,&sbill);
    int billall = 0;
    while(current!=NULL){
        billall += Bill(current,plate,billtime);
        current = current->next;
    }
    return billall;
}


int main() {
    struct Node* myList = createList();
    char mode[100];
    int billall=0;
    char plate[30];
    char inplate[30];
    char outplate[100];
    char billplate[30];
    char outtime[30];
    char time[100];
    char intime[100];
    char searchPlate[30];
    int h,m,s;
    while(1){
        scanf("%s",time);
        if(strcmp(time, "*") == 0) break; //Điều kiện dừng vòng lặp
        else if(strcmp(time, "***") == 0) return 1; //Điều kiện dừng chương trình 
        scanf("%s", plate);
        myList = insertNode(myList,plate,time);
    }
    while(1){
        scanf("%s", mode);
        if(strcmp(mode,"list")==0){
            printList(myList);
        }
        else if(strcmp(mode,"cnt")==0){
            int count = Count(myList);
            printf("%d",count);
        }
        else if(strcmp(mode,"find")==0){
            scanf("%s",searchPlate);
            int foundNode = findLicensePlate(myList,searchPlate);
            printf("%d",foundNode);
        }
        else if(strcmp(mode,"in")==0){
            scanf("%s",intime);
            scanf("%s",inplate);
            int inNode = findLicensePlate(myList,inplate);
            if (inNode == -1){
                printf("1");
                myList = insertNode(myList,inplate,intime);
            }else{printf("0");}
        }
        else if(strcmp(mode,"out")==0){
            scanf("%s",outtime);
            scanf("%s", outplate);
            int outNode = findLicensePlate(myList,outplate);
            if(outNode != -1){
                billall += Bill(myList,outplate,outtime);
                Delete(&myList,outplate);
                printf("1");
            }else{printf("0");}
        }
        else if(strcmp(mode,"bill")==0){
            scanf("%s",outtime);
            scanf("%s",billplate);
            int billNode = findLicensePlate(myList,billplate);
            if(billNode != -1){
                int x = Bill(myList,billplate,outtime);
                printf("%d",x);
            }else{printf("-1");}
        }
        else if(strcmp(mode,"billall")==0){
            printf("%d",billall);
        }
    }
}