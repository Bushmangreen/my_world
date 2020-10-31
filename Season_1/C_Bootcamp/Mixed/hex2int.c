//function : hex2int
//this function will return integer value against
//hexValue - which is in string format
 
unsigned int hex2int(unsigned char hex[])
{
    unsigned int x=0;
    x=(getNum(hex[0]))*16+(getNum(hex[1]));
}
int main()
{
    unsigned char hexValue[2]="9A";
    unsigned int  intValue=0; //can be stored in unsigned char
 
    intValue=hex2int(hexValue);
     
    printf("value is: %d\n",intValue);
     
    return 0;
}


int main(){
	char* name = "Aziza";
	int age = -28 ;
	int*ptr = &age;
	char s = 's';
	
	my_printf("Hello %s! %d\n", "World", 123);
	my_printf("Hello my name is %s i am %p years old and %c\n",name,age,s);
	printf("Hello my name is %s i am %p years old and %c\n",name,ptr,s);
	return 0;
}