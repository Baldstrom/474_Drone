#ifndef CSE474
#define CSE474

//////////////////////////////////////////////////////////////
//                        system control                    //
//////////////////////////////////////////////////////////////
#define SC_RCGCGPIO  (*((volatile uint32_t *)0x400FE608))
#define SC_RCGCTIMER (*((volatile uint32_t *)0x400FE604))
#define SC_RCGCADC   (*((volatile uint32_t *)0x400FE638))
#define SC_RIS       (*((volatile uint32_t *)0x400FE050))
#define SC_RCC       (*((volatile uint32_t *)0x400FE060))
#define SC_RCC2      (*((volatile uint32_t *)0x400FE070))
#define SC_RCGCUART  (*((volatile uint32_t *)0x400FE618))
#define SC_PRUART    (*((volatile uint32_t *)0x400FEA18))
#define SC_GPIOF_CGC_ENABLE  0x20
#define SC_GPIOA_CGC_ENABLE  0x01
#define SC_GPIOB_CGC_ENABLE  0x02
#define SC_GPIOC_CGC_ENABLE  0x04 
#define SC_GPIOD_CGC_ENABLE  0x08
#define SC_GPIOE_CGC_ENABLE  0x10
#define SC_GPT0_CGC_ENABLE   0x01
#define SC_GPT1_CGC_ENABLE   0x02
#define SC_GPT2_CGC_ENABLE   0x04
#define SC_GPT3_CGC_ENABLE   0x08
#define SC_GPT4_CGC_ENABLE   0x10
#define SC_GPT5_CGC_ENABLE   0x20

//////////////////////////////////////////////////////////////
//                           GPIO_A                         //
//////////////////////////////////////////////////////////////
// these are apb only !! ahb uses base 0x40058000
#define GPIODIR_PA   (*((volatile uint32_t *)0x40004400))
#define GPIODEN_PA   (*((volatile uint32_t *)0x4000451C))
#define GPIODATA_PA  (*((volatile uint32_t *)0x400043FC))
#define GPIOLOCK_PA  (*((volatile uint32_t *)0x40004520))
#define GPIOCR_PA    (*((volatile uint32_t *)0x40004524))
#define GPIOPUR_PA   (*((volatile uint32_t *)0x40004510))
#define GPIOPDR_PA   (*((volatile uint32_t *)0x40004514))
#define GPIOAMSEL_PA (*((volatile uint32_t *)0x40004528))
#define GPIOPCTL_PA  (*((volatile uint32_t *)0x4000452c))
#define GPIOAFSEL_PA (*((volatile uint32_t *)0x40004420))
#define GPIODR2R_PA  (*((volatile uint32_t *)0x40004500))
#define GPIODR8R_PA  (*((volatile uint32_t *)0x40004508))
#define GPIOSLR_PA   (*((volatile uint32_t *)0x40004518))

//////////////////////////////////////////////////////////////
//                           GPIO_B                         //
//////////////////////////////////////////////////////////////
// these are apb only !! ahb uses base 0x40059000
#define GPIODIR_PB   (*((volatile uint32_t *)0x40005400))
#define GPIODEN_PB   (*((volatile uint32_t *)0x4000551C))
#define GPIODATA_PB  (*((volatile uint32_t *)0x400053FC))
#define GPIOLOCK_PB  (*((volatile uint32_t *)0x40005520))
#define GPIOCR_PB    (*((volatile uint32_t *)0x40005524))
#define GPIOPUR_PB   (*((volatile uint32_t *)0x40005510))
#define GPIOPDR_PB   (*((volatile uint32_t *)0x40005514))
#define GPIOAMSEL_PB (*((volatile uint32_t *)0x40005528))
#define GPIOPCTL_PB  (*((volatile uint32_t *)0x4000552c))
#define GPIOAFSEL_PB (*((volatile uint32_t *)0x40005420))
#define GPIODR2R_PB  (*((volatile uint32_t *)0x40005500))
#define GPIODR8R_PB  (*((volatile uint32_t *)0x40005508))
#define GPIOSLR_PB   (*((volatile uint32_t *)0x40005518))

