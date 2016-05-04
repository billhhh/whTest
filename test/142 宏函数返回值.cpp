#include <iostream>

#define KADDR(addr) / 
({ int tmp = addr; / 
 if (addr > 5)/ 
	 tmp = 2;/ 
 else/ 
 tmp = 3;/ 
 (addr + tmp);/ 
})/ 

int main() 
 { 
	 int addr = 4; 
	 int ans; 

	 ans = KADDR(addr); 
	 printf("%d./n", ans); 
	 addr = 8; 
	 ans = KADDR(addr); 
	 printf("%d./n", ans); 

	 return 0; 
 }