#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pass {
  char username[50];
  char password[50];
  int date, month, year;
  char pnumber[15];
  char fname[20];
  char lname[20];
  char fathname[20];
  char mothname[20];
  char address[50];
  char typeaccount[20];
};

struct money {
  char usernameto[50];
  char userpersonfrom[50];
  long int money1;
};

void checkbalance(char username[]); // not yet implemented
void transfermoney(void);           // not yet implemented
void display(char username[]);      // not yet implemented
void login(void);
void account(void);
void accountcreated(void);
void afterlogin(void);
void logout(void);
void setPassword(struct pass *user);

int main() {
  int choice;
  printf("WELCOME TO BANK ACCOUNT SYSTEM\n\n");
  printf("1.... CREATE A BANK ACCOUNT\n");
  printf("2.... ALREADY A USER? SIGN IN\n");
  printf("3.... EXIT\n\n");
  printf("ENTER YOUR CHOICE: ");
  scanf("%d", &choice);

  switch (choice) {
  case 1:
    account();
    break;
  case 2:
    login();
    break;
  case 3:
    exit(0);
    break;
  default:
    printf("Invalid choice!\n");
  }

  return 0;
}

void account(void) {
  FILE *fp;
  struct pass user;

  fp = fopen("username.txt", "ab");
  if (fp == NULL) {
    printf("Error in opening file!\n");
    exit(1);
  }

  printf("\nFIRST NAME: ");
  scanf("%s", user.fname);
  printf("LAST NAME: ");
  scanf("%s", user.lname);
  printf("FATHER's NAME: ");
  scanf("%s", user.fathname);
  printf("MOTHER's NAME: ");
  scanf("%s", user.mothname);
  printf("ADDRESS: ");
  scanf("%s", user.address);
  printf("ACCOUNT TYPE: ");
  scanf("%s", user.typeaccount);
  printf("DATE OF BIRTH (DD MM YYYY): ");
  scanf("%d %d %d", &user.date, &user.month, &user.year);
  printf("PHONE NUMBER: ");
  scanf("%s", user.pnumber);
  printf("USERNAME: ");
  scanf("%s", user.username);

  setPassword(&user);

  fwrite(&user, sizeof(user), 1, fp);
  fclose(fp);

  accountcreated();
}

void setPassword(struct pass *user) {
  printf("Enter password: ");
  scanf("%s", user->password);
}

void accountcreated(void) {
  printf("\nAccount created successfully!\n");
  login();
}

void login(void) {
  char username[50], password[50];
  printf("\nEnter your username: ");
  scanf("%s", username);
  printf("Enter your password: ");
  scanf("%s", password);

  FILE *fp;
  struct pass user;
  fp = fopen("username.txt", "rb");
  if (fp == NULL) {
    printf("Error in opening file!\n");
    exit(1);
  }

  int found = 0;
  while (fread(&user, sizeof(user), 1, fp)) {
    if (strcmp(username, user.username) == 0 &&
        strcmp(password, user.password) == 0) {
      found = 1;
      break;
    }
  }
  fclose(fp);

  if (found) {
    printf("\nLogin successful!\n");
    afterlogin();
  } else {
    printf("\nInvalid username or password! Please try again.\n");
    login();
  }
}

void afterlogin(void) {
  printf("\nAfter login functionality is under construction...\n");
  // check balance, transfer money, etc. needs to be fixed
  // for now log out
  logout();
}

void logout(void) {
  printf("\nLogged out successfully!\n");
  main();
}

void display(char username[]) {
  FILE *fp;
  struct pass u1;

  fp = fopen("username.txt", "rb");

  if (fp == NULL) {
    printf("Error in opening file\n");
    return;
  }

  while (fread(&u1, sizeof(u1), 1, fp)) {
    if (strcmp(username, u1.username) == 0) {
      printf("WELCOME, %s %s\n", u1.fname, u1.lname);
      printf("***************************\n");
      printf("NAME: %s %s\n", u1.fname, u1.lname);
      printf("FATHER's NAME: %s %s\n", u1.fathname, u1.lname);
      printf("MOTHER's NAME: %s\n", u1.mothname);
      printf("MOBILE NUMBER: %s\n", u1.pnumber);
      printf("DATE OF BIRTH: %d-%d-%d\n", u1.date, u1.month, u1.year);
      printf("ADDRESS: %s\n", u1.address);
      printf("ACCOUNT TYPE: %s\n", u1.typeaccount);
    }
  }

  fclose(fp);
}

void transfermoney(void) {
  FILE *fp, *fm;
  struct pass u1;
  struct money m1;
  char usernamet[50], usernamep[50];

  fp = fopen("username.txt", "rb");
  fm = fopen("mon.txt", "ab");

  if (fp == NULL || fm == NULL) {
    printf("Error in opening file\n");
    return;
  }

  printf("---- TRANSFER MONEY ----\n");
  printf("========================\n");

  printf("FROM (your username): ");
  scanf("%s", usernamet);

  printf("TO (username of person): ");
  scanf("%s", usernamep);

  while (fread(&u1, sizeof(u1), 1, fp)) {
    if (strcmp(usernamep, u1.username) == 0) {
      strcpy(m1.usernameto, u1.username);
      strcpy(m1.userpersonfrom, usernamet);
    }
  }

  printf("ENTER THE AMOUNT TO BE TRANSFERRED: ");
  scanf("%ld", &m1.money1);

  fwrite(&m1, sizeof(m1), 1, fm);

  printf("Transferring amount, please wait...\n");

  for (int i = 0; i < 100000000; i++)
    ;

  printf("Amount successfully transferred.\n");

  fclose(fp);
  fclose(fm);
}

void checkbalance(char username[]) {
  FILE *fm;
  struct money m1;
  long int total_money = 0;

  fm = fopen("mon.txt", "rb");

  if (fm == NULL) {
    printf("Error in opening file\n");
    return;
  }

  printf("BALANCE DASHBOARD\n");
  printf("********************\n");
  printf("TRANSACTION ID\tAMOUNT\n");

  while (fread(&m1, sizeof(m1), 1, fm)) {
    if (strcmp(username, m1.usernameto) == 0) {

      printf("%s\t\t%ld\n", m1.userpersonfrom, m1.money1);
      total_money += m1.money1;
    }
  }

  printf("TOTAL AMOUNT: %ld\n", total_money);

  fclose(fm);
}