//////////////////////////////////////////////////////////////
//                           GPIO_E                         //
//////////////////////////////////////////////////////////////
// these are apb only !! ahb uses base 0x40059000
#define GPIODIR_PE   (*((volatile uint32_t *)0x40024400))
#define GPIODEN_PE   (*((volatile uint32_t *)0x4002451C))
#define GPIODATA_PE  (*((volatile uint32_t *)0x400243FC))
#define GPIOLOCK_PE  (*((volatile uint32_t *)0x40024520))
#define GPIOCR_PE    (*((volatile uint32_t *)0x40024524))
#define GPIOPUR_PE   (*((volatile uint32_t *)0x40024510))
#define GPIOPDR_PE   (*((volatile uint32_t *)0x40024514))
#define GPIOAMSEL_PE (*((volatile uint32_t *)0x40024528))
#define GPIOPCTL_PE  (*((volatile uint32_t *)0x4002452c))
#define GPIOAFSEL_PE (*((volatile uint32_t *)0x40024420))
#define GPIODR2R_PE  (*((volatile uint32_t *)0x40024500))
#define GPIODR8R_PE  (*((volatile uint32_t *)0x40024508))
#define GPIOSLR_PE   (*((volatile uint32_t *)0x40024518))

//////////////////////////////////////////////////////////////
//                           GPIO_F                         //
//////////////////////////////////////////////////////////////
// these are apb only !! ahb uses base 0x4005D000
#define GPIODIR_PF   (*((volatile uint32_t *)0x40025400))
#define GPIODEN_PF   (*((volatile uint32_t *)0x4002551C))
#define GPIODATA_PF  (*((volatile uint32_t *)0x400253FC))
#define GPIOLOCK_PF  (*((volatile uint32_t *)0x40025520))
#define GPIOCR_PF    (*((volatile uint32_t *)0x40025524))
#define GPIOPUR_PF   (*((volatile uint32_t *)0x40025510))
#define GPIOIM_PF    (*((volatile uint32_t *)0x40025410))
#define GPIOICR_PF   (*((volatile uint32_t *)0x4002541C))
#define GPIORIS_PF   (*((volatile uint32_t *)0x40025414))
#define GPIOIEV_PF   (*((volatile uint32_t *)0x4002540c))
#define GPIOIS_PF    (*((volatile uint32_t *)0x40025404))
#define GPIOIBE_PF   (*((volatile uint32_t *)0x40025408))

//////////////////////////////////////////////////////////////
//                        GPT_0                             //
//////////////////////////////////////////////////////////////
#define GPTMCFG_0        (*((volatile uint32_t *)0x40030000))
#define GPTMTAMR_0       (*((volatile uint32_t *)0x40030004))
#define GPTMTBMR_0       (*((volatile uint32_t *)0x40030008))
#define GPTMCTL_0        (*((volatile uint32_t *)0x4003000C))
#define GPTMSYNC_0       (*((volatile uint32_t *)0x40030010))
#define GPTMIMR_0        (*((volatile uint32_t *)0x40030018))
#define GPTMRIS_0        (*((volatile uint32_t *)0x4003001C))
#define GPTMMIS_0        (*((volatile uint32_t *)0x40030020))
#define GPTMICR_0        (*((volatile uint32_t *)0x40030024))
#define GPTMTAILR_0      (*((volatile uint32_t *)0x40030028))
#define GPTMTBILR_0      (*((volatile uint32_t *)0x4003002C))
#define GPTMTAMATCHR_0   (*((volatile uint32_t *)0x40030030))
#define GPTMTBMATCHR_0   (*((volatile uint32_t *)0x40030034))
#define GPTMTAPR_0       (*((volatile uint32_t *)0x40030038))
#define GPTMTBPR_0       (*((volatile uint32_t *)0x4003003C))
#define GPTMTAPMR_0      (*((volatile uint32_t *)0x40030040))
#define GPTMTBPMR_0      (*((volatile uint32_t *)0x40030044))
#define GPTMTAR_0        (*((volatile uint32_t *)0x40030048))
#define GPTMTBR_0        (*((volatile uint32_t *)0x4003004C))
#define GPTMTAV_0        (*((volatile uint32_t *)0x40030050))
#define GPTMTBV_0        (*((volatile uint32_t *)0x40030054))

