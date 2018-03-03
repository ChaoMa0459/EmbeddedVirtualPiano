
/* Necessary includes for device drivers */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h> /* printk() */
#include <linux/slab.h> /* kmalloc() */
#include <linux/fs.h> /* everything... */
#include <linux/errno.h> /* error codes */
#include <linux/types.h> /* size_t */
#include <linux/proc_fs.h>
#include <linux/string.h>
#include <linux/fcntl.h> /* O_ACCMODE */
#include <linux/jiffies.h> /* jiffies */
#include <asm/system.h> /* cli(), *_flags */
#include <asm/uaccess.h> /* copy_from/to_user */
#include <asm/gpio.h>
#include <asm/irq.h>
#include <linux/sched.h>
#include <linux/ctype.h>
#include <asm/checksum.h>
#include <asm/io.h>
#include <asm/hardware.h>
#include <asm/arch/pxa-regs.h>
#include <linux/delay.h>
#include <linux/time.h>






MODULE_LICENSE("Dual BSD/GPL");


static int mygpio_open(struct inode *inode, struct file *filp);
static int mygpio_release(struct inode *inode, struct file *filp);
static ssize_t mygpio_read(struct file *filp, char *buf, size_t count, loff_t *f_pos);
static int mygpio_init(void);
static void mygpio_exit(void);
static void timer_1s(unsigned long data);
char name[2][128];
int touserdata;
unsigned long starttime;
unsigned long time[2];
unsigned long loadtime;
int pid[2];
char comm[2][128];
int exist[2];
int num;
char tbuf[256];
int n;
static unsigned capacity = 128;
int gameflag;
char bell[256]="3345543211233223345543211232110000000888888888";
int count10;
int count11;
int musicpos;
char touser[5];
int s100=0;


static int mygpio_major = 61;
struct file_operations mygpio_fops = {
	open: mygpio_open,
	read: mygpio_read,
	release: mygpio_release
};

module_init(mygpio_init);
module_exit(mygpio_exit);

static struct timer_list * fasync_timer;
void music(int number);


static int mygpio_init(void) {
	int result;
	count11=0;

	count10=0;
	num=1500;
	music(0);
	n=2;
	gameflag=0;
	musicpos=0;

printk(KERN_INFO "Inserting mygpio module\n");
	fasync_timer = (struct timer_list *) kmalloc(sizeof(struct timer_list), GFP_KERNEL);
	
	result = register_chrdev(mygpio_major, "mygpio", &mygpio_fops);
	if (result < 0)
	{
		printk(KERN_ALERT
			"mygpio: cannot obtain major number %d\n", mygpio_major);
		return result;
	}

gpio_direction_input(118);//i2c 2
gpio_direction_input(117);//i2c 4
gpio_direction_input(16);//i2c 5
gpio_direction_input(29);//i2c 97 3
gpio_direction_input(101);//i2c 7
gpio_direction_output(28,1);
//Set the direction of each pin
	
setup_timer(fasync_timer, timer_1s, 1);

mod_timer(fasync_timer, jiffies + msecs_to_jiffies(100));
//Set a timer works every 0.1s
	return 0;
}

static void mygpio_exit(void) {
	del_timer(fasync_timer);
	unregister_chrdev(mygpio_major, "mygpio");
	printk(KERN_ALERT "Removing mygpio module\n");

}

static int mygpio_open(struct inode *inode, struct file *filp) {
	return 0;
}

static int mygpio_release(struct inode *inode, struct file *filp) {
	return 0;
}



static ssize_t mygpio_read(struct file *filp, char *buf, 
							size_t count, loff_t *f_pos)
{ 	

	char *tbptr = tbuf;	
	tbptr += sprintf(tbptr,"%s\n", touser);

	count = strlen(tbuf)+1;

	if (copy_to_user(buf, tbuf, count))
	{
		return -EFAULT;
	}
//Send to Qt the two numbers
	if(touser[1]=='1')
	{
		music(1);
	}
	if(touser[1]=='2')
	{
		music(2);
	}
	if(touser[1]=='3')
	{
		music(3);
	}
	if(touser[1]=='4')
	{
		music(4);
	}
	if(touser[1]=='5')
	{
		music(5);
	}
//Let buzzer play music

	*f_pos += count;
	return count;
}


