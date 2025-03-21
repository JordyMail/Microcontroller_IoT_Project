int one[] = {0, 1, 1, 0, 0, 0, 0, 0};
int two[] = {1, 1, 0, 1, 1, 0, 1, 0};
int three[] = {1, 1, 1, 1, 0, 0, 1, 0};
int four[] = {0, 1, 1, 0, 0, 1, 1, 0};
int five[] = {1, 0, 1, 1, 0, 1, 1, 0};
int six[] = {1, 0, 1, 1, 1, 1, 1, 0};
int seven[] = {1, 1, 1, 0, 0, 0, 0, 0};
int eight[] = {1, 1, 1, 1, 1, 1, 1, 0};
int nine[] = {1, 1, 1, 1, 0, 1, 1, 0};

void printNum(int num[]) {
 for (int i = 0; i < 8; i++) 
 digitalWrite(i+2, num[i]);
}

void setup()
{
 for (int i = 2; i < 10; i++) {
   pinMode(i, OUTPUT);
 }
}
void loop()
{
 printNum(one);
 delay(1000);
 printNum(two);
 delay(1000);
 printNum(three);
 delay(1000);
 printNum(four);
 delay(1000);
 printNum(five);
 delay(1000);
 printNum(six);
 delay(1000);
 printNum(seven);
 delay(1000);
 printNum(eight);
 delay(1000);
 printNum(nine);
 delay(1000);
}