//////////////////////////////////////////////////////////////
//                        GPT_1                             //
//////////////////////////////////////////////////////////////
#define GPTMCFG_1        (*((volatile uint32_t *)0x40031000))
#define GPTMTAMR_1       (*((volatile uint32_t *)0x40031004))
#define GPTMTBMR_1       (*((volatile uint32_t *)0x40031008))
#define GPTMCTL_1        (*((volatile uint32_t *)0x4003100C))
#define GPTMSYNC_1       (*((volatile uint32_t *)0x40031010))
#define GPTMIMR_1        (*((volatile uint32_t *)0x40031018))
#define GPTMRIS_1        (*((volatile uint32_t *)0x4003101C))
#define GPTMMIS_1        (*((volatile uint32_t *)0x40031020))
#define GPTMICR_1        (*((volatile uint32_t *)0x40031024))
#define GPTMTAILR_1      (*((volatile uint32_t *)0x40031028))
#define GPTMTBILR_1      (*((volatile uint32_t *)0x4003102C))
#define GPTMTAMATCHR_1   (*((volatile uint32_t *)0x40031030))
#define GPTMTBMATCHR_1   (*((volatile uint32_t *)0x40031034))
#define GPTMTAPR_1       (*((volatile uint32_t *)0x40031038))
#define GPTMTBPR_1       (*((volatile uint32_t *)0x4003103C))
#define GPTMTAPMR_1      (*((volatile uint32_t *)0x40031040))
#define GPTMTBPMR_1      (*((volatile uint32_t *)0x40031044))
#define GPTMTAR_1        (*((volatile uint32_t *)0x40031048))
#define GPTMTBR_1        (*((volatile uint32_t *)0x4003104C))
#define GPTMTAV_1        (*((volatile uint32_t *)0x40031050))
#define GPTMTBV_1        (*((volatile uint32_t *)0x40031054))

//////////////////////////////////////////////////////////////
//                        GPT_2                             //
//////////////////////////////////////////////////////////////
#define GPTMCFG_2        (*((volatile uint32_t *)0x40032000))
#define GPTMTAMR_2       (*((volatile uint32_t *)0x40032004))
#define GPTMTBMR_2       (*((volatile uint32_t *)0x40032008))
#define GPTMCTL_2        (*((volatile uint32_t *)0x4003200C))
#define GPTMSYNC_2       (*((volatile uint32_t *)0x40032010))
#define GPTMIMR_2        (*((volatile uint32_t *)0x40032018))
#define GPTMRIS_2        (*((volatile uint32_t *)0x4003201C))
#define GPTMMIS_2        (*((volatile uint32_t *)0x40032020))
#define GPTMICR_2        (*((volatile uint32_t *)0x40032024))
#define GPTAMTAILR_2     (*((volatile uint32_t *)0x40032028))
#define GPTMTBILR_2      (*((volatile uint32_t *)0x4003202C))
#define GPTMTAMATCHR_2   (*((volatile uint32_t *)0x40032030))
#define GPTMTBMATCHR_2   (*((volatile uint32_t *)0x40032034))
#define GPTMTAPR_2       (*((volatile uint32_t *)0x40032038))
#define GPTMTBPR_2       (*((volatile uint32_t *)0x4003203C))
#define GPTMTAPMR_2      (*((volatile uint32_t *)0x40032040))
#define GPTMTBPMR_2      (*((volatile uint32_t *)0x40032044))
#define GPTMTAR_2        (*((volatile uint32_t *)0x40032048))
#define GPTMTBR_2        (*((volatile uint32_t *)0x4003204C))
#define GPTMTAV_2        (*((volatile uint32_t *)0x40032050))
#define GPTMTBV_2        (*((volatile uint32_t *)0x40032054))

