#define BCM_IO_BASE           0x20000000    /* BCM2835의 I/O Peripherals physical addr*/

#define GPIO_BASE      (BCM_IO_BASE + 0x200000)
#define GPIO_SIZE                 (256)   // 0x7E2000B0 – 0x7E2000000 + 4 = 176 + 4 = 180

/* GPIO 설정 매크로 */
#define GPIO_IN(g)     (*(gpio+((g)/10)) &= ~(7<<(((g)%10)*3)))              /* 입력 설정 */
#define GPIO_OUT(g)    (*(gpio+((g)/10)) |= (1<<(((g)%10)*3)))               /* 출력 설정 */

#define GPIO_SET(g)    (*(gpio+7) = 1<<g)           /* 비트 설정 */
#define GPIO_CLR(g)    (*(gpio+10) = 1<<g)         /* 설정된 비트 해제 */
#define GPIO_GET(g)    (*(gpio+13)&(1<<g))        /* 현재 GPIO의 비트에 대한 정>보 획득 */


