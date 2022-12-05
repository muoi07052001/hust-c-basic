#include"binarySearchTree.h"

void saveInOrder(FILE* fptr, treeType *root){
  if(*root != NULL){
    saveInOrder(fptr, &((*root)->left));
    fprintf(fptr, "%-20s%-20s%-10.2lf\n", (*root)->element.username, (*root)->element.password, (*root)->element.diem);
    saveInOrder(fptr, &((*root)->right));
  }
}

void sinhVien(elementType SV, treeType *root){
  char choice;
  FILE* fptr = fopen("sinhvien.txt", "w");
  if(fptr == NULL){
    printf("Cannot open sinhvien.txt!\n");
    return;
  }
  
  while(1){
    printf("                 ---MENU---\n"
	   "|1. Xem diem sinh vien.                 |\n"
	   "|2. Thay doi mat khau.                  |\n"
	   "|3. Ghi lai thong tin len file + thoat. |\n");

    __fpurge(stdin);
    printf("Input your choice: ");
    scanf("%c", &choice);

    while(choice > '3' || choice < '1'){
      __fpurge(stdin);
      printf("Ivalid! Input your choice: ");
      scanf("%c", &choice);
    }

    switch(choice){
    case '1':{
      printf("Diem cua ban la: %.2lf\n", search(SV.username, *root)->element.diem );
      break;
    }

    case '2':{
      char x[40];    //Mat khau cu
      char new1[40]; //Mat khau moi lan 1
      char new2[40]; //Mat khau moi lan 2
      printf("\nNhap mat khau cu: ");
      scanf("%s", x);

      if(strcmp(x, SV.password) == 0){
	__fpurge(stdin);
	printf("\nNhap mat khau moi: ");
	scanf("%s", new1);
	__fpurge(stdin);
	printf("\nNhap mat khau moi lan 2: ");
	scanf("%s", new2);

	if(strcmp(new1, new2) == 0){//Neu 2 lan trung nhau
	  strcpy(search(SV.username, *root)->element.password, new1);//Copy mat khau moi vao mat khau cu
	}
	else{
	  printf("2 lan nhap mat khau moi khong giong nhau!\n");
	}
      }
      else{
	printf("Sai mat khau cu!\n");
      }
	
      break;
    }

    case '3':{
      saveInOrder(fptr, root);

      return;
      break;
    }

    }
  }

  fclose(fptr);
}

void phuTrachLop(elementType SV, treeType *root){
  char choice;
  FILE* fptr = fopen("sinhvien.txt", "w");
  if(fptr == NULL){
    printf("Cannot open sinhvien.txt!\n");
    return;
  }
  elementType new;
  while(1){
    printf("                 ---MENU---\n"
	   "|1. Them 1 sinh vien.                   |\n"
	   "|2. In danh sach sinh vien.             |\n"
	   "|3. Xoa sinh vien.                      |\n"
	   "|4. Ghi lai thong tin len file + thoat. |\n");

    __fpurge(stdin);
    printf("Input your choice: ");
    scanf("%c", &choice);

    while(choice > '4' || choice < '1'){
      __fpurge(stdin);
      printf("Ivalid! Input your choice: ");
      scanf("%c", &choice);
    }

    switch(choice){
    case '1':{
      __fpurge(stdin);
      printf("Nhap username: ");
      scanf("%s", new.username);
      __fpurge(stdin);
      printf("Nhap password: ");
      scanf("%s", new.password);
      printf("Nhap diem: ");
      scanf("%lf", &new.diem);

      insertNode(new, &(*root));
      break;
    }

    case '2':{
      inOrderPrint(*root);
      break;
    }

    case '3':{
      elementType tmp;
      printf("Nhap username sinh vien muon xoa: ");
      scanf("%s", tmp.username);
      if(strcmp(tmp.username, "Admin") == 0){
	printf("Ban khong the xoa Admin!\n");
	return;
      }
      
      if(search(tmp.username, *root) != NULL){
	deleteNode(tmp.username, &(*root));
      }
      else{
	printf("Khong co sinh vien ban muon xoa!\n");
      }
      break;
    }

    case '4':{
      saveInOrder(fptr, root);
      return;
      break;
    }

    }
  }
  fclose(fptr);
}

void dangNhap(treeType *root, int *x){
  elementType SV;
  FILE* fptr = fopen("sinhvien.txt", "r");
  if(fptr == NULL){
    printf("Cannot open sinhvien.txt!\n");
    return;
  }
  
  if(*x == 0){ //Neu lan dau
    int count = 0;
  
    __fpurge(stdin);
    printf("Nhap username: ");
    scanf("%s", SV.username);
    __fpurge(stdin);
    printf("Nhap password: ");
    scanf("%s", SV.password);
    
    //Nhap file vao cay
    char s[100];
    elementType tmp;
    while(fscanf(fptr, "%s\t%s\t%lf\n", tmp.username, tmp.password, &tmp.diem) != EOF){
      insertNode(tmp, &(*root));
    }
    
    int c;//lua chon
    while(count < 2){
      if(search(SV.username, *root) != NULL){//Neu trung username
	if(strcmp(SV.password, search(SV.username, *root)->element.password) == 0){//Neu trung password
	  printf("Dang nhap thanh cong!\n");
	}
	else{//Neu khong trung password
	  count++;
	  printf("Sai password! Nhap lai password - sai lan %d: ", count);
	  scanf("%s", SV.password);
	}
      }
      else{//Neu khong trung username
	count++;
	printf("Khong ton tai username! Nhap lai username - sai lan %d: ", count);
	scanf("%s", SV.username);
      }
    }
    if(count == 2){
      printf("\nBan da sai 3 lan! Chuong trinh se thoat!\n");
      exit(0);
    }
    
    printf("Ban la: \n"
	   "|1. Sinh vien.     |\n"
	   "|2. Phu trach lop. |\n"
	   "|3. Thoat.         |\n");
    printf("Nhap lua chon: ");
    scanf("%d", &c);
    
    switch(c){
    case 1:{	   
      sinhVien(SV, &(*root));
      break;
    }
    case 2: {
      phuTrachLop(SV, &(*root));
      break;
    }
      
    case 3:{
      return;
    }
      
    default:{
      printf("Nhap loi! Nhap lai: ");
    }
    }
    
    
    
  }
   /*else{
    return;
    }*/
  fclose(fptr);
}

int main(){
  char choice;
  treeType root;
  int x = 0; //bien danh dau
  makeNullTree(&root);
  while(1){
    printf("    ---MENU---\n"
	   "|1. Dang nhap.  |\n"
	   "|2. Thoat.      |\n");

    __fpurge(stdin);
    printf("Input your choice: ");
    scanf("%c", &choice);

    while(choice > '2' || choice < '1'){
      __fpurge(stdin);
      printf("Ivalid! Input your choice: ");
      scanf("%c", &choice);
    }

    switch(choice){
    case '1':{
      dangNhap(&root, &x);
      break;
    }

    case '2':{
      exit(0);
      break;
    }

    }
  }
  return 0;
}