//////////////////////////////////////////////////////////////
//                        GPT_3                             //
//////////////////////////////////////////////////////////////
#define GPTMCFG_3        (*((volatile uint32_t *)0x40033000))
#define GPTMTAMR_3       (*((volatile uint32_t *)0x40033004))
#define GPTMTBMR_3       (*((volatile uint32_t *)0x40033008))
#define GPTMCTL_3        (*((volatile uint32_t *)0x4003300C))
#define GPTMSYNC_3       (*((volatile uint32_t *)0x40033010))
#define GPTMIMR_3        (*((volatile uint32_t *)0x40033018))
#define GPTMRIS_3        (*((volatile uint32_t *)0x4003301C))
#define GPTMMIS_3        (*((volatile uint32_t *)0x40033020))
#define GPTMICR_3        (*((volatile uint32_t *)0x40033024))
#define GPTMTAILR_3      (*((volatile uint32_t *)0x40033028))
#define GPTMTBILR_3      (*((volatile uint32_t *)0x4003302C))
#define GPTMTAMATCHR_3   (*((volatile uint32_t *)0x40033030))
#define GPTMTBMATCHR_3   (*((volatile uint32_t *)0x40033034))
#define GPTMTAPR_3       (*((volatile uint32_t *)0x40033038))
#define GPTMTBPR_3       (*((volatile uint32_t *)0x4003303C))
#define GPTMTAPMR_3      (*((volatile uint32_t *)0x40033040))
#define GPTMTBPMR_3      (*((volatile uint32_t *)0x40033044))
#define GPTMTAR_3        (*((volatile uint32_t *)0x40033048))
#define GPTMTBR_3        (*((volatile uint32_t *)0x4003304C))
#define GPTMTAV_3        (*((volatile uint32_t *)0x40033050))
#define GPTMTBV_3        (*((volatile uint32_t *)0x40033054))

//////////////////////////////////////////////////////////////
//                       Special vaules                     //
//////////////////////////////////////////////////////////////
#define GPIOLOCK_UNLOCK 0x4C4F434B

//////////////////////////////////////////////////////////////
//                          ADC_0                           //
//////////////////////////////////////////////////////////////
#define ADCACTSS_0       (*((volatile uint32_t *)0x40038000))
#define ADCRIS_0         (*((volatile uint32_t *)0x40038004))
#define ADCIM_0          (*((volatile uint32_t *)0x40038008))
#define ADCISC_0         (*((volatile uint32_t *)0x4003800C))
#define ADCEMUX_0        (*((volatile uint32_t *)0x40038014))
#define ADCTSSEL_0       (*((volatile uint32_t *)0x4003801C))
#define ADCSPC_0         (*((volatile uint32_t *)0x40038024))
#define ADCPSSI_0        (*((volatile uint32_t *)0x40038028))
#define ADCSAC_0         (*((volatile uint32_t *)0x40038030))
#define ADCDCISC_0       (*((volatile uint32_t *)0x40038034))
#define ADCCTL_0         (*((volatile uint32_t *)0x40038038))
#define ADCCC_0          (*((volatile uint32_t *)0x40038FC8))
#define ADCSSCTL0_0      (*((volatile uint32_t *)0x40038044))
#define ADCSSCTL1_0      (*((volatile uint32_t *)0x40038064))
#define ADCSSCTL2_0      (*((volatile uint32_t *)0x40038084))
#define ADCSSCTL3_0      (*((volatile uint32_t *)0x400380A4))
#define ADCSSFIFO0_0     (*((volatile uint32_t *)0x40038048))
#define ADCSSFIFO1_0     (*((volatile uint32_t *)0x40038068))
#define ADCSSFIFO2_0     (*((volatile uint32_t *)0x40038088))
#define ADCSSFIFO3_0     (*((volatile uint32_t *)0x400380A8))

//////////////////////////////////////////////////////////////
//                          ADC_1                           //
//////////////////////////////////////////////////////////////
#define ADCACTSS_1       (*((volatile uint32_t *)0x40039000))
#define ADCRIS_1         (*((volatile uint32_t *)0x40039004))
#define ADCIM_1          (*((volatile uint32_t *)0x40039008))
#define ADCISC_1         (*((volatile uint32_t *)0x4003900C))
#define ADCEMUX_1        (*((volatile uint32_t *)0x40039014))
#define ADCTSSEL_1       (*((volatile uint32_t *)0x4003901C))
#define ADCSPC_1         (*((volatile uint32_t *)0x40039024))
#define ADCPSSI_1        (*((volatile uint32_t *)0x40039028))
#define ADCSAC_1         (*((volatile uint32_t *)0x40039030))
#define ADCDCISC_1       (*((volatile uint32_t *)0x40039034))
#define ADCCTL_1         (*((volatile uint32_t *)0x40039038))
#define ADCCC_1          (*((volatile uint32_t *)0x40039FC8))
#define ADCSSCTL0_1      (*((volatile uint32_t *)0x40039044))
#define ADCSSCTL1_1      (*((volatile uint32_t *)0x40039064))
#define ADCSSCTL2_1      (*((volatile uint32_t *)0x40039084))
#define ADCSSCTL3_1      (*((volatile uint32_t *)0x400390A4))
#define ADCSSFIFO0_1     (*((volatile uint32_t *)0x40039048))
#define ADCSSFIFO1_1     (*((volatile uint32_t *)0x40039068))
#define ADCSSFIFO2_1     (*((volatile uint32_t *)0x40039088))
#define ADCSSFIFO3_1     (*((volatile uint32_t *)0x400390A8))

