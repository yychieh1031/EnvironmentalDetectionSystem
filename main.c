#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<termios.h>
#include<time.h>
#include<mysql/mysql.h>

#define SERVER "localhost"
#define DB_NAME "hum"
#define DB_USRNAME "root"
#define DB_PASSWORD "raspberry"
MYSQL *db;

int main(){
    char tempbuf[10];
    char buf[256];
    struct termios tty;
    time_t mytime;
    int fd = open("/dev/ttyCM0", O_RDWR | O_NOCTTY);
    int res;
    float i, temp=0;
    db = mysql_init(NULL);
    if(!mysql_real_connect(db,SERVER,DB_USRNAME,DB_PASSWORD,DB_NAME,0,NULL,0)){
        fprintf(stderr,"%s\n",mysql_error(db));
        exit(1);
    }
    while(fd != -1){
        if(tcgetattr(fd,&tty)!=0){
            printf("Error!");
            break;
        }else{
            cfsetospeed(&tty, B9600);
            cfsetispeed(&tty, B9600);
            tty.c_cflag &= ~PARENB;
            tty.c_cflag &= ~CSTOPB;
            tty.c_cflag &= ~CSIZE;
            tty.c_cflag |= CS8;
            tty.c_cflag &= ~CRTSCTS;
            tty.c_cflag |= CLOCAL | CREAD;
            tty. |= IGNPAR | IGNCR;
            tty.c_iflag &= ~(IXON | IXOFF | IXANY);
            tty.c_lflag |= ICANON;
            tty.c_oflag &= ~OPOST;
            tcsetattr(fd, TCSANOW, &tty);
            int n = read(fd,tempbuf, 8);
            tempbuf[9] = 0;
            temp=atof(tempbuf);
            mytime = time(NULL);
            if(temp > 250){
                printf(ctime(&mytime));
                printf("Humidity: %0.2f\n",temp);
            }else{
                printf(ctime(&mytime));
                printf("Humidity: %0.2f\n",temp):
            }
            sprintf(buf,"INSERT INTO value(Hmidity) VALUES(%0.2f)",temp):
            res = mysql_query(db,buf);
        }
    }
    mysql_close(db);
    close(fd);
    return 0;
}