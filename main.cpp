#include <iostream>
#include "sculptor.hpp"

using namespace std;

int main()
{ 
	Sculptor figura1(10,10,10);
	figura1.setColor(0,0,1,1);
	figura1.putVoxel(5,5,5);
	
	figura1.writeOFF((char*)"Figura1.off");

	Sculptor figura2(50,50,50);
	figura2.setColor(0,1,0.2,1);
	figura2.putVoxel(25,25,25);
	figura2.setColor(0,0,1,1);	
	figura2.putVoxel(24,25,24);
	figura2.putVoxel(26,25,24);
	figura2.setColor(1,0,0.2,1);
	figura2.putVoxel(26,25,26);
    figura2.putVoxel(24,25,26);		
	
	figura2.writeOFF((char*)"Figura2.off");	
	
	Sculptor figura3(40,40,40);
	figura3.setColor(0,1,0.2,1);	
    figura3.putBox(19,22,29,31,19,22);
    figura3.putBox(19,22,31,32,19,22);

	figura3.writeOFF((char*)"Figura3.off");
	
	
	Sculptor figura4(50,50,50);
    figura4.setColor(0.5,0.2,1,1);
    figura4.putSphere(20,20,20,10);
    
    figura4.writeOFF((char*)"Figura4.off");
    
    
    Sculptor figura5(50,50,50);
    figura5.setColor(0,1,1,1);
    figura5.putEllipsoid(15,15,15,10,10,15);
    
    figura5.writeOFF((char*)"Figura5.off");

    return 0;
}
