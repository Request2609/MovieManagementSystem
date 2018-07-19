  #include <stdio.h>  
    #include <termios.h>  
    #include <unistd.h>  
    #include <errno.h>  
    #define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)  
    //函数set_disp_mode用于控制是否开启输入回显功能  
    //如果option为0，则关闭回显，为1则打开回显  
    int set_disp_mode(int fd,int option)  
    {  
       int err;  
       struct termios term;  
       if(tcgetattr(fd,&term)==-1){  
         perror("Cannot get the attribution of the terminal");  
         return 1;  
       }  
       if(option)  
            term.c_lflag|=ECHOFLAGS;  
       else  
            term.c_lflag &=~ECHOFLAGS;  
       err=tcsetattr(fd,TCSAFLUSH,&term);  
       if(err==-1 && err==EINTR){  
            perror("Cannot set the attribution of the terminal");  
            return 1;  
       }  
       return 0;  
    }  
    //函数getpasswd用于获得用户输入的密码，并将其存储在指定的字符数组中  
    int getpasswd(char* passwd, int size)  
    {  
       int c;  
       int n = 0;  
        
       printf("\n\n\t\tPlease Input user password:");
        
       do{  
          c=getchar();  
          if ((c != '\n')||(c!='\r')){  
             passwd[n++] = c;  
          }  
       }while(c != '\n' && c !='\r' && n < (size - 1));  
       passwd[n] = '\0';  
       return n;  
    }  