//////////////////////////////////////////////////////////////
//                          p_control                       //
//////////////////////////////////////////////////////////////
#define EN0     (*((volatile uint32_t *)0xE000E100))
#define EN1     (*((volatile uint32_t *)0xE000E104))
#define EN2     (*((volatile uint32_t *)0xE000E108))
#define EN3     (*((volatile uint32_t *)0xE000E10C))

//////////////////////////////////////////////////////////////
//                          UART_0                          //
//////////////////////////////////////////////////////////////
#define UARTDR_0         (*((volatile uint32_t *)0x4000C000))
#define UARTRSR_0        (*((volatile uint32_t *)0x4000C004))
#define UARTFR_0         (*((volatile uint32_t *)0x4000C018))
#define UARTILPR_0       (*((volatile uint32_t *)0x4000C020))
#define UARTIBRD_0       (*((volatile uint32_t *)0x4000C024))
#define UARTFBRD_0       (*((volatile uint32_t *)0x4000C028))
#define UARTLCRH_0       (*((volatile uint32_t *)0x4000C02C))
#define UARTCTL_0        (*((volatile uint32_t *)0x4000C030))
#define UARTIFLS_0       (*((volatile uint32_t *)0x4000C034))
#define UARTIM_0         (*((volatile uint32_t *)0x4000C038))
#define UARTRIS_0        (*((volatile uint32_t *)0x4000C03C))
#define UARTMIS_0        (*((volatile uint32_t *)0x4000C040))
#define UARTICR_0        (*((volatile uint32_t *)0x4000C044))
#define UARTDMACTL_0     (*((volatile uint32_t *)0x4000C048))
#define UART9BITADDR_0   (*((volatile uint32_t *)0x4000C0A4))
#define UART9BITAMASK_0  (*((volatile uint32_t *)0x4000C0A8))
#define UARTPP_0         (*((volatile uint32_t *)0x4000CFC0))
#define UARTCC_0         (*((volatile uint32_t *)0x4000CFC8))

//////////////////////////////////////////////////////////////
//                          UART_1                          //
//////////////////////////////////////////////////////////////
#define UARTDR_1         (*((volatile uint32_t *)0x4000D000))
#define UARTRSR_1        (*((volatile uint32_t *)0x4000D004))
#define UARTFR_1         (*((volatile uint32_t *)0x4000D018))
#define UARTILPR_1       (*((volatile uint32_t *)0x4000D020))
#define UARTIBRD_1       (*((volatile uint32_t *)0x4000D024))
#define UARTFBRD_1       (*((volatile uint32_t *)0x4000D028))
#define UARTLCRH_1       (*((volatile uint32_t *)0x4000D02C))
#define UARTCTL_1        (*((volatile uint32_t *)0x4000D030))
#define UARTIFLS_1       (*((volatile uint32_t *)0x4000D034))
#define UARTIM_1         (*((volatile uint32_t *)0x4000D038))
#define UARTRIS_1        (*((volatile uint32_t *)0x4000D03C))
#define UARTMIS_1        (*((volatile uint32_t *)0x4000D040))
#define UARTICR_1        (*((volatile uint32_t *)0x4000D044))
#define UARTDMACTL_1     (*((volatile uint32_t *)0x4000D048))
#define UART9BITADDR_1   (*((volatile uint32_t *)0x4000D0A4))
#define UART9BITAMASK_1  (*((volatile uint32_t *)0x4000D0A8))
#define UARTPP_1         (*((volatile uint32_t *)0x4000DFC0))
#define UARTCC_1         (*((volatile uint32_t *)0x4000DFC8))

  
#endif
