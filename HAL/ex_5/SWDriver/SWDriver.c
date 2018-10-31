#include <linux/gpio.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/wait.h>
#include <linux/sched.h>

#define IRQF_TRIGGER_NONE 0x00000000
#define IRQF_TRIGGER_RISING 0x00000001
#define IRQF_TRIGGER_FALLING 0x00000002
#define IRQF_TRIGGER_HIGH 0x00000004
#define IRQF_TRIGGER_LOW 0x00000008

static DECLARE_WAIT_QUEUE_HEAD(wq);
static int flag =0;
static int irq_line;

#define SW_MAJOR 2
#define SW_MINOR 0
#define SW_NBR_MINORS 1

MODULE_LICENSE("GPL");
MODULE_AUTHOR("HALboys420");
MODULE_DESCRIPTION("Returns the status of SW2(pressed/!pressed)");

static unsigned int gpioButton = 16;
static int devno;
struct cdev gpio16_cdev;
struct file_operations SW_fops;

static irqreturn_t mygpio_16_isr(int irq, void* dev_id)
{
  printk(KERN_ALERT "Interrupt\n");
  flag =1;
  wake_up_interruptible(&wq);
  return IRQ_HANDLED;
}

static int mygpio_16_init(void)
{
  //Error handling variable
  int err;
// Request GPIO
  err = gpio_request(gpioButton, "Switch");
  if(err < 0)
    goto err_exit;
// Set GPIO direction (in or out)
  gpio_direction_input(gpioButton);
// Make device no (vælg - Enten bruger I statisk eller også
// bruger I dynamisk major/minor nummer allokering)
  devno = MKDEV(SW_MAJOR, SW_MINOR);
// Register Device
  err = register_chrdev_region(devno, SW_NBR_MINORS, "SW2");
  if(err < 0)
    goto err_free_buff;
// Cdev Init
  cdev_init(&gpio16_cdev, &SW_fops);
// Add Cdev
  err = cdev_add(&gpio16_cdev, devno, SW_NBR_MINORS);
  if(err < 0)
    goto err_dev_unregister;

  printk(KERN_ALERT "SW-Module-init\n");

  // Request and ENABLE wait_event_interruptible
  irq_line = gpio_to_irq(gpioButton);
  err=request_irq(irq_line, mygpio_16_isr, IRQF_TRIGGER_FALLING, "my_irq", NULL);
  printk(KERN_ALERT "IRQ-Line %d\n", irq_line);
  return 0;

  err_dev_unregister:
    unregister_chrdev_region(devno, SW_NBR_MINORS);
  err_free_buff:
    gpio_free(gpioButton);
  err_exit:
    return err;
}

int mygpio_16_open(struct inode *inode, struct file *filep)
{
  int major, minor;
  major = MAJOR(inode->i_rdev);
  minor = MINOR(inode->i_rdev);
  printk("Opening MyGpio Device SW2 [major], [minor]: %i, %i\n", major, minor);

  return 0;
}

ssize_t mygpio_16_read(struct file *filep, char __user *buf, size_t count, loff_t *f_pos)
{
  printk(KERN_DEBUG "process %i (%s) going to sleep\n", current->pid, current->comm);
  wait_event_interruptible(wq,flag != 0);
  flag = 0;
  printk(KERN_DEBUG "awoken %i (%s)\n", current->pid, current->comm);


  int gpio_val = gpio_get_value(gpioButton);
  char internal_buffer[50];
  sprintf(internal_buffer, "%i", gpio_val);

  int internal_buffer_len = strlen(internal_buffer) + 1;
  internal_buffer_len = internal_buffer_len > count ? count : internal_buffer_len;
  unsigned long n = copy_to_user(buf, internal_buffer, internal_buffer_len);
  n = n; // To stop warnings of unused variable.

  *f_pos += internal_buffer_len;
  return internal_buffer_len;
}

int mygpio_16_release(struct inode *inode, struct file *filep)
{
 int minor, major;

 major = MAJOR(inode->i_rdev);
 minor = MINOR(inode->i_rdev);
 printk("Closing/Releasing MyGpio SW2 Device [major], [minor]: %i, %i\n", major, minor);

 return 0;
}

static void mygpio_16_exit(void)
{
  printk(KERN_ALERT "SW-Module-release\n");

// Free irq line
  free_irq(irq_line, NULL);
// Delete Cdevl
  cdev_del(&gpio16_cdev);
// Unregister Device
  unregister_chrdev_region(devno, SW_NBR_MINORS);
// Free GPIO
  gpio_free(gpioButton);
}

struct file_operations SW_fops = {
  //.write =    SW_write,
  .owner = THIS_MODULE,
  .open =    mygpio_16_open,
  .release =  mygpio_16_release,
};

module_init(mygpio_16_init)
module_exit(mygpio_16_exit)
