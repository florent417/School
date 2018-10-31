#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>
#include <sys/ioctl.h>

int main (int argc, char* argv[])
{
  //File description
  int fd, fd_LM_75, numWr,ioctl_Ret, fd_Web, web_numWr;
  char LEDState[]="1", LM75Read[2], WebText[128];

  fd_LM_75 = open("/dev/i2c-1", O_RDONLY);
  ioctl_Ret=ioctl(fd_LM_75, 0x0703, 0x48); // i2cdev sys call (0x0703) to set I2C addr

  fd = open("/sys/class/gpio/gpio20/value", O_RDWR);

  fd_Web = open("/www/pages/index.html", O_RDWR);

  while (1)
  {

    //LED skifter tilstand hvert sekund
    /*
    if(strcmp(LEDState, "1")==0)
    {strcpy(LEDState,"0");}
    else
    {strcpy(LEDState,"1");}
    */
    read(fd_LM_75, LM75Read, 2);

    if (LM75Read[1]!=0)
      {LM75Read[1] = 5;}

    sprintf(WebText, "<html><body><h1>The temperature is %i,%i\n\r</h1></body></html>", LM75Read[0], LM75Read[1]);

    if((*LM75Read >= 30))
    {
      strcpy(LEDState,"1");
    }

    else
    {
      strcpy(LEDState,"0");
    }
    web_numWr = write(fd_Web, WebText, strlen(WebText));
    numWr = write(fd, LEDState, strlen(LEDState));

    sleep(1);
  }

  close(fd_LM_75);
  close(fd_Web);
  close(fd);

  return 0;
}