static void timer_1s(unsigned long data) {
	touser[1]='0';
	mod_timer(fasync_timer, jiffies + msecs_to_jiffies(100));
	if(pxa_gpio_get_value(118)==0){
		touser[1]='1';
		printk(KERN_INFO "music 1 %d\n", pxa_gpio_get_value(118));
	}
	else if(pxa_gpio_get_value(117)==0){
		touser[1]='2';
		printk(KERN_INFO "music 2 %d\n", pxa_gpio_get_value(117));
	}
	else if(pxa_gpio_get_value(16)==0){
		touser[1]='3';
		printk(KERN_INFO "music 3 %d\n", pxa_gpio_get_value(16));
	}
	else if(pxa_gpio_get_value(29)==0){
		touser[1]='4';
		printk(KERN_INFO "music 4 %d\n", pxa_gpio_get_value(29));
	}
	else if(pxa_gpio_get_value(101)==0){
		touser[1]='5';
		printk(KERN_INFO "music 5 %d\n\n", pxa_gpio_get_value(101));
	}
//Check which keyboards are pressed
	if((pxa_gpio_get_value(118)==0)&&(pxa_gpio_get_value(117)!=0)&&(pxa_gpio_get_value(16)==0)&&(pxa_gpio_get_value(17)==0)&&(pxa_gpio_get_value(101)==0)){
		gameflag=1;
	}	
//If Do Mi Fa So are pressed together, start game mode		
	if(gameflag==0)	{
		touser[0]='9';
	}
//In play mode, set the first number as 9
	if(gameflag==1)	{	
		count10++;
		if (count10==10){
//Run every second
			count10=0;
			if(bell[musicpos]=='8'){
				touser[0]='8';
				touser[1]='9';
//When the song end, prepare to send 89 to show the result on screen
				
			}else
			{
				touser[0]=bell[musicpos];
//Read the song and prepare to send it to qt
			}
			musicpos++;
//Go to the next note
			if(musicpos>54){
				gameflag=0;	
				musicpos=0;
				touser[0]='9';
				touser[1]='0';
//When the result of the game shows enough time, go to play mode 
			}		
		}
	}
}



void music(int number){	
	if (number == 1){
printk(KERN_INFO "number  %d\n",number);

	s100=0;
	while(s100<52){
		pxa_gpio_set_value(28, 0);
		udelay(1910/2);
		pxa_gpio_set_value(28, 1);
	        udelay(1910/2);
		s100++;
		}

	}
	if (number == 2){
printk(KERN_INFO "number  %d\n",number);

	s100=0;
	while(s100<58){
		pxa_gpio_set_value(28, 0);
		udelay(1702/2);
		pxa_gpio_set_value(28, 1);
	        udelay(1702/2);
		s100++;
		}

	}
	if (number == 3){
printk(KERN_INFO "number  %d\n",number);

	s100=0;
	while(s100<65){
		pxa_gpio_set_value(28, 0);
		udelay(1516/2);
		pxa_gpio_set_value(28, 1);
		udelay(1516/2);
		s100++;
	}
	}
	if (number == 4){
printk(KERN_INFO "number  %d\n",number);

	s100=0;
	while(s100<69){
		pxa_gpio_set_value(28, 0);
		udelay(1432/2);
		pxa_gpio_set_value(28, 1);
		udelay(1432/2);
		s100++;
	}
	}
	if (number == 5){
printk(KERN_INFO "number  %d\n",number);

	s100=0;
	while(s100<78){
		pxa_gpio_set_value(28, 0);
		udelay(1276/2);
		pxa_gpio_set_value(28, 1);
		udelay(1276/2);
		s100++;
	}
	}
//Play the tone 0.1 when called
}
