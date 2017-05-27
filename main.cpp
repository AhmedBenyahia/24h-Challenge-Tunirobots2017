#include "mbed.h"
#include "HCSR04.h"


#define DIS_NUM 30 

 //Serial
    Serial bluetooth(PE_1,PE_0);//Tx Rx
    Serial pc(USBTX,USBRX); 
     
 //Def des object
    
//Def des pin Moteur
    //MA
    PwmOut LMF(PD_15);
    PwmOut LMB(PD_14);
    //MB
    PwmOut RMF(PD_13);
    PwmOut RMB(PD_12);
    // Enable
     
    //DigitalOut ENA(PG_13) ;
    //DigitalOut ENB(PA_14) ;
    
   

//Def des pin des capteur 
    //Eltra Sond Sonsor     
    //HCSR04 ES(PC_1, PC_2);
    
    //Scrotche Sonsor
   // AnalogIn RS_S(PB_0);
    //AnalogIn LS_S(PB_1);

    //Line Sonsor
    AnalogIn LS_L(PA_3);
    AnalogIn MS_L(PA_5);
    AnalogIn RS_L(PA_7);
    
    
    //Number Soonsor
     AnalogIn FS_N(PF_9);
     AnalogIn AS_N(PF_10);
     AnalogIn ES_N(PF_7);

//Def Autre 
    //Diode 
    DigitalOut LED(PG_14);
       
    
//Global varible 
    int ScR = 0 ;
    int ScL = 0 ;
    float RMS=0.36f ; //0.5f
    float LMS=0.5f ; //0.3f
    char c  ;
    int S_S = 200 ;
    int S_S2 = 700 ;


    
//Protytype function 
    int getSValue(AnalogIn,int);
    void Forward();
    void Back();
    void Left();
    void Right();
    void Stop();
    void Power_Right();
    void Power_Left();
        
int main (){
    
  //setup
    LED = 0 ;  
    wait(1.0f);
    //Bluetooth setup
        bluetooth.baud(9600);
        puts("Hi!");   
    
    //Partie A : Line Follower
      
  
        while(1){
            
            int N_SF = getSValue(FS_N,S_S2);
            int N_SA = getSValue(AS_N,S_S2);
            int N_SE = getSValue(ES_N,S_S2);
            
            
                
            puts("***");
            printf("%d %d %d",N_SF,N_SE,N_SA);
            wait(0.5f);
        //line Sensor : Detect line 
          int L_SM = getSValue(MS_L,S_S);
          int L_SL = getSValue(LS_L,S_S);
          int L_SR = getSValue(RS_L,S_S);
         
       
          
          
          //if(L_SL && !ScL && L_SM) ScL = 1 ;
          //else if(L_SR && !ScR && L_SM) ScR = 1 ;
          if(L_SL){  Left(); }
          else if (L_SR){  Right(); }
          else if(!L_SM && !L_SL && !L_SR) break;
          else Forward();
        
   
    wait(0.2f);
    
    }
    
    //Partie B : 
        
    
        RMS = 0.4f;
        LMS = 0.5f;
        while(1){
            c = 'S' ;
            if(bluetooth.readable())
                c = bluetooth.getc();
            printf("%c ",c);
            LED = !LED ;
            //int SR = RMS ,SL = LMS;
            switch(c){
                
                case 'S' : 
                   Stop();
                  break;
                   
                
                case 'B' : 
                    Forward();
                    puts("Back");
                    break;
                
                case 'F' :               
                    Back();
                    break;
                
                case 'L' : 
                    Left();
                   break;
                    
                case 'R' : 
                    Right();
                  break;
                
                
         
            }
            wait_us(100000);
              
           
        }
    
    
    
        
    }
    
    
    //Def des function 
    //Sensor Function
     int getSValue( AnalogIn s, int min){
        
        float meas = s.read(); // Converts and read the analog input value (value from 0.0 to 1.0)
        meas = meas * 1023; // Change the value to be in the 0 to 3300 range
        printf("|%.0f|", meas);
        
        if(meas > min)return 1;
        return 0;
    }
         
    //Motor fuction
    void Forward(){
        
        RMF = RMS ;
        RMB = 0.0f ;
        LMF = LMS ;
        LMB = 0.0f ;
                     
    }
    
    void Back(){
        
        RMF = 0.0f ;
        RMB = RMS ;
        LMF = 0.0f ;
        LMB = LMS ;
                     
    }
    
    void Left(){
        
        RMF = RMS ;
        RMB = 0.0f ;
        LMF = 0.0f ;
        LMB = 0.0f ;
        ScR = 0 ;
        ScL = 0 ;
                     
    }
    
    void Right(){
        
        RMF = 0.0f ;
        RMB = 0.0f ;
        LMF = LMS ;
        LMB = 0.0f ; 
        ScR = 0 ;
        ScL = 0 ;
                     
    }
    
    void Power_Left(){
        
        RMF = RMS ;
        RMB = 0.0f ;
        LMF = 0.0f ;
        LMB = LMS ;
        ScR = 0 ;
        ScL = 0 ;
                     
    }
    
    void Power_Right(){
        
        RMF = 0.0f ;
        RMB = RMS ;
        LMF = LMS ;
        LMB = 0.0f ; 
        ScR = 0 ;
        ScL = 0 ;
                     
    }
    
    void Stop(){
        
        RMF = 0.0f ;
        RMB = 0.0f ;
        LMF = 0.0f ;
        LMB = 0.0f ; 
        
                     
    }
    