#include <stdio.h>

char  names[9][30] = {
    "Lays Classic", "Kurkure Masala", "Oreo Cookies",
    "Coca-Cola",    "Pepsi",          "Sprite",
    "Nescafe Mocha", "Bru Cold Brew", "McCafe Latte"
};
float prices[9] = {20, 20, 30, 35, 35, 35, 60, 50, 70};
int   qty[9]    = {8,  6,  7,  6,  5,  2,  5,  1,  1};

#define MAX 50

int stack[MAX];
int top = -1;          

int queue[MAX];
int front = 0;
int rear = -1;       


void showMenu() 
{
    int i;
    for (i = 0; i < 9; i++) 
    {
        if (i == 0) printf("\n--- SNACKS ---\n");
        if (i == 3) printf("\n--- SOFT DRINKS ---\n");
        if (i == 6) printf("\n--- COLD COFFEES ---\n");

        printf("[%d] %-15s Rs.%.0f   ", i + 1, names[i], prices[i]);
        if (qty[i] > 0)
            printf("(%d left)\n", qty[i]);
        else
            printf("(OUT OF STOCK)\n");
    }
}

void buyItem() 
{
    int choice, i;
    float money;

    showMenu();
    printf("\nEnter item number (0 to go back): ");
    scanf("%d", &choice);

    if (choice == 0)
        return;
    if (choice < 1 || choice > 9) 
    {
        printf("Invalid item number!\n");
        return;
    }

    choice = choice - 1;     

    if (qty[choice] == 0) 
    {
        printf("This item is out of stock!\n");
        return;
    }

    printf("%s costs Rs.%.0f\n", names[choice], prices[choice]);
    printf("Insert money: ");
    scanf("%f", &money);

    if (money < prices[choice]) 
    {
        printf("Not enough money! Money returned.\n");
        return;
    }

    qty[choice] = qty[choice] - 1;

    if (top == MAX - 1) 
    {
        for (i = 0; i < MAX - 1; i++)
            stack[i] = stack[i + 1];
        top = top - 1;
    }

    top = top + 1;
    stack[top] = choice;

    printf("\nDispensing %s\n", names[choice]);
    if (money > prices[choice])
        printf("Change returned: Rs.%.2f\n", money - prices[choice]);
    printf("Thank you!\n");

    if (qty[choice] == 0 && rear < MAX - 1) 
    {
        rear = rear + 1;
        queue[rear] = choice;
        printf("(Restock request added for %s)\n", names[choice]);
    }
}


void viewStock() 
{
    int i;
    printf("\n--- STOCK ---\n");
    for (i = 0; i < 9; i++)
        printf("[%d] %-15s Quantity: %d\n", i + 1, names[i], qty[i]);
}

void restock() 
{
    int choice, add;

    viewStock();
    printf("Enter item number to restock: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > 9) {
        printf("Invalid item number!\n");
        return;
    }

    printf("How many to add? ");
    scanf("%d", &add);

    qty[choice - 1] = qty[choice - 1] + add;
    printf("Done! %s now has %d items.\n", names[choice - 1], qty[choice - 1]);
}

void undoLastSale() 
{
    int item;

    if (top == -1) 
    {
        printf("No sales to undo.\n");
        return;
    }

    item = stack[top];       
    top = top - 1;

    qty[item] = qty[item] + 1;
    printf("Last sale undone. %s added back to stock. Refund: Rs.%.0f\n",
           names[item], prices[item]);
}


void processRestock() 
{
    int item, add;

    if (front > rear)
    {
        printf("No restock requests.\n");
        return;
    }

    item = queue[front];       
    front = front + 1;

    printf("Restock request for: %s\n", names[item]);
    printf("How many to add? ");
    scanf("%d", &add);

    qty[item] = qty[item] + add;
    printf("Done! %s now has %d items.\n", names[item], qty[item]);

    if (front > rear)
    {
        front = 0;
        rear = -1;
    }
}

void adminPanel() 
{
    int choice;

    do {
        printf("\n===== ADMIN PANEL =====\n");
        printf("1. View stock\n");
        printf("2. Restock an item\n");
        printf("3. Undo last sale\n");
        printf("4. Process next restock request\n");
        printf("5. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1)
            viewStock();
        else if (choice == 2)
            restock();
        else if (choice == 3)
            undoLastSale();
        else if (choice == 4)
            processRestock();
        else if (choice != 5)
            printf("Invalid choice!\n");

    } while (choice != 5);
}

int main() 
{
    int choice;

    printf("Welcome to the Vending Machine!\n");

    do {
        printf("\n===== MAIN MENU =====\n");
        printf("1. Buy an item\n");
        printf("2. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) 
        {
            buyItem();
        }
        else if (choice == 1234)
        {
            adminPanel();
        }
        else if (choice == 2)
        {
            printf("Thank you! Goodbye!\n");
        }
        else
        {
            printf("Invalid choice!\n");
        }

    } while (choice != 2);

    return 0;
}
